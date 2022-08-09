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
#include <q_log.h>

#include <limits.h>

#include <libqrtr.h>
#include <qrild.h>
#include <qrild_qmi.h>
#include <qrild_msg.h>
#include <qmi_nas.h>

#include "qrild_radio.hh"
#include <aidl/android/hardware/radio/RadioAccessFamily.h>
#include <aidl/android/hardware/radio/network/CellConnectionStatus.h>
#include <aidl/android/hardware/radio/network/CellInfoRatSpecificInfo.h>
#include <list.h>

RadioNetwork::RadioNetwork(struct rild_state *state) : mState(state) {
    log_debug("xRadioNetwork::%s\n", __func__);
    int rc;

    mRegStateRes.regState = network::RegState::UNKNOWN;

    mLastCellInfoListUpdateMs = 0;
}

ndk::ScopedAStatus RadioNetwork::getAllowedNetworkTypesBitmap(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getAvailableBandModes(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getAvailableNetworks(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getBarringInfo(int32_t in_serial) {
    log_debug("xRadioNetwork::%s\n", __func__);
    network::CellIdentityLte i_lte;
    network::CellIdentity ident(i_lte);
    auto band = network::EutranBands::BAND_1;
    std::vector<network::BarringInfo> v_bi;
    network::BarringInfo bi;
    auto r_info = RESP_OK(in_serial);
    struct nas_get_lte_cphy_ca_info_resp_data data;
    int rc;

    rc = qrild_qmi_nas_get_lte_cphy_ca_info(mState, &data);
    if (rc < 0) {
        LOG(ERROR) << __func__ << ": Couldn't get lte CPhy CA info";
        r_info.error = RadioError::INTERNAL_ERR;
        goto no_info;
    }
    if (data.res->result) {
        LOG(ERROR) << __func__ << ": modem returned error: " << (int)data.res->error;
        switch (data.res->error) {
        case QMI_ERR_INFORMATION_UNAVAILABLE:
            r_info.error = RadioError::RADIO_NOT_AVAILABLE;
            break;
        default:
            r_info.error = RadioError::INTERNAL_ERR;
            break;
        }
        goto no_info;
    }

    LOG(INFO) << __func__ << ": Got physical cell ID " << data.phy_scell_info->pci;

    // FIXME: can be unknown but should probably set (and get from modem!!!)
    //i_lte.mcc = 234;
    //i_lte.mnc = 20;
    i_lte.ci = INT_MAX;
    i_lte.pci = data.phy_scell_info->pci;
    i_lte.tac = INT_MAX;
    // FIXME: aidl says this is 18-bit but QMI is only 16-bit, is this correct??
    i_lte.earfcn = data.phy_scell_info->rx_chan;
    i_lte.operatorNames = network::OperatorInfo{ "Three.co.uk", "3", "23420",
        network::OperatorInfo::STATUS_CURRENT };

    // FIXME: is data.phy_scell_info->dl_bandwidth the right thing to use??
    switch (data.phy_scell_info->dl_bandwidth) {
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

    LOG(DEBUG) << __func__ << ": Have LTE band: " << data.phy_scell_info->lte_band;

    // FIXME: This is awful lol, at least import QmiNasActiveBand enum
    // FIXME: This should be all the bands for this tower, not just the active one
    if (data.phy_scell_info->lte_band >= 120)
        band = network::EutranBands(data.phy_scell_info->lte_band - 119);

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
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

static bool getSignalStrengthGsm(
      struct nas_get_signal_strength_resp_data *data, network::GsmSignalStrength &gsm) {
    gsm.signalStrength = INT_MAX;
    gsm.timingAdvance = INT_MAX;
    gsm.bitErrorRate = INT_MAX;

    if (data->strength->interface != QMI_NAS_RADIO_INTERFACE_GSM)
        return false;

    gsm.signalStrength = data->strength->strength;

    return true;
}

static bool getSignalStrengthLte(
      struct nas_get_signal_strength_resp_data *data, network::LteSignalStrength &lte) {
    lte.signalStrength = INT_MAX;
    lte.rsrp = INT_MAX;
    lte.rsrq = INT_MAX;
    lte.rssnr = INT_MAX;
    lte.cqi = INT_MAX;
    lte.timingAdvance = INT_MAX;
    lte.cqiTableIndex = INT_MAX;

    if (data->strength->interface != QMI_NAS_RADIO_INTERFACE_LTE)
        return false;

    return true;
}

// FIXME: Move this somewhere in QMI land
static void printServingSystem(struct nas_serving_system_resp_data *stat) {
    std::string interfaces;
    std::string lac = "invalid";
    std::string cid = "invalid";
    for (int i = 0; i < stat->system->radio_interfaces_n; i++)
        interfaces +=
              toString(QmiNasRadioInterfaceToRadioTechnology(stat->system->radio_interfaces[i])) +
              " ";
    if (stat->lac_valid)
        lac = ::android::internal::ToString(stat->lac);
    if (stat->cid_valid)
        cid = ::android::internal::ToString(stat->cid);
    LOG(INFO)
          << __func__ << ": System {"
          << "regState: " << network::toString(network::RegState(stat->system->registration_state))
          << ", cs_attach: " << (int)stat->system->cs_attach_state
          << ", ps_attach: " << (int)stat->system->ps_attach_state
          << ", selectedNetwork: " << (int)stat->system->selected_network
          << ", interfaces: " << (int)stat->system->radio_interfaces_n << ": " << interfaces
          << ", lac: " << lac << ", cid: " << cid << "}";
}

// FIXME: This is awful and ugly and needs a much better implementation
static void nasServingSystemIndToResp(
      struct nas_serving_system_ind_data *ind, struct nas_serving_system_resp_data *resp) {
    if (sizeof(struct nas_serving_system_resp_data) !=
          sizeof(struct nas_serving_system_ind_data) + sizeof(struct qmi_response_type_v01 *)) {
        log_error(
              "FATAL: serving system indication and response message structs have mismatching sizes!");
        LOG(ERROR)
              << __func__
              << "FATAL: serving system indication and response message structs have mismatching sizes!";
        return;
    }
    resp->system_valid = ind->system_valid;
    resp->system = ind->system;
    resp->data_service_cap_valid = ind->data_service_cap_valid;
    resp->data_service_cap_n = ind->data_service_cap_n;
    resp->data_service_cap = ind->data_service_cap;
    resp->plmn_valid = ind->plmn_valid;
    resp->plmn = ind->plmn;
    resp->lac_valid = ind->lac_valid;
    resp->lac = ind->lac;
    resp->cid_valid = ind->cid_valid;
    resp->cid = ind->cid;
    resp->status_valid = ind->status_valid;
    resp->status = ind->status;
}

network::CellInfoGsm RadioNetwork::createCellInfoGsm(struct nas_get_cell_loc_info_data *loc) {
    auto info = network::CellInfoGsm();

    return info;
}

network::CellInfoWcdma RadioNetwork::createCellInfoWcdma(struct nas_get_cell_loc_info_data *loc) {
    auto info = network::CellInfoWcdma();
    struct nas_get_signal_strength_resp_data strength;
    int rc;

    updateOperatorInfo();

    auto &mccmnc = mOperator.operatorNumeric;
    if (mccmnc.length() >= 5 && mOperator.status == network::OperatorInfo::STATUS_CURRENT) {
        info.cellIdentityWcdma.mcc = mccmnc.substr(0, 3);
        info.cellIdentityWcdma.mnc = mccmnc.substr(3, mccmnc.length() - 3);
    }

    if (!loc->umts_valid) {
        LOG(ERROR) << __func__ << ": UMTS location info invalid!";
        return info;
    }

    info.cellIdentityWcdma.lac = loc->umts->lac;
    info.cellIdentityWcdma.cid = loc->umts->cell_id;
    info.cellIdentityWcdma.psc = loc->umts->psc;
    info.cellIdentityWcdma.uarfcn = loc->umts->abs_channel_num;
    info.cellIdentityWcdma.operatorNames = mOperator;
    info.cellIdentityWcdma.additionalPlmns = std::vector<std::string>();

    // FIXME: don't do this here, do it somewhere generic
    rc = qrild_qmi_nas_get_signal_strength(mState, &strength);
    if (rc < 0 || strength.res->result) {
        LOG(ERROR) << __func__ << ": Failed to get signal strength. rc: " << rc
                   << ", QMI err (if applicable): " << strength.res->error << ": "
                   << qmi_error_string(strength.res->error);
        return info;
    }

    auto &wcdma = info.signalStrengthWcdma;
    wcdma.signalStrength = INT_MAX;
    wcdma.bitErrorRate = INT_MAX;
    wcdma.rscp = INT_MAX;
    wcdma.ecno = INT_MAX;

    if (strength.strength->interface != QMI_NAS_RADIO_INTERFACE_UMTS) {
        LOG(ERROR) << __func__ << ": Signal strength is for wrong interface!";
        return info;
    }

    for (int i = 0; i < strength.err_rate_list_n; i++)
        if (strength.err_rate_list[i].interface | QMI_NAS_RADIO_INTERFACE_UMTS)
            wcdma.bitErrorRate = strength.err_rate_list[i].val;

    wcdma.rscp = loc->umts->rscp;
    // FIXME: unreported, maybe undocumented QMI cmd?
    //wcdma.ecno = loc->umts->ecio

    return info;
}

network::CellInfoLte RadioNetwork::createCellInfoLte(struct nas_get_cell_loc_info_data *loc) {
    auto info = network::CellInfoLte();

    LOG(ERROR) << "FIXME: LTE cell info not implemented!";

    return info;
}

int RadioNetwork::updateCellInfo(struct nas_serving_system_ind_data *ss) {
    network::CellInfo &c = mCellInfo;
    struct nas_serving_system_resp_data s;
    struct nas_get_cell_loc_info_data loc;
    RadioTechnology rat;
    int rc;
    // FIXME: This is awful and ugly and needs something better
    if (ss) {
        nasServingSystemIndToResp(ss, &s);
    } else {
        rc = qrild_qmi_nas_get_serving_system(mState, &s);
        if (rc < 0) {
            LOG(ERROR) << __func__ << ": Couldn't get serving system";
            return -1;
        }
        if (s.res->result) {
            LOG(ERROR) << __func__
                       << ": Couldn't get serving system, modem returned error: " << s.res->error
                       << ":  " << qmi_error_string(s.res->error);
            return -1;
        }
        if (!s.system_valid) {
            log_error("%s: Couldn't parse serving system TLV\n", __func__);
            return -1;
        }
    }

    c.registered = s.system->registration_state == QMI_NAS_REGISTRATION_STATE_REGISTERED;
    c.connectionStatus = network::CellConnectionStatus::NONE;
    if (c.registered) {
        if (s.system->cs_attach_state == QMI_NAS_ATTACH_STATE_ATTACHED)
            c.connectionStatus = network::CellConnectionStatus::PRIMARY_SERVING;
        else if (s.system->ps_attach_state == QMI_NAS_ATTACH_STATE_ATTACHED)
            c.connectionStatus = network::CellConnectionStatus::SECONDARY_SERVING;
    }

    if (!s.system->radio_interfaces_n || !s.system->radio_interfaces[0]) {
        LOG(DEBUG) << __func__ << ": Not connected!";
        return 1;
    }

    rc = qrild_qmi_nas_get_cell_loc_info(mState, &loc);
    if (rc < 0 || loc.res->result) {
        LOG(ERROR) << __func__ << ": Failed to get cell location info. rc: " << rc
                   << ", QMI err (if applicable): " << loc.res->error << ": "
                   << qmi_error_string(loc.res->error);
        return -1;
    }

    switch (QmiNasRadioInterfaceToRadioTechnology(s.system->radio_interfaces[0])) {
    case RadioTechnology::GSM:
        c.ratSpecificInfo = network::CellInfoRatSpecificInfo(createCellInfoGsm(&loc));
        break;
    case RadioTechnology::UMTS:
        c.ratSpecificInfo = network::CellInfoRatSpecificInfo(createCellInfoWcdma(&loc));
        break;
    case RadioTechnology::LTE:
        c.ratSpecificInfo = network::CellInfoRatSpecificInfo(createCellInfoLte(&loc));
        break;
    default:
        LOG(WARNING)
              << __func__ << ": Don't understand radio tech: "
              << toString(QmiNasRadioInterfaceToRadioTechnology(s.system->radio_interfaces[0]));
    }

    log_debug("Before return");

    return 0;
}

ndk::ScopedAStatus RadioNetwork::getCellInfoList(int32_t in_serial) {
    log_debug("WIP: RadioNetwork::%s\n", __func__);
    auto cellInfo = std::vector<network::CellInfo>();

    updateCellInfo();
    cellInfo.push_back(mCellInfo);

    LOG(INFO) << __func__ << ": " << mCellInfo.toString();

    mRep->getCellInfoListResponse(RESP_OK(in_serial), cellInfo);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getDataRegistrationState(int32_t in_serial) {
    log_debug("xRadioNetwork::%s\n", __func__);

    LOG(INFO) << __func__ << ": TODO! return: " << mRegStateRes.toString();

    mRep->getDataRegistrationStateResponse(RESP_OK(in_serial), mRegStateRes);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getImsRegistrationState(int32_t in_serial) {
    log_debug("xRadioNetwork::%s\n", __func__);
    network::RegStateResult res;

    res.regState = network::RegState::UNKNOWN;

    mRep->getImsRegistrationStateResponse(RESP_OK(in_serial), false, RadioTechnologyFamily());
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getNetworkSelectionMode(int32_t in_serial) {
    log_debug("xRadioNetwork::%s\n", __func__);
    struct nas_get_system_prefs_data data;
    auto r_info = RESP_OK(in_serial);
    bool selection_manual = false;
    int rc;

    rc = qrild_qmi_nas_get_system_prefs(mState, &data);
    if (rc < 0) {
        LOG(ERROR) << __func__ << ": Couldn't get system preferences: " << rc;
        r_info.error = RadioError::RADIO_NOT_AVAILABLE;
        goto out;
    }
    if (data.res->result) {
        LOG(ERROR) << __func__ << ": Modem returned error: " << (int)data.res->error;
        r_info.error = RadioError::MODEM_ERR;
        goto out;
    }
    if (!data.network_selection_valid) {
        LOG(ERROR) << __func__ << ": Couldn't get network selection";
        r_info.error = RadioError::INTERNAL_ERR;
        goto out;
    }

    selection_manual = !!data.network_selection;
    LOG(DEBUG) << __func__ << ": Manual selection? " << selection_manual;

out:
    mRep->getNetworkSelectionModeResponse(r_info, selection_manual);
    return ndk::ScopedAStatus::ok();
}

RadioError RadioNetwork::updateOperatorInfo() {
    struct nas_get_operator_name_resp_data data;
    struct nas_plmn_id plmn_id;
    struct nas_get_plmn_name_req_data plmn_req;
    struct nas_get_plmn_name_resp_data plmn_data;
    std::string long_name, short_name, mcc, mnc;
    int rc, i;
    RadioError err;

    rc = qrild_qmi_nas_get_operator_name(mState, &data);
    if (rc < 0) {
        LOG(ERROR) << __func__ << ": Failed to request operator name";
        err = RadioError::RADIO_NOT_AVAILABLE;
        goto out_err;
        goto out_err;
    }
    if (data.res->result) {
        LOG(ERROR) << __func__ << ": Modem responded with error: " << (int)data.res->error;
        switch (data.res->error) {
        case QMI_ERR_INFORMATION_UNAVAILABLE:
            err = RadioError::REQUEST_NOT_SUPPORTED;
            goto out_err;
        default:
            err = RadioError::MODEM_ERR;
            goto out_err;
        }
    }

    if (!data.operator_plmns_valid) {
        LOG(ERROR) << __func__ << ": No PLMN provided";
        err = RadioError::MODEM_ERR;
        goto out_err;
    }

    for (i = 0; i < 3; i++) {
        mcc += data.operator_plmns->operators[0].mcc[i];
        if (data.operator_plmns->operators[0].mnc[i] != 'F')
            mnc += data.operator_plmns->operators[0].mnc[i];
    }

    LOG(DEBUG) << __func__ << ": Got MCC: " << mcc << ", MNC: " << mnc;

    // FIXME: Exceptions disabled, add a check here
    plmn_id.mcc = std::stoi(mcc);
    plmn_id.mnc = std::stoi(mnc);

    plmn_req.plmn = &plmn_id;
    plmn_req.send_all_info = true;
    plmn_req.send_all_info_valid = true;

    rc = qrild_qmi_nas_get_plmn_name(mState, &plmn_req, &plmn_data);
    if (rc < 0) {
        LOG(ERROR) << __func__ << ": Failed to request plmn name";
        err = RadioError::RADIO_NOT_AVAILABLE;
        goto out_err;
    }
    if (data.res->result) {
        LOG(ERROR) << __func__ << ": Modem responded with error: " << (int)data.res->error;
        err = RadioError::SYSTEM_ERR;
        goto out_err;
    }

    if (!plmn_data.plmn_name_valid) {
        LOG(ERROR) << __func__ << ": No PLMN name provided";
        err = RadioError::SYSTEM_ERR;
        goto out_err;
    }

    // Sure hope encoding is ASCII and not one of the other two ...
    long_name =
          std::string((char *)plmn_data.plmn_name->long_name, plmn_data.plmn_name->long_name_n);

    short_name =
          std::string((char *)plmn_data.plmn_name->short_name, plmn_data.plmn_name->short_name_n);

    mOperator.alphaLong = long_name;
    mOperator.alphaShort = short_name;
    mOperator.operatorNumeric = mcc + mnc;
    mOperator.status = network::OperatorInfo::STATUS_CURRENT;

    return RadioError::NONE;

out_err:
    mOperator = network::OperatorInfo();
    mOperator.status = network::OperatorInfo::STATUS_UNKNOWN;
    return RadioError::INTERNAL_ERR;
}

ndk::ScopedAStatus RadioNetwork::getOperator(int32_t in_serial) {
    log_debug("xRadioNetwork::%s\n", __func__);
    auto r_info = RESP_OK(in_serial);

    r_info.error = updateOperatorInfo();

    mRep->getOperatorResponse(r_info, mOperator.alphaLong, mOperator.alphaShort,  mOperator.operatorNumeric);

    return ndk::ScopedAStatus::ok();

out_err:
    mOperator = network::OperatorInfo();
    mOperator.status = network::OperatorInfo::STATUS_UNKNOWN;
    mRep->getOperatorResponse(r_info, "", "", "");
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getSignalStrength(int32_t in_serial) {
    log_debug("xRadioNetwork::%s\n", __func__);
    auto strength = network::SignalStrength();
    auto gsm = network::GsmSignalStrength();
    auto cdma = network::CdmaSignalStrength();
    auto evdo = network::EvdoSignalStrength();
    auto lte = network::LteSignalStrength();
    auto tdscdma = network::TdscdmaSignalStrength();
    auto nr = network::NrSignalStrength();
    auto wcdmaCellInfo = network::CellInfoWcdma();
    auto r_info = RESP_OK(in_serial);

    int16_t lte_snr;
    struct nas_get_signal_strength_resp_data qmi_strength;
    struct nas_get_cell_loc_info_data loc;
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

    rc = qrild_qmi_nas_get_cell_loc_info(mState, &loc);
    if (rc < 0) {
        LOG(ERROR) << __func__ << ": Failed to get cell location info. rc: " << rc
                   << ", QMI err (if applicable): " << loc.res->error << ": "
                   << qmi_error_string(loc.res->error);
        r_info.error = RadioError::MODEM_ERR;
    }
    if (loc.res && loc.res->result) {
        switch(loc.res->error) {
            case QMI_ERR_NO_NETWORK_FOUND:
                r_info.error = RadioError::NO_NETWORK_FOUND;
                goto out;
            default:
                r_info.error = RadioError::INTERNAL_ERR;
                goto out;
        }
    }
    wcdmaCellInfo = createCellInfoWcdma(&loc);

    strength.wcdma = wcdmaCellInfo.signalStrengthWcdma;

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
    if (rc < 0) {
        LOG(ERROR) << __func__ << ": Couldn't get signal strength";
    }
    if (!qmi_strength.res)
        goto out;
    if (qmi_strength.res->result) {
        switch (qmi_strength.res->error) {
        case QMI_ERR_INFORMATION_UNAVAILABLE:
            // Not an "error", we just have no signal
            lte.signalStrength = INT_MAX;
            goto out;
        }
    }

    qrild_qmi_nas_show_signal_strength(&qmi_strength);

    lte.signalStrength = qmi_strength.strength->strength;
    lte.rsrp = 65;
    lte.rsrq = 18;
    lte.rssnr = 16;
    lte.cqi = 13;
    lte.timingAdvance = 647;
    lte.cqiTableIndex = 5;

    strength.lte = lte;

    LOG(INFO) << __func__ << ": " << strength.toString();

out:
    mRep->getSignalStrengthResponse(r_info, strength);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getSystemSelectionChannels(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getVoiceRadioTechnology(int32_t in_serial) {
    log_debug("xRadioNetwork::%s\n", __func__);
    RadioResponseInfo r_info = RESP_OK(in_serial);
    r_info.error = RadioError::REQUEST_NOT_SUPPORTED;

    mRep->getVoiceRadioTechnologyResponse(RESP_OK(in_serial), RadioTechnology::UNKNOWN);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getVoiceRegistrationState(int32_t in_serial) {
    log_debug("xRadioNetwork::%s\n", __func__);
    auto res = network::RegStateResult();

    mRep->getVoiceRegistrationStateResponse(RESP_OK(in_serial), mRegStateRes);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::isNrDualConnectivityEnabled(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::responseAcknowledgement() {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setAllowedNetworkTypesBitmap(
      int32_t in_serial, int32_t in_networkTypeBitmap) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    int32_t filter = in_networkTypeBitmap;
    int32_t filter_bit = 0b1;

    std::string types = "\t";

    // FIXME: don't hardcode this!
    while (filter_bit < (int32_t)RadioAccessFamily::NR) {
        if (filter & filter_bit)
            types += toString(RadioAccessFamily(filter & filter_bit));
        filter_bit <<= 1;
    }

    LOG(INFO) << __func__ << "(ignored) Allowed network types:\n" << types;

    mRep->setAllowedNetworkTypesBitmapResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setBandMode(int32_t in_serial, network::RadioBandMode in_mode) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setBarringPassword(int32_t in_serial,
      const std::string &in_facility, const std::string &in_oldPassword,
      const std::string &in_newPassword) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setCdmaRoamingPreference(
      int32_t in_serial, network::CdmaRoamingType in_type) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setCellInfoListRate(int32_t in_serial, int32_t in_rate) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setIndicationFilter(
      int32_t in_serial, int32_t in_indicationFilter) {
    log_debug("xRadioNetwork::%s\n", __func__);
    int32_t filter = in_indicationFilter;
    int32_t filter_bit = 0b1;

    LOG(INFO) << __func__ << " Filters:";

    // FIXME: don't hardcode this!
    while (filter_bit < (int32_t)network::IndicationFilter::BARRING_INFO) {
        if (filter & filter_bit)
            LOG(INFO) << network::toString(network::IndicationFilter(filter & filter_bit));
        filter_bit <<= 1;
    }

    mIndicationFilter = in_indicationFilter;

    mRep->setIndicationFilterResponse(RESP_OK(in_serial));
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setLinkCapacityReportingCriteria(int32_t in_serial,
      int32_t in_hysteresisMs, int32_t in_hysteresisDlKbps, int32_t in_hysteresisUlKbps,
      const std::vector<int32_t> &in_thresholdsDownlinkKbps,
      const std::vector<int32_t> &in_thresholdsUplinkKbps, AccessNetwork in_accessNetwork) {
    log_debug("xRadioNetwork::%s\n", __func__);

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
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

int RadioNetwork::_registerAndProvision() {
    int rc;

    rc = qrild_qmi_nas_network_register(mState, 1);
    if (rc < 0) {
        auto err = -rc;
        LOG(ERROR) << __func__ << ": Couldn't register to network: " << err << ": "
                   << qmi_error_string(err);
        return -1;
    }

    if (services.initialised) {
        LOG(DEBUG) << __func__ << ": provisioning default sim";
        rc = services.sim->_provisionDefaultSim();
    } else {
        return -2;
    }
    if (rc < 0) {
        LOG(ERROR) << __func__ << ": Failed to provision SIM!";
        rc = -3;
    }

    return rc;
}

ndk::ScopedAStatus RadioNetwork::setNetworkSelectionModeAutomatic(int32_t in_serial) {
    log_debug("xRadioNetwork::%s\n", __func__);
    int rc = 0;
    auto r_info = RESP_OK(in_serial);
    LOG(INFO) << __func__ << "WIP! Connect to network here";

    rc = _registerAndProvision();
    if (rc < 0)
        r_info.error = RadioError::MODEM_ERR;

out:
    mRep->setNetworkSelectionModeAutomaticResponse(r_info);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setNetworkSelectionModeManual(
      int32_t in_serial, const std::string &in_operatorNumeric, AccessNetwork in_ran) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    RadioResponseInfo r_info = RESP_OK(in_serial);

    LOG(ERROR) << __func__ << " Can't handle manual network selection!";
    r_info.error = RadioError::OPERATION_NOT_ALLOWED;

    mRep->setNetworkSelectionModeManualResponse(r_info);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setNrDualConnectivityState(
      int32_t in_serial, network::NrDualConnectivityState in_nrDualConnectivityState) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setResponseFunctions(
      const std::shared_ptr<network::IRadioNetworkResponse> &in_radioNetworkResponse,
      const std::shared_ptr<network::IRadioNetworkIndication> &in_radioNetworkIndication) {
    log_debug("xRadioNetwork::%s\n", __func__);

    mRep = in_radioNetworkResponse;
    mInd = in_radioNetworkIndication;

    qrild_qmi_send_basic_request_sync(mState, QMI_SERVICE_NAS, QMI_NAS_FORCE_NETWORK_SEARCH, NULL);
    _registerAndProvision();

    mInd->networkStateChanged(RadioIndicationType::UNSOLICITED);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setSignalStrengthReportingCriteria(
      int32_t in_serial, const std::vector<network::SignalThresholdInfo> &in_signalThresholdInfos) {
    log_debug("xRadioNetwork::%s\n", __func__);

    LOG(DEBUG) << __func__;
    for (auto thresh : in_signalThresholdInfos) {
        LOG(DEBUG) << thresh.toString();
    }

    mRep->setSignalStrengthReportingCriteriaResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setSuppServiceNotifications(int32_t in_serial, bool in_enable) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setSystemSelectionChannels(int32_t in_serial,
      bool in_specifyChannels, const std::vector<network::RadioAccessSpecifier> &in_specifiers) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::startNetworkScan(
      int32_t in_serial, const network::NetworkScanRequest &in_request) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::stopNetworkScan(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::supplyNetworkDepersonalization(
      int32_t in_serial, const std::string &in_netPin) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::setUsageSetting(
      int32_t in_serial, network::UsageSetting in_usageSetting) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioNetwork::getUsageSetting(int32_t in_serial) {
    log_debug("FIXME! TODO: RadioNetwork::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

void RadioNetwork::reportSystemStatus(struct qrild_msg *msg) {
    struct nas_serving_system_ind *ind_msg = NULL;
    struct nas_serving_system_ind_data ss_ind;
    struct nas_serving_system_resp_data stat;
    bool regStateChanged = false;
    int rc;
    auto cellInfo = network::CellInfo();

    if (!mInd) {
        LOG(ERROR) << __func__ << ": Tried to process indication before android ready";
        return;
    }

    ind_msg = nas_serving_system_ind_parse(msg->buf, msg->buf_len);
    if (!ind_msg) {
        log_error("%s: Couldn't parse serving system report\n", __func__);
        return;
    }
    nas_serving_system_ind_getall(ind_msg, &ss_ind);
    if (!ss_ind.system_valid) {
        log_error("%s: Couldn't parse serving system TLV\n", __func__);
        return;
    }

    nasServingSystemIndToResp(&ss_ind, &stat);
    printServingSystem(&stat);

    cellInfo.registered = stat.system->registration_state == QMI_NAS_REGISTRATION_STATE_REGISTERED;
    if (cellInfo.registered) {
        if (stat.system->cs_attach_state == QMI_NAS_ATTACH_STATE_ATTACHED)
            cellInfo.connectionStatus = network::CellConnectionStatus::PRIMARY_SERVING;
        else if (stat.system->ps_attach_state == QMI_NAS_ATTACH_STATE_ATTACHED)
            cellInfo.connectionStatus = network::CellConnectionStatus::SECONDARY_SERVING;
    }

    if (!stat.system->radio_interfaces_n) {
        LOG(WARNING) << __func__ << ": No radio interfaces reported";
        goto out_free;
    }

    if (stat.system->radio_interfaces_n > 1)
        LOG(WARNING) << __func__ << ": Serving more than 1 radio interface! Taking first";

    // Registration state
    if (mRegStateRes.regState != network::RegState(stat.system->registration_state) &&
          stat.system->registration_state < 5) {
        mRegStateRes.regState = network::RegState(stat.system->registration_state);
        regStateChanged = true;
        LOG(DEBUG)
              << __func__
              << ": Updated registration state to: " << network::toString(mRegStateRes.regState);
    }

    if (mRegStateRes.regState == network::RegState::REG_HOME) {
        auto rat = QmiNasRadioInterfaceToRadioTechnology(stat.system->radio_interfaces[0]);
        if (mRegStateRes.rat != rat)
            regStateChanged = true;
        mRegStateRes.rat = rat;
    } else {
        mRegStateRes.rat = RadioTechnology::UNKNOWN;
    }

    if (mRegStateRes.regState == network::RegState::REG_DENIED ||
          mRegStateRes.regState == network::RegState::REG_DENIED_EM) {
        LOG(ERROR) << __func__ << ": Network registration denied! Everybody panic!!!";
    }

    // if (stat.plmn) {
    //     regStateChanged = true;
    //     mRegStateRes.registeredPlmn = std::string();
    //     mRegStateRes.registeredPlmn += ::android::internal::ToString(stat.plmn->mcc);
    //     auto mnc = ::android::internal::ToString(stat.plmn->mnc);
    //     if (mnc.length() < 2) {
    //         mnc = "0" + mnc;
    //     }
    //     mRegStateRes.registeredPlmn += mnc;
    //     LOG(INFO) << __func__ << ": Last registered PLMN: '" << stat.plmn->description
    //               << "', id: " << mRegStateRes.registeredPlmn;
    // }

    updateCellInfo(&ss_ind);

    mRegStateRes.registeredPlmn = mOperator.operatorNumeric;

    switch(mRegStateRes.rat) {
        case RadioTechnology::UMTS:
            mRegStateRes.cellIdentity = mCellInfo.ratSpecificInfo.get<network::CellInfoRatSpecificInfo::wcdma>().cellIdentityWcdma;
            break;
        case RadioTechnology::GSM:
            mRegStateRes.cellIdentity = mCellInfo.ratSpecificInfo.get<network::CellInfoRatSpecificInfo::gsm>().cellIdentityGsm;
            break;
        case RadioTechnology::LTE:
            mRegStateRes.cellIdentity = mCellInfo.ratSpecificInfo.get<network::CellInfoRatSpecificInfo::lte>().cellIdentityLte;
            break;
        case RadioTechnology::UNKNOWN:
            break;
        default:
            LOG(WARNING) << __func__ << ": Couldn't get cell identity for RAT: " << toString(mRegStateRes.rat);
            break;
    }

    if (mRegStateRes.regState == network::RegState::NOT_REG_MT_NOT_SEARCHING_OP && services.initialised && services.modem->mEnabled) {
        log_info("Before forcing network search");
        LOG(WARNING) << __func__ << ": Forcing network search";
        qrild_qmi_send_basic_request_sync(mState, QMI_SERVICE_NAS, QMI_NAS_FORCE_NETWORK_SEARCH, NULL);
        _registerAndProvision();
    }

    log_debug("Got mRegStateRes: %s", mRegStateRes.toString().c_str());
    LOG(DEBUG) << __func__ << ": " << mRegStateRes.toString();

out_free:
    nas_serving_system_ind_data_free(&ss_ind);

    auto arr = std::vector<network::CellInfo>();
    arr.push_back(cellInfo);
    mInd->cellInfoList(RadioIndicationType::UNSOLICITED, arr);

    if (regStateChanged)
        mInd->networkStateChanged(RadioIndicationType::UNSOLICITED);
}

void RadioNetwork::_handleQmiIndications() {
    struct qrild_msg *msg;
    // FIXME: this feels like not the right way to use a mutex lol
    q_thread_mutex_lock(&mState->msg_mutex);
    list_for_each_entry(msg, &mState->pending_rx, li) {
        if (msg->type != 0x4)
            continue;

        q_thread_mutex_unlock(&mState->msg_mutex);
        switch (msg->msg_id) {
        case QMI_NAS_SERVING_SYSTEM_REPORT:
            reportSystemStatus(msg);
            break;
        default:
            break;
        }
        q_thread_mutex_lock(&mState->msg_mutex);
    }
    q_thread_mutex_unlock(&mState->msg_mutex);
}
