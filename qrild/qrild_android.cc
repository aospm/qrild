/*
 * Copyright (C) 2022, Linaro Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <pthread.h>

#include <memory>
#include <string>

#define LOG_TAG "android.hardware.radio"
#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include "qrild_android_interface.h"
#include "qrild_radio.hh"
#include "qrild_msg.h"
#include <list.h>

// FIXME: ehhh global or not pick one?!
static struct rild_state *state;
static std::vector<std::shared_ptr<IHandlesQmiIndications>> services;

void buildResponseInfo(RadioResponseInfo &info, int serial, RadioResponseType responseType, RadioError e) {
    info.serial = serial;
    info.type = responseType;
    info.error = e;

    return;
}

int QmiUimPhysicalCardStateToCardState(int physical_card_state)
{
    switch(physical_card_state) {
    case QMI_UIM_PHYSICAL_CARD_STATE_ABSENT:
        return sim::CardStatus::STATE_ABSENT;
    case QMI_UIM_PHYSICAL_CARD_STATE_PRESENT:
        return sim::CardStatus::STATE_PRESENT;
    case QMI_UIM_PHYSICAL_CARD_STATE_UNKNOWN:
    default:
        return sim::CardStatus::STATE_ERROR;
    }
}

template <typename T> std::shared_ptr<T> addService(std::string type, struct rild_state *state) {
    std::shared_ptr<T> ser = ndk::SharedRefBase::make<T>(state);
    auto instanceName = std::string(T::descriptor) + type;
    LOG(INFO) << "adding qrild service instance: " << instanceName;
    binder_status_t status = AServiceManager_addService(ser->asBinder().get(), instanceName.c_str());
    CHECK_EQ(status, STATUS_OK);
    return ser;
}

void *qmi_indications_loop(void *service)
{
    while (!state->exit) {
        pthread_mutex_lock(&state->msg_mutex);
        pthread_cond_wait(&state->pending_indications, &state->msg_mutex);
        for(auto svc : services) {
            svc->handleQmiIndications();
        }
        struct qrild_msg *msg;
        auto to_free = std::vector<struct qrild_msg*>();
        list_for_each_entry(msg, &state->pending_rx, li) {
            if (msg->type == 0x4)
                to_free.push_back(msg);
        }
        for(auto m : to_free)
            qrild_msg_free_locked(m);
        pthread_mutex_unlock(&state->msg_mutex);
    }

    return NULL;
}

void qrild_android_main(struct rild_state *qril_state) {
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    pthread_t qmi_indications_thread;

    state = qril_state;
    services = std::vector<std::shared_ptr<IHandlesQmiIndications>>();

    std::shared_ptr<RadioConfig> radioConfig = addService<RadioConfig>("/default", state);
    services.push_back(radioConfig);
    // Need to understand why hwservicemanager wants /slot1 here and what that means for
    // dual-sim devices.
    std::shared_ptr<RadioMessaging> radioMessaging = addService<RadioMessaging>("/slot1", state);
    services.push_back(radioMessaging);
    std::shared_ptr<RadioModem> radioModem = addService<RadioModem>("/slot1", state);
    services.push_back(radioModem);
    std::shared_ptr<RadioData> radioData = addService<RadioData>("/slot1", state);
    services.push_back(radioData);
    std::shared_ptr<RadioNetwork> radioNetwork = addService<RadioNetwork>("/slot1", state);
    services.push_back(radioNetwork);
    std::shared_ptr<RadioSim> radioSim = addService<RadioSim>("/slot1", state);
    services.push_back(radioSim);
    std::shared_ptr<RadioVoice> radioVoice = addService<RadioVoice>("/slot1", state);
    services.push_back(radioVoice);

    pthread_create(&qmi_indications_thread, NULL, qmi_indications_loop, NULL);

    ABinderProcess_joinThreadPool();
    LOG(ERROR) << "Should not be here!";
    state->exit = true;
}
