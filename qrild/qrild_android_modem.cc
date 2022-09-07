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

#define LOG_TAG "qrild.IModem"
#include <android-base/logging.h>
#include <q_log.h>

#include <qrild.h>
#include <util.h>

#include <qrild_qmi.h>
#include <qmi_dms.h>

#include "qrild_radio.hh"

#include <aidl/android/hardware/radio/RadioAccessFamily.h>

RadioModem::RadioModem(struct rild_state *state) : mState(state) {
    log_debug("xRadioModem::%s\n", __func__);

    LOG(INFO) << "Rebooting modem...";
    qrild_qmi_dms_set_operating_mode(mState, QMI_DMS_OPERATING_MODE_RESET);
    qrild_qmi_powerup(mState);

    int rc = qrild_qmi_nas_register_indications(mState);
    if (rc) {
        log_error("Failed to register NAS indications!: %d", rc);
    }

    mCaps.logicalModemUuid = "org.linaro.qrild.lm1";
    mCaps.phase = modem::RadioCapability::PHASE_CONFIGURED;
    mCaps.raf = (int32_t)RadioAccessFamily::LTE|(int32_t)RadioAccessFamily::UMTS;
    mCaps.status = modem::RadioCapability::STATUS_NONE;

    mEnabled = true;
}

ndk::ScopedAStatus RadioModem::enableModem(int32_t in_serial, bool in_on) {
    log_debug("FIXME! TODO: RadioModem::%s\n", __func__);

    LOG(INFO) << (in_on ? "en" : "dis") << "abling modem";

    mRep->enableModemResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getBasebandVersion(int32_t in_serial) {
    log_debug("xRadioModem::%s\n", __func__);
    char *revision = nullptr;
    int rc;
    RadioResponseInfo r_info;
    r_info.serial = in_serial;
    r_info.type = RESP_SOLICITED;
    r_info.error = RadioError::NONE;

    rc = qrild_qmi_dms_get_revision(mState, &revision);
    if (rc != QRILD_STATE_DONE) {
        LOG(ERROR) << "Couldn't get modem baseband version: " << rc;
        r_info.error = RadioError::INTERNAL_ERR;
    }

    mRep->getBasebandVersionResponse(r_info, std::string(revision));

    free(revision);

    return ndk::ScopedAStatus::ok();
}

#define MAX_LEN 255
ndk::ScopedAStatus RadioModem::getDeviceIdentity(int32_t in_serial) {
    log_debug("xRadioModem::%s\n", __func__);
    struct dms_get_ids_resp_data ids;
    int rc;
    auto r_info = RESP_OK(in_serial);

    rc = qrild_qmi_dms_get_ids(mState, &ids);
    if (rc != QRILD_STATE_DONE) {
        LOG(ERROR) << "Failed to get modem IDs: " << rc;
        r_info.error = RadioError::MODEM_ERR;
    }

    LOG(INFO)
          << __func__ << ": IMEI: " << ids.imei << ", ESN: " << ids.esn << ", MEID: " << ids.meid;

    mRep->getDeviceIdentityResponse(r_info, std::string(ids.imei), std::string(ids.imei_ver),
          std::string(ids.esn), std::string(ids.meid));

    dms_get_ids_resp_data_free(&ids);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getHardwareConfig(int32_t in_serial) {
    log_debug("xRadioModem::%s\n", __func__);
    uint8_t operating_mode;
    auto hw_config = std::vector<modem::HardwareConfig>();
    auto modem = modem::HardwareConfig();
    auto modemConfig = modem::HardwareConfigModem();
    auto sim1 = modem::HardwareConfig();
    //auto sim2 = modem::HardwareConfig();
    auto simConfig = modem::HardwareConfigSim();
    modem.type = modem::HardwareConfig::TYPE_MODEM;
    modem.uuid = "org.linaro.qrild.lm1";
    modem.state = modem::HardwareConfig::STATE_DISABLED;

    operating_mode = qrild_qmi_dms_get_operating_mode(mState);
    switch (operating_mode) {
    case QMI_DMS_OPERATING_MODE_ONLINE:
        modem.state = modem::HardwareConfig::STATE_ENABLED;
        break;
    // case QMI_DMS_OPERATING_MODE_LOW_POWER:
    //     modem.state = modem::HardwareConfig::STATE_STANDBY;
    //     break;
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

    modem.modem = std::vector<modem::HardwareConfigModem>();
    modem.modem.push_back(modemConfig);

    sim1.type = modem::HardwareConfig::TYPE_SIM;
    sim1.uuid = "totally-a-real-sim-card";
    // Can I hardcode this??
    sim1.state = modem::HardwareConfig::STATE_ENABLED;
    simConfig.modemUuid = modem.uuid;

    sim1.sim = std::vector<modem::HardwareConfigSim>();
    sim1.sim.push_back(simConfig);

    hw_config.push_back(modem);
    hw_config.push_back(sim1);

    // sim2.type = modem::HardwareConfig::TYPE_SIM;
    // sim2.uuid = "another-totally-a-real-sim-card";
    // // Can I hardcode this??
    // sim2.state = modem::HardwareConfig::STATE_STANDBY;
    // simConfig.modemUuid = modem.uuid;

    // sim2.sim = std::vector<modem::HardwareConfigSim>();
    // sim2.sim.push_back(simConfig);
    //hw_config.push_back(sim2);

    LOG(INFO) << modem.toString();
    LOG(INFO) << sim1.toString();

    mRep->getHardwareConfigResponse(RESP_OK(in_serial), hw_config);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getModemActivityInfo(int32_t in_serial) {
    log_debug("DISABLED: RadioModem::%s\n", __func__);
    static int multiplier = 1;
    auto activity = modem::ActivityStatsInfo();
    auto techSpecific = modem::ActivityStatsTechSpecificInfo();
    auto r_info = RESP_OK(in_serial);
    r_info.error = RadioError::REQUEST_NOT_SUPPORTED;
    mRep->getModemActivityInfoResponse(r_info, activity);
    goto out;

    activity.sleepModeTimeMs = 0;
    activity.idleModeTimeMs = 0;

    techSpecific.rat = AccessNetwork::UTRAN;
    techSpecific.frequencyRange = modem::ActivityStatsTechSpecificInfo::FREQUENCY_RANGE_UNKNOWN;
    techSpecific.txmModetimeMs = std::vector<int32_t>();
    for (int i = 0; i < 5; i++)
        techSpecific.txmModetimeMs.push_back(i * 5 * multiplier);

    techSpecific.rxModeTimeMs = 10 * multiplier;

    activity.techSpecificInfo = std::vector<modem::ActivityStatsTechSpecificInfo>();
    activity.techSpecificInfo.push_back(techSpecific);

    LOG(INFO) << __func__ << ": FIXME! Hardcoding UTRAN (LTE)";
    LOG(INFO) << activity.toString();

    mRep->getModemActivityInfoResponse(RESP_OK(in_serial), activity);

    multiplier++;

out:
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getModemStackStatus(int32_t in_serial) {
    log_debug("xRadioModem::%s\n", __func__);

    LOG(INFO) << __func__ << ": " << mEnabled;

    mRep->getModemStackStatusResponse(RESP_OK(in_serial), mEnabled);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::getRadioCapability(int32_t in_serial) {
    log_debug("xRadioModem::%s\n", __func__);

    mRep->getRadioCapabilityResponse(RESP_OK(in_serial), mCaps);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::nvReadItem(int32_t in_serial, modem::NvItem in_itemId) {
    log_debug("FIXME! TODO: RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::nvResetConfig(int32_t in_serial, modem::ResetNvType in_resetType) {
    log_debug("FIXME! TODO: RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::nvWriteCdmaPrl(
      int32_t in_serial, const std::vector<uint8_t> &in_prl) {
    log_debug("FIXME! TODO: RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::nvWriteItem(int32_t in_serial, const modem::NvWriteItem &in_item) {
    log_debug("FIXME! TODO: RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::requestShutdown(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioModem::responseAcknowledgement() {
    log_debug("FIXME! TODO: RadioModem::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
};
ndk::ScopedAStatus RadioModem::sendDeviceState(
      int32_t in_serial, modem::DeviceStateType in_deviceStateType, bool in_state) {
    log_debug("xRadioModem::%s\n", __func__);

    LOG(INFO) << "Got device state: " << modem::toString(in_deviceStateType);

    mRep->sendDeviceStateResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

// FIXME: finish this
ndk::ScopedAStatus RadioModem::setRadioCapability(
      int32_t in_serial, const modem::RadioCapability &in_rc) {
    log_debug("FIXME! TODO: RadioModem::%s\n", __func__);
    int32_t filter_bit = 0b1;
    RadioResponseInfo r_info;
    r_info.serial = in_serial;
    r_info.type = RESP_SOLICITED;
    r_info.error = RadioError::NONE;

    LOG(INFO) << "(incomplete) Request to set capability for " << in_rc.logicalModemUuid;
    LOG(INFO) << "Phase: " << in_rc.phase;
    LOG(INFO) << "Radio Families:";
    while (filter_bit < (int32_t)RadioAccessFamily::NR) {
        LOG(INFO) << toString(RadioAccessFamily(in_rc.raf & filter_bit));
        filter_bit <<= 1;
    }

    if (in_rc.logicalModemUuid != mCaps.logicalModemUuid) {
        r_info.error = RadioError::INVALID_ARGUMENTS;
        goto out;
    }

    mCaps = in_rc;
    mCaps.phase = modem::RadioCapability::PHASE_CONFIGURED;
    mCaps.status = modem::RadioCapability::STATUS_NONE;

out:
    mRep->setRadioCapabilityResponse(r_info, mCaps);

    // Must call mInd->radioCapabilityIndication() here
    return ndk::ScopedAStatus::ok();
}

// Oh I'm dumb, it's the /radio/ part of the modem, not the modem itself!!!
ndk::ScopedAStatus RadioModem::setRadioPower(int32_t in_serial, bool in_powerOn,
      bool in_forEmergencyCall, bool in_preferredForEmergencyCall) {
    log_debug("xRadioModem::%s\n", __func__);
    struct qmi_response_type_v01 res;
    RadioResponseInfo r_info = RESP_OK(in_serial);

    LOG(INFO) << "setRadioPower(powerOn: " << in_powerOn
              << ", forEmergencyCall: " << in_forEmergencyCall
              << ", preferredForEmergencyCall: " << in_preferredForEmergencyCall << ")";

    mRadioPower = (in_powerOn || in_forEmergencyCall || in_preferredForEmergencyCall) ?
        modem::RadioState::ON : modem::RadioState::OFF;

    mRep->setRadioPowerResponse(r_info);

    return ndk::ScopedAStatus::ok();


    // if (!in_powerOn) {
    //     LOG(INFO) << "Not powering modem off!";
    //     //mEnabled = false;
    //     mRep->setRadioPowerResponse(r_info);
    //     return ndk::ScopedAStatus::ok();
    // }

    // // FIXME: modem doesn't come back after setting to LOW_POWER ?
    // uint8_t desired_mode =
    //       in_powerOn ? QMI_DMS_OPERATING_MODE_ONLINE : QMI_DMS_OPERATING_MODE_LOW_POWER;

    // if (!mEnabled)
    //     mEnabled = desired_mode == QMI_DMS_OPERATING_MODE_ONLINE;

    // if (in_forEmergencyCall || in_preferredForEmergencyCall)
    //     desired_mode = QMI_DMS_OPERATING_MODE_ONLINE;

    // int current_mode = qrild_qmi_dms_get_operating_mode(mState);
    // if (current_mode < 0) {
    //     LOG(ERROR) << "Couldn't get modem operating mode";
    //     r_info.error = RadioError::MODEM_ERR;
    // } else if (current_mode != desired_mode) {
    //     res = qrild_qmi_dms_set_operating_mode(mState, desired_mode);
    //     if (res.result) {
    //         LOG(ERROR) << "Couldn't set modem operating mode";
    //         if (res.error == QMI_ERR_QRILD) {
    //             r_info.error = RadioError::INTERNAL_ERR;
    //         } else {
    //             LOG(ERROR) << "QMI response Error: " << res.error;
    //             r_info.error = RadioError::MODEM_ERR;
    //         }
    //     } else {
    //         LOG(INFO) << "Set modem operating mode to: " << (int)desired_mode << "!";
    //         log_debug("Set operating mode to %u\n", desired_mode);
    //         switch (desired_mode) {
    //         case QMI_DMS_OPERATING_MODE_ONLINE:
    //             if (services.initialised)
    //                 services.sim->_provisionDefaultSim();
    //             mInd->radioStateChanged(RadioIndicationType::UNSOLICITED, modem::RadioState::ON);
    //             break;
    //         case QMI_DMS_OPERATING_MODE_LOW_POWER:
    //             mInd->radioStateChanged(RadioIndicationType::UNSOLICITED, modem::RadioState::OFF);
    //             break;
    //         default:
    //             mInd->radioStateChanged(
    //                   RadioIndicationType::UNSOLICITED, modem::RadioState::UNAVAILABLE);
    //             break;
    //         }
    //     }
    // } else {
    //     LOG(WARNING) << "Modem already in mode: " << (int)desired_mode << " ignoring for now";
    //     r_info.error = RadioError::INVALID_ARGUMENTS;
    // }

    // // FIXME: HACK!!!
    // if (mEnabled) {
    //     qrild_qmi_nas_register_indications(mState);
    //     q_work_schedule_now(&services.network->restricted_state_changed_work);
    // }
}

ndk::ScopedAStatus RadioModem::setResponseFunctions(
      const std::shared_ptr<modem::IRadioModemResponse> &in_radioModemResponse,
      const std::shared_ptr<modem::IRadioModemIndication> &in_radioModemIndication) {
    log_debug("xRadioModem::%s\n", __func__);
    mRadioPower = modem::RadioState::UNAVAILABLE;

    mRep = in_radioModemResponse;
    mInd = in_radioModemIndication;

    // Must be called for RIL to continue initialisation
    mInd->rilConnected(RadioIndicationType::UNSOLICITED);

    int current_mode = qrild_qmi_dms_get_operating_mode(mState);
    switch (current_mode) {
    case QMI_DMS_OPERATING_MODE_ONLINE:
        mRadioPower = modem::RadioState::ON;
        break;
    case QMI_DMS_OPERATING_MODE_OFFLINE:
    case QMI_DMS_OPERATING_MODE_LOW_POWER:
    case QMI_DMS_OPERATING_MODE_SHUTTING_DOWN:
        mRadioPower = modem::RadioState::OFF;
        break;
    default:
        LOG(ERROR) << "Current operating mode: " << current_mode
                   << " Reporting radio state unavailable!";
        break;
    }

    LOG(ERROR) << "Reporting radio state " << modem::toString(mRadioPower);

    mInd->radioStateChanged(RadioIndicationType::UNSOLICITED, mRadioPower);

    return ndk::ScopedAStatus::ok();
}

void RadioModem::_handleQmiIndications()
{

}
