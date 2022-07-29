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

#include <qrild.h>
#include <qrild_qmi.h>
#include <qmi_uim.h>

#include "qrild_radio.hh"

RadioSim::RadioSim(struct rild_state *state) : mState(state) {
    printf("-RadioSim::%s\n", __func__);
}

ndk::ScopedAStatus RadioSim::areUiccApplicationsEnabled(int32_t in_serial) {
    printf("xRadioSim::%s\n", __func__);

    // FIXME: MUST be enabled at first
    LOG(ERROR) << __func__ << ": Hardcode enable UICC application";
    mRep->areUiccApplicationsEnabledResponse(RESP_OK(in_serial), true);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::changeIccPin2ForApp(int32_t in_serial, const std::string &in_oldPin2,
      const std::string &in_newPin2, const std::string &in_aid) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::changeIccPinForApp(int32_t in_serial, const std::string &in_oldPin,
      const std::string &in_newPin, const std::string &in_aid) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::enableUiccApplications(int32_t in_serial, bool in_enable) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getAllowedCarriers(int32_t in_serial) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getCdmaSubscription(int32_t in_serial) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getCdmaSubscriptionSource(int32_t in_serial) {
    printf("xRadioSim::%s\n", __func__);

    LOG(INFO) << __func__ << ": FIXME: hardcoded to RUIM_SIM";

    mRep->getCdmaSubscriptionSourceResponse(
          RESP_OK(in_serial), sim::CdmaSubscriptionSource::RUIM_SIM);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getFacilityLockForApp(int32_t in_serial,
      const std::string &in_facility, const std::string &in_password, int32_t in_serviceClass,
      const std::string &in_appId) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

// FIXME: Hardcoded SIM slot 1 here
// FIXME: EID length is 0 for some reason!
/*
07-18 14:19:18.816  1119  1119 E UiccController: com.android.internal.telephony.CommandException: MODEM_ERR
07-18 14:19:18.816  1119  1119 E UiccController: 	at com.android.internal.telephony.RILRequest.onError(RILRequest.java:236)
07-18 14:19:18.816  1119  1119 E UiccController: 	at com.android.internal.telephony.RIL.processResponseDoneInternal(RIL.java:5312)
07-18 14:19:18.816  1119  1119 E UiccController: 	at com.android.internal.telephony.RIL.processResponseDone(RIL.java:5297)
07-18 14:19:18.816  1119  1119 E UiccController: 	at com.android.internal.telephony.SimResponse.getIccCardStatusResponse(SimResponse.java:191)
07-18 14:19:18.816  1119  1119 E UiccController: 	at android.hardware.radio.sim.IRadioSimResponse$Stub.onTransact(IRadioSimResponse.java:820)
07-18 14:19:18.816  1119  1119 E UiccController: 	at android.os.Binder.execTransactInternal(Binder.java:1205)
07-18 14:19:18.816  1119  1119 E UiccController: 	at android.os.Binder.execTransact(Binder.java:1163)
*/
ndk::ScopedAStatus RadioSim::getIccCardStatus(int32_t in_serial) {
    printf("xRadioSim::%s\n", __func__);
    auto cardStatus = sim::CardStatus();
    int rc;
    struct uim_get_slot_status_resp_data slot_status;
    struct uim_card_status *qmi_card_status;
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

    rc = qrild_qmi_uim_get_card_status(mState);
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
    qmi_card_status = mState->card_status;

    cardStatus.cardState = QmiUimPhysicalCardStateToCardState(slot_status.slot_state->slots[0].card_state);

    cardStatus.universalPinState = sim::PinState(qmi_card_status->cards[0].upin_state);
    // FIXME: Is GSM/CDMA needed for LTE?
    // Zero-based?
    cardStatus.gsmUmtsSubscriptionAppIndex = 0;
    cardStatus.cdmaSubscriptionAppIndex = 0;
    cardStatus.imsSubscriptionAppIndex = 0;
    cardStatus.applications = std::vector<sim::AppStatus>();
    // FIXME: Should be USIM, hopefully can get away with this
    appn.appType = qmi_card_status->cards[0].applications[0].type;
    switch (qmi_card_status->cards[0].applications[0].state) {
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
                  << qmi_card_status->cards[0].applications[0].state << "!";
    }

    //FIXME: rename decode_atr to something generic
    appn.aidPtr = decode_atr(qmi_card_status->cards[0].applications[0].application_identifier_value, qmi_card_status->cards[0].applications[0].application_identifier_value_n);

    appn.pin1 = sim::PinState(qmi_card_status->cards[0].applications[0].pin1_state);
    appn.pin2 = sim::PinState(qmi_card_status->cards[0].applications[0].pin2_state);

    cardStatus.applications.push_back(appn);

    cardStatus.atr = decode_atr(
          slot_status.slot_info->slots[0].atr_value, slot_status.slot_info->slots[0].atr_value_n);
    cardStatus.eid = decode_eid(slot_status.eid_info, slot_status.eid_info_n);
    cardStatus.iccid = decode_iccid(
          slot_status.slot_state->slots[0].iccid, slot_status.slot_state->slots[0].iccid_n);

    map.physicalSlotId = 1;
    map.portId = 0;

    cardStatus.slotMap = map;

out:
    LOG(INFO) << __func__ << ": err: " << toString(r_info.error) << "\n\t" << cardStatus.toString();

    mRep->getIccCardStatusResponse(r_info, cardStatus);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getImsiForApp(int32_t in_serial, const std::string &in_aid) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getSimPhonebookCapacity(int32_t in_serial) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getSimPhonebookRecords(int32_t in_serial) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccCloseLogicalChannel(int32_t in_serial, int32_t in_channelId) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccIoForApp(int32_t in_serial, const sim::IccIo &in_iccIo) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccOpenLogicalChannel(
      int32_t in_serial, const std::string &in_aid, int32_t in_p2) {
    printf("xRadioSim::%s\n", __func__);
    auto r_info = RESP_OK(in_serial);

    LOG(WARNING) << __func__ << ": FIXME! TODO:? aid: " << in_aid << ", p2: " << in_p2;
    r_info.error = RadioError::REQUEST_NOT_SUPPORTED;

    mRep->iccOpenLogicalChannelResponse(r_info, 0, std::vector<uint8_t>());

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccTransmitApduBasicChannel(
      int32_t in_serial, const sim::SimApdu &in_message) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccTransmitApduLogicalChannel(
      int32_t in_serial, const sim::SimApdu &in_message) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::reportStkServiceIsRunning(int32_t in_serial) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::requestIccSimAuthentication(int32_t in_serial, int32_t in_authContext,
      const std::string &in_authData, const std::string &in_aid) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::responseAcknowledgement() {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::sendEnvelope(int32_t in_serial, const std::string &in_contents) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::sendEnvelopeWithStatus(
      int32_t in_serial, const std::string &in_contents) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::sendTerminalResponseToSim(
      int32_t in_serial, const std::string &in_contents) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setAllowedCarriers(int32_t in_serial,
      const sim::CarrierRestrictions &in_carriers, sim::SimLockMultiSimPolicy in_multiSimPolicy) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setCarrierInfoForImsiEncryption(
      int32_t in_serial, const sim::ImsiEncryptionInfo &in_imsiEncryptionInfo) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setCdmaSubscriptionSource(
      int32_t in_serial, sim::CdmaSubscriptionSource in_cdmaSub) {
    printf("xRadioSim::%s\n", __func__);

    LOG(INFO) << "(nop) got Cdma subscription source: " << sim::toString(in_cdmaSub);

    mRep->setCdmaSubscriptionSourceResponse(RESP_OK(in_serial));
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setFacilityLockForApp(int32_t in_serial,
      const std::string &in_facility, bool in_lockState, const std::string &in_password,
      int32_t in_serviceClass, const std::string &in_appId) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setResponseFunctions(
      const std::shared_ptr<sim::IRadioSimResponse> &in_radioSimResponse,
      const std::shared_ptr<sim::IRadioSimIndication> &in_radioSimIndication) {
    printf("xRadioSim::%s\n", __func__);

    mRep = in_radioSimResponse;
    mInd = in_radioSimIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setSimCardPower(int32_t in_serial, sim::CardPowerState in_powerUp) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setUiccSubscription(
      int32_t in_serial, const sim::SelectUiccSub &in_uiccSub) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPin2ForApp(
      int32_t in_serial, const std::string &in_pin2, const std::string &in_aid) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPinForApp(
      int32_t in_serial, const std::string &in_pin, const std::string &in_aid) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPuk2ForApp(int32_t in_serial, const std::string &in_puk2,
      const std::string &in_pin2, const std::string &in_aid) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPukForApp(int32_t in_serial, const std::string &in_puk,
      const std::string &in_pin, const std::string &in_aid) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplySimDepersonalization(
      int32_t in_serial, sim::PersoSubstate in_persoType, const std::string &in_controlKey) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::updateSimPhonebookRecords(
      int32_t in_serial, const sim::PhonebookRecordInfo &in_recordInfo) {
    printf("FIXME! TODO: RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

void RadioSim::handleQmiIndications()
{

}
