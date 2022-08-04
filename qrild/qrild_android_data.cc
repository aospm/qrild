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

#define LOG_TAG "qrild.IData"
#include <android-base/logging.h>

#include <qrild.h>

#include "qrild_radio.hh"

RadioData::RadioData(struct rild_state *state) : mState(state) {
    printf("-RadioData::%s\n", __func__);
}

ndk::ScopedAStatus RadioData::allocatePduSessionId(int32_t in_serial) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::cancelHandover(int32_t in_serial, int32_t in_callId) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::deactivateDataCall(int32_t in_serial, int32_t in_cid, data::DataRequestReason in_reason) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::getDataCallList(int32_t in_serial) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::getSlicingConfig(int32_t in_serial) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::releasePduSessionId(int32_t in_serial, int32_t in_id) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::responseAcknowledgement() {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setDataAllowed(int32_t in_serial, bool in_allow) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setDataProfile(int32_t in_serial, const std::vector<data::DataProfileInfo> &in_profiles) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);

    for (auto profile : in_profiles) {
        LOG(INFO) << "\tprofile: " << profile.toString();
    }

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setDataThrottling(
      int32_t in_serial, data::DataThrottlingAction in_dataThrottlingAction, int64_t in_completionDurationMillis) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setInitialAttachApn(
      int32_t in_serial, const std::optional<data::DataProfileInfo> &in_dataProfileInfo) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setResponseFunctions(
      const std::shared_ptr<data::IRadioDataResponse> &in_radioDataResponse,
      const std::shared_ptr<data::IRadioDataIndication> &in_radioDataIndication) {
    printf("xRadioData::%s\n", __func__);

    mRep = in_radioDataResponse;
    mInd = in_radioDataIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setupDataCall(int32_t in_serial, AccessNetwork in_accessNetwork,
      const data::DataProfileInfo &in_dataProfileInfo, bool in_roamingAllowed, data::DataRequestReason in_reason,
      const std::vector<data::LinkAddress> &in_addresses, const std::vector<std::string> &in_dnses,
      int32_t in_pduSessionId, const std::optional<data::SliceInfo> &in_sliceInfo, bool in_matchAllRuleAllowed) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::startHandover(int32_t in_serial, int32_t in_callId) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::startKeepalive(int32_t in_serial, const data::KeepaliveRequest &in_keepalive) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::stopKeepalive(int32_t in_serial, int32_t in_sessionHandle) {
    printf("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

void RadioData::handleQmiIndications()
{

}
