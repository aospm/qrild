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

#define LOG_TAG "qrild.IMessaging"
#include <android-base/logging.h>

#include <qrild.h>

#include "qrild_radio.hh"

RadioMessaging::RadioMessaging(struct rild_state *state) : mState(state) {
    printf("RadioMessaging::%s\n", __func__);
}

ndk::ScopedAStatus RadioMessaging::acknowledgeIncomingGsmSmsWithPdu(
      int32_t in_serial, bool in_success, const std::string &in_ackPdu) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::acknowledgeLastIncomingCdmaSms(
      int32_t in_serial, const messaging::CdmaSmsAck &in_smsAck) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::acknowledgeLastIncomingGsmSms(
      int32_t in_serial, bool in_success, messaging::SmsAcknowledgeFailCause in_cause) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::deleteSmsOnRuim(int32_t in_serial, int32_t in_index) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::deleteSmsOnSim(int32_t in_serial, int32_t in_index) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::getCdmaBroadcastConfig(int32_t in_serial) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::getGsmBroadcastConfig(int32_t in_serial) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::getSmscAddress(int32_t in_serial) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::reportSmsMemoryStatus(int32_t in_serial, bool in_available) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::responseAcknowledgement() {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::sendCdmaSms(int32_t in_serial, const messaging::CdmaSmsMessage &in_sms) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::sendCdmaSmsExpectMore(int32_t in_serial, const messaging::CdmaSmsMessage &in_sms) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::sendImsSms(int32_t in_serial, const messaging::ImsSmsMessage &in_message) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::sendSms(int32_t in_serial, const messaging::GsmSmsMessage &in_message) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::sendSmsExpectMore(int32_t in_serial, const messaging::GsmSmsMessage &in_message) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::setCdmaBroadcastActivation(int32_t in_serial, bool in_activate) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::setCdmaBroadcastConfig(
      int32_t in_serial, const std::vector<messaging::CdmaBroadcastSmsConfigInfo> &in_configInfo) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::setGsmBroadcastActivation(int32_t in_serial, bool in_activate) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::setGsmBroadcastConfig(
      int32_t in_serial, const std::vector<messaging::GsmBroadcastSmsConfigInfo> &in_configInfo) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::setResponseFunctions(
      const std::shared_ptr<messaging::IRadioMessagingResponse> &in_radioMessagingResponse,
      const std::shared_ptr<messaging::IRadioMessagingIndication> &in_radioMessagingIndication) {
    printf("xRadioMessaging::%s\n", __func__);

    mRep = in_radioMessagingResponse;
    mInd = in_radioMessagingIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::setSmscAddress(int32_t in_serial, const std::string &in_smsc) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::writeSmsToRuim(int32_t in_serial, const messaging::CdmaSmsWriteArgs &in_cdmaSms) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioMessaging::writeSmsToSim(int32_t in_serial, const messaging::SmsWriteArgs &in_smsWriteArgs) {
    printf("RadioMessaging::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}
