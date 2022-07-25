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

#include <qrild.h>
#include <qrild_qmi.h>
#include "qmi_nas.h"

#include "qrild_radio.hh"

RadioNetwork::RadioNetwork(struct rild_state *state) : mState(state) {
    printf("xRadioNetwork::%s\n", __func__);

    mRegStateRes.regState = network::RegState::UNKNOWN;
}

ndk::ScopedAStatus RadioNetwork::getAllowedNetworkTypesBitmap(int32_t in_serial) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getAvailableBandModes(int32_t in_serial) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getAvailableNetworks(int32_t in_serial) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getBarringInfo(int32_t in_serial) {
    printf("RadioNetwork::%s\n", __func__);

    LOG(INFO) << __func__ << " TODO!";

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getCdmaRoamingPreference(int32_t in_serial) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getCellInfoList(int32_t in_serial) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getDataRegistrationState(int32_t in_serial) {
    printf("xRadioNetwork::%s\n", __func__);

    LOG(INFO) << __func__ << ": TODO";

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

    int16_t lte_snr;
    struct nas_signal_strength qmi_strength;
    int rc;

    rc = qrild_qmi_nas_get_signal_strength(mState, &qmi_strength, &lte_snr);

    lte.signalStrength = qmi_strength.strength;
    lte.rsrp = 65;
    lte.rsrq = 18;
    lte.rssnr = 16;
    lte.cqi = 13;
    lte.timingAdvance = 647;
    lte.cqiTableIndex = 5;

    LOG(INFO) << __func__ << lte.toString();

    strength.lte = lte;

    // FIXME: stub everything else for now
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

    mRep->getSignalStrengthResponse(RESP_OK(in_serial), strength);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getSystemSelectionChannels(int32_t in_serial) {
    printf("RadioNetwork::%s\n", __func__);
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
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::responseAcknowledgement() {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setAllowedNetworkTypesBitmap(int32_t in_serial, int32_t in_networkTypeBitmap) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setBandMode(int32_t in_serial, network::RadioBandMode in_mode) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setBarringPassword(int32_t in_serial, const std::string &in_facility,
      const std::string &in_oldPassword, const std::string &in_newPassword) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setCdmaRoamingPreference(int32_t in_serial, network::CdmaRoamingType in_type) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setCellInfoListRate(int32_t in_serial, int32_t in_rate) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setIndicationFilter(int32_t in_serial, int32_t in_indicationFilter) {
    printf("xRadioNetwork::%s\n", __func__);
    int32_t filter = in_indicationFilter;
    int32_t filter_bit = 0b1;

    LOG(INFO) << __func__ << " Filters:";

    // FIXME: don't hardcode this!
    while(filter_bit < (int32_t)network::IndicationFilter::BARRING_INFO) {
        if (filter & filter_bit)
            LOG(INFO) << network::toString(network::IndicationFilter(filter & filter_bit));
        filter_bit <<= 1;
    }

    indicationFilter = in_indicationFilter;

    mRep->setIndicationFilterResponse(RESP_OK(in_serial));
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setLinkCapacityReportingCriteria(int32_t in_serial, int32_t in_hysteresisMs,
      int32_t in_hysteresisDlKbps, int32_t in_hysteresisUlKbps, const std::vector<int32_t> &in_thresholdsDownlinkKbps,
      const std::vector<int32_t> &in_thresholdsUplinkKbps, AccessNetwork in_accessNetwork) {
    printf("xRadioNetwork::%s\n", __func__);

    LOG(DEBUG) << __func__ << "(";
    LOG(DEBUG) << "\thysteresisMs: " << in_hysteresisMs;
    LOG(DEBUG) << "\thysteresisDlKbps: " << in_hysteresisDlKbps;
    LOG(DEBUG) << "\thysteresisUlKbps: " << in_hysteresisUlKbps;
    LOG(DEBUG) << "\tthresholdsDownLinkKbps:";
    for(auto thresh : in_thresholdsDownlinkKbps) {
        LOG(DEBUG) << "\t\t" << thresh;
    }
    LOG(DEBUG) << "\tthresholdsUplinkKbps:";
    for(auto thresh : in_thresholdsUplinkKbps) {
        LOG(DEBUG) << "\t\t" << thresh;
    }

    LOG(DEBUG) << "\tAccessNetwork: " << toString(in_accessNetwork);
    LOG(DEBUG) << ");";

    mRep->setLinkCapacityReportingCriteriaResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setLocationUpdates(int32_t in_serial, bool in_enable) {
    printf("RadioNetwork::%s\n", __func__);
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
    printf("RadioNetwork::%s\n", __func__);
    RadioResponseInfo r_info = RESP_OK(in_serial);

    LOG(ERROR) << __func__ << " Can't handle manual network selection!";
    r_info.error = RadioError::OPERATION_NOT_ALLOWED;

    mRep->setNetworkSelectionModeManualResponse(r_info);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setNrDualConnectivityState(
      int32_t in_serial, network::NrDualConnectivityState in_nrDualConnectivityState) {
    printf("RadioNetwork::%s\n", __func__);
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
    for(auto thresh : in_signalThresholdInfos) {
        LOG(DEBUG) << thresh.toString();
    }

    mRep->setSignalStrengthReportingCriteriaResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setSuppServiceNotifications(int32_t in_serial, bool in_enable) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setSystemSelectionChannels(
      int32_t in_serial, bool in_specifyChannels, const std::vector<network::RadioAccessSpecifier> &in_specifiers) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::startNetworkScan(int32_t in_serial, const network::NetworkScanRequest &in_request) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::stopNetworkScan(int32_t in_serial) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::supplyNetworkDepersonalization(int32_t in_serial, const std::string &in_netPin) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setUsageSetting(int32_t in_serial, network::UsageSetting in_usageSetting) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getUsageSetting(int32_t in_serial) {
    printf("RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}