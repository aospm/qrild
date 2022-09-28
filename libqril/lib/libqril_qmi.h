#ifndef __LIBQRIL_QMI_H__
#define __LIBQRIL_QMI_H__

#include "qmi_dms.h"
#include "qmi_dpm.h"
#include "qmi_nas.h"
#include "qmi_uim.h"
#include "qmi_wda.h"
#include "qmi_wds.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * QmiProtocolError:
  * @QMI_PROTOCOL_ERROR_NONE: No error.
  * @QMI_PROTOCOL_ERROR_MALFORMED_MESSAGE: Malformed message.
  * @QMI_PROTOCOL_ERROR_NO_MEMORY: No memory.
  * @QMI_PROTOCOL_ERROR_INTERNAL: Internal.
  * @QMI_PROTOCOL_ERROR_ABORTED: Aborted.
  * @QMI_PROTOCOL_ERROR_CLIENT_IDS_EXHAUSTED: Client IDs exhausted.
  * @QMI_PROTOCOL_ERROR_UNABORTABLE_TRANSACTION: Unabortable transaction.
  * @QMI_PROTOCOL_ERROR_INVALID_CLIENT_ID: Invalid client ID.
  * @QMI_PROTOCOL_ERROR_NO_THRESHOLDS_PROVIDED: No thresholds provided.
  * @QMI_PROTOCOL_ERROR_INVALID_HANDLE: Invalid handle.
  * @QMI_PROTOCOL_ERROR_INVALID_PROFILE: Invalid profile.
  * @QMI_PROTOCOL_ERROR_INVALID_PIN_ID: Invalid PIN ID.
  * @QMI_PROTOCOL_ERROR_INCORRECT_PIN: Incorrect PIN.
  * @QMI_PROTOCOL_ERROR_NO_NETWORK_FOUND: No network found.
  * @QMI_PROTOCOL_ERROR_CALL_FAILED: Call failed.
  * @QMI_PROTOCOL_ERROR_OUT_OF_CALL: Out of call.
  * @QMI_PROTOCOL_ERROR_NOT_PROVISIONED: Not provisioned.
  * @QMI_PROTOCOL_ERROR_MISSING_ARGUMENT: Missing argument.
  * @QMI_PROTOCOL_ERROR_ARGUMENT_TOO_LONG: Argument too long.
  * @QMI_PROTOCOL_ERROR_INVALID_TRANSACTION_ID: Invalid transaction ID.
  * @QMI_PROTOCOL_ERROR_DEVICE_IN_USE: Device in use.
  * @QMI_PROTOCOL_ERROR_NETWORK_UNSUPPORTED: Network unsupported.
  * @QMI_PROTOCOL_ERROR_DEVICE_UNSUPPORTED: Device unsupported.
  * @QMI_PROTOCOL_ERROR_NO_EFFECT: No effect.
  * @QMI_PROTOCOL_ERROR_NO_FREE_PROFILE: No free profile.
  * @QMI_PROTOCOL_ERROR_INVALID_PDP_TYPE: Invalid PDP type.
  * @QMI_PROTOCOL_ERROR_INVALID_TECHNOLOGY_PREFERENCE: Invalid technology preference.
  * @QMI_PROTOCOL_ERROR_INVALID_PROFILE_TYPE: Invalid profile type.
  * @QMI_PROTOCOL_ERROR_INVALID_SERVICE_TYPE: Invalid service type.
  * @QMI_PROTOCOL_ERROR_INVALID_REGISTER_ACTION: Invalid register action.
  * @QMI_PROTOCOL_ERROR_INVALID_PS_ATTACH_ACTION: Invalid PS attach action.
  * @QMI_PROTOCOL_ERROR_AUTHENTICATION_FAILED: Authentication failed.
  * @QMI_PROTOCOL_ERROR_PIN_BLOCKED: PIN blocked.
  * @QMI_PROTOCOL_ERROR_PIN_ALWAYS_BLOCKED: PIN always blocked.
  * @QMI_PROTOCOL_ERROR_UIM_UNINITIALIZED: UIM uninitialized.
  * @QMI_PROTOCOL_ERROR_MAXIMUM_QOS_REQUESTS_IN_USE: Maximum QoS requests in use.
  * @QMI_PROTOCOL_ERROR_INCORRECT_FLOW_FILTER: Incorrect flow filter.
  * @QMI_PROTOCOL_ERROR_NETWORK_QOS_UNAWARE: Network QoS unaware.
  * @QMI_PROTOCOL_ERROR_INVALID_QOS_ID: Invalid QoS ID.
  * @QMI_PROTOCOL_ERROR_REQUESTED_NUMBER_UNSUPPORTED: Requested number unsupported. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_INTERFACE_NOT_FOUND: Interface not found. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FLOW_SUSPENDED: Flow suspended.
  * @QMI_PROTOCOL_ERROR_INVALID_DATA_FORMAT: Invalid data format. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_GENERAL_ERROR: General error.
  * @QMI_PROTOCOL_ERROR_UNKNOWN_ERROR: Unknown error.
  * @QMI_PROTOCOL_ERROR_INVALID_ARGUMENT: Invalid argument.
  * @QMI_PROTOCOL_ERROR_INVALID_INDEX: Invalid index.
  * @QMI_PROTOCOL_ERROR_NO_ENTRY: No entry.
  * @QMI_PROTOCOL_ERROR_DEVICE_STORAGE_FULL: Device storage full.
  * @QMI_PROTOCOL_ERROR_DEVICE_NOT_READY: Device not ready.
  * @QMI_PROTOCOL_ERROR_NETWORK_NOT_READY: Network not ready.
  * @QMI_PROTOCOL_ERROR_WMS_CAUSE_CODE: WMS cause code.
  * @QMI_PROTOCOL_ERROR_WMS_MESSAGE_NOT_SENT: WMS message not sent.
  * @QMI_PROTOCOL_ERROR_WMS_MESSAGE_DELIVERY_FAILURE: WMS message delivery failure.
  * @QMI_PROTOCOL_ERROR_WMS_INVALID_MESSAGE_ID: WMS invalid message ID.
  * @QMI_PROTOCOL_ERROR_WMS_ENCODING: WMS encoding.
  * @QMI_PROTOCOL_ERROR_AUTHENTICATION_LOCK: Authentication lock.
  * @QMI_PROTOCOL_ERROR_INVALID_TRANSITION: Invalid transition.
  * @QMI_PROTOCOL_ERROR_NOT_MCAST_INTERFACE: Not a multicast interface. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_MAXIMUM_MCAST_REQUESTS_IN_USE: Maximum multicast requests in use. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_INVALID_MCAST_HANDLE: Invalid mulitcast handle. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_INVALID_IP_FAMILY_PREFERENCE: Invalid IP family preference. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_SESSION_INACTIVE: Session inactive.
  * @QMI_PROTOCOL_ERROR_SESSION_INVALID: Session invalid.
  * @QMI_PROTOCOL_ERROR_SESSION_OWNERSHIP: Session ownership.
  * @QMI_PROTOCOL_ERROR_INSUFFICIENT_RESOURCES: Insufficient resources.
  * @QMI_PROTOCOL_ERROR_DISABLED: Disabled.
  * @QMI_PROTOCOL_ERROR_INVALID_OPERATION: Invalid operation.
  * @QMI_PROTOCOL_ERROR_INVALID_QMI_COMMAND: Invalid QMI command.
  * @QMI_PROTOCOL_ERROR_WMS_T_PDU_TYPE: WMS T-PDU type.
  * @QMI_PROTOCOL_ERROR_WMS_SMSC_ADDRESS: WMS SMSC address.
  * @QMI_PROTOCOL_ERROR_INFORMATION_UNAVAILABLE: Information unavailable.
  * @QMI_PROTOCOL_ERROR_SEGMENT_TOO_LONG: Segment too long.
  * @QMI_PROTOCOL_ERROR_SEGMENT_ORDER: Segment order.
  * @QMI_PROTOCOL_ERROR_BUNDLING_NOT_SUPPORTED: Bundling not supported.
  * @QMI_PROTOCOL_ERROR_OPERATION_PARTIAL_FAILURE: Operation partial failure. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_POLICY_MISMATCH: Policy mismatch. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_SIM_FILE_NOT_FOUND: SIM file not found.
  * @QMI_PROTOCOL_ERROR_EXTENDED_INTERNAL: Extended internal error. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_ACCESS_DENIED: Access denied.
  * @QMI_PROTOCOL_ERROR_HARDWARE_RESTRICTED: Hardware restricted.
  * @QMI_PROTOCOL_ERROR_ACK_NOT_SENT: ACK not sent. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_INJECT_TIMEOUT: Inject timeout. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_INCOMPATIBLE_STATE: Incompatible state. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_FDN_RESTRICT: FDN restrict. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_SUPS_FAILURE_CASE: SUPS failure case. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_NO_RADIO: No radio. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_NOT_SUPPORTED: Not supported. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_NO_SUBSCRIPTION: No subscription. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_CARD_CALL_CONTROL_FAILED: Card call control failed. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_NETWORK_ABORTED: Network aborted. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_MSG_BLOCKED: Message blocked. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_INVALID_SESSION_TYPE: Invalid session type. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_INVALID_PB_TYPE: Invalid PB type. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_NO_SIM: No SIM. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PB_NOT_READY: PB not ready. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PIN_RESTRICTION: PIN restriction. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PIN2_RESTRICTION: PIN2 restriction. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PUK_RESTRICTION: PUK restriction. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PUK2_RESTRICTION: PUK2 restriction. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PB_ACCESS_RESTRICTED: PB access restricted. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PB_DELETE_IN_PROGRESS: PB delete in progress. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_PB_TEXT_TOO_LONG: PB text too long. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PB_NUMBER_TOO_LONG: PB number too long. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PB_HIDDEN_KEY_RESTRICTION: PB hidden key restriction. Since: 1.6.
  * @QMI_PROTOCOL_ERROR_PB_NOT_AVAILABLE: PB not available. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_DEVICE_MEMORY_ERROR: Device memory error. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_NO_PERMISSION: No permission. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_TOO_SOON: Too soon. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_TIME_NOT_ACQUIRED: Time not acquired. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_OPERATION_IN_PROGRESS: Operation in progress. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FW_WRITE_FAILED: Firmware write failed. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FW_INFO_READ_FAILED: Firmware info read failed. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FW_FILE_NOT_FOUND: Firmware file not found. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FW_DIR_NOT_FOUND: Firmware dir not found. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FW_ALREADY_ACTIVATED: Firmware already activated. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FW_CANNOT_GENERIC_IMAGE: Firmware cannot generic image. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FW_FILE_OPEN_FAILED: Firmware file open failed. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FW_UPDATE_DISCONTINUOUS_FRAME: Firmware update discontinuous frame. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_FW_UPDATE_FAILED: Firmware update failed. Since: 1.22.
  * @QMI_PROTOCOL_ERROR_CAT_EVENT_REGISTRATION_FAILED: Event registration failed.
  * @QMI_PROTOCOL_ERROR_CAT_INVALID_TERMINAL_RESPONSE: Invalid terminal response.
  * @QMI_PROTOCOL_ERROR_CAT_INVALID_ENVELOPE_COMMAND: Invalid envelope command.
  * @QMI_PROTOCOL_ERROR_CAT_ENVELOPE_COMMAND_BUSY: Envelope command busy.
  * @QMI_PROTOCOL_ERROR_CAT_ENVELOPE_COMMAND_FAILED: Envelope command failed.
  *
  * QMI protocol errors.
  *
  * Since: 1.0
  */
enum qmi_error { /*< since=1.0 >*/
		 QMI_ERR_NONE = 0, /*< nick=None >*/
		 QMI_ERR_MALFORMED_MESSAGE = 1, /*< nick=MalformedMessage >*/
		 QMI_ERR_NO_MEMORY = 2, /*< nick=NoMemory >*/
		 QMI_ERR_INTERNAL = 3, /*< nick=Internal >*/
		 QMI_ERR_ABORTED = 4, /*< nick=Aborted >*/
		 QMI_ERR_CLIENT_IDS_EXHAUSTED = 5, /*< nick=ClientIdsExhausted >*/
		 QMI_ERR_UNABORTABLE_TRANSACTION = 6, /*< nick=UnabortableTransaction >*/
		 QMI_ERR_INVALID_CLIENT_ID = 7, /*< nick=InvalidClientId >*/
		 QMI_ERR_NO_THRESHOLDS_PROVIDED = 8, /*< nick=NoThresholdsProvided >*/
		 QMI_ERR_INVALID_HANDLE = 9, /*< nick=InvalidHandle >*/
		 QMI_ERR_INVALID_PROFILE = 10, /*< nick=InvalidProfile >*/
		 QMI_ERR_INVALID_PIN_ID = 11, /*< nick=InvalidPinId >*/
		 QMI_ERR_INCORRECT_PIN = 12, /*< nick=IncorrectPin >*/
		 QMI_ERR_NO_NETWORK_FOUND = 13, /*< nick=NoNetworkFound >*/
		 QMI_ERR_CALL_FAILED = 14, /*< nick=CallFailed >*/
		 QMI_ERR_OUT_OF_CALL = 15, /*< nick=OutOfCall >*/
		 QMI_ERR_NOT_PROVISIONED = 16, /*< nick=NotProvisioned >*/
		 QMI_ERR_MISSING_ARGUMENT = 17, /*< nick=MissingArgument >*/
		 QMI_ERR_ARGUMENT_TOO_LONG = 19, /*< nick=ArgumentTooLong >*/
		 QMI_ERR_INVALID_TRANSACTION_ID = 22, /*< nick=InvalidTransactionId >*/
		 QMI_ERR_DEVICE_IN_USE = 23, /*< nick=DeviceInUse >*/
		 QMI_ERR_NETWORK_UNSUPPORTED = 24, /*< nick=NetworkUnsupported >*/
		 QMI_ERR_DEVICE_UNSUPPORTED = 25, /*< nick=DeviceUnsupported >*/
		 QMI_ERR_NO_EFFECT = 26, /*< nick=NoEffect >*/
		 QMI_ERR_NO_FREE_PROFILE = 27, /*< nick=NoFreeProfile >*/
		 QMI_ERR_INVALID_PDP_TYPE = 28, /*< nick=InvalidPdpType >*/
		 QMI_ERR_INVALID_TECHNOLOGY_PREFERENCE =
			 29, /*< nick=InvalidTechnologyPreference >*/
		 QMI_ERR_INVALID_PROFILE_TYPE = 30, /*< nick=InvalidProfileType >*/
		 QMI_ERR_INVALID_SERVICE_TYPE = 31, /*< nick=InvalidServiceType >*/
		 QMI_ERR_INVALID_REGISTER_ACTION = 32, /*< nick=InvalidRegisterAction >*/
		 QMI_ERR_INVALID_PS_ATTACH_ACTION = 33, /*< nick=InvalidPsAttachAction >*/
		 QMI_ERR_AUTHENTICATION_FAILED = 34, /*< nick=AuthenticationFailed >*/
		 QMI_ERR_PIN_BLOCKED = 35, /*< nick=PinBlocked >*/
		 QMI_ERR_PIN_ALWAYS_BLOCKED = 36, /*< nick=PinAlwaysBlocked >*/
		 QMI_ERR_UIM_UNINITIALIZED = 37, /*< nick=UimUninitialized >*/
		 QMI_ERR_MAXIMUM_QOS_REQUESTS_IN_USE = 38, /*< nick=MaximumQosRequestsInUse >*/
		 QMI_ERR_INCORRECT_FLOW_FILTER = 39, /*< nick=IncorrectFlowFilter >*/
		 QMI_ERR_NETWORK_QOS_UNAWARE = 40, /*< nick=NetworkQosUnaware >*/
		 QMI_ERR_INVALID_QOS_ID = 41, /*< nick=InvalidQosId >*/
		 QMI_ERR_REQUESTED_NUMBER_UNSUPPORTED = 42, /*< nick=RequestedNumberUnsupported >*/
		 QMI_ERR_INTERFACE_NOT_FOUND = 43, /*< nick=InterfaceNotFound >*/
		 QMI_ERR_FLOW_SUSPENDED = 44, /*< nick=FlowSuspended >*/
		 QMI_ERR_INVALID_DATA_FORMAT = 45, /*< nick=InvalidDataFormat >*/
		 QMI_ERR_GENERAL_ERROR = 46, /*< nick=GeneralError >*/
		 QMI_ERR_UNKNOWN_ERROR = 47, /*< nick=UnknownError >*/
		 QMI_ERR_INVALID_ARGUMENT = 48, /*< nick=InvalidArgument >*/
		 QMI_ERR_INVALID_INDEX = 49, /*< nick=InvalidIndex >*/
		 QMI_ERR_NO_ENTRY = 50, /*< nick=NoEntry >*/
		 QMI_ERR_DEVICE_STORAGE_FULL = 51, /*< nick=DeviceStorageFull >*/
		 QMI_ERR_DEVICE_NOT_READY = 52, /*< nick=DeviceNotReady >*/
		 QMI_ERR_NETWORK_NOT_READY = 53, /*< nick=NetworkNotReady >*/
		 QMI_ERR_WMS_CAUSE_CODE = 54, /*< nick=WmsCauseCode >*/
		 QMI_ERR_WMS_MESSAGE_NOT_SENT = 55, /*< nick=WmsMessageNotSent >*/
		 QMI_ERR_WMS_MESSAGE_DELIVERY_FAILURE = 56, /*< nick=WmsMessageDeliveryFailure >*/
		 QMI_ERR_WMS_INVALID_MESSAGE_ID = 57, /*< nick=WmsInvalidMessageId >*/
		 QMI_ERR_WMS_ENCODING = 58, /*< nick=WmsEncoding >*/
		 QMI_ERR_AUTHENTICATION_LOCK = 59, /*< nick=AuthenticationLock >*/
		 QMI_ERR_INVALID_TRANSITION = 60, /*< nick=InvalidTransition >*/
		 QMI_ERR_NOT_MCAST_INTERFACE = 61, /*< nick=NotMcastInterface >*/
		 QMI_ERR_MAXIMUM_MCAST_REQUESTS_IN_USE = 62, /*< nick=MaximumMcastRequestsInUse >*/
		 QMI_ERR_INVALID_MCAST_HANDLE = 63, /*< nick=InvalidMcastHandle >*/
		 QMI_ERR_INVALID_IP_FAMILY_PREFERENCE = 64, /*< nick=InvalidIpFamilyPreference >*/
		 QMI_ERR_SESSION_INACTIVE = 65, /*< nick=SessionInactive >*/
		 QMI_ERR_SESSION_INVALID = 66, /*< nick=SessionInvalid >*/
		 QMI_ERR_SESSION_OWNERSHIP = 67, /*< nick=SessionOwnership >*/
		 QMI_ERR_INSUFFICIENT_RESOURCES = 68, /*< nick=InsufficientResources >*/
		 QMI_ERR_DISABLED = 69, /*< nick=Disabled >*/
		 QMI_ERR_INVALID_OPERATION = 70, /*< nick=InvalidOperation >*/
		 QMI_ERR_INVALID_QMI_COMMAND = 71, /*< nick=InvalidQmiCommand >*/
		 QMI_ERR_WMS_T_PDU_TYPE = 72, /*< nick=WmsTPduType >*/
		 QMI_ERR_WMS_SMSC_ADDRESS = 73, /*< nick=WmsSmscAddress >*/
		 QMI_ERR_INFORMATION_UNAVAILABLE = 74, /*< nick=InformationUnavailable >*/
		 QMI_ERR_SEGMENT_TOO_LONG = 75, /*< nick=SegmentTooLong >*/
		 QMI_ERR_SEGMENT_ORDER = 76, /*< nick=SegmentOrder >*/
		 QMI_ERR_BUNDLING_NOT_SUPPORTED = 77, /*< nick=BundlingNotSupported >*/
		 QMI_ERR_OPERATION_PARTIAL_FAILURE = 78, /*< nick=OperationPartialFailure >*/
		 QMI_ERR_POLICY_MISMATCH = 79, /*< nick=PolicyMismatch >*/
		 QMI_ERR_SIM_FILE_NOT_FOUND = 80, /*< nick=SimFileNotFound >*/
		 QMI_ERR_EXTENDED_INTERNAL = 81, /*< nick=ExtendedInternal >*/
		 QMI_ERR_ACCESS_DENIED = 82, /*< nick=AccessDenied >*/
		 QMI_ERR_HARDWARE_RESTRICTED = 83, /*< nick=HardwareRestricted >*/
		 QMI_ERR_ACK_NOT_SENT = 84, /*< nick=AckNotSent >*/
		 QMI_ERR_INJECT_TIMEOUT = 85, /*< nick=InjectTimeout >*/
		 QMI_ERR_INCOMPATIBLE_STATE = 90, /*< nick=IncompatibleState >*/
		 QMI_ERR_FDN_RESTRICT = 91, /*< nick=FdnRestrict >*/
		 QMI_ERR_SUPS_FAILURE_CASE = 92, /*< nick=SupsFailureCase >*/
		 QMI_ERR_NO_RADIO = 93, /*< nick=NoRadio >*/
		 QMI_ERR_NOT_SUPPORTED = 94, /*< nick=NotSupported >*/
		 QMI_ERR_NO_SUBSCRIPTION = 95, /*< nick=NoSubscription >*/
		 QMI_ERR_CARD_CALL_CONTROL_FAILED = 96, /*< nick=CardCallControlFailed >*/
		 QMI_ERR_NETWORK_ABORTED = 97, /*< nick=NetworkAborted >*/
		 QMI_ERR_MSG_BLOCKED = 98, /*< nick=MsgBlocked >*/
		 QMI_ERR_INVALID_SESSION_TYPE = 100, /*< nick=InvalidSessionType >*/
		 QMI_ERR_INVALID_PB_TYPE = 101, /*< nick=InvalidPbType >*/
		 QMI_ERR_NO_SIM = 102, /*< nick=NoSim >*/
		 QMI_ERR_PB_NOT_READY = 103, /*< nick=PbNotReady >*/
		 QMI_ERR_PIN_RESTRICTION = 104, /*< nick=PinRestriction >*/
		 QMI_ERR_PIN2_RESTRICTION = 105, /*< nick=Pin1Restriction >*/
		 QMI_ERR_PUK_RESTRICTION = 106, /*< nick=PukRestriction >*/
		 QMI_ERR_PUK2_RESTRICTION = 107, /*< nick=Puk2Restriction >*/
		 QMI_ERR_PB_ACCESS_RESTRICTED = 108, /*< nick=PbAccessRestricted >*/
		 QMI_ERR_PB_DELETE_IN_PROGRESS = 109, /*< nick=PbDeleteInProgress >*/
		 QMI_ERR_PB_TEXT_TOO_LONG = 110, /*< nick=PbTextTooLong >*/
		 QMI_ERR_PB_NUMBER_TOO_LONG = 111, /*< nick=PbNumberTooLong >*/
		 QMI_ERR_PB_HIDDEN_KEY_RESTRICTION = 112, /*< nick=PbHiddenKeyRestriction >*/
		 QMI_ERR_PB_NOT_AVAILABLE = 113, /*< nick=PbNotAvailable >*/
		 QMI_ERR_DEVICE_MEMORY_ERROR = 114, /*< nick=DeviceMemoryError >*/
		 QMI_ERR_NO_PERMISSION = 115, /*< nick=NoPermission >*/
		 QMI_ERR_TOO_SOON = 116, /*< nick=TooSoon >*/
		 QMI_ERR_TIME_NOT_ACQUIRED = 117, /*< nick=TimeNotAcquired >*/
		 QMI_ERR_OPERATION_IN_PROGRESS = 118, /*< nick=OperationInProgress >*/
		 QMI_ERR_FW_WRITE_FAILED = 388, /*< nick=FwWriteFailed >*/
		 QMI_ERR_FW_INFO_READ_FAILED = 389, /*< nick=FwInfoReadFailed >*/
		 QMI_ERR_FW_FILE_NOT_FOUND = 390, /*< nick=FwFileNotFound >*/
		 QMI_ERR_FW_DIR_NOT_FOUND = 391, /*< nick=FwDirNotFound >*/
		 QMI_ERR_FW_ALREADY_ACTIVATED = 392, /*< nick=FwAlreadyActivated >*/
		 QMI_ERR_FW_CANNOT_GENERIC_IMAGE = 393, /*< nick=FwCannotGenericImage >*/
		 QMI_ERR_FW_FILE_OPEN_FAILED = 400, /*< nick=FwFileOpenFailed >*/
		 QMI_ERR_FW_UPDATE_DISCONTINUOUS_FRAME =
			 401, /*< nick=FwUpdateDiscontinuousFrame >*/
		 QMI_ERR_FW_UPDATE_FAILED = 402, /*< nick=FwUpdateFailed >*/
		 QMI_ERR_CAT_EVENT_REGISTRATION_FAILED =
			 61441, /*< nick=CatEventRegistrationFailed >*/
		 QMI_ERR_CAT_INVALID_TERMINAL_RESPONSE =
			 61442, /*< nick=CatInvalidTerminalResponse >*/
		 QMI_ERR_CAT_INVALID_ENVELOPE_COMMAND =
			 61443, /*< nick=CatInvalidEnvelopeCommand >*/
		 QMI_ERR_CAT_ENVELOPE_COMMAND_BUSY = 61444, /*< nick=CatEnvelopeCommandBusy >*/
		 QMI_ERR_CAT_ENVELOPE_COMMAND_FAILED = 61445, /*< nick=CatEnvelopeCommandFailed >*/
};

/**
 * QmiService:
 * @QMI_SERVICE_UNKNOWN: Unknown service.
 * @QMI_SERVICE_CTL: Control service.
 * @QMI_SERVICE_WDS: Wireless Data Service.
 * @QMI_SERVICE_DMS: Device Management Service.
 * @QMI_SERVICE_NAS: Network Access Service.
 * @QMI_SERVICE_QOS: Quality Of Service service.
 * @QMI_SERVICE_WMS: Wireless Messaging Service.
 * @QMI_SERVICE_PDS: Position Determination Service.
 * @QMI_SERVICE_AUTH: Authentication service.
 * @QMI_SERVICE_AT: AT service.
 * @QMI_SERVICE_VOICE: Voice service.
 * @QMI_SERVICE_CAT2: Card Application Toolkit service (v2).
 * @QMI_SERVICE_UIM: User Identity Module service.
 * @QMI_SERVICE_PBM: Phonebook Management service.
 * @QMI_SERVICE_QCHAT: QCHAT service. Since: 1.8.
 * @QMI_SERVICE_RMTFS: Remote file system service.
 * @QMI_SERVICE_TEST: Test service. Since: 1.8.
 * @QMI_SERVICE_LOC: Location service (~ PDS v2).
 * @QMI_SERVICE_SAR: Service access proxy service.
 * @QMI_SERVICE_IMS: IMS settings service. Since: 1.8.
 * @QMI_SERVICE_ADC: Analog to digital converter driver service. Since: 1.8.
 * @QMI_SERVICE_CSD: Core sound driver service. Since: 1.8.
 * @QMI_SERVICE_MFS: Modem embedded file system service. Since: 1.8.
 * @QMI_SERVICE_TIME: Time service. Since: 1.8.
 * @QMI_SERVICE_TS: Thermal sensors service. Since: 1.8.
 * @QMI_SERVICE_TMD: Thermal mitigation device service. Since: 1.8.
 * @QMI_SERVICE_SAP: Service access proxy service. Since: 1.8.
 * @QMI_SERVICE_WDA: Wireless data administrative service. Since: 1.8.
 * @QMI_SERVICE_TSYNC: TSYNC control service. Since: 1.8.
 * @QMI_SERVICE_RFSA: Remote file system access service. Since: 1.8.
 * @QMI_SERVICE_CSVT: Circuit switched videotelephony service. Since: 1.8.
 * @QMI_SERVICE_QCMAP: Qualcomm mobile access point service. Since: 1.8.
 * @QMI_SERVICE_IMSP: IMS presence service. Since: 1.8.
 * @QMI_SERVICE_IMSVT: IMS videotelephony service. Since: 1.8.
 * @QMI_SERVICE_IMSA: IMS application service. Since: 1.8.
 * @QMI_SERVICE_COEX: Coexistence service. Since: 1.8.
 * @QMI_SERVICE_PDC: Persistent device configuration service. Since: 1.8.
 * @QMI_SERVICE_STX: Simultaneous transmit service. Since: 1.8.
 * @QMI_SERVICE_BIT: Bearer independent transport service. Since: 1.8.
 * @QMI_SERVICE_IMSRTP: IMS RTP service. Since: 1.8.
 * @QMI_SERVICE_RFRPE: RF radiated performance enhancement service. Since: 1.8.
 * @QMI_SERVICE_DSD: Data system determination service. Since: 1.8.
 * @QMI_SERVICE_SSCTL: Subsystem control service. Since: 1.8.
 * @QMI_SERVICE_DPM: Data Port Mapper service. Since: 1.30.
 * @QMI_SERVICE_CAT: Card Application Toolkit service (v1).
 * @QMI_SERVICE_RMS: Remote Management Service.
 * @QMI_SERVICE_OMA: Open Mobile Alliance device management service.
 * @QMI_SERVICE_FOTA: Firmware Over The Air service. Since: 1.24.
 * @QMI_SERVICE_GMS: Telit General Modem Service. Since: 1.24.
 * @QMI_SERVICE_GAS: Telit General Application Service. Since: 1.24.
 *
 * QMI services.
 *
 * Since: 1.0
 */
enum qmi_service { /*< since=1.0 >*/
		   QMI_SERVICE_UNKNOWN = -1,
		   QMI_SERVICE_CTL = 0x00,
		   QMI_SERVICE_WDS = 0x01,
		   QMI_SERVICE_DMS = 0x02,
		   QMI_SERVICE_NAS = 0x03,
		   QMI_SERVICE_QOS = 0x04,
		   QMI_SERVICE_WMS = 0x05,
		   QMI_SERVICE_PDS = 0x06,
		   QMI_SERVICE_AUTH = 0x07,
		   QMI_SERVICE_AT = 0x08,
		   QMI_SERVICE_VOICE = 0x09,
		   QMI_SERVICE_CAT2 = 0x0A,
		   QMI_SERVICE_UIM = 0x0B,
		   QMI_SERVICE_PBM = 0x0C,
		   QMI_SERVICE_QCHAT = 0x0D,
		   QMI_SERVICE_RMTFS = 0x0E,
		   QMI_SERVICE_TEST = 0x0F,
		   QMI_SERVICE_LOC = 0x10,
		   QMI_SERVICE_SAR = 0x11,
		   QMI_SERVICE_IMS = 0x12,
		   QMI_SERVICE_ADC = 0x13,
		   QMI_SERVICE_CSD = 0x14,
		   QMI_SERVICE_MFS = 0x15,
		   QMI_SERVICE_TIME = 0x16,
		   QMI_SERVICE_TS = 0x17,
		   QMI_SERVICE_TMD = 0x18,
		   QMI_SERVICE_SAP = 0x19,
		   QMI_SERVICE_WDA = 0x1A,
		   QMI_SERVICE_TSYNC = 0x1B,
		   QMI_SERVICE_RFSA = 0x1C,
		   QMI_SERVICE_CSVT = 0x1D,
		   QMI_SERVICE_QCMAP = 0x1E,
		   QMI_SERVICE_IMSP = 0x1F,
		   QMI_SERVICE_IMSVT = 0x20,
		   QMI_SERVICE_IMSA = 0x21,
		   QMI_SERVICE_COEX = 0x22,
		   /* 0x23, reserved */
		   QMI_SERVICE_PDC = 0x24,
		   /* 0x25, reserved */
		   QMI_SERVICE_STX = 0x26,
		   QMI_SERVICE_BIT = 0x27,
		   QMI_SERVICE_IMSRTP = 0x28,
		   QMI_SERVICE_RFRPE = 0x29,
		   QMI_SERVICE_DSD = 0x2A,
		   QMI_SERVICE_SSCTL = 0x2B,
		   QMI_SERVICE_DPM = 0x2F,
		   QMI_SERVICE_CAT = 0xE0,
		   QMI_SERVICE_RMS = 0xE1,
		   QMI_SERVICE_OMA = 0xE2,
		   QMI_SERVICE_FOTA = 0xE6,
		   QMI_SERVICE_GMS = 0xE7,
		   QMI_SERVICE_GAS = 0xE8,
};

#ifdef __cplusplus
}
#endif

#endif