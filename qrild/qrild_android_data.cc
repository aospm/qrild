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

#include "arpa/inet.h"
#include "limits.h"

#define LOG_TAG "qrild.IData"
#include <android-base/logging.h>
#include <q_log.h>

#include "qrild.h"
#include "qrild_qmi.h"
#include "qmi_wds.h"
#include "qrild_link.h"

#include "qrild_radio.hh"

static void _work_setup_data(struct q_work_task *) {
    if (!services.initialised) {
        log_warn("Trying to set up data connection before services initialised!!!!");
    }
    services.data->setup_data_connection();
}

RadioData::RadioData(struct rild_state *state) : mState(state) {
    log_debug("xRadioData::%s\n", __func__);

    setup_data_work.func = _work_setup_data;
}

ndk::ScopedAStatus RadioData::allocatePduSessionId(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::cancelHandover(int32_t in_serial, int32_t in_callId) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::deactivateDataCall(
      int32_t in_serial, int32_t in_cid, data::DataRequestReason in_reason) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::getDataCallList(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::getSlicingConfig(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::releasePduSessionId(int32_t in_serial, int32_t in_id) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::responseAcknowledgement() {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setDataAllowed(int32_t in_serial, bool in_allow) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setDataProfile(
      int32_t in_serial, const std::vector<data::DataProfileInfo> &in_profiles) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);

    LOG(INFO) << "Got data profiles: ";
    for (auto profile : in_profiles) {
        LOG(INFO) << "\tprofile: " << profile.toString();
    }

    q_work_schedule_delayed(&setup_data_work, 50);

    mRep->setDataProfileResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setDataThrottling(int32_t in_serial,
      data::DataThrottlingAction in_dataThrottlingAction, int64_t in_completionDurationMillis) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setInitialAttachApn(
      int32_t in_serial, const std::optional<data::DataProfileInfo> &in_dataProfileInfo) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setResponseFunctions(
      const std::shared_ptr<data::IRadioDataResponse> &in_radioDataResponse,
      const std::shared_ptr<data::IRadioDataIndication> &in_radioDataIndication) {
    log_debug("xRadioData::%s\n", __func__);

    mRep = in_radioDataResponse;
    mInd = in_radioDataIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::setupDataCall(int32_t in_serial, AccessNetwork in_accessNetwork,
      const data::DataProfileInfo &in_dataProfileInfo, bool in_roamingAllowed,
      data::DataRequestReason in_reason, const std::vector<data::LinkAddress> &in_addresses,
      const std::vector<std::string> &in_dnses, int32_t in_pduSessionId,
      const std::optional<data::SliceInfo> &in_sliceInfo, bool in_matchAllRuleAllowed) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::startHandover(int32_t in_serial, int32_t in_callId) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::startKeepalive(
      int32_t in_serial, const data::KeepaliveRequest &in_keepalive) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioData::stopKeepalive(int32_t in_serial, int32_t in_sessionHandle) {
    log_debug("FIXME! TODO: RadioData::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

#define FN_OR_RET(fn, ...)                                                                         \
    ({                                                                                             \
        rc = fn(__VA_ARGS__);                                                                      \
        if (rc) {                                                                                  \
            log_error("%s failed: %d", #fn, rc);                                                   \
            goto out_err;                                                                          \
        }                                                                                          \
    })

// FIXME: implement proper failure recovery if this doesn't go right
RadioError RadioData::setup_data_connection() {
    int rc;
    struct wds_data_settings wds_ds;
    data::SetupDataCallResult result;
    struct wds_start_network_interface_resp_data iface_resp;
    uint32_t data_handle;
    uint32_t prefix;
    data::LinkAddress addr;
    std::vector<data::SetupDataCallResult> res_arr;
    auto state_exp = QDSTATE_DISCONNECTED;
    /*
     * If state is QDSTATE_DISCONNNECTED then atomically change it to QDSTATE_CONNECTING
     * otherwise read the current state into state_exp and return false. Make sure
     * we don't attempt to connect at the same time from different threads.
     */
    log_debug("%s: checking that we aren't already connecting: %d", __func__, mDataState.load());
    if (!mDataState.compare_exchange_weak(state_exp, QDSTATE_CONNECTING)) {
        LOG(DEBUG) << __func__ << ": Connection already in progress, state: " << state_exp;
        return RadioError::INTERNAL_ERR;
    }

    log_debug("%s: start!", __func__);

    FN_OR_RET(qrild_qmi_dpm_open_port, mState);
    FN_OR_RET(qrild_qmi_wds_bind_subscription, mState);
    FN_OR_RET(qrild_qmi_wds_bind_mux_data_port, mState);
    FN_OR_RET(qrild_qmi_wds_start_network_interface, mState, &iface_resp);
    if (!iface_resp.res) {
        LOG(ERROR) << __func__ << ": Couldn't parse response for start_network_interface";
        goto out_err;
    }
    if (iface_resp.res->result) {
        LOG(ERROR) << __func__
                   << ": start_network_interface failed with error: " << iface_resp.res->error
                   << ": " << qmi_error_string(iface_resp.res->error);
        if (iface_resp.res->error == QMI_ERR_NO_EFFECT) {
            LOG(ERROR) << __func__ << ": shouldn't happen! Network interface already started";
            mDataState.store(QDSTATE_ERROR);
        }
        goto out_err;
    }

    data_handle = iface_resp.pkt_data_handle;
    wds_start_network_interface_resp_data_free(&iface_resp);

    log_debug("Waiting for srvc status arrive");
    {
        std::unique_lock lk(mSrvcStatusMtex);
        mSrvctatusArrived.wait(lk); /*, [&state = mDataState](){
                return state == QDSTATE_SRVC_STATUS_ARRIVE4;
            });*/
    }
    log_debug("srvc status arrived!!!");

    FN_OR_RET(qrild_qmi_wds_get_current_settings, mState, &wds_ds);

    rc = qrild_link_configure(&wds_ds.ip, &wds_ds.sub, &wds_ds.brd);
    if (rc < 0) {
        LOG(ERROR) << "\n\n" << __func__ << ": Failed to configure network interfaces!!\n\n";
    }

    prefix = mask_to_prefix(&wds_ds.sub);

    result.cause = data::DataCallFailCause::NONE;
    result.cid = data_handle;
    result.active = data::SetupDataCallResult::DATA_CONNECTION_STATUS_ACTIVE;
    // FIXME: support ipv6
    result.type = data::PdpProtocolType::IP;
    // FIXME: don't hardcode this
    result.ifname = "rmnet_data0";
    addr.address = std::string(inet_ntoa(wds_ds.ip)) + "/" + ::android::internal::ToString(prefix);
    //addr.addressProperties = 0x80; // IFA_F_PERMANENT
    addr.deprecationTime = LONG_MAX;
    addr.expirationTime = LONG_MAX;
    result.addresses.push_back(addr);
    result.gateways.push_back(std::string(inet_ntoa(wds_ds.brd)));
    result.mtuV4 = wds_ds.mtu;
    result.pduSessionId = 0; // Can't find anything about this in public QMI docs

    LOG(DEBUG) << __func__ << ": Configured data call: " << result.toString();

    res_arr.push_back(result);
    mInd->dataCallListChanged(RadioIndicationType::UNSOLICITED, res_arr);

    return RadioError::NONE;

out_err:
    mDataState.store(QDSTATE_DISCONNECTED);

    return RadioError::MODEM_ERR;
}

void RadioData::_handleQmiIndications() {
    log_debug("data: Handing QMI indications");
    struct qrild_msg *msg;
    // FIXME: this feels like not the right way to use a mutex lol
    q_thread_mutex_lock(&mState->msg_mutex);
    list_for_each_entry(msg, &mState->pending_rx, li) {
        if (msg->type != 0x4)
            continue;

        switch (msg->msg_id) {
        case QMI_WDS_PKT_SRVC_STATUS:
            {
                log_debug("Got pkt srvc status indication!");
                std::lock_guard lk(mSrvcStatusMtex);
                // FIXME: pick ARRIVE4/6 based on ip_family in ths srvc status message
                // FIXME: use compare_exchange_weak() "just in case"?
                mDataState.store(QDSTATE_SRVC_STATUS_ARRIVE4);
            }
            log_debug("Notifying mSrvcStatusArrived");
            mSrvctatusArrived.notify_all();
            break;
        default:
            break;
        }
    }
    q_thread_mutex_unlock(&mState->msg_mutex);
}
