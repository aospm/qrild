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

#define LOG_TAG "qrild.ISim"
#include <android-base/logging.h>
#include <q_log.h>

#include <qrild.h>
#include <util.h>
#include <qrild_qmi.h>
#include <qmi_uim.h>

#include "qrild_radio.hh"

RadioSim::RadioSim(struct rild_state *state) : mState(state) {
    log_debug("-RadioSim::%s\n", __func__);
}

ndk::ScopedAStatus RadioSim::areUiccApplicationsEnabled(int32_t in_serial) {
    log_debug("xRadioSim::%s\n", __func__);

    // FIXME: MUST be enabled at first
    LOG(ERROR) << __func__ << ": Hardcode enable UICC application";
    mRep->areUiccApplicationsEnabledResponse(RESP_OK(in_serial), true);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::changeIccPin2ForApp(int32_t in_serial, const std::string &in_oldPin2,
      const std::string &in_newPin2, const std::string &in_aid) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::changeIccPinForApp(int32_t in_serial, const std::string &in_oldPin,
      const std::string &in_newPin, const std::string &in_aid) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::enableUiccApplications(int32_t in_serial, bool in_enable) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getAllowedCarriers(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getCdmaSubscription(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getCdmaSubscriptionSource(int32_t in_serial) {
    log_debug("xRadioSim::%s\n", __func__);

    LOG(INFO) << __func__ << ": FIXME: hardcoded to RUIM_SIM";

    mRep->getCdmaSubscriptionSourceResponse(
          RESP_OK(in_serial), sim::CdmaSubscriptionSource::RUIM_SIM);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getFacilityLockForApp(int32_t in_serial,
      const std::string &in_facility, const std::string &in_password, int32_t in_serviceClass,
      const std::string &in_appId) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

int RadioSim::_provisionDefaultSim() {
    int rc;
    struct uim_get_card_status_resp_data data;
    rc = qrild_qmi_uim_get_card_status(mState, &data);
    if (rc) {
        LOG(ERROR) << __func__ << ": couldn't get card status: " << rc;
        return rc;
    }
    if (data.result->result) {
        LOG(ERROR) << __func__ << ": data: modem returned error: "
                   << (int)data.result->error;
        return -data.result->error;
    }
    if (!data.status_valid) {
        LOG(ERROR) << __func__ << ": Modem response empty?";
        return -1;
    }
    if (!data.status->cards_n || !data.status->cards[0].applications_n
            || !data.status->cards[0].applications[0].application_identifier_value_n) {
        LOG(ERROR) << __func__ << ": No valid applications found, no SIM?";
        return -1;
    }

    rc = qrild_qmi_uim_set_provisioning(mState, 1, data.status->cards[0].applications[0].application_identifier_value,
    data.status->cards[0].applications[0].application_identifier_value_n);
    if (!rc) {
        LOG(INFO) << __func__ << ": Successfully provisioned default sim";
        if (mInd) // This function might be called before setResponsefunctions() has been called.
            mInd->simStatusChanged(RadioIndicationType::UNSOLICITED);
    } else {
        LOG(ERROR) << __func__ << ": Failed to provision default sim";
        return -1;
    }

    if (!rc)
        mProvisioned = true;

    return rc;
}

// FIXME: Hardcoded SIM slot 1 here
ndk::ScopedAStatus RadioSim::getIccCardStatus(int32_t in_serial) {
    log_debug("xRadioSim::%s\n", __func__);
    int rc;
    struct uim_get_slot_status_resp_data slot_status;
    struct uim_get_card_status_resp_data card_status;
    auto r_info = RESP_OK(in_serial);
    sim::AppStatus appn;
    config::SlotPortMapping map;

    rc = qrild_qmi_uim_get_slot_status(mState, &slot_status);
    switch (rc) {
    case QRILD_STATE_PENDING:
        r_info.error = RadioError::RADIO_NOT_AVAILABLE;
        goto out;
    case QRILD_STATE_DONE:
        break;
    default:
        r_info.error = RadioError::MODEM_ERR;
        goto out;
    }
    if (slot_status.result->result) {
        LOG(ERROR) << __func__ << ": slot_status: modem returned error: "
                   << (int)slot_status.result->error;
        switch (slot_status.result->error) {
        case QMI_ERR_INFORMATION_UNAVAILABLE:
            r_info.error = RadioError::RADIO_NOT_AVAILABLE;
            break;
        default:
            r_info.error = RadioError::INTERNAL_ERR;
            break;
        }
        goto out;
    }

    rc = qrild_qmi_uim_get_card_status(mState, &card_status);
    switch (rc) {
    case QRILD_STATE_PENDING:
        r_info.error = RadioError::RADIO_NOT_AVAILABLE;
        goto out;
    case QRILD_STATE_DONE:
        break;
    default:
        r_info.error = RadioError::MODEM_ERR;
        goto out_free_slot;
    }
    if (card_status.result->result) {
        LOG(ERROR) << __func__ << ": card_status: modem returned error: "
                   << (int)card_status.result->error;
        switch (card_status.result->error) {
        case QMI_ERR_INFORMATION_UNAVAILABLE:
            r_info.error = RadioError::RADIO_NOT_AVAILABLE;
            break;
        default:
            r_info.error = RadioError::INTERNAL_ERR;
            break;
        }
        goto out_free_slot;
    }

    mCardStatus.cardState =
          QmiUimPhysicalCardStateToCardState(slot_status.slot_state->slots[0].card_state);

    mCardStatus.universalPinState = sim::PinState(card_status.status->cards[0].upin_state);
    // FIXME: Is GSM/CDMA needed for LTE?
    // Zero-based?
    mCardStatus.gsmUmtsSubscriptionAppIndex = 0;
    mCardStatus.cdmaSubscriptionAppIndex = 0;
    mCardStatus.imsSubscriptionAppIndex = 0;
    mCardStatus.applications = std::vector<sim::AppStatus>();
    // FIXME: Should be USIM, hopefully can get away with this
    appn.appType = card_status.status->cards[0].applications[0].type;
    switch (card_status.status->cards[0].applications[0].state) {
    case QMI_UIM_CARD_APPLICATION_STATE_DETECTED:
        appn.appState = sim::AppStatus::APP_STATE_DETECTED;
        break;
    case QMI_UIM_CARD_APPLICATION_STATE_PIN1_OR_UPIN_PIN_REQUIRED:
        appn.appState = sim::AppStatus::APP_STATE_PIN;
        break;
    case QMI_UIM_CARD_APPLICATION_STATE_PUK1_OR_UPIN_PUK_REQUIRED:
        appn.appState = sim::AppStatus::APP_STATE_DETECTED;
        break;
    case QMI_UIM_CARD_APPLICATION_STATE_READY:
        appn.appState = sim::AppStatus::APP_STATE_READY;
        break;
    default:
        appn.appState = sim::AppStatus::APP_STATE_UNKNOWN;
        LOG(WARNING) << "Got unhandled application state: "
                     << (int)card_status.status->cards[0].applications[0].state;
    }

    appn.aidPtr = decode_bytes(card_status.status->cards[0].applications[0].application_identifier_value,
          card_status.status->cards[0].applications[0].application_identifier_value_n);

    appn.pin1 = sim::PinState(card_status.status->cards[0].applications[0].pin1_state);
    appn.pin2 = sim::PinState(card_status.status->cards[0].applications[0].pin2_state);

    mCardStatus.applications.push_back(appn);

    mCardStatus.atr = decode_bytes(
          slot_status.slot_info->slots[0].atr_value, slot_status.slot_info->slots[0].atr_value_n);
    mCardStatus.eid = decode_eid(slot_status.eid_info, slot_status.eid_info_n);
    mCardStatus.iccid = decode_iccid(
          slot_status.slot_state->slots[0].iccid, slot_status.slot_state->slots[0].iccid_n);

    map.physicalSlotId = 0;
    map.portId = 0;

    mCardStatus.slotMap = map;

out_no_sim:
    uim_get_card_status_resp_data_free(&card_status);

out_free_slot:
    uim_get_slot_status_resp_data_free(&slot_status);

out:
    LOG(INFO) << __func__ << ": err: " << toString(r_info.error)
              << "\n\t" << mCardStatus.toString();

    mRep->getIccCardStatusResponse(r_info, mCardStatus);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getImsiForApp(int32_t in_serial, const std::string &in_aid) {
    log_debug("WIP: RadioSim::%s\n", __func__);
    auto r_info = RESP_OK(in_serial);
    struct dms_uim_get_imsi_data imsi_data;
    struct dms_get_msisdn_data msisdn_data;
    std::string imsi;
    int rc;

    LOG(INFO) << __func__ << ": FIXME! which QMI message to get IMSI for specific AID?: " << in_aid;

    // rc = qrild_qmi_dms_uim_get_imsi(mState, &imsi_data);
    // if (rc) {
    //     LOG(ERROR) << __func__ << ": Couldn't get IMSI: " << rc;
    //     r_info.error = RadioError::MODEM_ERR;
    //     goto out;
    // }
    // if (imsi_data.res->result) {
    //     LOG(ERROR) << __func__ << ": IMSI: Modem returned error: " << imsi_data.res->error
    //                << ": " << qmi_error_string(imsi_data.res->error);
    // }

    // if (imsi_data.imsi_valid) {
    //     imsi = imsi_data.imsi;
    //     LOG(DEBUG) << __func__ << ": Got IMSI: " << imsi;
    // } else {
    //     LOG(ERROR) << __func__ << ": Modem sent empty response";
    //     r_info.error = RadioError::MODEM_ERR;
    // }

    rc = qrild_qmi_dms_get_msisdn(mState, &msisdn_data);
    if (rc) {
        LOG(ERROR) << __func__ << ": Couldn't get msisdn";
    }
    if (msisdn_data.res->result) {
        LOG(ERROR) << __func__ << ": MSISDN: Modem returned error: " << msisdn_data.res->error
                   << ": " << qmi_error_string(msisdn_data.res->error);
    } else if (msisdn_data.imsi) {
        imsi = msisdn_data.imsi;
    }

    if (msisdn_data.imsi_valid) {
        LOG(DEBUG) << __func__ << ": MSISDN: Got IMSI: " << msisdn_data.imsi;
        if (!imsi.length())
            imsi = msisdn_data.imsi;
        r_info.error = RadioError::NONE;
    }

    dms_get_msisdn_data_free(&msisdn_data);

    LOG(INFO) << __func__ << ": Got imsi: " << imsi;

// out_free_imsi:
//     dms_uim_get_imsi_data_free(&imsi_data);
out:
    mRep->getImsiForAppResponse(r_info, imsi);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getSimPhonebookCapacity(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getSimPhonebookRecords(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccCloseLogicalChannel(int32_t in_serial, int32_t in_channelId) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccIoForApp(int32_t in_serial, const sim::IccIo &in_iccIo) {
    log_debug("STUB: RadioSim::%s\n", __func__);
    auto r_info = RESP_OK(in_serial);

    LOG(DEBUG) << "Got ICCIO: " << in_iccIo.toString();
    r_info.error = RadioError::REQUEST_NOT_SUPPORTED;

    mRep->iccIoForAppResponse(r_info, sim::IccIoResult());

    return ndk::ScopedAStatus::ok();
}

/*
 * Carrier privileged applications.
 * See frameworks/opt/telephony/src/java/com/android/internal/telephony/uicc/UiccCarrierPrivilegeRules.java
 * for details.
 */
#define ARAM_AID "A00000015141434C00"
#define ARAD_AID "A00000015144414300"
#define PKCS15_AID "A000000063504B43532D3135"

ndk::ScopedAStatus RadioSim::iccOpenLogicalChannel(
      int32_t in_serial, const std::string &in_aid, int32_t in_p2) {
    log_debug("xRadioSim::%s\n", __func__);
    auto r_info = RESP_OK(in_serial);
    int rc;
    struct uim_icc_open_logical_channel_resp_data resp;
    int32_t channelId = 0;
    std::vector<uint8_t> selectResponse;

    LOG(INFO) << __func__ << ": " << in_aid << ", p2: " << in_p2;

    if (in_aid == ARAM_AID || in_aid == ARAD_AID || in_aid == PKCS15_AID) {
        LOG(WARNING) << __func__ << ": Unsupported AID";
        r_info.error = RadioError::REQUEST_NOT_SUPPORTED;
        goto out;
    }

    rc = qrild_qmi_uim_icc_open_logical_channel(mState, 0, in_aid.c_str(), 4, &resp);
    if (resp.result->result > 0) {
        LOG(INFO) << "Failed to open logical channel, err: " << (int)resp.result->error << ": " <<
            qmi_error_string(resp.result->error);
        switch(resp.result->error) {
        case 48: // INVALID_ARGUMENT
            r_info.error = RadioError::NO_SUCH_ELEMENT;
            break;
        default:
            r_info.error = RadioError::INTERNAL_ERR;
        }
        
        goto out;
    }

    channelId = resp.channel_id;
    selectResponse =
          std::vector<uint8_t>(resp.select_response, resp.select_response + resp.select_response_n);

    LOG(INFO) << __func__ << ": Success! channelID: " << (int)resp.channel_id
              << "selectResponse: " << ::android::internal::ToString(selectResponse)
              << ", cardResult: " << std::hex << resp.card_result;

    uim_icc_open_logical_channel_resp_data_free(&resp);

out:
    mRep->iccOpenLogicalChannelResponse(r_info, channelId, selectResponse);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccTransmitApduBasicChannel(
      int32_t in_serial, const sim::SimApdu &in_message) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccTransmitApduLogicalChannel(
      int32_t in_serial, const sim::SimApdu &in_message) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::reportStkServiceIsRunning(int32_t in_serial) {
    log_debug("xRadioSim::%s\n", __func__);
    auto r_info = RESP_OK(in_serial);
    r_info.error = RadioError::REQUEST_NOT_SUPPORTED;

    mRep->reportStkServiceIsRunningResponse(r_info);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::requestIccSimAuthentication(int32_t in_serial, int32_t in_authContext,
      const std::string &in_authData, const std::string &in_aid) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::responseAcknowledgement() {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::sendEnvelope(int32_t in_serial, const std::string &in_contents) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::sendEnvelopeWithStatus(
      int32_t in_serial, const std::string &in_contents) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::sendTerminalResponseToSim(
      int32_t in_serial, const std::string &in_contents) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setAllowedCarriers(int32_t in_serial,
      const sim::CarrierRestrictions &in_carriers, sim::SimLockMultiSimPolicy in_multiSimPolicy) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setCarrierInfoForImsiEncryption(
      int32_t in_serial, const sim::ImsiEncryptionInfo &in_imsiEncryptionInfo) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setCdmaSubscriptionSource(
      int32_t in_serial, sim::CdmaSubscriptionSource in_cdmaSub) {
    log_debug("xRadioSim::%s\n", __func__);

    LOG(INFO) << "(nop) got Cdma subscription source: " << sim::toString(in_cdmaSub);

    mRep->setCdmaSubscriptionSourceResponse(RESP_OK(in_serial));
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setFacilityLockForApp(int32_t in_serial,
      const std::string &in_facility, bool in_lockState, const std::string &in_password,
      int32_t in_serviceClass, const std::string &in_appId) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setResponseFunctions(
      const std::shared_ptr<sim::IRadioSimResponse> &in_radioSimResponse,
      const std::shared_ptr<sim::IRadioSimIndication> &in_radioSimIndication) {
    log_debug("xRadioSim::%s\n", __func__);

    mRep = in_radioSimResponse;
    mInd = in_radioSimIndication;

    if (services.initialised && services.modem->mEnabled)
        _provisionDefaultSim();

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setSimCardPower(int32_t in_serial, sim::CardPowerState in_powerUp) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setUiccSubscription(
      int32_t in_serial, const sim::SelectUiccSub &in_uiccSub) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPin2ForApp(
      int32_t in_serial, const std::string &in_pin2, const std::string &in_aid) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPinForApp(
      int32_t in_serial, const std::string &in_pin, const std::string &in_aid) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPuk2ForApp(int32_t in_serial, const std::string &in_puk2,
      const std::string &in_pin2, const std::string &in_aid) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPukForApp(int32_t in_serial, const std::string &in_puk,
      const std::string &in_pin, const std::string &in_aid) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplySimDepersonalization(
      int32_t in_serial, sim::PersoSubstate in_persoType, const std::string &in_controlKey) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::updateSimPhonebookRecords(
      int32_t in_serial, const sim::PhonebookRecordInfo &in_recordInfo) {
    log_debug("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

void RadioSim::_handleQmiIndications() {
}
