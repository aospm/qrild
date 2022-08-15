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
#include <q_log.h>

#include <qrild.h>

#include "qrild_radio.hh"

RadioVoice::RadioVoice(struct rild_state *state) : mState(state) {
    log_debug("-RadioVoice::%s\n", __func__);
}

ndk::ScopedAStatus RadioVoice::acceptCall(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::cancelPendingUssd(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::conference(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::dial(
      int32_t in_serial, const voice::Dial &in_dialInfo) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::emergencyDial(int32_t in_serial,
      const voice::Dial &in_dialInfo, int32_t in_categories,
      const std::vector<std::string> &in_urns, voice::EmergencyCallRouting in_routing,
      bool in_hasKnownUserIntentEmergency, bool in_isTesting) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::exitEmergencyCallbackMode(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::explicitCallTransfer(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getCallForwardStatus(
      int32_t in_serial, const voice::CallForwardInfo &in_callInfo) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getCallWaiting(int32_t in_serial, int32_t in_serviceClass) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getClip(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getClir(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getCurrentCalls(int32_t in_serial) {
    log_debug("xRadioVoice::%s\n", __func__);
    auto calls = std::vector<voice::Call>();

    mRep->getCurrentCallsResponse(RESP_OK(in_serial), calls);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getLastCallFailCause(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getMute(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getPreferredVoicePrivacy(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::getTtyMode(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::handleStkCallSetupRequestFromSim(int32_t in_serial, bool in_accept) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::hangup(int32_t in_serial, int32_t in_gsmIndex) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::hangupForegroundResumeBackground(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::hangupWaitingOrBackground(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::isVoNrEnabled(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::rejectCall(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::responseAcknowledgement() {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::sendBurstDtmf(
      int32_t in_serial, const std::string &in_dtmf, int32_t in_on, int32_t in_off) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::sendCdmaFeatureCode(int32_t in_serial, const std::string &in_featureCode) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::sendDtmf(int32_t in_serial, const std::string &in_s) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::sendUssd(int32_t in_serial, const std::string &in_ussd) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::separateConnection(int32_t in_serial, int32_t in_gsmIndex) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setCallForward(
      int32_t in_serial, const voice::CallForwardInfo &in_callInfo) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setCallWaiting(int32_t in_serial, bool in_enable, int32_t in_serviceClass) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setClir(int32_t in_serial, int32_t in_status) {
    log_debug("STUB: UNSUPPORTED: RadioVoice::%s\n", __func__);
    auto r_info = RESP_OK(in_serial);
    r_info.error = RadioError::REQUEST_NOT_SUPPORTED;

    mRep->setClirResponse(r_info);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setMute(int32_t in_serial, bool in_enable) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setPreferredVoicePrivacy(int32_t in_serial, bool in_enable) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setResponseFunctions(
      const std::shared_ptr< voice::IRadioVoiceResponse> &in_radioVoiceResponse,
      const std::shared_ptr< voice::IRadioVoiceIndication> &in_radioVoiceIndication) {
    log_debug("xRadioVoice::%s\n", __func__);

    mRep = in_radioVoiceResponse;
    mInd = in_radioVoiceIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setTtyMode(int32_t in_serial, voice::TtyMode in_mode) {
    log_debug("xRadioVoice::%s\n", __func__);

    log_debug("(nop) Set TTY mode to %s\n", voice::toString(in_mode).c_str());

    mRep->setTtyModeResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::setVoNrEnabled(int32_t in_serial, bool in_enable) {
    log_debug("STUB: RadioVoice::%s\n", __func__);

    LOG(INFO) << __func__ << ": " << in_enable;
    mRep->setVoNrEnabledResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::startDtmf(int32_t in_serial, const std::string &in_s) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::stopDtmf(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioVoice::switchWaitingOrHoldingAndActive(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioVoice::%s\n", __func__);

    return ndk::ScopedAStatus::ok();
}

void RadioVoice::_handleQmiIndications()
{

}
