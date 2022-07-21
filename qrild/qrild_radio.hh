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

#include <aidl/android/hardware/radio/modem/BnRadioModem.h>
#include <aidl/android/hardware/radio/modem/BnRadioModemIndication.h>
#include <aidl/android/hardware/radio/modem/BnRadioModemResponse.h>

#include <aidl/android/hardware/radio/network/BnRadioNetwork.h>
#include <aidl/android/hardware/radio/network/BnRadioNetworkIndication.h>
#include <aidl/android/hardware/radio/network/BnRadioNetworkResponse.h>

#include <aidl/android/hardware/radio/sim/BnRadioSim.h>
#include <aidl/android/hardware/radio/sim/BnRadioSimIndication.h>
#include <aidl/android/hardware/radio/sim/BnRadioSimResponse.h>

#include <qrild.h>

using namespace aidl::android::hardware::radio;

/*
using namespace aidl::android::hardware::radio::config;
using namespace aidl::android::hardware::radio::data;
using namespace aidl::android::hardware::radio::messaging;
using namespace aidl::android::hardware::radio::modem;
using namespace aidl::android::hardware::radio::network;
using namespace aidl::android::hardware::radio::sim;
using namespace aidl::android::hardware::radio::voice;
*/

// clang-format off

class RadioConfig : public config::BnRadioConfig {
	ndk::ScopedAStatus getHalDeviceCapabilities(int32_t in_serial) override;
	ndk::ScopedAStatus getNumOfLiveModems(int32_t in_serial) override;
	ndk::ScopedAStatus getPhoneCapability(int32_t in_serial) override;
	ndk::ScopedAStatus getSimSlotsStatus(int32_t in_serial) override;
	ndk::ScopedAStatus setNumOfLiveModems(int32_t in_serial, int8_t in_numOfLiveModems) override;
	ndk::ScopedAStatus setPreferredDataModem(int32_t in_serial, int8_t in_modemId) override;
	ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<config::IRadioConfigResponse> &in_radioConfigResponse, const std::shared_ptr<config::IRadioConfigIndication> &in_radioConfigIndication) override;
	ndk::ScopedAStatus setSimSlotsMapping(int32_t in_serial, const std::vector<config::SlotPortMapping> &in_slotMap) override;

	std::shared_ptr<config::BnRadioConfigResponse> mRep;
	std::shared_ptr<config::BnRadioConfigIndication> mInd;
	struct qrild_state *mState;

    public:
	RadioConfig(struct qrild_state *state);
};

class RadioData : public data::BnRadioData {
	ndk::ScopedAStatus allocatePduSessionId(int32_t in_serial) override;
	ndk::ScopedAStatus getDataCallList(int32_t in_serial) override;
	ndk::ScopedAStatus getSlicingConfig(int32_t in_serial) override;
	ndk::ScopedAStatus releasePduSessionId(int32_t in_serial, int32_t in_id) override;
	ndk::ScopedAStatus setDataAllowed(int32_t in_serial, bool in_allow) override;
	ndk::ScopedAStatus setDataProfile(int32_t in_serial, const std::vector<data::DataProfileInfo> &in_profiles) override;
	ndk::ScopedAStatus setInitialAttachApn(int32_t in_serial, const std::optional<data::DataProfileInfo> &in_dataProfileInfo) override;
	ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<data::IRadioDataResponse>& in_radioDataResponse, const std::shared_ptr<data::IRadioDataIndication>& in_radioDataIndication) override;
	ndk::ScopedAStatus setupDataCall(int32_t in_serial, AccessNetwork in_accessNetwork, const data::DataProfileInfo& in_dataProfileInfo, bool in_roamingAllowed, data::DataRequestReason in_reason, const std::vector<data::LinkAddress>& in_addresses, const std::vector<std::string>& in_dnses, int32_t in_pduSessionId, const std::optional<data::SliceInfo>& in_sliceInfo, bool in_matchAllRuleAllowed) override;

	ndk::ScopedAStatus deactivateDataCall(int32_t in_serial, int32_t in_cid, data::DataRequestReason in_reason) override;

	std::shared_ptr<data::BnRadioDataResponse> mRep;
	std::shared_ptr<data::BnRadioDataIndication> mInd;
	struct qrild_state *mState;

    public:
	RadioData(struct qrild_state *state);
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
	ndk::ScopedAStatus responseAcknowledgement() override;;
	ndk::ScopedAStatus sendDeviceState(int32_t in_serial, modem::DeviceStateType in_deviceStateType, bool in_state) override;
	ndk::ScopedAStatus setRadioCapability(int32_t in_serial, const modem::RadioCapability &in_rc) override;
	ndk::ScopedAStatus setRadioPower(int32_t in_serial, bool in_powerOn, bool in_forEmergencyCall, bool in_preferredForEmergencyCall) override;
	ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr< modem::IRadioModemResponse> &in_radioModemResponse, const std::shared_ptr< modem::IRadioModemIndication> &in_radioModemIndication) override;

	std::shared_ptr<modem::BnRadioModemResponse> mRep;
	std::shared_ptr<modem::BnRadioModemIndication> mInd;
	struct qrild_state *mState;

    public:
	RadioModem(struct qrild_state *state);
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
	ndk::ScopedAStatus responseAcknowledgement() override;;
	ndk::ScopedAStatus setAllowedNetworkTypesBitmap(int32_t in_serial, int32_t in_networkTypeBitmap) override;
	ndk::ScopedAStatus setBandMode(int32_t in_serial, network::RadioBandMode in_mode) override;
	ndk::ScopedAStatus setBarringPassword(int32_t in_serial, const std::string& in_facility, const std::string& in_oldPassword, const std::string& in_newPassword) override;
	ndk::ScopedAStatus setCdmaRoamingPreference(int32_t in_serial, network::CdmaRoamingType in_type) override;
	ndk::ScopedAStatus setCellInfoListRate(int32_t in_serial, int32_t in_rate) override;
	ndk::ScopedAStatus setIndicationFilter(int32_t in_serial, int32_t in_indicationFilter) override;
	ndk::ScopedAStatus setLinkCapacityReportingCriteria(int32_t in_serial, int32_t in_hysteresisMs, int32_t in_hysteresisDlKbps, int32_t in_hysteresisUlKbps, const std::vector<int32_t>& in_thresholdsDownlinkKbps, const std::vector<int32_t>& in_thresholdsUplinkKbps, AccessNetwork in_accessNetwork) override;
	ndk::ScopedAStatus setLocationUpdates(int32_t in_serial, bool in_enable) override;
	ndk::ScopedAStatus setNetworkSelectionModeAutomatic(int32_t in_serial) override;
	ndk::ScopedAStatus setNetworkSelectionModeManual(int32_t in_serial, const std::string& in_operatorNumeric, AccessNetwork in_ran) override;
	ndk::ScopedAStatus setNrDualConnectivityState(int32_t in_serial, network::NrDualConnectivityState in_nrDualConnectivityState) override;
	ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<network::IRadioNetworkResponse>& in_radioNetworkResponse, const std::shared_ptr<network::IRadioNetworkIndication>& in_radioNetworkIndication) override;
	ndk::ScopedAStatus setSignalStrengthReportingCriteria(int32_t in_serial, const std::vector<network::SignalThresholdInfo>& in_signalThresholdInfos) override;
	ndk::ScopedAStatus setSuppServiceNotifications(int32_t in_serial, bool in_enable) override;
	ndk::ScopedAStatus setSystemSelectionChannels(int32_t in_serial, bool in_specifyChannels, const std::vector<network::RadioAccessSpecifier>& in_specifiers) override;
	ndk::ScopedAStatus startNetworkScan(int32_t in_serial, const network::NetworkScanRequest& in_request) override;
	ndk::ScopedAStatus stopNetworkScan(int32_t in_serial) override;
	ndk::ScopedAStatus supplyNetworkDepersonalization(int32_t in_serial, const std::string& in_netPin) override;
	ndk::ScopedAStatus setUsageSetting(int32_t in_serial, network::UsageSetting in_usageSetting) override;
	ndk::ScopedAStatus getUsageSetting(int32_t in_serial) override;

	std::shared_ptr<network::BnRadioNetworkResponse> mRep;
	std::shared_ptr<network::BnRadioNetworkIndication> mInd;
	struct qrild_state *mState;

    public:
	RadioNetwork(struct qrild_state *state);
};

class RadioSim : public sim::BnRadioSim {
	ndk::ScopedAStatus areUiccApplicationsEnabled(int32_t in_serial) override;
	ndk::ScopedAStatus changeIccPin2ForApp(int32_t in_serial, const std::string& in_oldPin2, const std::string& in_newPin2, const std::string& in_aid) override;
	ndk::ScopedAStatus changeIccPinForApp(int32_t in_serial, const std::string& in_oldPin, const std::string& in_newPin, const std::string& in_aid) override;
	ndk::ScopedAStatus enableUiccApplications(int32_t in_serial, bool in_enable) override;
	ndk::ScopedAStatus getAllowedCarriers(int32_t in_serial) override;
	ndk::ScopedAStatus getCdmaSubscription(int32_t in_serial) override;
	ndk::ScopedAStatus getCdmaSubscriptionSource(int32_t in_serial) override;
	ndk::ScopedAStatus getFacilityLockForApp(int32_t in_serial, const std::string& in_facility, const std::string& in_password, int32_t in_serviceClass, const std::string& in_appId) override;
	ndk::ScopedAStatus getIccCardStatus(int32_t in_serial) override;
	ndk::ScopedAStatus getImsiForApp(int32_t in_serial, const std::string& in_aid) override;
	ndk::ScopedAStatus getSimPhonebookCapacity(int32_t in_serial) override;
	ndk::ScopedAStatus getSimPhonebookRecords(int32_t in_serial) override;
	ndk::ScopedAStatus iccCloseLogicalChannel(int32_t in_serial, int32_t in_channelId) override;
	ndk::ScopedAStatus iccIoForApp(int32_t in_serial, const sim::IccIo& in_iccIo) override;
	ndk::ScopedAStatus iccOpenLogicalChannel(int32_t in_serial, const std::string& in_aid, int32_t in_p2) override;
	ndk::ScopedAStatus iccTransmitApduBasicChannel(int32_t in_serial, const sim::SimApdu& in_message) override;
	ndk::ScopedAStatus iccTransmitApduLogicalChannel(int32_t in_serial, const sim::SimApdu& in_message) override;
	ndk::ScopedAStatus reportStkServiceIsRunning(int32_t in_serial) override;
	ndk::ScopedAStatus requestIccSimAuthentication(int32_t in_serial, int32_t in_authContext, const std::string& in_authData, const std::string& in_aid) override;
	ndk::ScopedAStatus responseAcknowledgement() override;;
	ndk::ScopedAStatus sendEnvelope(int32_t in_serial, const std::string& in_contents) override;
	ndk::ScopedAStatus sendEnvelopeWithStatus(int32_t in_serial, const std::string& in_contents) override;
	ndk::ScopedAStatus sendTerminalResponseToSim(int32_t in_serial, const std::string& in_contents) override;
	ndk::ScopedAStatus setAllowedCarriers(int32_t in_serial, const sim::CarrierRestrictions& in_carriers, sim::SimLockMultiSimPolicy in_multiSimPolicy) override;
	ndk::ScopedAStatus setCarrierInfoForImsiEncryption(int32_t in_serial, const sim::ImsiEncryptionInfo& in_imsiEncryptionInfo) override;
	ndk::ScopedAStatus setCdmaSubscriptionSource(int32_t in_serial, sim::CdmaSubscriptionSource in_cdmaSub) override;
	ndk::ScopedAStatus setFacilityLockForApp(int32_t in_serial, const std::string& in_facility, bool in_lockState, const std::string& in_password, int32_t in_serviceClass, const std::string& in_appId) override;
	ndk::ScopedAStatus setResponseFunctions(const std::shared_ptr<sim::IRadioSimResponse>& in_radioSimResponse, const std::shared_ptr<sim::IRadioSimIndication>& in_radioSimIndication) override;
	ndk::ScopedAStatus setSimCardPower(int32_t in_serial, sim::CardPowerState in_powerUp) override;
	ndk::ScopedAStatus setUiccSubscription(int32_t in_serial, const sim::SelectUiccSub& in_uiccSub) override;
	ndk::ScopedAStatus supplyIccPin2ForApp(int32_t in_serial, const std::string& in_pin2, const std::string& in_aid) override;
	ndk::ScopedAStatus supplyIccPinForApp(int32_t in_serial, const std::string& in_pin, const std::string& in_aid) override;
	ndk::ScopedAStatus supplyIccPuk2ForApp(int32_t in_serial, const std::string& in_puk2, const std::string& in_pin2, const std::string& in_aid) override;
	ndk::ScopedAStatus supplyIccPukForApp(int32_t in_serial, const std::string& in_puk, const std::string& in_pin, const std::string& in_aid) override;
	ndk::ScopedAStatus supplySimDepersonalization(int32_t in_serial, sim::PersoSubstate in_persoType, const std::string& in_controlKey) override;
	ndk::ScopedAStatus updateSimPhonebookRecords(int32_t in_serial, const sim::PhonebookRecordInfo& in_recordInfo) override;

	std::shared_ptr<sim::BnRadioSimResponse> mRep;
	std::shared_ptr<sim::BnRadioSimIndication> mInd;
	struct qrild_state *mState;

    public:
	RadioSim(struct qrild_state *state);
};


// clang-format on

#endif // __QRILD_RADIO_HH__
