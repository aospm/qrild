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

#define LOG_TAG "qrild.IVoice"
#include <android-base/logging.h>

#include <qrild.h>

#include "qrild_radio.hh"

RadioVoice::RadioVoice(struct rild_state *state) : mState(state) {
    printf("RadioVoice::%s\n", __func__);
}

ndk::ScopedAStatus RadioVoice::acceptCall(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::cancelPendingUssd(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::conference(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::dial(
      int32_t in_serial, const voice::Dial &in_dialInfo) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::emergencyDial(int32_t in_serial,
      const voice::Dial &in_dialInfo, int32_t in_categories,
      const std::vector<std::string> &in_urns, voice::EmergencyCallRouting in_routing,
      bool in_hasKnownUserIntentEmergency, bool in_isTesting) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::exitEmergencyCallbackMode(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::explicitCallTransfer(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getCallForwardStatus(
      int32_t in_serial, const voice::CallForwardInfo &in_callInfo) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getCallWaiting(int32_t in_serial, int32_t in_serviceClass) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getClip(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getClir(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getCurrentCalls(int32_t in_serial) {
    printf("xRadioVoice::%s\n", __func__);
    auto calls = std::vector<voice::Call>();

    mRep->getCurrentCallsResponse(RESP_OK(in_serial), calls);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getLastCallFailCause(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getMute(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getPreferredVoicePrivacy(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getTtyMode(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::handleStkCallSetupRequestFromSim(int32_t in_serial, bool in_accept) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::hangup(int32_t in_serial, int32_t in_gsmIndex) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::hangupForegroundResumeBackground(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::hangupWaitingOrBackground(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::isVoNrEnabled(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::rejectCall(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::responseAcknowledgement() {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::sendBurstDtmf(
      int32_t in_serial, const std::string &in_dtmf, int32_t in_on, int32_t in_off) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::sendCdmaFeatureCode(int32_t in_serial, const std::string &in_featureCode) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::sendDtmf(int32_t in_serial, const std::string &in_s) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::sendUssd(int32_t in_serial, const std::string &in_ussd) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::separateConnection(int32_t in_serial, int32_t in_gsmIndex) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setCallForward(
      int32_t in_serial, const voice::CallForwardInfo &in_callInfo) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setCallWaiting(int32_t in_serial, bool in_enable, int32_t in_serviceClass) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setClir(int32_t in_serial, int32_t in_status) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setMute(int32_t in_serial, bool in_enable) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setPreferredVoicePrivacy(int32_t in_serial, bool in_enable) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setResponseFunctions(
      const std::shared_ptr< voice::IRadioVoiceResponse> &in_radioVoiceResponse,
      const std::shared_ptr< voice::IRadioVoiceIndication> &in_radioVoiceIndication) {
    printf("xRadioVoice::%s\n", __func__);

    mRep = in_radioVoiceResponse;
    mInd = in_radioVoiceIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setTtyMode(int32_t in_serial, voice::TtyMode in_mode) {
    printf("xRadioVoice::%s\n", __func__);

    printf("(nop) Set TTY mode to %s\n", voice::toString(in_mode).c_str());

    mRep->setTtyModeResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setVoNrEnabled(int32_t in_serial, bool in_enable) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::startDtmf(int32_t in_serial, const std::string &in_s) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::stopDtmf(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::switchWaitingOrHoldingAndActive(int32_t in_serial) {
    printf("RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}
