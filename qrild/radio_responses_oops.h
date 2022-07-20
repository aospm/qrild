class RadioSimIndication : public sim::BnRadioSimIndication {
	ndk::ScopedAStatus carrierInfoForImsiEncryption(RadioIndicationType in_info) override;
	ndk::ScopedAStatus cdmaSubscriptionSourceChanged(RadioIndicationType in_type, sim::CdmaSubscriptionSource in_cdmaSource) override;
	ndk::ScopedAStatus simPhonebookChanged(RadioIndicationType in_type) override;
	ndk::ScopedAStatus simPhonebookRecordsReceived(RadioIndicationType in_type, sim::PbReceivedStatus in_status, const std::vector<sim::PhonebookRecordInfo>& in_records) override;
	ndk::ScopedAStatus simRefresh(RadioIndicationType in_type, const sim::SimRefreshResult& in_refreshResult) override;
	ndk::ScopedAStatus simStatusChanged(RadioIndicationType in_type) override;
	ndk::ScopedAStatus stkEventNotify(RadioIndicationType in_type, const std::string& in_cmd) override;
	ndk::ScopedAStatus stkProactiveCommand(RadioIndicationType in_type, const std::string& in_cmd) override;
	ndk::ScopedAStatus stkSessionEnd(RadioIndicationType in_type) override;
	ndk::ScopedAStatus subscriptionStatusChanged(RadioIndicationType in_type, bool in_activate) override;
	ndk::ScopedAStatus uiccApplicationsEnablementChanged(RadioIndicationType in_type, bool in_enabled) override;

    public:
	RadioSimIndication();
};

class RadioSimResponse : public sim::BnRadioSimResponse {
	ndk::ScopedAStatus acknowledgeRequest(int32_t in_serial) override;
	ndk::ScopedAStatus areUiccApplicationsEnabledResponse(const RadioResponseInfo& in_info, bool in_enabled) override;
	ndk::ScopedAStatus changeIccPin2ForAppResponse(const RadioResponseInfo& in_info, int32_t in_remainingRetries) override;
	ndk::ScopedAStatus changeIccPinForAppResponse(const RadioResponseInfo& in_info, int32_t in_remainingRetries) override;
	ndk::ScopedAStatus enableUiccApplicationsResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus getAllowedCarriersResponse(const RadioResponseInfo& in_info, const sim::CarrierRestrictions& in_carriers, sim::SimLockMultiSimPolicy in_multiSimPolicy) override;
	ndk::ScopedAStatus getCdmaSubscriptionResponse(const RadioResponseInfo& in_info, const std::string& in_mdn, const std::string& in_hSid, const std::string& in_hNid, const std::string& in_min, const std::string& in_prl) override;
	ndk::ScopedAStatus getCdmaSubscriptionSourceResponse(const RadioResponseInfo& in_info, sim::CdmaSubscriptionSource in_source) override;
	ndk::ScopedAStatus getFacilityLockForAppResponse(const RadioResponseInfo& in_info, int32_t in_response) override;
	ndk::ScopedAStatus getIccCardStatusResponse(const RadioResponseInfo& in_info, const sim::CardStatus& in_cardStatus) override;
	ndk::ScopedAStatus getImsiForAppResponse(const RadioResponseInfo& in_info, const std::string& in_imsi) override;
	ndk::ScopedAStatus getSimPhonebookCapacityResponse(const RadioResponseInfo& in_info, const sim::PhonebookCapacity& in_capacity) override;
	ndk::ScopedAStatus getSimPhonebookRecordsResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus iccCloseLogicalChannelResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus iccIoForAppResponse(const RadioResponseInfo& in_info, const sim::IccIoResult& in_iccIo) override;
	ndk::ScopedAStatus iccOpenLogicalChannelResponse(const RadioResponseInfo& in_info, int32_t in_channelId, const std::vector<uint8_t>& in_selectResponse) override;
	ndk::ScopedAStatus iccTransmitApduBasicChannelResponse(const RadioResponseInfo& in_info, const sim::IccIoResult& in_result) override;
	ndk::ScopedAStatus iccTransmitApduLogicalChannelResponse(const RadioResponseInfo& in_info, const sim::IccIoResult& in_result) override;
	ndk::ScopedAStatus reportStkServiceIsRunningResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus requestIccSimAuthenticationResponse(const RadioResponseInfo& in_info, const sim::IccIoResult& in_result) override;
	ndk::ScopedAStatus sendEnvelopeResponse(const RadioResponseInfo& in_info, const std::string& in_commandResponse) override;
	ndk::ScopedAStatus sendEnvelopeWithStatusResponse(const RadioResponseInfo& in_info, const sim::IccIoResult& in_iccIo) override;
	ndk::ScopedAStatus sendTerminalResponseToSimResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setAllowedCarriersResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setCarrierInfoForImsiEncryptionResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setCdmaSubscriptionSourceResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setFacilityLockForAppResponse(const RadioResponseInfo& in_info, int32_t in_retry) override;
	ndk::ScopedAStatus setSimCardPowerResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setUiccSubscriptionResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus supplyIccPin2ForAppResponse(const RadioResponseInfo& in_info, int32_t in_remainingRetries) override;
	ndk::ScopedAStatus supplyIccPinForAppResponse(const RadioResponseInfo& in_info, int32_t in_remainingRetries) override;
	ndk::ScopedAStatus supplyIccPuk2ForAppResponse(const RadioResponseInfo& in_info, int32_t in_remainingRetries) override;
	ndk::ScopedAStatus supplyIccPukForAppResponse(const RadioResponseInfo& in_info, int32_t in_remainingRetries) override;
	ndk::ScopedAStatus supplySimDepersonalizationResponse(const RadioResponseInfo& in_info, sim::PersoSubstate in_persoType, int32_t in_remainingRetries) override;
	ndk::ScopedAStatus updateSimPhonebookRecordsResponse(const RadioResponseInfo& in_info, int32_t in_updatedRecordIndex) override;

    public:
	RadioSimResponse();
};

class RadioNetworkIndication : public network::BnRadioNetworkIndication {
	ndk::ScopedAStatus barringInfoChanged(RadioIndicationType in_type, const network::CellIdentity& in_cellIdentity, const std::vector<network::BarringInfo>& in_barringInfos) override;
	ndk::ScopedAStatus cdmaPrlChanged(RadioIndicationType in_type, int32_t in_version) override;
	ndk::ScopedAStatus cellInfoList(RadioIndicationType in_type, const std::vector<network::CellInfo>& in_records) override;
	ndk::ScopedAStatus currentLinkCapacityEstimate(RadioIndicationType in_type, const network::LinkCapacityEstimate& in_lce) override;
	ndk::ScopedAStatus currentPhysicalChannelConfigs(RadioIndicationType in_type, const std::vector<network::PhysicalChannelConfig>& in_configs) override;
	ndk::ScopedAStatus currentSignalStrength(RadioIndicationType in_type, const network::SignalStrength& in_signalStrength) override;
	ndk::ScopedAStatus imsNetworkStateChanged(RadioIndicationType in_type) override;
	ndk::ScopedAStatus networkScanResult(RadioIndicationType in_type, const network::NetworkScanResult& in_result) override;
	ndk::ScopedAStatus networkStateChanged(RadioIndicationType in_type) override;
	ndk::ScopedAStatus nitzTimeReceived(RadioIndicationType in_type, const std::string& in_nitzTime, int64_t in_receivedTimeMs, int64_t in_ageMs) override;
	ndk::ScopedAStatus registrationFailed(RadioIndicationType in_type, const network::CellIdentity& in_cellIdentity, const std::string& in_chosenPlmn, int32_t in_domain, int32_t in_causeCode, int32_t in_additionalCauseCode) override;
	ndk::ScopedAStatus restrictedStateChanged(RadioIndicationType in_type, network::PhoneRestrictedState in_state) override;
	ndk::ScopedAStatus suppSvcNotify(RadioIndicationType in_type, const network::SuppSvcNotification& in_suppSvc) override;
	ndk::ScopedAStatus voiceRadioTechChanged(RadioIndicationType in_type, RadioTechnology in_rat) override;

    public:
	RadioNetworkIndication();
};

class RadioNetworkResponse : public network::BnRadioNetworkResponse {
	ndk::ScopedAStatus acknowledgeRequest(int32_t in_serial) override;
	ndk::ScopedAStatus getAllowedNetworkTypesBitmapResponse(const RadioResponseInfo& in_info, int32_t in_networkTypeBitmap) override;
	ndk::ScopedAStatus getAvailableBandModesResponse(const RadioResponseInfo& in_info, const std::vector<network::RadioBandMode>& in_bandModes) override;
	ndk::ScopedAStatus getAvailableNetworksResponse(const RadioResponseInfo& in_info, const std::vector<network::OperatorInfo>& in_networkInfos) override;
	ndk::ScopedAStatus getBarringInfoResponse(const RadioResponseInfo& in_info, const network::CellIdentity& in_cellIdentity, const std::vector<network::BarringInfo>& in_barringInfos) override;
	ndk::ScopedAStatus getCdmaRoamingPreferenceResponse(const RadioResponseInfo& in_info, network::CdmaRoamingType in_type) override;
	ndk::ScopedAStatus getCellInfoListResponse(const RadioResponseInfo& in_info, const std::vector<network::CellInfo>& in_cellInfo) override;
	ndk::ScopedAStatus getDataRegistrationStateResponse(const RadioResponseInfo& in_info, const network::RegStateResult& in_dataRegResponse) override;
	ndk::ScopedAStatus getImsRegistrationStateResponse(const RadioResponseInfo& in_info, bool in_isRegistered, RadioTechnologyFamily in_ratFamily) override;
	ndk::ScopedAStatus getNetworkSelectionModeResponse(const RadioResponseInfo& in_info, bool in_manual) override;
	ndk::ScopedAStatus getOperatorResponse(const RadioResponseInfo& in_info, const std::string& in_longName, const std::string& in_shortName, const std::string& in_numeric) override;
	ndk::ScopedAStatus getSignalStrengthResponse(const RadioResponseInfo& in_info, const network::SignalStrength& in_signalStrength) override;
	ndk::ScopedAStatus getSystemSelectionChannelsResponse(const RadioResponseInfo& in_info, const std::vector<network::RadioAccessSpecifier>& in_specifiers) override;
	ndk::ScopedAStatus getVoiceRadioTechnologyResponse(const RadioResponseInfo& in_info, RadioTechnology in_rat) override;
	ndk::ScopedAStatus getVoiceRegistrationStateResponse(const RadioResponseInfo& in_info, const network::RegStateResult& in_voiceRegResponse) override;
	ndk::ScopedAStatus isNrDualConnectivityEnabledResponse(const RadioResponseInfo& in_info, bool in_isEnabled) override;
	ndk::ScopedAStatus setAllowedNetworkTypesBitmapResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setBandModeResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setBarringPasswordResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setCdmaRoamingPreferenceResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setCellInfoListRateResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setIndicationFilterResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setLinkCapacityReportingCriteriaResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setLocationUpdatesResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setNetworkSelectionModeAutomaticResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setNetworkSelectionModeManualResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setNrDualConnectivityStateResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setSignalStrengthReportingCriteriaResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setSuppServiceNotificationsResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setSystemSelectionChannelsResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus startNetworkScanResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus stopNetworkScanResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus supplyNetworkDepersonalizationResponse(const RadioResponseInfo& in_info, int32_t in_remainingRetries) override;
	ndk::ScopedAStatus setUsageSettingResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus getUsageSettingResponse(const RadioResponseInfo& in_info, network::UsageSetting in_usageSetting) override;

    public:
	RadioNetworkResponse();
};

class RadioModemIndication : public modem::BnRadioModemIndication {
	ndk::ScopedAStatus hardwareConfigChanged(RadioIndicationType in_type, const std::vector<modem::HardwareConfig>& in_configs) override;
	ndk::ScopedAStatus modemReset(RadioIndicationType in_type, const std::string& in_reason) override;
	ndk::ScopedAStatus radioCapabilityIndication(RadioIndicationType in_type, const modem::RadioCapability& in_rc) override;
	ndk::ScopedAStatus radioStateChanged(RadioIndicationType in_type, modem::RadioState in_radioState) override;
	ndk::ScopedAStatus rilConnected(RadioIndicationType in_type) override;

    public:
	RadioModemIndication();
};

class RadioModemResponse : public modem::BnRadioModemResponse {
	ndk::ScopedAStatus acknowledgeRequest(int32_t in_serial) override;
	ndk::ScopedAStatus enableModemResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus getBasebandVersionResponse(const RadioResponseInfo& in_info, const std::string& in_version) override;
	ndk::ScopedAStatus getDeviceIdentityResponse(const RadioResponseInfo& in_info, const std::string& in_imei, const std::string& in_imeisv, const std::string& in_esn, const std::string& in_meid) override;
	ndk::ScopedAStatus getHardwareConfigResponse(const RadioResponseInfo& in_info, const std::vector<modem::HardwareConfig>& in_config) override;
	ndk::ScopedAStatus getModemActivityInfoResponse(const RadioResponseInfo& in_info, const modem::ActivityStatsInfo& in_activityInfo) override;
	ndk::ScopedAStatus getModemStackStatusResponse(const RadioResponseInfo& in_info, bool in_isEnabled) override;
	ndk::ScopedAStatus getRadioCapabilityResponse(const RadioResponseInfo& in_info, const modem::RadioCapability& in_rc) override;
	ndk::ScopedAStatus nvReadItemResponse(const RadioResponseInfo& in_info, const std::string& in_result) override;
	ndk::ScopedAStatus nvResetConfigResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus nvWriteCdmaPrlResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus nvWriteItemResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus requestShutdownResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus sendDeviceStateResponse(const RadioResponseInfo& in_info) override;
	ndk::ScopedAStatus setRadioCapabilityResponse(const RadioResponseInfo& in_info, const modem::RadioCapability& in_rc) override;
	ndk::ScopedAStatus setRadioPowerResponse(const RadioResponseInfo& in_info) override;

    public:
	RadioModemResponse();
};

class RadioConfigIndication : public config::BnRadioConfigIndication {
	ndk::ScopedAStatus simSlotsStatusChanged(RadioIndicationType in_type, const std::vector<config::SimSlotStatus> &in_slotStatus) override;

    public:
	RadioConfigIndication();
};

class RadioConfigResponse : public config::BnRadioConfigResponse {
	ndk::ScopedAStatus getHalDeviceCapabilitiesResponse(const RadioResponseInfo &in_info, bool in_modemReducedFeatureSet1) override;
	ndk::ScopedAStatus getNumOfLiveModemsResponse(const RadioResponseInfo &in_info, int8_t in_numOfLiveModems) override;
	ndk::ScopedAStatus getPhoneCapabilityResponse(const RadioResponseInfo &in_info, const config::PhoneCapability &in_phoneCapability) override;
	ndk::ScopedAStatus getSimSlotsStatusResponse(const RadioResponseInfo &in_info, const std::vector<config::SimSlotStatus> &in_slotStatus) override;
	ndk::ScopedAStatus setNumOfLiveModemsResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus setPreferredDataModemResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus setSimSlotsMappingResponse(const RadioResponseInfo &in_info) override;

    public:
	RadioConfigResponse();
};

class RadioDataIndication : public data::BnRadioDataIndication {
	ndk::ScopedAStatus dataCallListChanged(RadioIndicationType in_type, const std::vector<data::SetupDataCallResult> &in_dcList) override;
	ndk::ScopedAStatus keepaliveStatus(RadioIndicationType in_type, const data::KeepaliveStatus &in_status) override;
	ndk::ScopedAStatus pcoData(RadioIndicationType in_type, const data::PcoDataInfo &in_pco) override;
	ndk::ScopedAStatus unthrottleApn(RadioIndicationType in_type, const data::DataProfileInfo &in_dataProfileInfo) override;
	ndk::ScopedAStatus slicingConfigChanged(RadioIndicationType in_type, const data::SlicingConfig &in_slicingConfig) override;

    public:
	RadioDataIndication();
};

class RadioDataResponse : public data::BnRadioDataResponse {
	ndk::ScopedAStatus acknowledgeRequest(int32_t in_serial) override;
	ndk::ScopedAStatus allocatePduSessionIdResponse(const RadioResponseInfo &in_info, int32_t in_id) override;
	ndk::ScopedAStatus cancelHandoverResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus deactivateDataCallResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus getDataCallListResponse(const RadioResponseInfo &in_info, const std::vector<data::SetupDataCallResult> &in_dcResponse) override;
	ndk::ScopedAStatus getSlicingConfigResponse(const RadioResponseInfo &in_info, const data::SlicingConfig &in_slicingConfig) override;
	ndk::ScopedAStatus releasePduSessionIdResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus setDataAllowedResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus setDataProfileResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus setDataThrottlingResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus setInitialAttachApnResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus setupDataCallResponse(const RadioResponseInfo &in_info, const data::SetupDataCallResult &in_dcResponse) override;
	ndk::ScopedAStatus startHandoverResponse(const RadioResponseInfo &in_info) override;
	ndk::ScopedAStatus startKeepaliveResponse(const RadioResponseInfo &in_info, const data::KeepaliveStatus &in_status) override;
	ndk::ScopedAStatus stopKeepaliveResponse(const RadioResponseInfo &in_info) override;

    public:
	RadioDataResponse();
};