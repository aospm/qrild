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
    printf("RadioSim::%s\n", __func__);
}

ndk::ScopedAStatus RadioSim::areUiccApplicationsEnabled(int32_t in_serial) {
    printf("xRadioSim::%s\n", __func__);

    // FIXME: Not sure if needed
    mRep->areUiccApplicationsEnabledResponse(RESP_OK(in_serial), true);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::changeIccPin2ForApp(
      int32_t in_serial, const std::string &in_oldPin2, const std::string &in_newPin2, const std::string &in_aid) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::changeIccPinForApp(
      int32_t in_serial, const std::string &in_oldPin, const std::string &in_newPin, const std::string &in_aid) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::enableUiccApplications(int32_t in_serial, bool in_enable) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getAllowedCarriers(int32_t in_serial) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getCdmaSubscription(int32_t in_serial) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getCdmaSubscriptionSource(int32_t in_serial) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getFacilityLockForApp(int32_t in_serial, const std::string &in_facility,
      const std::string &in_password, int32_t in_serviceClass, const std::string &in_appId) {
    printf("RadioSim::%s\n", __func__);
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
    struct uim_slot_status_msg qmi_slot_status;
    struct uim_card_status *qmi_card_status;
    RadioResponseInfo info;
    RadioError err = RadioError::NONE;
    sim::AppStatus appn;
    config::SlotPortMapping map;

    rc = qrild_qmi_uim_get_slot_status(mState, &qmi_slot_status);
    switch (rc) {
    case QRILD_STATE_PENDING:
        err = RadioError::RADIO_NOT_AVAILABLE;
        goto out;
    case QRILD_STATE_DONE:
        break;
    default:
        err = RadioError::MODEM_ERR;
        goto out;
    }

    rc = qrild_qmi_uim_get_card_status(mState);
    switch (rc) {
    case QRILD_STATE_PENDING:
        err = RadioError::RADIO_NOT_AVAILABLE;
        goto out;
    case QRILD_STATE_DONE:
        break;
    default:
        err = RadioError::MODEM_ERR;
        goto out;
    }
    qmi_card_status = mState->card_status;

    cardStatus.cardState = qmi_slot_status.state->slots[0].card_state;

    cardStatus.universalPinState = sim::PinState(qmi_card_status->cards[0].upin_state);
    // FIXME: Is GSM/CDMA needed for LTE?
    cardStatus.gsmUmtsSubscriptionAppIndex = -1;
    cardStatus.cdmaSubscriptionAppIndex = -1;
    cardStatus.imsSubscriptionAppIndex = -1;
    cardStatus.applications = std::vector<sim::AppStatus>();
    // FIXME: Should be USIM, hopefully can get away with this
    appn.appType = sim::AppStatus::APP_TYPE_SIM;
    appn.appState = sim::AppStatus::APP_STATE_READY;
    cardStatus.applications.push_back(appn);

    cardStatus.atr = decode_atr(qmi_slot_status.info->slots[0].atr_value, qmi_slot_status.info->slots[0].atr_value_n);
    cardStatus.eid = decode_eid(qmi_slot_status.eid_info, qmi_slot_status.eid_info_n);
    cardStatus.iccid = decode_iccid(qmi_slot_status.state->slots[0].iccid, qmi_slot_status.state->slots[0].iccid_n);

    map.physicalSlotId = 1;
    map.portId = 0;

    cardStatus.slotMap = map;

out:
    buildResponseInfo(info, in_serial, RESP_SOLICITED, err);

    mRep->getIccCardStatusResponse(info, cardStatus);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getImsiForApp(int32_t in_serial, const std::string &in_aid) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getSimPhonebookCapacity(int32_t in_serial) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::getSimPhonebookRecords(int32_t in_serial) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccCloseLogicalChannel(int32_t in_serial, int32_t in_channelId) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccIoForApp(int32_t in_serial, const sim::IccIo &in_iccIo) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccOpenLogicalChannel(int32_t in_serial, const std::string &in_aid, int32_t in_p2) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccTransmitApduBasicChannel(int32_t in_serial, const sim::SimApdu &in_message) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::iccTransmitApduLogicalChannel(int32_t in_serial, const sim::SimApdu &in_message) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::reportStkServiceIsRunning(int32_t in_serial) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::requestIccSimAuthentication(
      int32_t in_serial, int32_t in_authContext, const std::string &in_authData, const std::string &in_aid) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::responseAcknowledgement() {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::sendEnvelope(int32_t in_serial, const std::string &in_contents) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::sendEnvelopeWithStatus(int32_t in_serial, const std::string &in_contents) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::sendTerminalResponseToSim(int32_t in_serial, const std::string &in_contents) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setAllowedCarriers(
      int32_t in_serial, const sim::CarrierRestrictions &in_carriers, sim::SimLockMultiSimPolicy in_multiSimPolicy) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setCarrierInfoForImsiEncryption(
      int32_t in_serial, const sim::ImsiEncryptionInfo &in_imsiEncryptionInfo) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setCdmaSubscriptionSource(int32_t in_serial, sim::CdmaSubscriptionSource in_cdmaSub) {
    printf("xRadioSim::%s\n", __func__);

    LOG(INFO) << "(nop) got Cdma subscription source: " << sim::toString(in_cdmaSub);

    mRep->setCdmaSubscriptionSourceResponse(RESP_OK(in_serial));
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setFacilityLockForApp(int32_t in_serial, const std::string &in_facility, bool in_lockState,
      const std::string &in_password, int32_t in_serviceClass, const std::string &in_appId) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setResponseFunctions(const std::shared_ptr<sim::IRadioSimResponse> &in_radioSimResponse,
      const std::shared_ptr<sim::IRadioSimIndication> &in_radioSimIndication) {
    printf("xRadioSim::%s\n", __func__);

    mRep = in_radioSimResponse;
    mInd = in_radioSimIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setSimCardPower(int32_t in_serial, sim::CardPowerState in_powerUp) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setUiccSubscription(int32_t in_serial, const sim::SelectUiccSub &in_uiccSub) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPin2ForApp(
      int32_t in_serial, const std::string &in_pin2, const std::string &in_aid) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPinForApp(
      int32_t in_serial, const std::string &in_pin, const std::string &in_aid) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPuk2ForApp(
      int32_t in_serial, const std::string &in_puk2, const std::string &in_pin2, const std::string &in_aid) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplyIccPukForApp(
      int32_t in_serial, const std::string &in_puk, const std::string &in_pin, const std::string &in_aid) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::supplySimDepersonalization(
      int32_t in_serial, sim::PersoSubstate in_persoType, const std::string &in_controlKey) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::updateSimPhonebookRecords(
      int32_t in_serial, const sim::PhonebookRecordInfo &in_recordInfo) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}
