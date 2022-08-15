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
#include <map>
#include <string>

#define LOG_TAG "android.hardware.radio"
#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include <qrild_msg.h>
#include <qmi_nas.h>
#include <util.h>
#include <list.h>
#include <q_log.h>

#include "timespec.h"
#include "qrild.h"
#include "qrild_android_interface.h"
#include "qrild_radio.hh"

static std::vector<std::shared_ptr<IHandlesQmiIndications> > services_list;
RadioServices services;

void buildResponseInfo(
      RadioResponseInfo &info, int serial, RadioResponseType responseType, RadioError e) {
    info.serial = serial;
    info.type = responseType;
    info.error = e;

    return;
}

enum RadioTechnology QmiNasRadioInterfaceToRadioTechnology(int radio_interface) {
    switch (radio_interface) {
    case QMI_NAS_RADIO_INTERFACE_GSM:
        return RadioTechnology::GSM;
    case QMI_NAS_RADIO_INTERFACE_CDMA_1X:
        return RadioTechnology::ONE_X_RTT;
    case QMI_NAS_RADIO_INTERFACE_CDMA_1XEVDO:
        return RadioTechnology::EHRPD; // nooo idea if this is right
    case QMI_NAS_RADIO_INTERFACE_UMTS:
        return RadioTechnology::UMTS;
    case QMI_NAS_RADIO_INTERFACE_LTE:
        return RadioTechnology::LTE;
    case QMI_NAS_RADIO_INTERFACE_TD_SCDMA:
        return RadioTechnology::TD_SCDMA;
    case QMI_NAS_RADIO_INTERFACE_5GNR: // I can dream ;)
        return RadioTechnology::NR;
    case QMI_NAS_RADIO_INTERFACE_AMPS: // What is AMPS ???
    case QMI_NAS_RADIO_INTERFACE_NONE:
    case QMI_NAS_RADIO_INTERFACE_UNKNOWN:
    default:
        return RadioTechnology::UNKNOWN;
    }
}

int QmiUimPhysicalCardStateToCardState(int physical_card_state) {
    switch (physical_card_state) {
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
    binder_status_t status =
          AServiceManager_addService(ser->asBinder().get(), instanceName.c_str());
    CHECK_EQ(status, STATUS_OK);
    return ser;
}

void *qrild_event_loop(void *data) {
    int rc;
    struct timespec ts;
    // This thread will handle pending events every 500ms

    while (true) {
        ts = timespec_from_ms(500);
        do {
            rc = nanosleep(&ts, &ts);
        } while (rc && errno == EINTR);
    }

    return NULL;
}

void *qmi_indications_loop(void *arg) {
    struct rild_state *state = (struct rild_state *)arg;
    while (!state->exit) {
        /* Wait for a new indication, call each service to let them process it */
        q_thread_mutex_lock(&state->msg_mutex);
        q_thread_cond_wait(&state->pending_indications, &state->msg_mutex);
        q_thread_mutex_unlock(&state->msg_mutex);
        for (auto svc : services_list) {
            svc->_handleQmiIndications();
        }

        q_thread_mutex_lock(&state->msg_mutex);
        /* Free all indications */
        struct qrild_msg *msg;
        // FIXME: Should use list_for_each_entry_safe
        // To avoid the silly extra loop here.
        auto to_free = std::vector<struct qrild_msg *>();
        list_for_each_entry(msg, &state->pending_rx, li) {
            if (msg->type == 0x4)
                to_free.push_back(msg);
        }

        for (auto m : to_free)
            qrild_msg_free_locked(m);
        q_thread_mutex_unlock(&state->msg_mutex);
    }

    return NULL;
}

extern "C" void qrild_android_main(struct rild_state *qril_state) {
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    pthread_t qmi_indications_thread;

    services.initialised = false;
    services_list = std::vector<std::shared_ptr<IHandlesQmiIndications> >();

    std::shared_ptr<RadioConfig> radioConfig = addService<RadioConfig>("/default", qril_state);
    services_list.push_back(radioConfig);
    services.config = radioConfig;
    // Need to understand why hwservicemanager wants /slot1 here and what that means for
    // dual-sim devices.
    std::shared_ptr<RadioData> radioData = addService<RadioData>("/slot1", qril_state);
    services_list.push_back(radioData);
    services.data = radioData;
    std::shared_ptr<RadioMessaging> radioMessaging =
          addService<RadioMessaging>("/slot1", qril_state);
    services_list.push_back(radioMessaging);
    services.messaging = radioMessaging;
    std::shared_ptr<RadioModem> radioModem = addService<RadioModem>("/slot1", qril_state);
    services_list.push_back(radioModem);
    services.modem = radioModem;
    std::shared_ptr<RadioNetwork> radioNetwork = addService<RadioNetwork>("/slot1", qril_state);
    services_list.push_back(radioNetwork);
    services.network = radioNetwork;
    std::shared_ptr<RadioSim> radioSim = addService<RadioSim>("/slot1", qril_state);
    services_list.push_back(radioSim);
    services.sim = radioSim;
    std::shared_ptr<RadioVoice> radioVoice = addService<RadioVoice>("/slot1", qril_state);
    services_list.push_back(radioVoice);
    services.voice = radioVoice;

    services.initialised = true;

    pthread_create(&qmi_indications_thread, NULL, qmi_indications_loop, qril_state);

    ABinderProcess_joinThreadPool();
    LOG(ERROR) << "Should not be here!";
    qril_state->exit = true;
}
