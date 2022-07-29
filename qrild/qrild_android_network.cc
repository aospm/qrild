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

#define LOG_TAG "qrild.INetwork"
#include <android-base/logging.h>

#include <limits.h>

#include <libqrtr.h>
#include <qrild.h>
#include <qrild_qmi.h>
#include <qrild_msg.h>
#include "qmi_nas.h"

#include "qrild_radio.hh"
#include <list.h>

RadioNetwork::RadioNetwork(struct rild_state *state) : mState(state) {
    printf("xRadioNetwork::%s\n", __func__);
    int rc;

    mRegStateRes.regState = network::RegState::UNKNOWN;
    rc = qrild_qmi_nas_register_indications(mState);
    if (rc) {
        fprintf(stderr, "Failed to register NAS indications!");
        mState->exit = true;
    }
}

ndk::ScopedAStatus RadioNetwork::getAllowedNetworkTypesBitmap(int32_t in_serial) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getAvailableBandModes(int32_t in_serial) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getAvailableNetworks(int32_t in_serial) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getBarringInfo(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);
    network::CellIdentityLte i_lte;
    network::CellIdentity ident(i_lte);
    auto band = network::EutranBands::BAND_1;
    std::vector<network::BarringInfo> v_bi;
    network::BarringInfo bi;
    auto r_info = RESP_OK(in_serial);
    struct nas_get_lte_cphy_ca_info_resp_data ca_info;
    int rc;

    rc = qrild_qmi_nas_get_lte_cphy_ca_info(mState, &ca_info);
    if (rc) {
        LOG(ERROR) << __func__ << ": Couldn't get lte CPhy CA info";
        switch(rc) {
        case QMI_ERR_INFO_UNAVAILABLE:
            r_info.error = RadioError::RADIO_NOT_AVAILABLE;
            break;
        default:
            r_info.error = RadioError::INTERNAL_ERR;
            break;
        }
        mRep->getBarringInfoResponse(r_info, network::CellIdentity(), v_bi);
    }
    if (ca_info.res->result) {
        switch(ca_info.res->error) {
        case QMI_ERR_INFO_UNAVAILABLE:
            goto no_info;
        }
    }

    LOG(DEBUG) << __func__ << ": Got physical cell ID " << ca_info.phy_scell_info->pci;

    // FIXME: can be unknown but should probably set (and get from modem!!!)
    //i_lte.mcc = 234;
    //i_lte.mnc = 20;
    i_lte.ci = INT_MAX;
    i_lte.pci = ca_info.phy_scell_info->pci;
    i_lte.tac = INT_MAX;
    // FIXME: aidl says this is 18-bit but QMI is only 16-bit, is this correct??
    i_lte.earfcn = ca_info.phy_scell_info->rx_chan;
    i_lte.operatorNames = network::OperatorInfo{ "Three.co.uk", "3", "23420",
        network::OperatorInfo::STATUS_CURRENT };
    
    // FIXME: is ca_info.phy_scell_info->dl_bandwidth the right thing to use??
    switch(ca_info.phy_scell_info->dl_bandwidth) {
    case QMI_NAS_DL_BANDWIDTH_1_4:
        i_lte.bandwidth = 1400;
        break;
    case QMI_NAS_DL_BANDWIDTH_3:
        i_lte.bandwidth = 3000;
        break;
    case QMI_NAS_DL_BANDWIDTH_5:
        i_lte.bandwidth = 5000;
        break;
    case QMI_NAS_DL_BANDWIDTH_10:
        i_lte.bandwidth = 10000;
        break;
    case QMI_NAS_DL_BANDWIDTH_15:
        i_lte.bandwidth = 15000;
        break;
    case QMI_NAS_DL_BANDWIDTH_20:
        i_lte.bandwidth = 20000;
        break;
    case QMI_NAS_DL_BANDWIDTH_INVALID:
    default:
        LOG(WARNING) << __func__ << "Got invalid LTE DL bandwidth!";
        i_lte.bandwidth = 11111;
        break;
    }
    
    i_lte.additionalPlmns = std::vector<std::string>();

    LOG(DEBUG) << __func__ << ": Have LTE band: " << ca_info.phy_scell_info->lte_band;

    // FIXME: This is awful lol, at least import QmiNasActiveBand enum
    // FIXME: This should be all the bands for this tower, not just the active one
    if(ca_info.phy_scell_info->lte_band >= 120)
        band = network::EutranBands(ca_info.phy_scell_info->lte_band - 119);

    i_lte.bands = std::vector<network::EutranBands>();
    i_lte.bands.push_back(band);

    // FIXME: this is a cursed union class which intellisense hates
    // the aidl generator needs to do better
    ident = network::CellIdentity(i_lte);

no_info:

    bi.barringType = network::BarringInfo::BARRING_TYPE_NONE;
    v_bi.push_back(bi);

    mRep->getBarringInfoResponse(r_info, ident, v_bi);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getCdmaRoamingPreference(int32_t in_serial) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getCellInfoList(int32_t in_serial) {
    printf("FIXME! WIP: RadioNetwork::%s\n", __func__);
    auto cellInfo = std::vector<network::CellInfo>();

    LOG(ERROR) << "\n\n\n===============\n" << __func__ << "\n\tDO THIS NEXT!!! subid is -1 because we don't report data here, android needs to know about cell tower connections to actually register a change and detect the proper subscription info ID!\n\n\n";

    cellInfo.push_back(network::CellInfo{false, network::CellConnectionStatus::NONE});

    mRep->getCellInfoListResponse(RESP_OK(in_serial), cellInfo);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getDataRegistrationState(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);

    LOG(INFO) << __func__ << ": TODO! return: " << mRegStateRes.toString();

    mRep->getDataRegistrationStateResponse(RESP_OK(in_serial), mRegStateRes);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getImsRegistrationState(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);
    network::RegStateResult res;

    res.regState = network::RegState::UNKNOWN;

    mRep->getImsRegistrationStateResponse(RESP_OK(in_serial), false, RadioTechnologyFamily());
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getNetworkSelectionMode(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);

    mRep->getNetworkSelectionModeResponse(RESP_OK(in_serial), false);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getOperator(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);

    LOG(INFO) << __func__ << " FIXME: hardcoded values";

    // Not sure if correct mcc/mnc
    mRep->getOperatorResponse(RESP_OK(in_serial), "Three.co.uk", "3", "23420");

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getSignalStrength(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);
    auto strength = network::SignalStrength();
    auto gsm = network::GsmSignalStrength();
    auto cdma = network::CdmaSignalStrength();
    auto evdo = network::EvdoSignalStrength();
    auto lte = network::LteSignalStrength();
    auto tdscdma = network::TdscdmaSignalStrength();
    auto wcdma = network::WcdmaSignalStrength();
    auto nr = network::NrSignalStrength();
    auto r_info = RESP_OK(in_serial);

    int16_t lte_snr;
    struct nas_get_signal_strength_resp_data qmi_strength;
    int rc;

    // FIXME: stub everything except LTE
    gsm.signalStrength = INT_MAX;
    gsm.timingAdvance = INT_MAX;
    gsm.bitErrorRate = INT_MAX;
    strength.gsm = gsm;

    cdma.dbm = INT_MAX;
    cdma.ecio = INT_MAX;
    strength.cdma = cdma;

    evdo.dbm = INT_MAX;
    evdo.signalNoiseRatio = INT_MAX;
    evdo.ecio = INT_MAX;
    strength.evdo = evdo;

    tdscdma.bitErrorRate = INT_MAX;
    tdscdma.rscp = INT_MAX;
    tdscdma.signalStrength = INT_MAX;
    strength.tdscdma = tdscdma;

    wcdma.bitErrorRate = INT_MAX;
    wcdma.signalStrength = INT_MAX;
    wcdma.rscp = INT_MAX;
    wcdma.ecno = INT_MAX;
    strength.wcdma = wcdma;

    nr.csiCqiReport = std::vector<uint8_t>();
    nr.csiCqiReport.push_back(0xFF);
    nr.csiCqiTableIndex = INT_MAX;
    nr.csiRsrp = INT_MAX;
    nr.csiRsrq = INT_MAX;
    nr.csiSinr = INT_MAX;
    nr.ssRsrp = INT_MAX;
    nr.ssRsrq = INT_MAX;
    nr.ssSinr = INT_MAX;
    strength.nr = nr;

    rc = qrild_qmi_nas_get_signal_strength(mState, &qmi_strength);
    if (rc < 0){
        LOG(ERROR) << __func__ << ": Couldn't get signal strength";
    }
    if (qmi_strength.res->result) {
        switch(qmi_strength.res->error) {
        case QMI_ERR_INFO_UNAVAILABLE:
            // Not an "error", we just have no signal
            lte.signalStrength = INT_MAX;
            goto out;
        }
    }

    lte.signalStrength = qmi_strength.strength->strength;
    lte.rsrp = 65;
    lte.rsrq = 18;
    lte.rssnr = 16;
    lte.cqi = 13;
    lte.timingAdvance = 647;
    lte.cqiTableIndex = 5;

    LOG(INFO) << __func__ << lte.toString();

    strength.lte = lte;

out:
    mRep->getSignalStrengthResponse(r_info, strength);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getSystemSelectionChannels(int32_t in_serial) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getVoiceRadioTechnology(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);
    RadioResponseInfo r_info = RESP_OK(in_serial);
    r_info.error = RadioError::REQUEST_NOT_SUPPORTED;

    mRep->getVoiceRadioTechnologyResponse(RESP_OK(in_serial), RadioTechnology::UNKNOWN);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getVoiceRegistrationState(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);
    network::RegStateResult res;

    LOG(INFO) << __func__ << " FIXME: Always reporting unknown state";
    res.regState = network::RegState::UNKNOWN;

    mRep->getVoiceRegistrationStateResponse(RESP_OK(in_serial), res);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::isNrDualConnectivityEnabled(int32_t in_serial) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::responseAcknowledgement() {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setAllowedNetworkTypesBitmap(
      int32_t in_serial, int32_t in_networkTypeBitmap) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setBandMode(int32_t in_serial, network::RadioBandMode in_mode) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setBarringPassword(int32_t in_serial,
      const std::string &in_facility, const std::string &in_oldPassword,
      const std::string &in_newPassword) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setCdmaRoamingPreference(
      int32_t in_serial, network::CdmaRoamingType in_type) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setCellInfoListRate(int32_t in_serial, int32_t in_rate) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setIndicationFilter(
      int32_t in_serial, int32_t in_indicationFilter) {
    printf("xRadioNetwork::%s\n", __func__);
    int32_t filter = in_indicationFilter;
    int32_t filter_bit = 0b1;

    LOG(INFO) << __func__ << " Filters:";

    // FIXME: don't hardcode this!
    while (filter_bit < (int32_t)network::IndicationFilter::BARRING_INFO) {
        if (filter & filter_bit)
            LOG(INFO) << network::toString(network::IndicationFilter(filter & filter_bit));
        filter_bit <<= 1;
    }

    indicationFilter = in_indicationFilter;

    mRep->setIndicationFilterResponse(RESP_OK(in_serial));
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setLinkCapacityReportingCriteria(int32_t in_serial,
      int32_t in_hysteresisMs, int32_t in_hysteresisDlKbps, int32_t in_hysteresisUlKbps,
      const std::vector<int32_t> &in_thresholdsDownlinkKbps,
      const std::vector<int32_t> &in_thresholdsUplinkKbps, AccessNetwork in_accessNetwork) {
    printf("xRadioNetwork::%s\n", __func__);

    LOG(DEBUG) << __func__ << "(";
    LOG(DEBUG) << "\thysteresisMs: " << in_hysteresisMs;
    LOG(DEBUG) << "\thysteresisDlKbps: " << in_hysteresisDlKbps;
    LOG(DEBUG) << "\thysteresisUlKbps: " << in_hysteresisUlKbps;
    LOG(DEBUG) << "\tthresholdsDownLinkKbps:";
    for (auto thresh : in_thresholdsDownlinkKbps) {
        LOG(DEBUG) << "\t\t" << thresh;
    }
    LOG(DEBUG) << "\tthresholdsUplinkKbps:";
    for (auto thresh : in_thresholdsUplinkKbps) {
        LOG(DEBUG) << "\t\t" << thresh;
    }

    LOG(DEBUG) << "\tAccessNetwork: " << toString(in_accessNetwork);
    LOG(DEBUG) << ");";

    mRep->setLinkCapacityReportingCriteriaResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setLocationUpdates(int32_t in_serial, bool in_enable) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setNetworkSelectionModeAutomatic(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);

    LOG(INFO) << __func__;

    mRep->setNetworkSelectionModeAutomaticResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setNetworkSelectionModeManual(
      int32_t in_serial, const std::string &in_operatorNumeric, AccessNetwork in_ran) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    RadioResponseInfo r_info = RESP_OK(in_serial);

    LOG(ERROR) << __func__ << " Can't handle manual network selection!";
    r_info.error = RadioError::OPERATION_NOT_ALLOWED;

    mRep->setNetworkSelectionModeManualResponse(r_info);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setNrDualConnectivityState(
      int32_t in_serial, network::NrDualConnectivityState in_nrDualConnectivityState) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setResponseFunctions(
      const std::shared_ptr<network::IRadioNetworkResponse> &in_radioNetworkResponse,
      const std::shared_ptr<network::IRadioNetworkIndication> &in_radioNetworkIndication) {
    printf("xRadioNetwork::%s\n", __func__);

    mRep = in_radioNetworkResponse;
    mInd = in_radioNetworkIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setSignalStrengthReportingCriteria(
      int32_t in_serial, const std::vector<network::SignalThresholdInfo> &in_signalThresholdInfos) {
    printf("xRadioNetwork::%s\n", __func__);

    LOG(DEBUG) << __func__;
    for (auto thresh : in_signalThresholdInfos) {
        LOG(DEBUG) << thresh.toString();
    }

    mRep->setSignalStrengthReportingCriteriaResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setSuppServiceNotifications(int32_t in_serial, bool in_enable) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setSystemSelectionChannels(int32_t in_serial,
      bool in_specifyChannels, const std::vector<network::RadioAccessSpecifier> &in_specifiers) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::startNetworkScan(
      int32_t in_serial, const network::NetworkScanRequest &in_request) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::stopNetworkScan(int32_t in_serial) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::supplyNetworkDepersonalization(
      int32_t in_serial, const std::string &in_netPin) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setUsageSetting(
      int32_t in_serial, network::UsageSetting in_usageSetting) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getUsageSetting(int32_t in_serial) {
    printf("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

void RadioNetwork::reportSystemStatus(struct qrild_msg *serving_system_ind)
{
    struct nas_serving_system_ind_msg status;
    int rc;
    memset(&status, 0, sizeof(struct nas_serving_system_ind_msg));

    rc = qrild_qmi_nas_parse_serving_system_ind(mState, serving_system_ind, &status);
    if (rc < 0) {
        fprintf(stderr, "Couldn't parse serving system report!");
        return;
    }

    LOG(INFO) << __func__ << ": FIXME! implement this";
}

void RadioNetwork::handleQmiIndications()
{
    struct qrild_msg *msg;
    list_for_each_entry(msg, &mState->pending_rx, li)
    {
        if (msg->type != 0x4)
            continue;
        switch(msg->msg_id) {
        case QMI_NAS_SERVING_SYSTEM_REPORT:
            reportSystemStatus(msg);
            
            break;
        default:
            break;
        }
    }
}
