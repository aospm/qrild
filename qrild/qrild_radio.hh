#ifndef __QRILD_RADIO_HH__
#define __QRILD_RADIO_HH__

#include <memory>
#include <optional>
#include <vector>

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include <aidl/android/hardware/radio/config/BnRadioConfig.h>
#include <aidl/android/hardware/radio/config/BnRadioConfigIndication.h>
#include <aidl/android/hardware/radio/config/BnRadioConfigResponse.h>

#include <aidl/android/hardware/radio/data/BnRadioData.h>
#include <aidl/android/hardware/radio/data/BnRadioDataIndication.h>
#include <aidl/android/hardware/radio/data/BnRadioDataResponse.h>

#include <aidl/android/hardware/radio/messaging/BnRadioMessaging.h>
#include <aidl/android/hardware/radio/messaging/BnRadioMessagingIndication.h>
#include <aidl/android/hardware/radio/messaging/BnRadioMessagingResponse.h>

#include <aidl/android/hardware/radio/modem/BnRadioModem.h>
#include <aidl/android/hardware/radio/modem/BnRadioModemIndication.h>
#include <aidl/android/hardware/radio/modem/BnRadioModemResponse.h>

#include <aidl/android/hardware/radio/network/BnRadioNetwork.h>
#include <aidl/android/hardware/radio/network/BnRadioNetworkIndication.h>
#include <aidl/android/hardware/radio/network/BnRadioNetworkResponse.h>
#include <aidl/android/hardware/radio/network/IndicationFilter.h>

#include <aidl/android/hardware/radio/sim/BnRadioSim.h>
#include <aidl/android/hardware/radio/sim/BnRadioSimIndication.h>
#include <aidl/android/hardware/radio/sim/BnRadioSimResponse.h>

#include <aidl/android/hardware/radio/voice/BnRadioVoice.h>
#include <aidl/android/hardware/radio/voice/BnRadioVoiceIndication.h>
#include <aidl/android/hardware/radio/voice/BnRadioVoiceResponse.h>

#include <qrild.h>

using namespace aidl::android::hardware::radio;

/*****************************************************
 * AIDL impl class definitions
 */

class RadioConfig : public config::BnRadioConfig {
    ndk::ScopedAStatus getHalDeviceCapabilities(int32_t in_serial) override;
    ndk::ScopedAStatus getNumOfLiveModems(int32_t in_serial) override;
    ndk::ScopedAStatus getPhoneCapability(int32_t in_serial) override;
    ndk::ScopedAStatus getSimSlotsStatus(int32_t in_serial) override;
    ndk::ScopedAStatus setNumOfLiveModems(int32_t in_serial, int8_t in_numOfLiveModems) override;
    ndk::ScopedAStatus setPreferredDataModem(int32_t in_serial, int8_t in_modemId) override;
    ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<config::IRadioConfigResponse> &in_radioConfigResponse,
          const std::shared_ptr<config::IRadioConfigIndication> &in_radioConfigIndication) override;
    ndk::ScopedAStatus setSimSlotsMapping(
          int32_t in_serial, const std::vector<config::SlotPortMapping> &in_slotMap) override;

    std::shared_ptr<config::IRadioConfigResponse> mRep;
    std::shared_ptr<config::IRadioConfigIndication> mInd;
    struct rild_state *mState;

public:
    RadioConfig(struct rild_state *state);
};

class RadioData : public data::BnRadioData {
    ndk::ScopedAStatus allocatePduSessionId(int32_t in_serial) override;
    ndk::ScopedAStatus cancelHandover(int32_t in_serial, int32_t in_callId) override;
    ndk::ScopedAStatus deactivateDataCall(
          int32_t in_serial, int32_t in_cid, data::DataRequestReason in_reason) override;
    ndk::ScopedAStatus getDataCallList(int32_t in_serial) override;
    ndk::ScopedAStatus getSlicingConfig(int32_t in_serial) override;
    ndk::ScopedAStatus releasePduSessionId(int32_t in_serial, int32_t in_id) override;
    ndk::ScopedAStatus responseAcknowledgement() override;
    ndk::ScopedAStatus setDataAllowed(int32_t in_serial, bool in_allow) override;
    ndk::ScopedAStatus setDataProfile(
          int32_t in_serial, const std::vector<data::DataProfileInfo> &in_profiles) override;
    ndk::ScopedAStatus setDataThrottling(int32_t in_serial, data::DataThrottlingAction in_dataThrottlingAction,
          int64_t in_completionDurationMillis) override;
    ndk::ScopedAStatus setInitialAttachApn(
          int32_t in_serial, const std::optional<data::DataProfileInfo> &in_dataProfileInfo) override;
    ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<data::IRadioDataResponse> &in_radioDataResponse,
          const std::shared_ptr<data::IRadioDataIndication> &in_radioDataIndication) override;
    ndk::ScopedAStatus setupDataCall(int32_t in_serial, AccessNetwork in_accessNetwork,
          const data::DataProfileInfo &in_dataProfileInfo, bool in_roamingAllowed, data::DataRequestReason in_reason,
          const std::vector<data::LinkAddress> &in_addresses, const std::vector<std::string> &in_dnses,
          int32_t in_pduSessionId, const std::optional<data::SliceInfo> &in_sliceInfo,
          bool in_matchAllRuleAllowed) override;
    ndk::ScopedAStatus startHandover(int32_t in_serial, int32_t in_callId) override;
    ndk::ScopedAStatus startKeepalive(int32_t in_serial, const data::KeepaliveRequest &in_keepalive) override;
    ndk::ScopedAStatus stopKeepalive(int32_t in_serial, int32_t in_sessionHandle) override;

    std::shared_ptr<data::IRadioDataResponse> mRep;
    std::shared_ptr<data::IRadioDataIndication> mInd;
    struct rild_state *mState;

public:
    RadioData(struct rild_state *state);
};

class RadioMessaging : public messaging::BnRadioMessaging {
    ndk::ScopedAStatus acknowledgeIncomingGsmSmsWithPdu(
          int32_t in_serial, bool in_success, const std::string &in_ackPdu) override;
    ndk::ScopedAStatus acknowledgeLastIncomingCdmaSms(
          int32_t in_serial, const messaging::CdmaSmsAck &in_smsAck) override;
    ndk::ScopedAStatus acknowledgeLastIncomingGsmSms(
          int32_t in_serial, bool in_success, messaging::SmsAcknowledgeFailCause in_cause) override;
    ndk::ScopedAStatus deleteSmsOnRuim(int32_t in_serial, int32_t in_index) override;
    ndk::ScopedAStatus deleteSmsOnSim(int32_t in_serial, int32_t in_index) override;
    ndk::ScopedAStatus getCdmaBroadcastConfig(int32_t in_serial) override;
    ndk::ScopedAStatus getGsmBroadcastConfig(int32_t in_serial) override;
    ndk::ScopedAStatus getSmscAddress(int32_t in_serial) override;
    ndk::ScopedAStatus reportSmsMemoryStatus(int32_t in_serial, bool in_available) override;
    ndk::ScopedAStatus responseAcknowledgement() override;
    ndk::ScopedAStatus sendCdmaSms(int32_t in_serial, const messaging::CdmaSmsMessage &in_sms) override;
    ndk::ScopedAStatus sendCdmaSmsExpectMore(int32_t in_serial, const messaging::CdmaSmsMessage &in_sms) override;
    ndk::ScopedAStatus sendImsSms(int32_t in_serial, const messaging::ImsSmsMessage &in_message) override;
    ndk::ScopedAStatus sendSms(int32_t in_serial, const messaging::GsmSmsMessage &in_message) override;
    ndk::ScopedAStatus sendSmsExpectMore(int32_t in_serial, const messaging::GsmSmsMessage &in_message) override;
    ndk::ScopedAStatus setCdmaBroadcastActivation(int32_t in_serial, bool in_activate) override;
    ndk::ScopedAStatus setCdmaBroadcastConfig(
          int32_t in_serial, const std::vector<messaging::CdmaBroadcastSmsConfigInfo> &in_configInfo) override;
    ndk::ScopedAStatus setGsmBroadcastActivation(int32_t in_serial, bool in_activate) override;
    ndk::ScopedAStatus setGsmBroadcastConfig(
          int32_t in_serial, const std::vector<messaging::GsmBroadcastSmsConfigInfo> &in_configInfo) override;
    ndk::ScopedAStatus setResponseFunctions(
          const std::shared_ptr<messaging::IRadioMessagingResponse> &in_radioMessagingResponse,
          const std::shared_ptr<messaging::IRadioMessagingIndication> &in_radioMessagingIndication) override;
    ndk::ScopedAStatus setSmscAddress(int32_t in_serial, const std::string &in_smsc) override;
    ndk::ScopedAStatus writeSmsToRuim(int32_t in_serial, const messaging::CdmaSmsWriteArgs &in_cdmaSms) override;
    ndk::ScopedAStatus writeSmsToSim(int32_t in_serial, const messaging::SmsWriteArgs &in_smsWriteArgs) override;

    std::shared_ptr<messaging::IRadioMessagingResponse> mRep;
    std::shared_ptr<messaging::IRadioMessagingIndication> mInd;
    struct rild_state *mState;

public:
    RadioMessaging(struct rild_state *state);
};

class RadioModem : public modem::BnRadioModem {
    ndk::ScopedAStatus enableModem(int32_t in_serial, bool in_on) override;
    ndk::ScopedAStatus getBasebandVersion(int32_t in_serial) override;
    ndk::ScopedAStatus getDeviceIdentity(int32_t in_serial) override;
    ndk::ScopedAStatus getHardwareConfig(int32_t in_serial) override;
    ndk::ScopedAStatus getModemActivityInfo(int32_t in_serial) override;
    ndk::ScopedAStatus getModemStackStatus(int32_t in_serial) override;
    ndk::ScopedAStatus getRadioCapability(int32_t in_serial) override;
    ndk::ScopedAStatus nvReadItem(int32_t in_serial, modem::NvItem in_itemId) override;
    ndk::ScopedAStatus nvResetConfig(int32_t in_serial, modem::ResetNvType in_resetType) override;
    ndk::ScopedAStatus nvWriteCdmaPrl(int32_t in_serial, const std::vector<uint8_t> &in_prl) override;
    ndk::ScopedAStatus nvWriteItem(int32_t in_serial, const modem::NvWriteItem &in_item) override;
    ndk::ScopedAStatus requestShutdown(int32_t in_serial) override;
    ndk::ScopedAStatus responseAcknowledgement() override;
    ndk::ScopedAStatus sendDeviceState(
          int32_t in_serial, modem::DeviceStateType in_deviceStateType, bool in_state) override;
    ndk::ScopedAStatus setRadioCapability(int32_t in_serial, const modem::RadioCapability &in_rc) override;
    ndk::ScopedAStatus setRadioPower(
          int32_t in_serial, bool in_powerOn, bool in_forEmergencyCall, bool in_preferredForEmergencyCall) override;
    ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<modem::IRadioModemResponse> &in_radioModemResponse,
          const std::shared_ptr<modem::IRadioModemIndication> &in_radioModemIndication) override;

    std::shared_ptr<modem::IRadioModemResponse> mRep;
    std::shared_ptr<modem::IRadioModemIndication> mInd;
    modem::RadioCapability mCaps;
    bool mEnabled;
    struct rild_state *mState;

public:
    RadioModem(struct rild_state *state);
};

class RadioNetwork : public network::BnRadioNetwork {
    ndk::ScopedAStatus getAllowedNetworkTypesBitmap(int32_t in_serial) override;
    ndk::ScopedAStatus getAvailableBandModes(int32_t in_serial) override;
    ndk::ScopedAStatus getAvailableNetworks(int32_t in_serial) override;
    ndk::ScopedAStatus getBarringInfo(int32_t in_serial) override;
    ndk::ScopedAStatus getCdmaRoamingPreference(int32_t in_serial) override;
    ndk::ScopedAStatus getCellInfoList(int32_t in_serial) override;
    ndk::ScopedAStatus getDataRegistrationState(int32_t in_serial) override;
    ndk::ScopedAStatus getImsRegistrationState(int32_t in_serial) override;
    ndk::ScopedAStatus getNetworkSelectionMode(int32_t in_serial) override;
    ndk::ScopedAStatus getOperator(int32_t in_serial) override;
    ndk::ScopedAStatus getSignalStrength(int32_t in_serial) override;
    ndk::ScopedAStatus getSystemSelectionChannels(int32_t in_serial) override;
    ndk::ScopedAStatus getVoiceRadioTechnology(int32_t in_serial) override;
    ndk::ScopedAStatus getVoiceRegistrationState(int32_t in_serial) override;
    ndk::ScopedAStatus isNrDualConnectivityEnabled(int32_t in_serial) override;
    ndk::ScopedAStatus responseAcknowledgement() override;
    ndk::ScopedAStatus setAllowedNetworkTypesBitmap(int32_t in_serial, int32_t in_networkTypeBitmap) override;
    ndk::ScopedAStatus setBandMode(int32_t in_serial, network::RadioBandMode in_mode) override;
    ndk::ScopedAStatus setBarringPassword(int32_t in_serial, const std::string &in_facility,
          const std::string &in_oldPassword, const std::string &in_newPassword) override;
    ndk::ScopedAStatus setCdmaRoamingPreference(int32_t in_serial, network::CdmaRoamingType in_type) override;
    ndk::ScopedAStatus setCellInfoListRate(int32_t in_serial, int32_t in_rate) override;
    ndk::ScopedAStatus setIndicationFilter(int32_t in_serial, int32_t in_indicationFilter) override;
    ndk::ScopedAStatus setLinkCapacityReportingCriteria(int32_t in_serial, int32_t in_hysteresisMs,
          int32_t in_hysteresisDlKbps, int32_t in_hysteresisUlKbps,
          const std::vector<int32_t> &in_thresholdsDownlinkKbps, const std::vector<int32_t> &in_thresholdsUplinkKbps,
          AccessNetwork in_accessNetwork) override;
    ndk::ScopedAStatus setLocationUpdates(int32_t in_serial, bool in_enable) override;
    ndk::ScopedAStatus setNetworkSelectionModeAutomatic(int32_t in_serial) override;
    ndk::ScopedAStatus setNetworkSelectionModeManual(
          int32_t in_serial, const std::string &in_operatorNumeric, AccessNetwork in_ran) override;
    ndk::ScopedAStatus setNrDualConnectivityState(
          int32_t in_serial, network::NrDualConnectivityState in_nrDualConnectivityState) override;
    ndk::ScopedAStatus setResponseFunctions(
          const std::shared_ptr<network::IRadioNetworkResponse> &in_radioNetworkResponse,
          const std::shared_ptr<network::IRadioNetworkIndication> &in_radioNetworkIndication) override;
    ndk::ScopedAStatus setSignalStrengthReportingCriteria(
          int32_t in_serial, const std::vector<network::SignalThresholdInfo> &in_signalThresholdInfos) override;
    ndk::ScopedAStatus setSuppServiceNotifications(int32_t in_serial, bool in_enable) override;
    ndk::ScopedAStatus setSystemSelectionChannels(int32_t in_serial, bool in_specifyChannels,
          const std::vector<network::RadioAccessSpecifier> &in_specifiers) override;
    ndk::ScopedAStatus startNetworkScan(int32_t in_serial, const network::NetworkScanRequest &in_request) override;
    ndk::ScopedAStatus stopNetworkScan(int32_t in_serial) override;
    ndk::ScopedAStatus supplyNetworkDepersonalization(int32_t in_serial, const std::string &in_netPin) override;
    ndk::ScopedAStatus setUsageSetting(int32_t in_serial, network::UsageSetting in_usageSetting) override;
    ndk::ScopedAStatus getUsageSetting(int32_t in_serial) override;

    std::shared_ptr<network::IRadioNetworkResponse> mRep;
    std::shared_ptr<network::IRadioNetworkIndication> mInd;
    struct rild_state *mState;
    int32_t indicationFilter;
    network::RegStateResult mRegStateRes;

public:
    RadioNetwork(struct rild_state *state);
};

class RadioSim : public sim::BnRadioSim {
    ndk::ScopedAStatus areUiccApplicationsEnabled(int32_t in_serial) override;
    ndk::ScopedAStatus changeIccPin2ForApp(int32_t in_serial, const std::string &in_oldPin2,
          const std::string &in_newPin2, const std::string &in_aid) override;
    ndk::ScopedAStatus changeIccPinForApp(int32_t in_serial, const std::string &in_oldPin, const std::string &in_newPin,
          const std::string &in_aid) override;
    ndk::ScopedAStatus enableUiccApplications(int32_t in_serial, bool in_enable) override;
    ndk::ScopedAStatus getAllowedCarriers(int32_t in_serial) override;
    ndk::ScopedAStatus getCdmaSubscription(int32_t in_serial) override;
    ndk::ScopedAStatus getCdmaSubscriptionSource(int32_t in_serial) override;
    ndk::ScopedAStatus getFacilityLockForApp(int32_t in_serial, const std::string &in_facility,
          const std::string &in_password, int32_t in_serviceClass, const std::string &in_appId) override;
    ndk::ScopedAStatus getIccCardStatus(int32_t in_serial) override;
    ndk::ScopedAStatus getImsiForApp(int32_t in_serial, const std::string &in_aid) override;
    ndk::ScopedAStatus getSimPhonebookCapacity(int32_t in_serial) override;
    ndk::ScopedAStatus getSimPhonebookRecords(int32_t in_serial) override;
    ndk::ScopedAStatus iccCloseLogicalChannel(int32_t in_serial, int32_t in_channelId) override;
    ndk::ScopedAStatus iccIoForApp(int32_t in_serial, const sim::IccIo &in_iccIo) override;
    ndk::ScopedAStatus iccOpenLogicalChannel(int32_t in_serial, const std::string &in_aid, int32_t in_p2) override;
    ndk::ScopedAStatus iccTransmitApduBasicChannel(int32_t in_serial, const sim::SimApdu &in_message) override;
    ndk::ScopedAStatus iccTransmitApduLogicalChannel(int32_t in_serial, const sim::SimApdu &in_message) override;
    ndk::ScopedAStatus reportStkServiceIsRunning(int32_t in_serial) override;
    ndk::ScopedAStatus requestIccSimAuthentication(int32_t in_serial, int32_t in_authContext,
          const std::string &in_authData, const std::string &in_aid) override;
    ndk::ScopedAStatus responseAcknowledgement() override;
    ndk::ScopedAStatus sendEnvelope(int32_t in_serial, const std::string &in_contents) override;
    ndk::ScopedAStatus sendEnvelopeWithStatus(int32_t in_serial, const std::string &in_contents) override;
    ndk::ScopedAStatus sendTerminalResponseToSim(int32_t in_serial, const std::string &in_contents) override;
    ndk::ScopedAStatus setAllowedCarriers(int32_t in_serial, const sim::CarrierRestrictions &in_carriers,
          sim::SimLockMultiSimPolicy in_multiSimPolicy) override;
    ndk::ScopedAStatus setCarrierInfoForImsiEncryption(
          int32_t in_serial, const sim::ImsiEncryptionInfo &in_imsiEncryptionInfo) override;
    ndk::ScopedAStatus setCdmaSubscriptionSource(int32_t in_serial, sim::CdmaSubscriptionSource in_cdmaSub) override;
    ndk::ScopedAStatus setFacilityLockForApp(int32_t in_serial, const std::string &in_facility, bool in_lockState,
          const std::string &in_password, int32_t in_serviceClass, const std::string &in_appId) override;
    ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<sim::IRadioSimResponse> &in_radioSimResponse,
          const std::shared_ptr<sim::IRadioSimIndication> &in_radioSimIndication) override;
    ndk::ScopedAStatus setSimCardPower(int32_t in_serial, sim::CardPowerState in_powerUp) override;
    ndk::ScopedAStatus setUiccSubscription(int32_t in_serial, const sim::SelectUiccSub &in_uiccSub) override;
    ndk::ScopedAStatus supplyIccPin2ForApp(
          int32_t in_serial, const std::string &in_pin2, const std::string &in_aid) override;
    ndk::ScopedAStatus supplyIccPinForApp(
          int32_t in_serial, const std::string &in_pin, const std::string &in_aid) override;
    ndk::ScopedAStatus supplyIccPuk2ForApp(int32_t in_serial, const std::string &in_puk2, const std::string &in_pin2,
          const std::string &in_aid) override;
    ndk::ScopedAStatus supplyIccPukForApp(
          int32_t in_serial, const std::string &in_puk, const std::string &in_pin, const std::string &in_aid) override;
    ndk::ScopedAStatus supplySimDepersonalization(
          int32_t in_serial, sim::PersoSubstate in_persoType, const std::string &in_controlKey) override;
    ndk::ScopedAStatus updateSimPhonebookRecords(
          int32_t in_serial, const sim::PhonebookRecordInfo &in_recordInfo) override;

    std::shared_ptr<sim::IRadioSimResponse> mRep;
    std::shared_ptr<sim::IRadioSimIndication> mInd;
    struct rild_state *mState;

public:
    RadioSim(struct rild_state *state);
};

class RadioVoice : public voice::BnRadioVoice {
    ndk::ScopedAStatus acceptCall(int32_t in_serial) override;
    ndk::ScopedAStatus cancelPendingUssd(int32_t in_serial) override;
    ndk::ScopedAStatus conference(int32_t in_serial) override;
    ndk::ScopedAStatus dial(int32_t in_serial, const voice::Dial &in_dialInfo) override;
    ndk::ScopedAStatus emergencyDial(int32_t in_serial, const voice::Dial &in_dialInfo, int32_t in_categories,
          const std::vector<std::string> &in_urns, voice::EmergencyCallRouting in_routing,
          bool in_hasKnownUserIntentEmergency, bool in_isTesting) override;
    ndk::ScopedAStatus exitEmergencyCallbackMode(int32_t in_serial) override;
    ndk::ScopedAStatus explicitCallTransfer(int32_t in_serial) override;
    ndk::ScopedAStatus getCallForwardStatus(int32_t in_serial, const voice::CallForwardInfo &in_callInfo) override;
    ndk::ScopedAStatus getCallWaiting(int32_t in_serial, int32_t in_serviceClass) override;
    ndk::ScopedAStatus getClip(int32_t in_serial) override;
    ndk::ScopedAStatus getClir(int32_t in_serial) override;
    ndk::ScopedAStatus getCurrentCalls(int32_t in_serial) override;
    ndk::ScopedAStatus getLastCallFailCause(int32_t in_serial) override;
    ndk::ScopedAStatus getMute(int32_t in_serial) override;
    ndk::ScopedAStatus getPreferredVoicePrivacy(int32_t in_serial) override;
    ndk::ScopedAStatus getTtyMode(int32_t in_serial) override;
    ndk::ScopedAStatus handleStkCallSetupRequestFromSim(int32_t in_serial, bool in_accept) override;
    ndk::ScopedAStatus hangup(int32_t in_serial, int32_t in_gsmIndex) override;
    ndk::ScopedAStatus hangupForegroundResumeBackground(int32_t in_serial) override;
    ndk::ScopedAStatus hangupWaitingOrBackground(int32_t in_serial) override;
    ndk::ScopedAStatus isVoNrEnabled(int32_t in_serial) override;
    ndk::ScopedAStatus rejectCall(int32_t in_serial) override;
    ndk::ScopedAStatus responseAcknowledgement() override;
    ndk::ScopedAStatus sendBurstDtmf(
          int32_t in_serial, const std::string &in_dtmf, int32_t in_on, int32_t in_off) override;
    ndk::ScopedAStatus sendCdmaFeatureCode(int32_t in_serial, const std::string &in_featureCode) override;
    ndk::ScopedAStatus sendDtmf(int32_t in_serial, const std::string &in_s) override;
    ndk::ScopedAStatus sendUssd(int32_t in_serial, const std::string &in_ussd) override;
    ndk::ScopedAStatus separateConnection(int32_t in_serial, int32_t in_gsmIndex) override;
    ndk::ScopedAStatus setCallForward(int32_t in_serial, const voice::CallForwardInfo &in_callInfo) override;
    ndk::ScopedAStatus setCallWaiting(int32_t in_serial, bool in_enable, int32_t in_serviceClass) override;
    ndk::ScopedAStatus setClir(int32_t in_serial, int32_t in_status) override;
    ndk::ScopedAStatus setMute(int32_t in_serial, bool in_enable) override;
    ndk::ScopedAStatus setPreferredVoicePrivacy(int32_t in_serial, bool in_enable) override;
    ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<voice::IRadioVoiceResponse> &in_radioVoiceResponse,
          const std::shared_ptr<voice::IRadioVoiceIndication> &in_radioVoiceIndication) override;
    ndk::ScopedAStatus setTtyMode(int32_t in_serial, voice::TtyMode in_mode) override;
    ndk::ScopedAStatus setVoNrEnabled(int32_t in_serial, bool in_enable) override;
    ndk::ScopedAStatus startDtmf(int32_t in_serial, const std::string &in_s) override;
    ndk::ScopedAStatus stopDtmf(int32_t in_serial) override;
    ndk::ScopedAStatus switchWaitingOrHoldingAndActive(int32_t in_serial) override;

    std::shared_ptr<voice::IRadioVoiceResponse> mRep;
    std::shared_ptr<voice::IRadioVoiceIndication> mInd;
    struct rild_state *mState;

public:
    RadioVoice(struct rild_state *state);
};

/*****************************************************
 * Helpers
 */

// Standard response
#define RESP_SOLICITED RadioResponseType::SOLICITED
// Standard ACK
#define RESP_SOLICITED_ACK RadioResponseType::SOLICITED_ACK
// We expect an ACK
#define RESP_SOLICITED_ACK_EXP RadioResponseType::SOLICITED_ACK_EXP

void buildResponseInfo(RadioResponseInfo &info, int serial, RadioResponseType responseType, RadioError e);

#define RESP_OK(serial)                                                                                                \
    ({                                                                                                                 \
        RadioResponseInfo info;                                                                                        \
        buildResponseInfo(info, serial, RESP_SOLICITED, RadioError::NONE);                                             \
        info;                                                                                                          \
    })


// Helpers defined in qrild_android_config.cc for now
// should be moved
std::string decode_iccid(uint8_t *bcd, uint8_t len);
std::string decode_eid(uint8_t *eid, uint8_t len);
std::string decode_atr(uint8_t *atr, uint8_t len);

#endif // __QRILD_RADIO_HH__