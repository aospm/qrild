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

#include <qrild.h>

#include "qrild_radio.hh"

RadioSim::RadioSim(struct rild_state *state) : mState(state) {
    printf("RadioSim::%s\n", __func__);
}

ndk::ScopedAStatus RadioSim::areUiccApplicationsEnabled(int32_t in_serial) {
    printf("RadioSim::%s\n", __func__);
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

ndk::ScopedAStatus RadioSim::getIccCardStatus(int32_t in_serial) {
    printf("RadioSim::%s\n", __func__);
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
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setFacilityLockForApp(int32_t in_serial, const std::string &in_facility, bool in_lockState,
      const std::string &in_password, int32_t in_serviceClass, const std::string &in_appId) {
    printf("RadioSim::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioSim::setResponseFunctions(const std::shared_ptr<sim::IRadioSimResponse> &in_radioSimResponse,
      const std::shared_ptr<sim::IRadioSimIndication> &in_radioSimIndication) {
    printf("RadioSim::%s\n", __func__);

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
