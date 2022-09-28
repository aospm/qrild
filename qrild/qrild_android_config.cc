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

#define LOG_TAG "qrild.IConfig"
#include <android-base/logging.h>
#include <q_log.h>

#include <string>

#include <libqril.h>
#include <qmi_uim.h>

#include "qrild_radio.hh"

RadioConfig::RadioConfig(struct rild_state *state) : mState(state) {
    log_debug("xRadioConfig::%s\n", __func__);
}

ndk::ScopedAStatus RadioConfig::getHalDeviceCapabilities(int32_t in_serial) {
    log_debug("xRadioConfig::%s\n", __func__);

    mRep->getHalDeviceCapabilitiesResponse(RESP_OK(in_serial), true);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::getNumOfLiveModems(int32_t in_serial) {
    log_debug("xRadioConfig::%s\n", __func__);

    // We only have 1 modem
    mRep->getNumOfLiveModemsResponse(RESP_OK(in_serial), 1);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::getPhoneCapability(int32_t in_serial) {
    log_debug("xRadioConfig::%s\n", __func__);

    config::PhoneCapability cap = config::PhoneCapability();

    cap.maxActiveData = 1;
    cap.maxActiveInternetData = 1;
    cap.isInternetLingeringSupported = false;
    cap.logicalModemIds = std::vector<uint8_t>(0);

    mRep->getPhoneCapabilityResponse(RESP_OK(in_serial), cap);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::getSimSlotsStatus(int32_t in_serial) {
    struct uim_get_slot_status_resp *resp = UIM_GET_SLOT_STATUS_RESP_NEW;
    int rc = sizeof(resp);
    auto r_info = RESP_OK(in_serial);
    auto slots = std::vector<config::SimSlotStatus>();
    auto slot = config::SimSlotStatus();
    auto port = config::SimPortInfo();

    rc = libqril_send_basic_request_sync(QMI_SERVICE_UIM, QMI_UIM_GET_SLOT_STATUS, &resp->hdr);
    if (rc < 0) {
        ALOGE("Failed to send request: %d", rc);
        r_info.error = RadioError::INTERNAL_ERR;
        goto out;
    }
    if (rc > 0) {
        ALOGE("Modem returned error: %s", libqril_qmi_error_string(rc));
        r_info.error = RadioError::MODEM_ERR;
        goto out;
    }

    if (!resp->slot_state_valid || !resp->slot_state_len || !resp->slot_info_valid
            || !resp->slot_info.slots_len) {
        ALOGE("No slots found");
        r_info.error = RadioError::RADIO_NOT_AVAILABLE;
        goto out;
    }

    slot.cardState = QmiUimPhysicalCardStateToCardState(resp->slot_state[0].card_state);
    slot->atr = bytes_to_hex(resp->slot_info.slots[0].atr_value,
        resp->slot_info.slots[0].atr_value_len)



    port.logicalSlotId = resp->slot_state[0].logical_slot - 1;
    port.portActive = resp->slot_state[0].slot_state;

out:
    mRep->getSimSlotsStatusResponse(r_info, slots);
    return ndk::ScopedAStatus::ok();
}

/*
ndk::ScopedAStatus RadioConfig::getSimSlotsStatus(int32_t in_serial) {
    log_debug("xRadioConfig::%s\n", __func__);
    int rc;
    struct uim_get_slot_status_resp_data status;
    auto slots = std::vector<config::SimSlotStatus>();
    auto r_info = RESP_OK(in_serial);
    RadioError err = RadioError::NONE;
    auto slot = new config::SimSlotStatus();
    auto port = new config::SimPortInfo();

    rc = qrild_qmi_uim_get_slot_status(mState, &status);
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

    // FIXME: is it correct to only report one SIM?
    //for (size_t i = 0; i < status.slot_state->slots_n; i++) {

    slot->cardState = QmiUimPhysicalCardStateToCardState(status.slot_state->slots[0].card_state);

    port->logicalSlotId = status.slot_state->slots[0].logical_slot - 1;
    port->portActive = status.slot_state->slots[0].slot_state;

    log_debug("Slot %d\n\tcardState: %d\n\tlogicalSlotId: %d\n\tportActive: %d\n", 0, slot->cardState, port->logicalSlotId, port->portActive);

    // if (slot->cardState != QMI_UIM_CARD_STATE_PRESENT)
    //     goto cont;

    slot->atr = decode_bytes(status.slot_info->slots[0].atr_value, status.slot_info->slots[0].atr_value_n);
    if (status.slot_info->slots[0].is_euicc)
        slot->eid = decode_eid(status.eid_info, status.eid_info_n);
    else
        LOG(DEBUG) << __func__ << ": not EUICC -> no EID";
    port->iccId = decode_iccid(status.slot_state->slots[0].iccid, status.slot_state->slots[0].iccid_n);

    log_debug("\tATR: %s\n\tEID: %s\n\tICCID: %s\n", slot->atr.c_str(), slot->eid.c_str(), port->iccId.c_str());

    //cont:
        slot->portInfo.push_back(*port);
        slots.push_back(*slot);
    //}

out:
    r_info.error = err;
    mRep->getSimSlotsStatusResponse(r_info, slots);
    return ndk::ScopedAStatus::ok();
}
*/

ndk::ScopedAStatus RadioConfig::setNumOfLiveModems(int32_t in_serial, int8_t in_numOfLiveModems) {
    log_debug("FIXME! TODO: RadioConfig::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::setPreferredDataModem(int32_t in_serial, int8_t in_modemId) {
    log_debug("xRadioConfig::%s\n", __func__);

    log_debug("(nop) Setting modem to %d\n", in_modemId);
    mRep->setPreferredDataModemResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::setResponseFunctions(
      const std::shared_ptr<config::IRadioConfigResponse> &in_radioConfigResponse,
      const std::shared_ptr<config::IRadioConfigIndication> &in_radioConfigIndication) {
    log_debug("xRadioConfig::%s\n", __func__);

    mRep = in_radioConfigResponse;
    mInd = in_radioConfigIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::setSimSlotsMapping(
      int32_t in_serial, const std::vector<config::SlotPortMapping> &in_slotMap) {
    log_debug("FIXME! TODO: RadioConfig::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

void RadioConfig::_handleQmiIndications()
{

}
