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

#define LOG_TAG "android.hardware.radio.IModem"
#include <android-base/logging.h>

#include <qrild.h>

#include <qrild_qmi.h>
#include <qmi_dms.h>

#include "qrild_radio.hh"

RadioModem::RadioModem(struct rild_state *state) : mState(state) {
    printf("xRadioModem::%s\n", __func__);

    LOG(INFO) << "Powering on modem...";
    qrild_qmi_powerup(mState);
}

ndk::ScopedAStatus RadioModem::enableModem(int32_t in_serial, bool in_on) {
    printf("RadioModem::%s\n", __func__);

    LOG(INFO) << (in_on ? "en" : "dis") << "abling modem";

    mRep->enableModemResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getBasebandVersion(int32_t in_serial) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getDeviceIdentity(int32_t in_serial) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getHardwareConfig(int32_t in_serial) {
    printf("xRadioModem::%s\n", __func__);
    uint8_t operating_mode;
    auto hw_config = std::vector<modem::HardwareConfig>();
    auto modem = modem::HardwareConfig();
    auto modemConfig = modem::HardwareConfigModem();
    auto sim1 = modem::HardwareConfig();
    auto sim2 = modem::HardwareConfig();
    auto simConfig = modem::HardwareConfigSim();
    modem.type = modem::HardwareConfig::TYPE_MODEM;
    modem.uuid = "a-real-modem-i-promise";
    modem.state = modem::HardwareConfig::STATE_DISABLED;

    operating_mode = qrild_qmi_dms_get_operating_mode(mState);
    switch(operating_mode) {
    case QMI_DMS_OPERATING_MODE_ONLINE:
        modem.state = modem::HardwareConfig::STATE_ENABLED;
        break;
    case QMI_DMS_OPERATING_MODE_LOW_POWER:
        modem.state = modem::HardwareConfig::STATE_STANDBY;
        break;
    case QMI_DMS_OPERATING_MODE_OFFLINE:
    default:
        modem.state = modem::HardwareConfig::STATE_DISABLED;
        break;
    }

    modemConfig.rilModel = 0;
    // hmmm
    modemConfig.rat = RadioTechnology::LTE;
    modemConfig.maxVoiceCalls = 0;
    modemConfig.maxDataCalls = 1;
    modemConfig.maxStandby = 1;

    LOG(INFO) << modemConfig.toString();

    modem.modem = std::vector<modem::HardwareConfigModem>();
    modem.modem.push_back(modemConfig);
    hw_config.push_back(modem);

    sim1.type = modem::HardwareConfig::TYPE_SIM;
    sim1.uuid = "totally-a-real-sim-card";
    // Can I hardcode this??
    sim1.state = modem::HardwareConfig::STATE_ENABLED;
    simConfig.modemUuid = modem.uuid;

    sim1.sim = std::vector<modem::HardwareConfigSim>();
    sim1.sim.push_back(simConfig);

    sim2.type = modem::HardwareConfig::TYPE_SIM;
    sim2.uuid = "another-totally-a-real-sim-card";
    // Can I hardcode this??
    sim2.state = modem::HardwareConfig::STATE_ENABLED;
    simConfig.modemUuid = modem.uuid;

    sim2.sim = std::vector<modem::HardwareConfigSim>();
    sim2.sim.push_back(simConfig);
    hw_config.push_back(sim1);
    hw_config.push_back(sim2);

    mRep->getHardwareConfigResponse(RESP_OK(in_serial), hw_config);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getModemActivityInfo(int32_t in_serial) {
    printf("xRadioModem::%s\n", __func__);
    auto activity = modem::ActivityStatsInfo();
    auto techSpecific = modem::ActivityStatsTechSpecificInfo();

    activity.sleepModeTimeMs = 0;
    activity.idleModeTimeMs = 0;

    activity.techSpecificInfo = std::vector<modem::ActivityStatsTechSpecificInfo>();
    activity.techSpecificInfo.push_back(techSpecific);

    LOG(INFO) << activity.toString();

    mRep->getModemActivityInfoResponse(RESP_OK(in_serial), activity);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getModemStackStatus(int32_t in_serial) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getRadioCapability(int32_t in_serial) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::nvReadItem(int32_t in_serial, modem::NvItem in_itemId) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::nvResetConfig(int32_t in_serial, modem::ResetNvType in_resetType) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::nvWriteCdmaPrl(int32_t in_serial, const std::vector<uint8_t> &in_prl) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::nvWriteItem(int32_t in_serial, const modem::NvWriteItem &in_item) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::requestShutdown(int32_t in_serial) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::responseAcknowledgement() {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
};
ndk::ScopedAStatus RadioModem::sendDeviceState(
      int32_t in_serial, modem::DeviceStateType in_deviceStateType, bool in_state) {
    printf("xRadioModem::%s\n", __func__);

    LOG(INFO) << "Got device state: " << modem::toString(in_deviceStateType);

    mRep->sendDeviceStateResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::setRadioCapability(int32_t in_serial, const modem::RadioCapability &in_rc) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::setRadioPower(
      int32_t in_serial, bool in_powerOn, bool in_forEmergencyCall, bool in_preferredForEmergencyCall) {
    printf("RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::setResponseFunctions(
      const std::shared_ptr<modem::IRadioModemResponse> &in_radioModemResponse,
      const std::shared_ptr<modem::IRadioModemIndication> &in_radioModemIndication) {
    printf("xRadioModem::%s\n", __func__);

    mRep = in_radioModemResponse;
    mInd = in_radioModemIndication;

    return ndk::ScopedAStatus::ok();
}
