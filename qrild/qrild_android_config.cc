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

#include <string>

#include <qrild.h>
#include <qrild_qmi.h>

#include <util.h>
#include <qmi_uim.h>

#include "qrild_radio.hh"

RadioConfig::RadioConfig(struct rild_state *state) : mState(state) {
    printf("xRadioConfig::%s\n", __func__);
}

ndk::ScopedAStatus RadioConfig::getHalDeviceCapabilities(int32_t in_serial) {
    printf("xRadioConfig::%s\n", __func__);

    mRep->getHalDeviceCapabilitiesResponse(RESP_OK(in_serial), true);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::getNumOfLiveModems(int32_t in_serial) {
    printf("xRadioConfig::%s\n", __func__);

    // We only have 1 modem
    mRep->getNumOfLiveModemsResponse(RESP_OK(in_serial), 1);

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::getPhoneCapability(int32_t in_serial) {
    printf("xRadioConfig::%s\n", __func__);

    config::PhoneCapability cap = config::PhoneCapability();

    cap.maxActiveData = 1;
    cap.maxActiveInternetData = 1;
    cap.isInternetLingeringSupported = false;
    cap.logicalModemIds = std::vector<uint8_t>(0);

    mRep->getPhoneCapabilityResponse(RESP_OK(in_serial), cap);

    return ndk::ScopedAStatus::ok();
}

/* Thanks qmicli
 * https://gitlab.freedesktop.org/mobile-broadband/libqmi/-/blob/main/src/qmicli/qmicli-uim.c#L999
 */
static const char bcd_chars[] = "0123456789\0\0\0\0\0\0";

std::string decode_iccid(uint8_t *bcd, uint8_t len)
{
    char *str = (char*)zalloc(len * 2 + 1);
    for (size_t i = 0; i < len; i++)
    {
        str[i] = (bcd_chars[bcd[i] & 0xF]);
        str[i+1] = (bcd_chars[(bcd[i] >> 4) & 0xF]);
    }

    return std::string(str);
}

std::string decode_eid(uint8_t *eid, uint8_t len)
{
    char *str = (char*)zalloc(len * 2 + 1);
    for (size_t i = 0; i < len; i++)
    {
        str[i] = bcd_chars[(eid[i] >> 4) & 0xF];
        str[i+1] = bcd_chars[eid[i] & 0xF];
    }

    return std::string(str);
}

std::string decode_atr(uint8_t *atr, uint8_t len)
{
    char *str = (char*)zalloc(len * 2 + 1);
    for (size_t i = 0; i < len; i++)
    {
        str[i] = to_hex(atr[i] >> 4);
        str[i+1] = to_hex(atr[i]);
    }

    return std::string(str);
}

ndk::ScopedAStatus RadioConfig::getSimSlotsStatus(int32_t in_serial) {
    printf("xRadioConfig::%s\n", __func__);
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

    printf("Slot %d\n\tcardState: %d\n\tlogicalSlotId: %d\n\tportActive: %d\n", 0, slot->cardState, port->logicalSlotId, port->portActive);

    // if (slot->cardState != QMI_UIM_CARD_STATE_PRESENT)
    //     goto cont;

    slot->atr = decode_atr(status.slot_info->slots[0].atr_value, status.slot_info->slots[0].atr_value_n);
    if (status.slot_info->slots[0].is_euicc)
        slot->eid = decode_eid(status.eid_info, status.eid_info_n);
    else
        LOG(DEBUG) << __func__ << ": not EUICC -> no EID";
    port->iccId = decode_iccid(status.slot_state->slots[0].iccid, status.slot_state->slots[0].iccid_n);

    printf("\tFIXME! should start with 3B!!! ATR: %s\n\tEID: %s\n\tICCID: %s\n", slot->atr.c_str(), slot->eid.c_str(), port->iccId.c_str());

    //cont:
        slot->portInfo.push_back(*port);
        slots.push_back(*slot);
    //}

out:
    r_info.error = err;
    mRep->getSimSlotsStatusResponse(r_info, slots);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::setNumOfLiveModems(int32_t in_serial, int8_t in_numOfLiveModems) {
    printf("FIXME! TODO: RadioConfig::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::setPreferredDataModem(int32_t in_serial, int8_t in_modemId) {
    printf("xRadioConfig::%s\n", __func__);

    printf("(nop) Setting modem to %d\n", in_modemId);
    mRep->setPreferredDataModemResponse(RESP_OK(in_serial));

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::setResponseFunctions(
      const std::shared_ptr<config::IRadioConfigResponse> &in_radioConfigResponse,
      const std::shared_ptr<config::IRadioConfigIndication> &in_radioConfigIndication) {
    printf("xRadioConfig::%s\n", __func__);

    mRep = in_radioConfigResponse;
    mInd = in_radioConfigIndication;

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus RadioConfig::setSimSlotsMapping(
      int32_t in_serial, const std::vector<config::SlotPortMapping> &in_slotMap) {
    printf("FIXME! TODO: RadioConfig::%s\n", __func__);
    return ndk::ScopedAStatus::ok();
}

void RadioConfig::handleQmiIndications()
{

}
