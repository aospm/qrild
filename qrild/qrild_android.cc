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

#include <memory>
#include <string>

#define LOG_TAG "android.hardware.radio"
#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include "qrild_android.h"
#include "qrild_radio.hh"

template <typename T, class... Args>
std::shared_ptr<T> addService(Args&&... args) {
    std::shared_ptr<T> ser = ndk::SharedRefBase::make<T>(std::forward<Args>(args)...);
    auto instanceName = std::string(T::descriptor) + "/default";
    LOG(INFO) << "adding qrild service instance: " << instanceName;
    binder_status_t status =
            AServiceManager_addService(ser->asBinder().get(), instanceName.c_str());
    CHECK_EQ(status, STATUS_OK);
    return ser;
}

void qrild_android_main(struct qrild_state *state)
{
	ABinderProcess_setThreadPoolMaxThreadCount(0);
	std::string instance;
	std::shared_ptr<RadioConfig> radioConfig = addService<RadioConfig>(state);
	std::shared_ptr<RadioData> radioData = addService<RadioData>(state);
	std::shared_ptr<RadioModem> radioModem = addService<RadioModem>(state);
	std::shared_ptr<RadioNetwork> radioNetwork = addService<RadioNetwork>(state);
	std::shared_ptr<RadioSim> radioSim = addService<RadioSim>(state);

	ABinderProcess_joinThreadPool();
	LOG(ERROR) << "Should not be here!";
}
