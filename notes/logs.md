# Radio logs

## First boot qrild logcat log

```log
02-12 14:55:25.154   686   686 I android.hardware.radio: adding qrild service instance: android.hardware.radio.config.IRadioConfig/default
02-12 14:55:25.155   686   686 I android.hardware.radio: adding qrild service instance: android.hardware.radio.messaging.IRadioMessaging/slot1
02-12 14:55:25.156   686   686 I qrild.IModem: HACK: Powering on modem...
02-12 14:55:25.274   686   686 I android.hardware.radio: adding qrild service instance: android.hardware.radio.modem.IRadioModem/slot1
02-12 14:55:25.275   686   686 I android.hardware.radio: adding qrild service instance: android.hardware.radio.data.IRadioData/slot1
02-12 14:55:25.325   686   686 I android.hardware.radio: adding qrild service instance: android.hardware.radio.network.IRadioNetwork/slot1
02-12 14:55:25.326   686   686 I android.hardware.radio: adding qrild service instance: android.hardware.radio.sim.IRadioSim/slot1
02-12 14:55:25.328   686   686 I android.hardware.radio: adding qrild service instance: android.hardware.radio.voice.IRadioVoice/slot1
02-12 14:55:27.117   686   689 I qrild.INetwork: reportSystemStatus: FIXME! implement this
02-12 14:55:27.135   686   689 I qrild.INetwork: reportSystemStatus: FIXME! implement this
02-12 14:55:27.137   686   689 I qrild.INetwork: reportSystemStatus: FIXME! implement this
08-02 00:04:29.981   686   686 E qrild.IModem: Reporting radio state ON
08-02 00:04:30.032   686   686 I qrild.IModem: HardwareConfig{type: 0, uuid: org.linaro.qrild.lm1, state: 0, modem: [HardwareConfigModem{rilModel: 0, rat: LTE, maxVoiceCalls: 1, maxDataCalls: 1, maxStandby: 2}], sim: []}
08-02 00:04:30.032   686   686 I qrild.ISim: (nop) got Cdma subscription source: RUIM_SIM
08-02 00:04:30.034   686   686 I qrild.IModem: setRadioPower(powerOn: 0, forEmergencyCall: 0, preferredForEmergencyCall: 0)
08-02 00:04:30.084   686   686 I qrild.IModem: Set modem operating mode to: !
08-02 00:04:30.128   686   689 I qrild.INetwork: reportSystemStatus: FIXME! implement this
08-02 00:04:30.128   686   689 I qrild.INetwork: reportSystemStatus: FIXME! implement this
08-02 00:04:30.184   686   686 I qrild.INetwork: getSignalStrengthLteSignalStrength{signalStrength: -128, rsrp: 65, rsrq: 18, rssnr: 16, cqi: 13, timingAdvance: 647, cqiTableIndex: 5}
08-02 00:04:30.641   686   686 I qrild.ISim: getIccCardStatus: err: NONE
08-02 00:04:30.641   686   686 I qrild.ISim: 	CardStatus{cardState: 1, universalPinState: UNKNOWN, gsmUmtsSubscriptionAppIndex: 0, cdmaSubscriptionAppIndex: 0, imsSubscriptionAppIndex: 0, applications: [AppStatus{appType: 2, appState: 1, persoSubstate: UNKNOWN, aidPtr: a000810ffff800000, appLabelPtr: , pin1Replaced: false, pin1: UNKNOWN, pin2: UNKNOWN}], atr: 39981c83e7f216d01c10c0, iccid: 8420099350, eid: , slotMap: SlotPortMapping{physicalSlotId: 1, portId: 0}}
08-02 00:04:30.751   686   686 E qrild.ISim: areUiccApplicationsEnabled: Hardcode enable UICC application
08-02 00:04:30.807   686   686 I qrild.IModem: getDeviceIdentity: IMEI: 869295038309353, ESN: 8018E647, MEID: 99001202896467
08-02 00:04:30.807   686   686 I qrild.INetwork: getOperator FIXME: hardcoded values
08-02 00:04:30.808   686   686 I qrild.IModem: setRadioPower(powerOn: 1, forEmergencyCall: 0, preferredForEmergencyCall: 0)
08-02 00:04:30.918   686   686 I qrild.IModem: Set modem operating mode to:
08-02 00:04:30.919   686   686 I qrild.IModem: setRadioPower(powerOn: 1, forEmergencyCall: 0, preferredForEmergencyCall: 0)
08-02 00:04:30.969   686   686 I qrild.IModem: Modem already in mode:
08-02 00:04:30.969   686   686 I qrild.INetwork: getOperator FIXME: hardcoded values
08-02 00:04:30.969   686   686 I qrild.IModem: Got device state: CHARGING_STATE
08-02 00:04:30.969   686   686 I qrild.IModem: Got device state: LOW_DATA_EXPECTED
08-02 00:04:30.970   686   686 I qrild.INetwork: setIndicationFilter Filters:
08-02 00:04:30.970   686   686 I qrild.INetwork: SIGNAL_STRENGTH
08-02 00:04:30.970   686   686 I qrild.INetwork: FULL_NETWORK_STATE
08-02 00:04:30.971   686   686 I qrild.INetwork: DATA_CALL_DORMANCY_CHANGED
08-02 00:04:30.971   686   686 I qrild.INetwork: LINK_CAPACITY_ESTIMATE
08-02 00:04:30.971   686   686 I qrild.INetwork: PHYSICAL_CHANNEL_CONFIG
08-02 00:04:30.971   686   686 I qrild.INetwork: REGISTRATION_FAILURE
08-02 00:04:30.971   686   686 I qrild.IModem: Got device state: POWER_SAVE_MODE
08-02 00:04:30.972   686   686 I qrild.IModem: Got device state: CHARGING_STATE
08-02 00:04:30.972   686   686 I qrild.IModem: Got device state: LOW_DATA_EXPECTED
08-02 00:04:30.972   686   686 I qrild.IModem: Got device state: POWER_SAVE_MODE
08-02 00:04:30.973   686   686 I qrild.INetwork: setIndicationFilter Filters:
08-02 00:04:30.973   686   686 I qrild.INetwork: SIGNAL_STRENGTH
08-02 00:04:30.973   686   686 I qrild.INetwork: FULL_NETWORK_STATE
08-02 00:04:30.974   686   686 I qrild.INetwork: DATA_CALL_DORMANCY_CHANGED
08-02 00:04:30.974   686   686 I qrild.INetwork: LINK_CAPACITY_ESTIMATE
08-02 00:04:30.974   686   686 I qrild.INetwork: PHYSICAL_CHANNEL_CONFIG
08-02 00:04:30.975   686   686 I qrild.INetwork: REGISTRATION_FAILURE
08-02 00:04:31.027   686   686 I qrild.IModem: getModemStackStatus: 1
08-02 00:04:31.119   686   686 W qrild.ISim: iccOpenLogicalChannel: FIXME! TODO:? aid: A00000015144414300, p2: 0
08-02 00:04:31.159   686   686 I qrild.INetwork: getOperator FIXME: hardcoded values
08-02 00:04:31.166   686   686 I qrild.ISim: getCdmaSubscriptionSource: FIXME: hardcoded to RUIM_SIM
08-02 00:04:31.169   686   686 I qrild.INetwork: setIndicationFilter Filters:
08-02 00:04:31.169   686   686 I qrild.INetwork: SIGNAL_STRENGTH
08-02 00:04:31.169   686   686 I qrild.INetwork: FULL_NETWORK_STATE
08-02 00:04:31.170   686   686 I qrild.INetwork: DATA_CALL_DORMANCY_CHANGED
08-02 00:04:31.170   686   686 I qrild.INetwork: LINK_CAPACITY_ESTIMATE
08-02 00:04:31.170   686   686 I qrild.INetwork: PHYSICAL_CHANNEL_CONFIG
08-02 00:04:31.170   686   686 I qrild.INetwork: REGISTRATION_FAILURE
08-02 00:04:31.355   686   686 W qrild.ISim: iccOpenLogicalChannel: FIXME! TODO:? aid: A00000015141434C00, p2: 0
08-02 00:04:31.557   686   689 I qrild.INetwork: reportSystemStatus: FIXME! implement this
08-02 00:04:31.563   686   689 I qrild.INetwork: reportSystemStatus: FIXME! implement this
08-02 00:04:31.564   686   689 I qrild.INetwork: reportSystemStatus: FIXME! implement this
08-02 00:04:31.676   686   686 W qrild.ISim: iccOpenLogicalChannel: FIXME! TODO:? aid: A000000063504B43532D3135, p2: 4
```

## First boot qrild stdout/err log

```log
DEBUG android.hardware.radio-service: | Type | Node | Port | Major | Minor | Service Name
DEBUG android.hardware.radio-service: |   66 |    0 |     1 |  180  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   43 |    0 |     4 |   18  |    0  | QMI_SERVICE_SSCTL
DEBUG android.hardware.radio-service: |   15 |    0 |    22 |    0  |    0  | QMI_SERVICE_TEST
DEBUG android.hardware.radio-service: |   51 |    0 |    23 |    2  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   21 |    0 |    24 |    0  |    0  | QMI_SERVICE_MFS
DEBUG android.hardware.radio-service: |   24 |    0 |    25 |    0  |    0  | QMI_SERVICE_TMD
DEBUG android.hardware.radio-service: |   23 |    0 |    26 |    0  |    0  | QMI_SERVICE_TS
DEBUG android.hardware.radio-service: |   22 |    0 |    27 |    0  |    0  | QMI_SERVICE_TIME
DEBUG android.hardware.radio-service: |   36 |    0 |    29 |    0  |    0  | QMI_SERVICE_PDC
DEBUG android.hardware.radio-service: |   49 |    0 |    30 |    2  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   54 |    0 |    35 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   17 |    0 |    36 |    0  |    0  | QMI_SERVICE_SAR
DEBUG android.hardware.radio-service: |   74 |    0 |    37 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: | 4098 |    0 |    38 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   34 |    0 |    40 |    0  |    0  | QMI_SERVICE_COEX
DEBUG android.hardware.radio-service: |   41 |    0 |    43 |    1  |    0  | QMI_SERVICE_RFRPE
DEBUG android.hardware.radio-service: |  228 |    0 |    46 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   55 |    0 |    47 |    2  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   50 |    0 |    51 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |    9 |    0 |    53 |    0  |    0  | QMI_SERVICE_VOICE
DEBUG android.hardware.radio-service: |    3 |    0 |    54 |    0  |    0  | QMI_SERVICE_NAS
DEBUG android.hardware.radio-service: |   12 |    0 |    55 |    0  |    0  | QMI_SERVICE_PBM
DEBUG android.hardware.radio-service: |   10 |    0 |    56 |    0  |    0  | QMI_SERVICE_CAT2
DEBUG android.hardware.radio-service: |    1 |    0 |    57 |    0  |    0  | QMI_SERVICE_WDS
DEBUG android.hardware.radio-service: |    4 |    0 |    58 |    0  |    0  | QMI_SERVICE_QOS
DEBUG android.hardware.radio-service: |   26 |    0 |    59 |    0  |    0  | QMI_SERVICE_WDA
DEBUG android.hardware.radio-service: |    7 |    0 |    60 |    0  |    0  | QMI_SERVICE_AUTH
DEBUG android.hardware.radio-service: |    8 |    0 |    61 |    0  |    0  | QMI_SERVICE_AT
DEBUG android.hardware.radio-service: |   29 |    0 |    62 |    0  |    0  | QMI_SERVICE_CSVT
DEBUG android.hardware.radio-service: |   47 |    0 |    63 |    0  |    0  | QMI_SERVICE_DPM
DEBUG android.hardware.radio-service: |   11 |    0 |    64 |    0  |    0  | QMI_SERVICE_UIM
DEBUG android.hardware.radio-service: |   71 |    0 |    65 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   42 |    0 |    71 |    0  |    0  | QMI_SERVICE_DSD
DEBUG android.hardware.radio-service: |    2 |    0 |    72 |    0  |    0  | QMI_SERVICE_DMS
DEBUG android.hardware.radio-service: |    5 |    0 |    74 |    0  |    0  | QMI_SERVICE_WMS
DEBUG android.hardware.radio-service: |   48 |    0 |    75 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   68 |    0 |    76 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   16 |    0 |    77 |    0  |    0  | QMI_SERVICE_LOC
DEBUG android.hardware.radio-service: |   51 |    0 |    84 |    3  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   69 |    0 |    85 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   77 |    0 |    87 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   33 |    0 |    90 |    0  |    0  | QMI_SERVICE_IMSA
DEBUG android.hardware.radio-service: |   18 |    0 |    91 |    0  |    0  | QMI_SERVICE_IMS
DEBUG android.hardware.radio-service: |   14 |    1 |    14 |    0  |    0  | QMI_SERVICE_RMTFS
DEBUG android.hardware.radio-service: |   49 |    1 | 16387 |    1  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   64 |    1 | 16393 |    1  |    0  | <unknown>
DEBUG android.hardware.radio-service: | 4096 |    1 | 16396 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   15 |    5 |     1 |   32  |    0  | QMI_SERVICE_TEST
DEBUG android.hardware.radio-service: |   66 |    5 |     2 |   74  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   43 |    5 |     5 |   20  |    0  | QMI_SERVICE_SSCTL
DEBUG android.hardware.radio-service: |   51 |    5 |     6 |    5  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   24 |    5 |     8 |    1  |    0  | QMI_SERVICE_TMD
DEBUG android.hardware.radio-service: |   15 |    5 |     9 |   33  |    0  | QMI_SERVICE_TEST
DEBUG android.hardware.radio-service: |  769 |    5 |    11 |    0  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   15 |   10 |     1 |   64  |    0  | QMI_SERVICE_TEST
DEBUG android.hardware.radio-service: |   66 |   10 |     2 |   76  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   43 |   10 |     5 |   23  |    0  | QMI_SERVICE_SSCTL
DEBUG android.hardware.radio-service: |   51 |   10 |     6 |   13  |    0  | <unknown>
DEBUG android.hardware.radio-service: |   24 |   10 |     8 |   67  |    0  | QMI_SERVICE_TMD
DEBUG android.hardware.radio-service: Operating mode:
	mode: 5
	hw_restriced: No

DEBUG android.hardware.radio-service: Freeing msg {id: 2d, txn: 4}
DEBUG android.hardware.radio-service: Freeing msg {id: 2e, txn: 5}
DEBUG android.hardware.radio-service: Freeing msg {id: 3, txn: 6}
DEBUG android.hardware.radio-service: Freeing msg {id: 24, txn: 1}
DEBUG android.hardware.radio-service: Freeing msg {id: 53, txn: 2}
DEBUG android.hardware.radio-service: Freeing msg {id: 24, txn: 3}
DEBUG android.hardware.radio-service: Freeing msg {id: 51, txn: 4}
DEBUG android.hardware.radio-service: Freeing msg {id: 53, txn: 5}
DEBUG android.hardware.radio-service: Freeing msg {id: 24, txn: 6}
DEBUG android.hardware.radio-service: Operating mode:
	mode: 0
	hw_restriced: No

DEBUG android.hardware.radio-service: Freeing msg {id: 2d, txn: 7}
DEBUG android.hardware.radio-service: Operating mode:
	mode: 0
	hw_restriced: No

DEBUG android.hardware.radio-service: Freeing msg {id: 2d, txn: 8}
DEBUG android.hardware.radio-service: Operating mode:
	mode: 0
	hw_restriced: No

DEBUG android.hardware.radio-service: Freeing msg {id: 2d, txn: 9}
xRadioConfig::RadioConfig
-RadioMessaging::RadioMessaging
xRadioModem::RadioModem
Waiting for response to msg {id: 0x2d, txn: 4}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:04:00:2d:00:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x2d, txn: 4, type: 2
QRTR RX:
02:04:00:2d:00:0b:00:02:04:00:00:00:00:00:01:01:00:05

Found msg (id: 0x2d (4 == 4)) with matching txn
Got response for msg {id: 0x2d, txn: 4}: {id: 0x2d, txn: 4} (rc: 0)
Modem state: 5
Turning on modem
Waiting for response to msg {id: 0x2e, txn: 5}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:05:00:2e:00:04:00:01:01:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x2e, txn: 5, type: 2
QRTR RX:
02:05:00:2e:00:07:00:02:04:00:00:00:00:00

Found msg (id: 0x2e (5 == 5)) with matching txn
Got response for msg {id: 0x2e, txn: 5}: {id: 0x2e, txn: 5} (rc: 0)
-RadioData::RadioData
xRadioNetwork::RadioNetwork
Waiting for response to msg {id: 0x3, txn: 6}
Sending to service 'QMI_SERVICE_NAS'
QRTR TX:
00:06:00:03:00:41:00:10:01:00:00:12:01:00:00:13:01:00:01:14:01:00:00:15:01:00:01:17:01:00:01:18:01:00:00:19:01:00:01:1a:01:00:01:1b:01:00:00:1c:01:00:00:1d:01:00:01:1e:01:00:01:1f:01:00:00:20

01:00:00:21:02:00:01:01

[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x 3, txn: 6, type: 2
QRTR RX:
02:06:00:03:00:07:00:02:04:00:00:00:00:00

Found msg (id: 0x3 (6 == 6)) with matching txn
Got response for msg {id: 0x3, txn: 6}: {id: 0x3, txn: 6} (rc: 0)
-RadioSim::RadioSim
-RadioVoice::RadioVoice
[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x24, txn: 1, type: 4
QRTR RX:
04:01:00:24:00:15:00:01:06:00:02:02:02:00:01:00:11:01:00:00:22:05:00:00:00:00:00:00

[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x53, txn: 2, type: 4
QRTR RX:
04:02:00:53:00:04:00:12:01:00:ff

[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x24, txn: 3, type: 4
QRTR RX:
04:03:00:24:00:25:00:01:06:00:02:02:02:02:01:04:11:01:00:00:12:05:00:ea:00:1e:00:00:22:05:00:01:01:00:00:00:29:05:00:ea:00:1e:00:00

[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x51, txn: 4, type: 4
QRTR RX:
04:04:00:51:00:04:00:12:01:00:a4

[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x53, txn: 5, type: 4
QRTR RX:
04:05:00:53:00:04:00:12:01:00:ff

nas_serving_system_ind_get_plmn: expected at least 6 bytes but got 5
[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x24, txn: 6, type: 4
QRTR RX:
04:06:00:24:00:1f:00:01:06:00:02:02:02:02:01:04:10:01:00:00:11:01:00:00:15:03:00:01:04:00:22:05:00:01:03:00:00:00

xRadioModem::setResponseFunctions
Waiting for response to msg {id: 0x2d, txn: 7}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:07:00:2d:00:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x2d, txn: 7, type: 2
QRTR RX:
02:07:00:2d:00:0b:00:02:04:00:00:00:00:00:01:01:00:00

Found msg (id: 0x2d (7 == 7)) with matching txn
Got response for msg {id: 0x2d, txn: 7}: {id: 0x2d, txn: 7} (rc: 0)
xRadioData::setResponseFunctions
xRadioMessaging::setResponseFunctions
xRadioNetwork::setResponseFunctions
xRadioSim::setResponseFunctions
xRadioVoice::setResponseFunctions
xRadioModem::getHardwareConfig
Waiting for response to msg {id: 0x2d, txn: 8}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:08:00:2d:00:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x2d, txn: 8, type: 2
QRTR RX:
02:08:00:2d:00:0b:00:02:04:00:00:00:00:00:01:01:00:00

Found msg (id: 0x2d (8 == 8)) with matching txn
Got response for msg {id: 0x2d, txn: 8}: {id: 0x2d, txn: 8} (rc: 0)
xRadioSim::setCdmaSubscriptionSource
xRadioConfig::setResponseFunctions
xRadioModem::setRadioPower
Waiting for response to msg {id: 0x2d, txn: 9}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:09:00:2d:00:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x2d, txn: 9, type: 2
QRTR RX:
02:09:00:2d:00:0b:00:02:04:00:00:00:00:00:01:01:00:00

Found msg (id: 0x2d (9 == 9)) with matching txn
Got response for msg {id: 0x2d, txn: 9}: {id: 0x2d, txn: 9} (rc: 0)
Waiting for response to msg {id: 0x2e, txn: 10}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:0a:00:2e:00:04:00:01:01:00:01

[QRTR] data packet from QMI_SERVICE_DMS, msDEBUG android.hardware.radio-service: Freeing msg {id: 2e, txn: 10}
DEBUG android.hardware.radio-service: Freeing msg {id: 24, txn: 7}
DEBUG android.hardware.radio-service: Freeing msg {id: 24, txn: 8}
DEBUG android.hardware.radio-service: Freeing msg {id: 47, txn: 12}
DEBUG android.hardware.radio-service: Freeing msg {id: 2f, txn: 13}
DEBUG android.hardware.radio-service: Freeing msg {id: 47, txn: 14}
g_id: 0x2e, txn: 10, type: 2
QRTR RX:
02:0a:00:2e:00:07:00:02:04:00:00:00:00:00

Found msg (id: 0x2e (10 == 10)) with matching txn
Got response for msg {id: 0x2e, txn: 10}: {id: 0x2e, txn: 10} (rc: 0)
Set operating mode to 1
xRadioConfig::getHalDeviceCapabilities
[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x24, txn: 7, type: 4
QRTR RX:
04:07:00:24:00:15:00:01:06:00:00:02:02:00:01:00:11:01:00:00:22:05:00:00:03:00:00:00

[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x24, txn: 8, type: 4
QRTR RX:
04:08:00:24:00:15:00:01:06:00:00:02:02:00:01:00:11:01:00:00:22:05:00:00:03:00:00:00

xRadioNetwork::getSignalStrength
Waiting for response to msg {id: 0x20, txn: 11}
Sending to service 'QMI_SERVICE_NAS'
QRTR TX:
00:0b:00:20:00:05:00:10:02:00:40:00

[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x20, txn: 11, type: 2
QRTR RX:
02:0b:00:20:00:0c:00:02:04:00:00:00:00:00:01:02:00:80:00

Found msg (id: 0x20 (11 == 11)) with matching txn
Got response for msg {id: 0x20, txn: 11}: {id: 0x20, txn: 11} (rc: 0)
xRadioVoice::setTtyMode
(nop) Set TTY mode to OFF
xRadioSim::getIccCardStatus
Waiting for response to msg {id: 0x47, txn: 12}
Sending to service 'QMI_SERVICE_UIM'
QRTR TX:
00:0c:00:47:00:00:00

[QRTR] data packet from QMI_SERVICE_UIM, msg_id: 0x47, txn: 12, type: 2
QRTR RX:
02:0c:00:47:00:50:00:02:04:00:00:00:00:00:11:24:00:02:02:00:00:00:00:15:3b:9e:95:80:1f:c7:80:31:e0:73:fe:21:1b:66:d0:02:17:c7:11:00:c0:00:00:00:00:00:00:00:00:10:1f:00:02:02:00:00:00:01:00:00

00:01:0a:98:44:02:10:30:99:09:73:55:f0:02:00:00:00:01:00:00:00:02:00

Found msg (id: 0x47 (12 == 12)) with matching txn
Got response for msg {id: 0x47, txn: 12}: {id: 0x47, txn: 12} (rc: 0)
Waiting for response to msg {id: 0x2f, txn: 13}
Sending to service 'QMI_SERVICE_UIM'
QRTR TX:
00:0d:00:2f:00:00:00

[QRTR] data packet from QMI_SERVICE_UIM, msg_id: 0x2f, txn: 13, type: 2
QRTR RX:
02:0d:00:2f:00:55:00:02:04:00:00:00:00:00:16:09:00:02:00:00:00:00:00:00:00:00:15:03:00:02:00:00:11:03:00:02:02:02:10:33:00:ff:ff:ff:ff:ff:ff:ff:ff:02:01:00:00:00:00:01:02:01:00:0b:00:00:10:a0

00:00:00:87:10:02:ff:ff:ff:ff:89:03:02:00:00:00:00:00:00:00:00:00:02:00:00:00:03:00

Found msg (id: 0x2f (13 == 13)) with matching txn
Got response for msg {id: 0x2f, txn: 13}: {id: 0x2f, txn: 13} (rc: 0)
index_gw_primary: 65535, index_1x_primary: 65535, index_gw_secondary: 65535, index_1x_secondary: 65535, cards_n: 2
card 0:
	card_state: 1, upin_state: 0, upin_retries: 0, upuk_retries: 0, error_code: 0, applications_n: 1,
	application 0:
		type: 2, state: 1, personalization_state: 0, personalization_feature: 11, personalization_retries: 0, application_identifier_value_n: 16,
		application identifier
			[160], [0], [0], [0], [135], [16], [2], [255], [255], [255], [255], [137], [3], [2], [0], [0],
		pin2_state: 0, pin2_retries: 0, puk2_retries: 0,
card 1:
	card_state: 2, upin_state: 0, upin_retries: 0, upuk_retries: 0, error_code: 3, applications_n: 0,
xRadioConfig::getSimSlotsStatus
Waiting for response to msg {id: 0x47, txn: 14}
Sending to service 'QMI_SERVICE_UIM'
QRTR TX:
00:0e:00:47:00:00:00

[QRTR] data packet from QMI_SERVICE_UIM, msg_id: 0x47, txn: 14, type: 2
QRTR RX:
02:0e:00:47:00:50:00:02:04:00:00:00:00:00:11:24:00:02:02:00:00:00:00:15:3b:9e:95:80:1f:c7:80:31:e0:73:fe:21:1b:66:d0:02:17:c7:11:00:c0:00:00:00:00:00:00:00:00:10:1f:00:02:02:00:00:00:01:00:00

00:01:0a:98:44:02:10:30:99:09:73:55:f0:02:00:00:00:01:00:00:00:02:00

Found msg (id: 0x47 (14 == 14)) with matching txn
Got response for msg {id: 0x47, txn: 14}: {id: 0x47, txn: 14} (rc: 0)
Slot 0
	cardState: 1
	logicalSlotId: 0
	portActive: 1
	FIXME! should start with 3B!!! ATR: 39981c83e7f216d01c10c0
	EID:
	ICCID: 8420099350
xRadioVoice::getCurrentCalls
xRadioModem::getBasebandVersion
Waiting for response to msg {id: 0x23, txn: 15}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:0f:00:23:00:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x23, txn: 15, type: 2
QRTR RX:
02:0f:00:23:00:60:00:02:04:00:00:00:00:00:01:56:00:4d:50:53:53:2e:41:54:2e:34:2e:30:2e:63:32:2e:31:35:2d:30:30:30:30:37:2d:53:44:4d:38:34DEBUG android.hardware.radio-service: Freeing msg {id: 23, txn: 15}
DEBUG android.hardware.radio-service: Freeing msg {id: 25, txn: 16}
DEBUG android.hardware.radio-service: Operating mode:
	mode: 1
	hw_restriced: No

DEBUG android.hardware.radio-service: Freeing msg {id: 2d, txn: 17}
DEBUG android.hardware.radio-service: Freeing msg {id: 2e, txn: 18}
DEBUG android.hardware.radio-service: Operating mode:
	mode: 0
	hw_restriced: No

DEBUG android.hardware.radio-service: Freeing msg {id: 2d, txn: 19}
:35:5f:47:45:4e:5f:50:41:43:4b:2d:31:2e:33:35:38:38:38

30:2e:31:2e:33:39:39:32:35:36:2e:32:20:20:31:20:20:5b:4d:61:79:20:30:39:20:32:30:32:31:20:32:32:3a:30:30:3a:30:30:5d

Found msg (id: 0x23 (15 == 15)) with matching txn
Got response for msg {id: 0x23, txn: 15}: {id: 0x23, txn: 15} (rc: 0)
xRadioNetwork::setSignalStrengthReportingCriteria
xRadioSim::areUiccApplicationsEnabled
xRadioModem::getDeviceIdentity
Waiting for response to msg {id: 0x25, txn: 16}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:10:00:25:00:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x25, txn: 16, type: 2
QRTR RX:
02:10:00:25:00:39:00:02:04:00:00:00:00:00:10:08:00:38:30:31:38:45:36:34:37:11:0f:00:38:36:39:32:39:35:30:33:38:33:30:39:33:35:33:12:0e:00:39:39:30:30:31:32:30:32:38:39:36:34:36:37:13:01:00:32

Found msg (id: 0x25 (16 == 16)) with matching txn
Got response for msg {id: 0x25, txn: 16}: {id: 0x25, txn: 16} (rc: 0)
xRadioNetwork::setSignalStrengthReportingCriteria
xRadioModem::getRadioCapability
xRadioNetwork::getOperator
xRadioModem::setRadioPower
Waiting for response to msg {id: 0x2d, txn: 17}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:11:00:2d:00:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x2d, txn: 17, type: 2
QRTR RX:
02:11:00:2d:00:0b:00:02:04:00:00:00:00:00:01:01:00:01

Found msg (id: 0x2d (17 == 17)) with matching txn
Got response for msg {id: 0x2d, txn: 17}: {id: 0x2d, txn: 17} (rc: 0)
Waiting for response to msg {id: 0x2e, txn: 18}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:12:00:2e:00:04:00:01:01:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x2e, txn: 18, type: 2
QRTR RX:
02:12:00:2e:00:07:00:02:04:00:00:00:00:00

Found msg (id: 0x2e (18 == 18)) with matching txn
Got response for msg {id: 0x2e, txn: 18}: {id: 0x2e, txn: 18} (rc: 0)
Set operating mode to 0
xRadioNetwork::getNetworkSelectionMode
xRadioModem::setRadioPower
Waiting for response to msg {id: 0x2d, txn: 19}
Sending to service 'QMI_SERVICE_DMS'
QRTR TX:
00:13:00:2d:00:00:00

[QRTR] data packet from QMI_SERVICE_DMS, msg_id: 0x2d, txn: 19, type: 2
QRTR RX:
02:13:00:2d:00:0b:00:02:04:00:00:00:00:00:01:01:00:00

Found msg (id: 0x2d (19 == 19)) with matching txn
Got response for msg {id: 0x2d, txn: 19}: {id: 0x2d, txn: 19} (rc: 0)
xRadioNetwork::getOperator
xRadioModem::sendDeviceState
xRadioNetwork::getNetworkSelectionMode
xRadioModem::sendDeviceState
xRadioNetwork::setIndicationFilter
xRadioModem::sendDeviceState
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioModem::sendDeviceState
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioModem::sendDeviceState
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioModem::sendDeviceState
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioNetwork::setIndicationFilter
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioNetwork::setLinkCapacityReportingCriteria
xRadioModem::getModemStackStatus
xRadioConfig::getPhoneCapability
xRadioSim::iccOpenLogicalChannel
xRadioConfig::setPreferredDataModem
(nop) Setting modem to 0
xRadioNetwork::getOperator
xRadioNetwork::getNetworkSelectionMode
xRadioVoice::getCurrentCalls
xRadioNetwork::getImsRegistrationState
xRadioNetwork::getVoiceRadioTechnology
xRadioSim::getCdmaSubscriptionSource
xRadioNetwork::setIndicationFilter
xRadioNetwork::getBarringInfo
Waiting for response to msg {id: 0xac, txn: 20}
Sending to service 'QMI_SERVICE_NAS'
QRTR TX:
00:14:00:ac:00:00:00

[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0xac, txn: 20, type: 2
QRTR RX:
02:14:00:ac:00:07:00:02:04:00:01:00:4a:00

Found msg (id: 0xac (20 == 20)) with matching txn
Got response for msg {id: 0xac, txn: 20}: {id: 0xac, txn: 20} (rc: 0)
xRadioConfig::setPreferredDataModem
(nop) Setting modem to 0
xRadioNetwork::setSignalStrengthReportingCriteria
xRadioSim::iccOpenLogicalChannel
[QRTR] data packet from QMI_SERVICE_NAS, msg_id: 0x24, txn: 9, type: 4
QRTR RX:
04:09:00:2DEBUG android.hardware.radio-service: Freeing msg {id: 24, txn: 9}
DEBUG android.hardware.radio-service: Freeing msg {id: 24, txn: 10}
DEBUG android.hardware.radio-service: Freeing msg {id: 51, txn: 11}
DEBUG android.hardware.radio-service: Freeing msg {id: 53, txn: 12}
DEBUG android.hardware.radio-service: Freeing msg {id: 24, txn: 13}
```

## Telephony RIL first boot logs

```log
08-02 00:04:22.494   695   695 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:25.534   695  1840 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:27.476   695  1857 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:27.532   695  1841 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:27.647   695   762 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:27.663   695   695 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:27.730   695   695 D TelephonyRegistry: systemRunning register for intents
08-02 00:04:27.986   695   725 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:28.162  2109  2109 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:29.498   695   712 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:29.608   695   695 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:29.609  1937  1937 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:29.616   695   695 D TelephonyRegistry: notifyCellLocationForSubscriber: subId=2147483647 cellIdentity=null
08-02 00:04:29.651   695   762 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:29.881  2202  2202 D TelephonyComponentFactory: validated paths: null
08-02 00:04:29.881  2202  2202 D TelephonyComponentFactory: Total components injected: 0
08-02 00:04:29.882  2202  2202 D TDC     : updateOrInsert: inserting: Modem { uuid=a-real-modem-i-promise, state=0, rilModel=0, rat={0, 1, 2}, maxActiveVoiceCall=0, maxActiveDataCall=1, maxStandby=1 }
08-02 00:04:29.883  2202  2202 D TDC     : updateOrInsert: inserting: Sim { uuid=totally-a-real-sim-card, modemUuid=a-real-modem-i-promise, state=0 }
08-02 00:04:29.887  2202  2202 D PersistAtomsStorage: PersistAtoms file not found
08-02 00:04:29.892  2202  2202 D PersistAtomsStorage: created new PersistAtoms
08-02 00:04:29.920  2202  2202 D MetricsCollector: registered
08-02 00:04:29.926  2202  2202 D CdmaSSM : subscriptionSource from settings: 0
08-02 00:04:29.926  2202  2202 I PhoneFactory: Cdma Subscription set to 0
08-02 00:04:29.927  2202  2202 I PhoneFactory: Network Mode set to 0
08-02 00:04:29.928  2202  2202 D RILJ    : RIL: init allowedNetworkTypes=50055 cdmaSubscription=0) [PHONEnull]
08-02 00:04:29.958  2202  2202 D RadioModemProxy: AIDL initialized
08-02 00:04:29.964  2202  2236 D RILJ    : [UNSL]< UNSOL_RIL_CONNECTED [PHONE0]
08-02 00:04:29.965  2202  2202 D RILJ    : [0000]> GET_HARDWARE_CONFIG [PHONE0]
08-02 00:04:29.967  2202  2202 D RadioDataProxy: AIDL initialized
08-02 00:04:29.970  2202  2202 D RadioMessagingProxy: AIDL initialized
08-02 00:04:29.971  2202  2236 D RILJ    : [0001]> RADIO_POWER on = false forEmergencyCall= false preferredForEmergencyCall=false [PHONE0]
08-02 00:04:29.973  2202  2202 D RadioNetworkProxy: AIDL initialized
08-02 00:04:29.976  2202  2202 D RadioSimProxy: AIDL initialized
08-02 00:04:29.979  2202  2202 D RadioVoiceProxy: AIDL initialized
08-02 00:04:29.980  2202  2202 D RILJ    : Radio HAL version: 2.0 [PHONE0]
08-02 00:04:29.982  2202  2202 D UiccController: Creating UiccController
08-02 00:04:29.983  2202  2202 D UiccController: config_num_physical_slots = 2
08-02 00:04:29.984  2202  2236 D RILJ    : [0002]> CDMA_SET_SUBSCRIPTION_SOURCE cdmaSubscription = 0 [PHONE0]
08-02 00:04:29.986  2202  2236 D RILJ    : [UNSL]< UNSOL_RESPONSE_RADIO_STATE_CHANGED radioStateChanged: 2 [PHONE0]
08-02 00:04:29.987  2202  2236 D RILJ    : [UNSL]< UNSOL_RESPONSE_RADIO_STATE_CHANGED radioStateChanged: 1 [PHONE0]
08-02 00:04:29.992  2202  2364 D RadioConfig: [0003]> GET_HAL_DEVICE_CAPABILITIES
08-02 00:04:29.993  2202  2364 E RadioInterfaceCapabilityController: getRadioInterfaceCapabilities: Radio Capabilities not loaded in time
08-02 00:04:30.000  2202  2202 D PinStorage: KeyStore: alias PinStorage_longTerm_always_key does not exist - Creating (exp=, auth=false)
08-02 00:04:30.019  2202  2202 D PinStorage: onDeviceReady
08-02 00:04:30.021  2202  2202 D PinStorage: KeyStore: alias PinStorage_shortTerm_key does not exist - Nothing to do
08-02 00:04:30.028  2202  2202 I PhoneFactory: Creating SubscriptionController
08-02 00:04:30.034  2202  2221 D RILJ    : [0002]< CDMA_SET_SUBSCRIPTION_SOURCE  [PHONE0]
08-02 00:04:30.035  2202  2236 D RILJ    : [0000]< GET_HARDWARE_CONFIG  [Modem { uuid=org.linaro.qrild.lm1, state=0, rilModel=0, rat={0, 1, 2}, maxActiveVoiceCall=1, maxActiveDataCall=1, maxStandby=2 }] [Sim { uuid=totally-a-real-sim-card, modemUuid=org.linaro.qrild.lm1, state=0 }]  [PHONE0]
08-02 00:04:30.038  2202  2202 D SubscriptionController: [SubscriptionController] init by Context
08-02 00:04:30.041  2202  2202 I PhoneFactory: Creating Phone with type = 1 phoneId = 0
08-02 00:04:30.042  2202  2202 D TelephonyTester: register for intent action=com.android.internal.telephony.action_detached
08-02 00:04:30.043  2202  2202 D TelephonyTester: register for intent action=com.android.internal.telephony.action_attached
08-02 00:04:30.043  2202  2202 D TelephonyTester: register for intent action=com.android.internal.telephony.TestServiceState
08-02 00:04:30.043  2202  2202 D TelephonyTester: register for intent action=com.android.internal.telephony.TestChangeNumber
08-02 00:04:30.046  2202  2202 D Phone   : mDoesRilSendMultipleCallRing=true
08-02 00:04:30.047  2202  2202 D Phone   : mCallRingDelay=3000
08-02 00:04:30.057  2202  2202 D RILJ    : startLceService: REQUEST_NOT_SUPPORTED
08-02 00:04:30.060  2202  2202 D SmsDispatchersController: SmsDispatchersController created
08-02 00:04:30.064  2202  2202 D SMSDispatcher: SMSDispatcher: ctor mSmsCapable=true format=unknown mSmsSendDisabled=false
08-02 00:04:30.068  2202  2202 D SMSDispatcher: SMSDispatcher: ctor mSmsCapable=true format=3gpp2 mSmsSendDisabled=false
08-02 00:04:30.068  2202  2202 D CdmaSMSDispatcher: CdmaSMSDispatcher created
08-02 00:04:30.084  2202  2202 D GsmInboundSmsHandler: created InboundSmsHandler
08-02 00:04:30.085  2202  2236 D RILJ    : [UNSL]< UNSOL_RESPONSE_RADIO_STATE_CHANGED radioStateChanged: 0 [PHONE0]
08-02 00:04:30.085  2202  2368 D RILUtils: Radio Hal Version = 2.0
08-02 00:04:30.086  2202  2221 D RILJ    : [0001]< RADIO_POWER  [PHONE0]
08-02 00:04:30.086  2202  2368 D RILUtils: CAPABILITY_USES_ALLOWED_NETWORK_TYPES_BITMASK
08-02 00:04:30.086  2202  2368 D RILUtils: CAPABILITY_SIM_PHONEBOOK_IN_MODEM
08-02 00:04:30.091  2202  2364 D RadioInterfaceCapabilityController: setupRadioInterfaceCapabilities: mRadioInterfaceCapabilities now setup
08-02 00:04:30.091  2202  2368 D RadioConfigResponseAidl: [0003]< GET_HAL_DEVICE_CAPABILITIES
08-02 00:04:30.094  2202  2370 D GsmInboundSmsHandler: StartupState.enter: entering StartupState
08-02 00:04:30.103  2202  2202 D CdmaInboundSmsHandler: created InboundSmsHandler
08-02 00:04:30.108  2202  2371 D CdmaInboundSmsHandler: StartupState.enter: entering StartupState
08-02 00:04:30.110  2202  2202 D SMSDispatcher: SMSDispatcher: ctor mSmsCapable=true format=3gpp mSmsSendDisabled=false
08-02 00:04:30.111  2202  2202 D GsmSMSDispatcher: GsmSMSDispatcher created
08-02 00:04:30.113  2202  2370 D GsmInboundSmsHandler: StartupState.processMessage: processing EVENT_START_ACCEPTING_SMS
08-02 00:04:30.113  2202  2371 D CdmaInboundSmsHandler: StartupState.processMessage: processing EVENT_START_ACCEPTING_SMS
08-02 00:04:30.113  2202  2370 D GsmInboundSmsHandler: IdleState.enter: entering IdleState
08-02 00:04:30.113  2202  2371 D CdmaInboundSmsHandler: IdleState.enter: entering IdleState
08-02 00:04:30.114  2202  2370 D GsmInboundSmsHandler: IdleState.processMessage: processing EVENT_RELEASE_WAKELOCK
08-02 00:04:30.114  2202  2371 D CdmaInboundSmsHandler: IdleState.processMessage: processing EVENT_RELEASE_WAKELOCK
08-02 00:04:30.115  2202  2370 D GsmInboundSmsHandler: IdleState.processMessage: EVENT_RELEASE_WAKELOCK: mWakeLock released
08-02 00:04:30.115  2202  2202 D CdmaSSM : subscriptionSource from settings: 0
08-02 00:04:30.115  2202  2202 D CdmaSSM : cdmaSSM constructor: 0
08-02 00:04:30.116  2202  2371 D CdmaInboundSmsHandler: IdleState.processMessage: EVENT_RELEASE_WAKELOCK: mWakeLock released
08-02 00:04:30.119  2202  2202 D GsmCdmaPhone: [0] Precise phone type 1
08-02 00:04:30.120  2202  2202 D RILJ    : setPhoneType=1 old value=0 [PHONE0]
08-02 00:04:30.123  2202  2202 D CarrierActionAgent: [0]Creating CarrierActionAgent
08-02 00:04:30.124  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.126  2202  2202 D ANM-0   : operates in AP-assisted mode.
08-02 00:04:30.139  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.146  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.148   695  1876 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:30.150  2202  2202 D NRM-C-0 : registerForNetworkRegistrationInfoChanged
08-02 00:04:30.152  2202  2202 D NRM-I-0 : registerForNetworkRegistrationInfoChanged
08-02 00:04:30.162  2202  2202 D RILJ    : [0004]> SIGNAL_STRENGTH [PHONE0]
08-02 00:04:30.163  2202  2202 D SST     : [0] notifyVoiceRegStateRilRadioTechnologyChanged: vrs=1 rat=0
08-02 00:04:30.165   695  1876 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:30.168  2202  2202 D Phone   : [0] SubId-1,get allowed network types user: value = GPRS|EDGE|UMTS|HSDPA|HSUPA|HSPA|HSPA+|GSM
08-02 00:04:30.169  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.183  2202  2202 D EmergencyNumberTracker:  asset emergency database is loaded. Ver: 1 Phone Id: 0
08-02 00:04:30.184  2202  2202 E EmergencyNumberTracker: Cache ota emergency database IOException: java.io.FileNotFoundException: /data/misc/emergencynumberdb/emergency_number_db: open failed: ENOENT (No such file or directory)
08-02 00:04:30.185  2202  2202 D EmergencyNumberTracker: Using Asset Emergency database. Version: 1
08-02 00:04:30.196  2202  2368 E CellSignalStrengthLte: convertRssiAsuToDBm: invalid RSSI in ASU=-128
08-02 00:04:30.200  2202  2202 D DNC-0   : DataNetworkController created.
08-02 00:04:30.201  2202  2368 D RILJ    : [0004]< SIGNAL_STRENGTH SignalStrength:{mCdma=CellSignalStrengthCdma: cdmaDbm=2147483647 cdmaEcio=2147483647 evdoDbm=2147483647 evdoEcio=2147483647 evdoSnr=2147483647 level=0,mGsm=CellSignalStrengthGsm: rssi=2147483647 ber=2147483647 mTa=2147483647 mLevel=0,mWcdma=CellSignalStrengthWcdma: ss=2147483647 ber=2147483647 rscp=2147483647 ecno=2147483647 level=0,mTdscdma=CellSignalStrengthTdscdma: rssi=2147483647 ber=2147483647 rscp=2147483647 level=0,mLte=CellSignalStrengthLte: rssi=2147483647 rsrp=-65 rsrq=-18 rssnr=1 cqiTableIndex=5 cqi=13 ta=647 level=4 parametersUseForLevel=1,mNr=CellSignalStrengthNr:{ csiRsrp = 2147483647 csiRsrq = 2147483647 csiCqiTableIndex = 2147483647 csiCqiReport = [2147483647] ssRsrp = 2147483647 ssRsrq = 2147483647 ssSinr = 2147483647 level = 0 parametersUseForLevel = 1 },primary=CellSignalStrengthLte} [PHONE0]
08-02 00:04:30.204  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.208  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.209  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.214  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.230  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.233  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.234  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.235  2202  2202 E DSM-I-0 : Can't find the binding package
08-02 00:04:30.237  2202  2202 D DCM-0   : DataConfigManager created.
08-02 00:04:30.242  2202  2202 W CarrierConfigManager: Error getting config for subId -1 ICarrierConfigLoader is null
08-02 00:04:30.259  2202  2202 D DCM-0   : Data config updated. Config is not carrier specific.
08-02 00:04:30.265  2202  2202 D DSMGR-0 : DataSettingsManager created.
08-02 00:04:30.274  2202  2202 D SubscriptionController: Valid row not present in db
08-02 00:04:30.275  2202  2202 D SubscriptionController: getSubscriptionProperty Query value = null
08-02 00:04:30.280  2202  2202 D DSRM-0  : DataStallRecoveryManager created.
08-02 00:04:30.284  2202  2202 D CarrierResolver: Creating CarrierResolver[0]
08-02 00:04:30.290  2202  2202 D SST     : [0] notifyVoiceRegStateRilRadioTechnologyChanged: vrs=1 rat=0
08-02 00:04:30.310  2202  2202 I GsmCdmaPhone: [0] updateTtyMode ttyMode=0
08-02 00:04:30.314  2202  2202 D RILJ    : [0005]> SET_TTY_MODE ttyMode = 0 [PHONE0]
08-02 00:04:30.315  2202  2368 D RILJ    : [0005]< SET_TTY_MODE  [PHONE0]
08-02 00:04:30.316  2202  2202 I GsmCdmaPhone: [0] updateUiTtyMode ttyMode=0
08-02 00:04:30.316  2202  2202 D CallManager: registerPhone(GSM Handler (com.android.internal.telephony.GsmCdmaPhone) {90720e9})
08-02 00:04:30.317  2202  2202 D GsmCdmaPhone: [0] GsmCdmaPhone: constructor: sub = 0
08-02 00:04:30.321  2202  2202 I PhoneFactory: defaultSmsApplication: NONE
08-02 00:04:30.324  2202  2202 I PhoneFactory: Creating SubInfoRecordUpdater
08-02 00:04:30.325  2202  2202 D SubscriptionInfoUpdater: Constructor invoked
08-02 00:04:30.339  2202  2202 I PhoneFactory: IMS is not supported on this device, skipping ImsResolver.
08-02 00:04:30.351  2202  2202 W FeatureConnector: [InstanceManager, 0] connect: not supported.
08-02 00:04:30.351  2202  2393 I ImsManagerIM [0]: connectionUnavailable, reason: 2
08-02 00:04:30.354   695  1876 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:30.359  2202  2202 D PhoneSwitcher: PhoneSwitcher started
08-02 00:04:30.360  2202  2202 D ProxyController: Constructor - Enter
08-02 00:04:30.363  2202  2202 D ProxyController: clearTransaction
08-02 00:04:30.364  2202  2202 D ProxyController: clearTransaction: phoneId=0 status=IDLE
08-02 00:04:30.364  2202  2202 D ProxyController: Constructor - Exit
08-02 00:04:30.399   695  1876 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:30.400  2202  2202 D TelephonyNetworkFactory[0]: Registering NetworkFactory
08-02 00:04:30.528   695  1876 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:30.536  2202  2202 D CallManager: registerForMmiComplete
08-02 00:04:30.573   695  1876 D TelephonyRegistry: listen oscl: mHasNotifySubscriptionInfoChangedOccurred==false no callback
08-02 00:04:30.587  2202  2202 D UiccController: handleMessage: Received RADIO_UNAVAILABLE for phoneId 0
08-02 00:04:30.588  2202  2202 D UiccController: EVENT_RADIO_UNAVAILABLE, dispose card
08-02 00:04:30.588  2202  2202 D UiccController: handleMessage: Received RADIO_AVAILABLE for phoneId 0
08-02 00:04:30.588  2202  2202 D UiccController: Received EVENT_RADIO_AVAILABLE/EVENT_RADIO_ON, calling getIccCardStatus
08-02 00:04:30.592  2202  2202 D RILJ    : [0006]> GET_SIM_STATUS [PHONE0]
08-02 00:04:30.593  2202  2202 D UiccController: Received EVENT_RADIO_AVAILABLE/EVENT_RADIO_ON for phoneId 0, calling getIccSlotsStatus
08-02 00:04:30.593  2202  2202 D RadioConfig: [0007]> GET_SLOT_STATUS
08-02 00:04:30.594  2202  2202 D Phone   : config LCE service failed: com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED
08-02 00:04:30.595  2202  2202 D RILJ    : [0008]> GET_CURRENT_CALLS [PHONE0]
08-02 00:04:30.595  2202  2202 W FeatureConnector: [ImsSmsDispatcher, 0] connect: not supported.
08-02 00:04:30.596  2202  2202 D GsmSMSDispatcher: GsmSMSDispatcher: subId = -1 slotId = 0
08-02 00:04:30.597  2202  2202 D RILJ    : [0009]> BASEBAND_VERSION [PHONE0]
08-02 00:04:30.598  2202  2202 D RILJ    : [0010]> DEVICE_IDENTITY [PHONE0]
08-02 00:04:30.599  2202  2202 D RILJ    : [0011]> GET_RADIO_CAPABILITY [PHONE0]
08-02 00:04:30.601  2202  2202 D RILJ    : [0012]> GET_UICC_APPLICATIONS_ENABLEMENT [PHONE0]
08-02 00:04:30.601  2202  2202 D RILJ    : startLceService: REQUEST_NOT_SUPPORTED
08-02 00:04:30.601  2202  2202 D GsmCdmaPhone: [0] Event EVENT_RADIO_OFF_OR_NOT_AVAILABLE Received
08-02 00:04:30.602  2202  2202 D GsmCdmaPhone: [0] EVENT EVENT_RADIO_STATE_CHANGED
08-02 00:04:30.602  2202  2202 D GsmCdmaPhone: handleRadioPowerStateChange, state= 0
08-02 00:04:30.606  2202  2202 E ANM-0   : Can't find the binding package
08-02 00:04:30.611  2202  2202 D RILJ    : [0013]> SET_SIGNAL_STRENGTH_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.612  2202  2202 D SSCtr   : setSignalStrengthReportingCriteria consolidatedSignalThresholdInfos=[SignalThresholdInfo{mRan=1 mSignalMeasurementType=1 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=2 mSignalMeasurementType=2 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=3 mSignalMeasurementType=3 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=4 mSignalMeasurementType=1 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=3 mSignalMeasurementType=4 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}, SignalThresholdInfo{mRan=3 mSignalMeasurementType=5 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=6 mSignalMeasurementType=6 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=6 mSignalMeasurementType=7 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}, SignalThresholdInfo{mRan=6 mSignalMeasurementType=8 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}]
08-02 00:04:30.615  2202  2202 D RILJ    : [0014]> SET_SIGNAL_STRENGTH_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.616  2202  2202 D SSCtr   : setSignalStrengthReportingCriteria consolidatedSignalThresholdInfos=[SignalThresholdInfo{mRan=1 mSignalMeasurementType=1 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=2 mSignalMeasurementType=2 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=3 mSignalMeasurementType=3 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=4 mSignalMeasurementType=1 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=3 mSignalMeasurementType=4 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}, SignalThresholdInfo{mRan=3 mSignalMeasurementType=5 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=6 mSignalMeasurementType=6 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=true}, SignalThresholdInfo{mRan=6 mSignalMeasurementType=7 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}, SignalThresholdInfo{mRan=6 mSignalMeasurementType=8 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}]
08-02 00:04:30.617  2202  2202 D SST     : [0] EVENT_ICC_CHANGED: SIM absent
08-02 00:04:30.617  2202  2202 D SST     : [0] cancelAllNotifications: mPrevSubId=-1
08-02 00:04:30.618  2202  2202 D SST     : [0] updateSpnDisplayLegacy+
08-02 00:04:30.623  2202  2202 D SST     : [0] updateSpnDisplay: radio is on but out of service, set plmn='No service'
08-02 00:04:30.624  2202  2202 D SST     : [0] updateSpnDisplay: rawSpn =
08-02 00:04:30.626  2202  2202 D SST     : [0] updateSpnDisplay: updateSpnDisplay: changed sending intent, rule=2, showPlmn='true', plmn='No service', showSpn='false', spn='', dataSpn='', subId='-1'
08-02 00:04:30.627  2202  2202 D SubscriptionManager: putPhoneIdAndSubIdExtra: no valid subs
08-02 00:04:30.634  2202  2202 D SubscriptionController: [setPlmnSpn] No valid subscription to store info
08-02 00:04:30.635  2202  2202 D SubscriptionController: notifySubscriptionInfoChanged:
08-02 00:04:30.636   695  1876 D TelephonyRegistry: notifySubscriptionInfoChanged: first invocation mRecords.size=30
08-02 00:04:30.641  2202  2202 D SST     : [0] updateSpnDisplayLegacy-
08-02 00:04:30.644  2202  2202 D NRM-C-0 : Trying to bind com.android.phone for transport WWAN
08-02 00:04:30.645  2202  2400 D RILJ    : responseIccCardStatus: from AIDL: IccCardState {CARDSTATE_PRESENT,PINSTATE_UNKNOWN,num_apps=1,gsm_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},cdma_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},ims_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},atr=39981c83e7f216d01c10c0,iccid=8420099350,eid=,SlotPortMapping={physicalSlotIndex=1, portIndex=0}} [PHONE0]
08-02 00:04:30.646  2202  2400 D RILJ    : [0006]< GET_SIM_STATUS IccCardState {CARDSTATE_PRESENT,PINSTATE_UNKNOWN,num_apps=1,gsm_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},cdma_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},ims_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},atr=39981c83e7f216d01c10c0,iccid=8420099350,eid=,SlotPortMapping={physicalSlotIndex=1, portIndex=0}} [PHONE0]
08-02 00:04:30.649  2202  2202 E NRM-I-0 : Can't find the binding package
08-02 00:04:30.650  2202  2202 D SST     : [0] setPowerStateToDesired: mDeviceShuttingDown=false, mDesiredPowerState=true, getRadioState=0, mRadioDisabledByCarrier=false, IMS reg state=false, pending radio off=false
08-02 00:04:30.651  2202  2202 D RILJ    : [0015]> RADIO_POWER on = true forEmergencyCall= false preferredForEmergencyCall=false [PHONE0]
08-02 00:04:30.652  2202  2202 D SST     : [0] pollState: modemTriggered=true
08-02 00:04:30.653  2202  2202 D RILJ    : [0016]> OPERATOR [PHONE0]
08-02 00:04:30.654  2202  2202 E NRM-C-0 : service not connected. Domain = PS
08-02 00:04:30.654  2202  2202 E NRM-C-0 : service not connected. Domain = CS
08-02 00:04:30.654  2202  2202 E NRM-I-0 : service not connected. Domain = PS
08-02 00:04:30.655  2202  2202 D RILJ    : [0017]> QUERY_NETWORK_SELECTION_MODE [PHONE0]
08-02 00:04:30.656  2202  2202 D SST     : [0] setPowerStateToDesired: mDeviceShuttingDown=false, mDesiredPowerState=true, getRadioState=0, mRadioDisabledByCarrier=false, IMS reg state=false, pending radio off=false
08-02 00:04:30.657  2202  2202 D RILJ    : [0018]> RADIO_POWER on = true forEmergencyCall= false preferredForEmergencyCall=false [PHONE0]
08-02 00:04:30.658  2202  2202 D SST     : [0] pollState: modemTriggered=true
08-02 00:04:30.659  2202  2202 D RILJ    : [0019]> OPERATOR [PHONE0]
08-02 00:04:30.659  2202  2202 E NRM-C-0 : service not connected. Domain = PS
08-02 00:04:30.660  2202  2202 E NRM-C-0 : service not connected. Domain = CS
08-02 00:04:30.660  2202  2202 E NRM-I-0 : service not connected. Domain = PS
08-02 00:04:30.661  2202  2202 D RILJ    : [0020]> QUERY_NETWORK_SELECTION_MODE [PHONE0]
08-02 00:04:30.662  2202  2202 D Phone   : [0] SubId-1,get allowed network types user: value = GPRS|EDGE|UMTS|HSDPA|HSUPA|HSPA|HSPA+|GSM
08-02 00:04:30.662  2202  2202 D PhoneFactory: calculatePreferredNetworkType: phoneId = 0 networkType = 50055
08-02 00:04:30.663  2202  2202 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:30.664  2202  2202 D Phone   : [0] Allowed network types for 'carrier' reason is changed by carrier config = GPRS|EDGE|UMTS|HSDPA|HSUPA|HSPA|HSPA+|GSM
08-02 00:04:30.665  2202  2202 D Phone   : [0] SubId-1,get allowed network types carrier: value = GPRS|EDGE|UMTS|HSDPA|HSUPA|HSPA|HSPA+|GSM
08-02 00:04:30.665  2202  2202 I CSST    : isNrSupported:  carrierConfigEnabled: true, AccessFamilySupported: false, isNrNetworkTypeAllowed: false
08-02 00:04:30.666  2202  2202 I CSST    : PrefNetworkNotification: sendMessage() w/values: ,false,-1,false,false
08-02 00:04:30.667  2202  2202 I CSST    : canceling notifications: 1000
08-02 00:04:30.667  2202  2202 D Phone   : isWifiCallingEnabled =false
08-02 00:04:30.668  2202  2202 D CSST    : isPhoneRegisteredForWifiCalling: false
08-02 00:04:30.668  2202  2202 D Phone   : isWifiCallingEnabled =false
08-02 00:04:30.668  2202  2202 I CSST    : EmergencyNetworkNotification: sendMessage() w/values: ,-1,false,false
08-02 00:04:30.669  2202  2202 I CSST    : canceling notifications: 1001
08-02 00:04:30.670  2202  2202 D Phone   : [0] SubId-1,get allowed network types user: value = GPRS|EDGE|UMTS|HSDPA|HSUPA|HSPA|HSPA+|GSM
08-02 00:04:30.670  2202  2202 D PhoneFactory: calculatePreferredNetworkType: phoneId = 0 networkType = 50055
08-02 00:04:30.671  2202  2202 D Phone   : [0] Allowed network types for 'carrier' reason is changed by carrier config = GPRS|EDGE|UMTS|HSDPA|HSUPA|HSPA|HSPA+|GSM
08-02 00:04:30.671  2202  2202 D Phone   : [0] SubId-1,get allowed network types carrier: value = GPRS|EDGE|UMTS|HSDPA|HSUPA|HSPA|HSPA+|GSM
08-02 00:04:30.672  2202  2202 I CSST    : isNrSupported:  carrierConfigEnabled: true, AccessFamilySupported: false, isNrNetworkTypeAllowed: false
08-02 00:04:30.672  2202  2202 I CSST    : PrefNetworkNotification: sendMessage() w/values: ,false,-1,false,false
08-02 00:04:30.673  2202  2202 I CSST    : canceling notifications: 1000
08-02 00:04:30.673  2202  2202 D Phone   : isWifiCallingEnabled =false
08-02 00:04:30.673  2202  2202 D CSST    : isPhoneRegisteredForWifiCalling: false
08-02 00:04:30.674  2202  2202 D Phone   : isWifiCallingEnabled =false
08-02 00:04:30.674  2202  2202 I CSST    : EmergencyNetworkNotification: sendMessage() w/values: ,-1,false,false
08-02 00:04:30.675  2202  2202 I CSST    : canceling notifications: 1001
08-02 00:04:30.675  2202  2202 D EmergencyNumberTracker: updateRadioEmergencyNumberListAndNotify(): receiving []
08-02 00:04:30.677  2202  2202 D RILJ    : [0021]> SEND_DEVICE_STATE 1:true [PHONE0]
08-02 00:04:30.678  2202  2202 D RILJ    : [0022]> SEND_DEVICE_STATE 2:false [PHONE0]
08-02 00:04:30.680  2202  2202 D RILJ    : [0023]> SEND_DEVICE_STATE 0:false [PHONE0]
08-02 00:04:30.681  2202  2202 D RILJ    : [0024]> SET_UNSOLICITED_RESPONSE_FILTER -1 [PHONE0]
08-02 00:04:30.682  2202  2202 D RILJ    : [0025]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.683  2202  2202 D RILJ    : [0026]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.684  2202  2202 D RILJ    : [0027]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.685  2202  2202 D RILJ    : [0028]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.686  2202  2202 D RILJ    : [0029]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.687  2202  2202 D RILJ    : [0030]> SEND_DEVICE_STATE 1:true [PHONE0]
08-02 00:04:30.689  2202  2202 D RILJ    : [0031]> SEND_DEVICE_STATE 2:false [PHONE0]
08-02 00:04:30.690  2202  2202 D RILJ    : [0032]> SEND_DEVICE_STATE 0:false [PHONE0]
08-02 00:04:30.691  2202  2202 D RILJ    : [0033]> SET_UNSOLICITED_RESPONSE_FILTER -1 [PHONE0]
08-02 00:04:30.692  2202  2202 D RILJ    : [0034]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.693  2202  2202 D RILJ    : [0035]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.694  2202  2202 D RILJ    : [0036]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.695  2202  2202 D RILJ    : [0037]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.696  2202  2202 D RILJ    : [0038]> SET_LINK_CAPACITY_REPORTING_CRITERIA [PHONE0]
08-02 00:04:30.697  2202  2202 D NetworkTypeController: [0] DefaultState: process EVENT_INITIALIZE
08-02 00:04:30.699  2202  2400 D RadioConfigResponseAidl: [0007]< GET_SLOT_STATUS [IccSlotStatus {CARDSTATE_PRESENT,atr=39981c83e7f216d01c10c0,eid=,num_ports=1, IccSimPortInfo-0{iccid=8420099350,logicalSlotIndex=0,portActive=true}}]
08-02 00:04:30.699  2202  2220 D RILJ    : [0008]< GET_CURRENT_CALLS {} [PHONE0]
08-02 00:04:30.702  2202  2202 D NetworkTypeController: [0] mOverrideTimerRules: {connected={mState=connected, mOverrideType=NR_NSA, mPrimaryTimers={}, mSecondaryTimers={}}, not_restricted_rrc_con={mState=not_restricted_rrc_con, mOverrideType=NR_NSA, mPrimaryTimers={}, mSecondaryTimers={}}, legacy={mState=legacy, mOverrideType=NONE, mPrimaryTimers={}, mSecondaryTimers={}}, not_restricted_rrc_idle={mState=not_restricted_rrc_idle, mOverrideType=NR_NSA, mPrimaryTimers={}, mSecondaryTimers={}}, restricted={mState=restricted, mOverrideType=NONE, mPrimaryTimers={}, mSecondaryTimers={}}, connected_mmwave={mState=connected_mmwave, mOverrideType=NR_NSA, mPrimaryTimers={}, mSecondaryTimers={}}}
08-02 00:04:30.703  2202  2202 D NetworkTypeController: [0] DefaultState: process EVENT_UPDATE
08-02 00:04:30.703  2202  2202 D NetworkTypeController: [0] Reset timers since preferred network mode changed.
08-02 00:04:30.703  2202  2202 D NetworkTypeController: [0] Entering LegacyState
08-02 00:04:30.704  2202  2202 D NetworkTypeController: [0] Reset timers since NR is not allowed.
08-02 00:04:30.704  2202  2202 D DIC-0   : TelephonyDisplayInfo changed from null to TelephonyDisplayInfo {network=UNKNOWN, override=NONE}
08-02 00:04:30.709  2202  2202 D DataService: Data service created
08-02 00:04:30.716  2202  2202 D DSMGR-0 : getDataEnabled during provisioning retVal=false - (false, 0)
08-02 00:04:30.716  2202  2202 D DSMGR-0 : mIsDataEnabled=false, prevDataEnabled=false
08-02 00:04:30.717  2202  2202 D DSMGR-0 : notifyDataEnabledChanged: enabled=false, reason=UNKNOWN, callingPackage=com.android.phone
08-02 00:04:30.723  2202  2202 D CarrierResolver: handleMessage: 2
08-02 00:04:30.752  2202  2400 D RILJ    : [0013]< SET_SIGNAL_STRENGTH_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.752  2202  2399 D RILJ    : [0012]< GET_UICC_APPLICATIONS_ENABLEMENT true [PHONE0]
08-02 00:04:30.753  2202  2220 D RILJ    : [0009]< BASEBAND_VERSION MPSS.AT.4.0.c2.15-00007-SDM845_GEN_PACK-1.358880.1.399256.2  1  [May 09 2021 22:00:00] [PHONE0]
08-02 00:04:30.809  2202  2399 D RILJ    : [0014]< SET_SIGNAL_STRENGTH_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.810  2202  2399 D RILJ    : [0016]< OPERATOR {Three.co.uk, 3, 23420} [PHONE0]
08-02 00:04:30.811  2202  2220 D RILJ    : [0010]< DEVICE_IDENTITY {[gCWURUll5cJmBSWfEXIein_Hj3E], 2, 8018E647, 99001202896467} [PHONE0]
08-02 00:04:30.816  2202  2220 D RILJ    : convertHalRadioCapability: session=0, phase=0, rat=4096, logicModemUuid=org.linaro.qrild.lm1, status=0, rcRil.raf=16384 [PHONE0]
08-02 00:04:30.818  2202  2220 D RILJ    : [0011]< GET_RADIO_CAPABILITY {mPhoneId = 0 mVersion=1 mSession=0 mPhase=0 mRadioAccessFamily=4096 mLogicModemId=org.linaro.qrild.lm1 mStatus=0} [PHONE0]
08-02 00:04:30.920  2202  2400 D RILJ    : [0017]< QUERY_NETWORK_SELECTION_MODE {0} [PHONE0]
08-02 00:04:30.920  2202  2220 D RILJ    : [UNSL]< UNSOL_RESPONSE_RADIO_STATE_CHANGED radioStateChanged: 1 [PHONE0]
08-02 00:04:30.921  2202  2399 D RILJ    : [0015]< RADIO_POWER  [PHONE0]
08-02 00:04:30.969  2202  2399 D RILJ    : [0018]< RADIO_POWER  [PHONE0]
08-02 00:04:30.970  2202  2220 D RILJ    : [0019]< OPERATOR {Three.co.uk, 3, 23420} [PHONE0]
08-02 00:04:30.970  2202  2400 D RILJ    : [0021]< SEND_DEVICE_STATE  [PHONE0]
08-02 00:04:30.971  2202  2400 D RILJ    : [0022]< SEND_DEVICE_STATE  [PHONE0]
08-02 00:04:30.972  2202  2220 D RILJ    : [0020]< QUERY_NETWORK_SELECTION_MODE {0} [PHONE0]
08-02 00:04:30.972  2202  2400 D RILJ    : [0023]< SEND_DEVICE_STATE  [PHONE0]
08-02 00:04:30.973  2202  2220 D RILJ    : [0024]< SET_UNSOLICITED_RESPONSE_FILTER  [PHONE0]
08-02 00:04:30.974  2202  2400 D RILJ    : [0030]< SEND_DEVICE_STATE  [PHONE0]
08-02 00:04:30.975  2202  2220 D RILJ    : [0025]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.975  2202  2400 D RILJ    : [0031]< SEND_DEVICE_STATE  [PHONE0]
08-02 00:04:30.976  2202  2220 D RILJ    : [0026]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.977  2202  2400 D RILJ    : [0032]< SEND_DEVICE_STATE  [PHONE0]
08-02 00:04:30.977  2202  2220 D RILJ    : [0027]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.978  2202  2220 D RILJ    : [0028]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.979  2202  2220 D RILJ    : [0029]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.980  2202  2220 D RILJ    : [0033]< SET_UNSOLICITED_RESPONSE_FILTER  [PHONE0]
08-02 00:04:30.981  2202  2220 D RILJ    : [0034]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.982  2202  2220 D RILJ    : [0035]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.983  2202  2220 D RILJ    : [0036]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.984  2202  2220 D RILJ    : [0037]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:30.985  2202  2220 D RILJ    : [0038]< SET_LINK_CAPACITY_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:31.022  2202  2202 D GsmCdmaPhone: [0] onVoiceRegStateOrRatChanged
08-02 00:04:31.023  2202  2202 D GsmCdmaPhone: [0] getCsCallRadioTech, current vrs=1, vrat=0
08-02 00:04:31.023  2202  2202 D GsmCdmaPhone: [0] getCsCallRadioTech, result calcVrat=0
08-02 00:04:31.024  2202  2202 D PhoneCfgMgr: Received EVENT_RADIO_AVAILABLE/EVENT_RADIO_ON
08-02 00:04:31.027  2202  2202 D RILJ    : [0039]> GET_MODEM_STATUS [PHONE0]
08-02 00:04:31.028  2202  2202 D PhoneCfgMgr: getStaticPhoneCapability: sending the request for getting PhoneCapability
08-02 00:04:31.028  2202  2202 D RadioConfig: [0040]> GET_PHONE_CAPABILITY
08-02 00:04:31.028  2202  2220 D RILJ    : [0039]< GET_MODEM_STATUS true [PHONE0]
08-02 00:04:31.029  2202  2202 D PhoneCfgMgr: getStaticPhoneCapability: mStaticCapability mMaxActiveVoiceSubscriptions=1 mMaxActiveDataSubscriptions=1 mNetworkValidationBeforeSwitchSupported=false mDeviceNrCapability []
08-02 00:04:31.033  2202  2400 D RadioConfigResponseAidl: [0040]< GET_PHONE_CAPABILITY mMaxActiveVoiceSubscriptions=0 mMaxActiveDataSubscriptions=1 mNetworkValidationBeforeSwitchSupported=false mDeviceNrCapability []
08-02 00:04:31.035  2202  2202 D TelephonyNetworkFactory[0]: onActivePhoneSwitch
08-02 00:04:31.037  2202  2202 D DebugService: DebugService DebugService:
08-02 00:04:31.040  2202  2202 D GsmSMSDispatcher: GsmSMSDispatcher: subId = -1 slotId = 0
08-02 00:04:31.040  2202  2202 D SST     : [0] EVENT_ICC_CHANGED: SIM absent
08-02 00:04:31.041  2202  2202 D SST     : [0] cancelAllNotifications: mPrevSubId=-1
08-02 00:04:31.042  2202  2202 D SST     : [0] updateSpnDisplayLegacy+
08-02 00:04:31.043  2202  2202 D SST     : [0] updateSpnDisplay: radio is on but out of service, set plmn='No service'
08-02 00:04:31.044  2202  2202 D SST     : [0] updateSpnDisplay: rawSpn =
08-02 00:04:31.044  2202  2202 D SST     : [0] updateSpnDisplayLegacy-
08-02 00:04:31.045  2202  2202 D CarrierResolver: handleMessage: 2
08-02 00:04:31.045  2202  2202 D ImsSmsDispatcher [0]: ImsManager: connection unavailable, reason=2
08-02 00:04:31.045  2202  2202 D Phone   : config LCE service failed: com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED
08-02 00:04:31.045  2202  2202 D SST     : [0] SubscriptionListener.onSubscriptionInfoChanged
08-02 00:04:31.057  2202  2202 D Phone   : isImsRegistered =false
08-02 00:04:31.060  2202  2202 E PhoneSubInfoController: getLine1Number phone is null for Subscription:-1
08-02 00:04:31.096  2202  2202 D UiccController: handleMessage: Received GET_ICC_STATUS_DONE for phoneId 0
08-02 00:04:31.096  2202  2202 D UiccController: Received EVENT_GET_ICC_STATUS_DONE
08-02 00:04:31.097  2202  2202 D UiccController: onGetIccCardStatusDone: phoneId 0 IccCardStatus: IccCardState {CARDSTATE_PRESENT,PINSTATE_UNKNOWN,num_apps=1,gsm_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},cdma_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},ims_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},atr=39981c83e7f216d01c10c0,iccid=8420099350,eid=,SlotPortMapping={physicalSlotIndex=1, portIndex=0}}
08-02 00:04:31.098  2202  2202 D UiccSlot: Creating
08-02 00:04:31.098  2202  2202 D UiccSlot: cardStatus update: IccCardState {CARDSTATE_PRESENT,PINSTATE_UNKNOWN,num_apps=1,gsm_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},cdma_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},ims_id=0{APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN},atr=39981c83e7f216d01c10c0,iccid=8420099350,eid=,SlotPortMapping={physicalSlotIndex=1, portIndex=0}}
08-02 00:04:31.098  2202  2202 E AnswerToReset: Unrecognized convention byte 39
08-02 00:04:31.099  2202  2202 D UiccSlot: update: radioState=1 mLastRadioState={}
08-02 00:04:31.099  2202  2202 D UiccCard: Creating
08-02 00:04:31.100  2202  2202 D UiccPort: Creating
08-02 00:04:31.100  2202  2202 D UiccProfile: Creating profile
08-02 00:04:31.100  2202  2202 D UiccProfile: 1 applications
08-02 00:04:31.101  2202  2202 D UiccCardApplication: Creating UiccApp: {APPTYPE_USIM,APPSTATE_DETECTED,pin1=PINSTATE_UNKNOWN,pin2=PINSTATE_UNKNOWN}
08-02 00:04:31.101  2202  2202 D CarrierTestOverride: File path : /user_de/0/com.android.phone/files/carrier_test_conf_sim0.xml
08-02 00:04:31.103  2202  2202 W CarrierTestOverride: Can not open /data/user_de/0/com.android.phone/files/carrier_test_conf_sim0.xml
08-02 00:04:31.103  2202  2202 D UiccCardApplication: Notifying 1 registrant: DETECTED
08-02 00:04:31.104  2202  2202 W VoiceMailConstants: Can't open /system/etc/voicemail-conf.xml
08-02 00:04:31.105  2202  2202 D SIMRecords: [SIMRecords-0] setting0 mMncLength-1
08-02 00:04:31.105  2202  2202 D SIMRecords: [SIMRecords-0] SIMRecords: onRadioOffOrNotAvailable set 'gsm.sim.operator.numeric' to operator=null
08-02 00:04:31.105  2202  2202 D SIMRecords: [SIMRecords-0] update icc_operator_numeric=null
08-02 00:04:31.109  2202  2202 D SIMRecords: [SIMRecords-0] getOperatorNumeric: IMSI == null
08-02 00:04:31.109  2202  2202 D SIMRecords: [SIMRecords-0] SIMRecords X ctor this=SimRecords: mDestroyed=false mContext=com.android.phone.PhoneGlobals@2c524ad mCi=com.android.internal.telephony.RIL@9eb83e2 mFh=Handler (com.android.internal.telephony.uicc.UsimFileHandler) {e423373} mParentApp=com.android.internal.telephony.uicc.UiccCardApplication@bcf2230 recordsToLoad=0 adnCache=Handler (com.android.internal.telephony.uicc.AdnRecordCache) {4bc5ea9} recordsRequested=false lockedRecordsReqReason=0 iccid=null msisdnTag=null voiceMailNum=null voiceMailTag=null voiceMailNum=null newVoiceMailTag=null isVoiceMailFixed=false mImsi=null mncLength=-1 mailboxIndex=0 spn=null mVmConfigcom.android.internal.telephony.uicc.VoiceMailConstants@8c1fc2e callForwardingEnabled=0 spnState=null mCphsInfo=null mCspPlmnEnabled=true efMWIS=null efCPHS_MWI=null mEfCff=null mEfCfis=null getOperatorNumeric=null
08-02 00:04:31.112  2202  2202 D CAT     : CatService: registerForRecordsLoaded slotid=0 instance:Handler (com.android.internal.telephony.cat.CatService) {5be9deb}
08-02 00:04:31.113  2202  2202 D CAT     : CatService: Running CAT service on Slotid: 0. STK app installed:false
08-02 00:04:31.114  2202  2202 D UiccProfile: Before privilege rules: null : CARDSTATE_PRESENT
08-02 00:04:31.114  2202  2202 D UiccProfile: iccOpenLogicalChannel: A00000015144414300 , 0 by pid:2202 uid:1001
08-02 00:04:31.118  2202  2202 D RILJ    : [0041]> SIM_OPEN_CHANNEL aid = A00000015144414300 p2 = 0 [PHONE0]
08-02 00:04:31.119  2202  2202 E UiccProfile: App index 0 is invalid since it's not APPTYPE_RUIM and not APPTYPE_CSIM
08-02 00:04:31.119  2202  2202 E UiccProfile: App index 0 is invalid since it's not APPTYPE_ISIM and not null
08-02 00:04:31.120  2202  2202 D UiccProfile: Icc changed. Reregistering.
08-02 00:04:31.120  2202  2400 D RILJ    : [0041]< SIM_OPEN_CHANNEL error 6 [PHONE0]
08-02 00:04:31.120  2202  2202 D UiccProfile: setExternalState: set mPhoneId=0 mExternalState=NOT_READY
08-02 00:04:31.121  2202  2400 D RilRequest: [0041]< SIM_OPEN_CHANNEL error: com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED ret= result={ when=-3m5s313ms what=8 obj={ when=-3m5s313ms what=1 target=com.android.internal.telephony.uicc.UiccCarrierPrivilegeRules } target=com.android.internal.telephony.uicc.UiccProfile$4 }
08-02 00:04:31.122  2202  2202 D SubscriptionInfoUpdater: updateInternalIccState to simStatus NOT_READY reason null phoneId 0
08-02 00:04:31.122  2202  2202 D UiccProfile: update icc_operator_numeric=
08-02 00:04:31.131  2202  2202 D UiccController: Notifying IccChangedRegistrants
08-02 00:04:31.132  2202  2202 D NetworkService: network service created
08-02 00:04:31.134  2202  2202 D SST     : [0] handlePollStateResult exception java.lang.IllegalStateException: Service not connected.
08-02 00:04:31.134  2202  2202 E SST     : [0] RIL implementation has returned an error where it must succeedjava.lang.IllegalStateException: Service not connected.
08-02 00:04:31.134  2202  2202 D SST     : [0] handlePollStateResult exception java.lang.IllegalStateException: Service not connected.
08-02 00:04:31.135  2202  2202 E SST     : [0] RIL implementation has returned an error where it must succeedjava.lang.IllegalStateException: Service not connected.
08-02 00:04:31.135  2202  2202 D SST     : [0] handlePollStateResult exception java.lang.IllegalStateException: Service not connected.
08-02 00:04:31.135  2202  2202 E SST     : [0] RIL implementation has returned an error where it must succeedjava.lang.IllegalStateException: Service not connected.
08-02 00:04:31.135  2202  2202 D NetworkTypeController: [0] LegacyState: process EVENT_DATA_RAT_CHANGED
08-02 00:04:31.136  2202  2202 D NetworkTypeController: [0] Reset timers since NR is not allowed.
08-02 00:04:31.136  2202  2202 D NetworkTypeController: [0] Reset timers since 2G and 3G don't need NR timers.
08-02 00:04:31.137  2202  2202 D UiccController: handleMessage: Received GET_SLOT_STATUS_DONE for phoneId 0
08-02 00:04:31.137  2202  2202 D UiccController: Received EVENT_SLOT_STATUS_CHANGED or EVENT_GET_SLOT_STATUS_DONE
08-02 00:04:31.138  2202  2202 D UiccController: onGetSlotStatusDone: [IccSlotStatus {CARDSTATE_PRESENT,atr=39981c83e7f216d01c10c0,eid=,num_ports=1, IccSimPortInfo-0{iccid=8420099350,logicalSlotIndex=0,portActive=true}}]
08-02 00:04:31.138  2202  2202 D UiccSlot: Creating
08-02 00:04:31.138  2202  2202 D UiccSlot: slotStatus update: IccSlotStatus {CARDSTATE_PRESENT,atr=39981c83e7f216d01c10c0,eid=,num_ports=1, IccSimPortInfo-0{iccid=8420099350,logicalSlotIndex=0,portActive=true}}
08-02 00:04:31.139  2202  2202 E AnswerToReset: Unrecognized convention byte 39
08-02 00:04:31.139  2202  2202 D UiccController: onGetSlotStatusDone: mDefaultEuiccCardId=UNINITIALIZED
08-02 00:04:31.141  2202  2202 D GsmCdmaCallTracker: Event EVENT_POLL_CALLS_RESULT Received
08-02 00:04:31.141  2202  2202 D GsmCdmaCallTracker: [0] update phone state, old=IDLE new=IDLE
08-02 00:04:31.141  2202  2202 D DSM-C-0 : onServiceConnected: ComponentInfo{com.android.phone/com.android.internal.telephony.data.CellularDataService}
08-02 00:04:31.143  2202  2401 D CellularDataService: Cellular data service created for slot 0
08-02 00:04:31.144  2202  2202 D PhoneSwitcher: No active subscriptions: resetting preferred phone to 0 for emergency
08-02 00:04:31.144  2202  2202 D PhoneSwitcher: evaluating due to EVENT_DATA_ENABLED_CHANGED phone[0] 0->-1
08-02 00:04:31.144  2202  2202 D PhoneSwitcher: sendRilCommands: setPreferredDataModem - phoneId: 0
08-02 00:04:31.145  2202  2202 D RadioConfig: [0042]> SET_PREFERRED_DATA_MODEM
08-02 00:04:31.145  2202  2202 D PhoneSwitcher: Data switch event. subId=-1, state=START, reason=IN_CALL
08-02 00:04:31.146  2202  2400 D RadioConfigResponseAidl: [0042]< SET_PREFERRED_DATA_MODEM
08-02 00:04:31.149  2202  2202 D DSRM-0  : onMobileDataEnabledChanged: DataEnabled:false,DataStalled:false
08-02 00:04:31.150  2202  2202 D DNC-0   : onDataEnabledChanged: enabled=false
08-02 00:04:31.151  2202  2202 D GsmCdmaPhone: [0] Baseband version: MPSS.AT.4.0.c2.15-00007-SDM845_GEN_PACK-1.358880.1.399256.2  1  [May 09 2021 22:00:00]
08-02 00:04:31.153  2202  2202 D GsmCdmaPhone: EVENT_GET_RADIO_CAPABILITY: phone rc: {mPhoneId = 0 mVersion=1 mSession=0 mPhase=0 mRadioAccessFamily=4096 mLogicModemId=org.linaro.qrild.lm1 mStatus=0}
08-02 00:04:31.153  2202  2202 D SST     : [0] EVENT_POLL_STATE_NETWORK_SELECTION_MODE
08-02 00:04:31.153  2202  2202 D GsmCdmaPhone: [0] EVENT EVENT_RADIO_STATE_CHANGED
08-02 00:04:31.153  2202  2202 D GsmCdmaPhone: handleRadioPowerStateChange, state= 1
08-02 00:04:31.154  2202  2202 D SST     : [0] setPowerStateToDesired: mDeviceShuttingDown=false, mDesiredPowerState=true, getRadioState=1, mRadioDisabledByCarrier=false, IMS reg state=false, pending radio off=false
08-02 00:04:31.155  2202  2202 D SST     : [0] pollState: modemTriggered=true
08-02 00:04:31.158  2202  2202 D RILJ    : [0043]> OPERATOR [PHONE0]
08-02 00:04:31.159  2202  2202 E NRM-C-0 : service not connected. Domain = PS
08-02 00:04:31.159  2202  2202 E NRM-C-0 : service not connected. Domain = CS
08-02 00:04:31.159  2202  2202 E NRM-I-0 : service not connected. Domain = PS
08-02 00:04:31.160  2202  2400 D RILJ    : [0043]< OPERATOR {Three.co.uk, 3, 23420} [PHONE0]
08-02 00:04:31.161  2202  2202 D RILJ    : [0044]> QUERY_NETWORK_SELECTION_MODE [PHONE0]
08-02 00:04:31.162  2202  2400 D RILJ    : [0044]< QUERY_NETWORK_SELECTION_MODE {0} [PHONE0]
08-02 00:04:31.162  2202  2202 D RILJ    : [0045]> GET_CURRENT_CALLS [PHONE0]
08-02 00:04:31.163  2202  2400 D RILJ    : [0045]< GET_CURRENT_CALLS {} [PHONE0]
08-02 00:04:31.164  2202  2202 D RILJ    : [0046]> IMS_REGISTRATION_STATE [PHONE0]
08-02 00:04:31.164  2202  2202 D GsmCdmaPhone: [0] Event EVENT_RADIO_ON Received
08-02 00:04:31.164  2202  2220 D RILJ    : [0046]< IMS_REGISTRATION_STATE {0, 1} [PHONE0]
08-02 00:04:31.165  2202  2202 D RILJ    : [0047]> VOICE_RADIO_TECH [PHONE0]
08-02 00:04:31.166  2202  2202 D RILJ    : [0048]> CDMA_GET_SUBSCRIPTION_SOURCE [PHONE0]
08-02 00:04:31.166  2202  2220 D RILJ    : [0047]< VOICE_RADIO_TECH {0} [PHONE0]
08-02 00:04:31.166  2202  2202 D SSCtr   : onDeviceIdleStateChanged isDeviceIdle=false
08-02 00:04:31.169  2202  2202 D RILJ    : [0049]> SET_UNSOLICITED_RESPONSE_FILTER 127 [PHONE0]
08-02 00:04:31.169  2202  2220 D RILJ    : [0048]< CDMA_GET_SUBSCRIPTION_SOURCE {0} [PHONE0]
08-02 00:04:31.170  2202  2202 D RILJ    : [0050]> GET_BARRING_INFO [PHONE0]
08-02 00:04:31.170  2202  2202 D DRM-0   : Remove all retry and throttling entries, reason=RADIO_ON
08-02 00:04:31.171  2202  2220 D RILJ    : [0049]< SET_UNSOLICITED_RESPONSE_FILTER  [PHONE0]
08-02 00:04:31.172  2202  2202 D PhoneSwitcher: evaluating due to EVENT_RADIO_ON
08-02 00:04:31.172  2202  2202 D PhoneSwitcher: sendRilCommands: setPreferredDataModem - phoneId: 0
08-02 00:04:31.172  2202  2202 D RadioConfig: [0051]> SET_PREFERRED_DATA_MODEM
08-02 00:04:31.173  2202  2202 D SST     : [0] EVENT_POLL_STATE_NETWORK_SELECTION_MODE
08-02 00:04:31.175  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=7, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1000 RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ]
08-02 00:04:31.176  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=27, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1001 RequestorUid: 1001 RequestorPkg: com.android.phone UnderlyingNetworks: Null] ]
08-02 00:04:31.176  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=1, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VPN&NOT_VCN_MANAGED RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ]
08-02 00:04:31.176  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=16, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1073 RequestorUid: 1073 RequestorPkg: com.android.networkstack UnderlyingNetworks: Null] ]
08-02 00:04:31.177  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=14, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1000 RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ]
08-02 00:04:31.177  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=21, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 10062 RequestorUid: 10062 RequestorPkg: com.android.systemui UnderlyingNetworks: Null] ]
08-02 00:04:31.177  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=23, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 10062 RequestorUid: 10062 RequestorPkg: com.android.systemui UnderlyingNetworks: Null] ]
08-02 00:04:31.178  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ BACKGROUND_REQUEST id=2, [ Transports: CELLULAR Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VPN&NOT_VCN_MANAGED RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ]
08-02 00:04:31.180  2202  2202 E PhoneSubInfoController: getLine1Number phone is null for Subscription:-1
08-02 00:04:31.190  2202  2202 D CAT     : CatService: handleMessage[8]
08-02 00:04:31.191  2202  2202 D CAT     : CatService: MSG_ID_ICC_CHANGED
08-02 00:04:31.191  2202  2202 D CAT     : CatService: New Card State = CARDSTATE_ABSENT Old Card State = CARDSTATE_ABSENT
08-02 00:04:31.191  2202  2202 D UiccProfile: handleMessage: Received ICC_RECORD_EVENTS for phoneId 0
08-02 00:04:31.192  2202  2202 D UiccProfile: handleMessage: Received ICC_RECORD_EVENTS for phoneId 0
08-02 00:04:31.192  2202  2202 D UiccProfile: handleMessage: Received OPEN_LOGICAL_CHANNEL_DONE for phoneId 0
08-02 00:04:31.192  2202  2202 D UiccProfile: handleMessage: Error in SIM access with exception com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED
08-02 00:04:31.194  2202  2202 D SubscriptionInfoUpdater: updateEmbeddedSubscriptions: eUICC not enabled
08-02 00:04:31.194  2202  2202 D SubscriptionInfoUpdater: handleSimNotReady: phoneId: 0
08-02 00:04:31.194  2202  2202 D SubscriptionManager: putPhoneIdAndSubIdExtra: no valid subs
08-02 00:04:31.195  2202  2202 D SubscriptionInfoUpdater: Broadcasting intent ACTION_SIM_STATE_CHANGED NOT_READY reason null for phone: 0
08-02 00:04:31.197  2202  2202 D SubscriptionManager: putPhoneIdAndSubIdExtra: no valid subs
08-02 00:04:31.198  2202  2202 D SubscriptionInfoUpdater: Broadcasting intent ACTION_SIM_CARD_STATE_CHANGED PRESENT for phone: 0 slot: 0
08-02 00:04:31.204  2202  2202 D GsmSMSDispatcher: GsmSMSDispatcher: subId = -1 slotId = 0
08-02 00:04:31.204  2202  2202 D SST     : [0] EVENT_ICC_CHANGED: SIM absent
08-02 00:04:31.205  2202  2202 D SST     : [0] cancelAllNotifications: mPrevSubId=-1
08-02 00:04:31.206  2202  2202 D SST     : [0] updateSpnDisplayLegacy+
08-02 00:04:31.207  2202  2202 D SST     : [0] updateSpnDisplay: radio is on but out of service, set plmn='No service'
08-02 00:04:31.208  2202  2202 D SST     : [0] updateSpnDisplay: rawSpn =
08-02 00:04:31.208  2202  2202 D SST     : [0] updateSpnDisplayLegacy-
08-02 00:04:31.209  2202  2202 D CarrierResolver: handleMessage: 2
08-02 00:04:31.209  2202  2202 D CAT     : CatService: handleMessage[8]
08-02 00:04:31.209  2202  2202 D CAT     : CatService: MSG_ID_ICC_CHANGED
08-02 00:04:31.209  2202  2202 D CAT     : CatService: New Card State = CARDSTATE_ABSENT Old Card State = CARDSTATE_ABSENT
08-02 00:04:31.210  2202  2202 D NRM-C-0 : service ComponentInfo{com.android.phone/com.android.internal.telephony.CellularNetworkService} for transport WWAN is now connected.
08-02 00:04:31.210  2202  2202 D DNC-0   : onDataServiceBindingChanged: WWAN data service is bound.
08-02 00:04:31.212  2202  2202 D PhoneSwitcher: onDdsSwitchResponse: DDS switch success on phoneId = 0
08-02 00:04:31.212  2202  2202 D PhoneSwitcher: notifyPreferredDataSubIdChanged to -1
08-02 00:04:31.213   695   762 D TelephonyRegistry: notifyActiveDataSubIdChanged: activeDataSubId=-1
08-02 00:04:31.217  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=29, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1001 RequestorUid: 1001 RequestorPkg: com.android.phone UnderlyingNetworks: Null] ]
08-02 00:04:31.218  2202  2202 D DNC-0   : onReevaluateExistingDataNetworks: No existing data networks to re-evaluate.
08-02 00:04:31.218  2202  2202 D SST     : [0] handlePollStateResult exception java.lang.IllegalStateException: Service not connected.
08-02 00:04:31.218  2202  2202 E SST     : [0] RIL implementation has returned an error where it must succeedjava.lang.IllegalStateException: Service not connected.
08-02 00:04:31.219  2202  2202 D SST     : [0] handlePollStateResult exception java.lang.IllegalStateException: Service not connected.
08-02 00:04:31.219  2202  2202 E SST     : [0] RIL implementation has returned an error where it must succeedjava.lang.IllegalStateException: Service not connected.
08-02 00:04:31.219  2202  2202 D SST     : [0] handlePollStateResult exception java.lang.IllegalStateException: Service not connected.
08-02 00:04:31.220  2202  2202 E SST     : [0] RIL implementation has returned an error where it must succeedjava.lang.IllegalStateException: Service not connected.
08-02 00:04:31.220  2202  2220 D RadioConfigResponseAidl: [0051]< SET_PREFERRED_DATA_MODEM
08-02 00:04:31.220  2202  2202 D SST     : [0] EVENT_POLL_STATE_NETWORK_SELECTION_MODE
08-02 00:04:31.221  2202  2202 D SST     : [0] combinePsRegistrationStates: {mVoiceRegState=3(POWER_OFF), mDataRegState=1(OUT_OF_SERVICE), mChannelNumber=-1, duplexMode()=0, mCellBandwidths=[], mOperatorAlphaLong=Three.co.uk, mOperatorAlphaShort=3, isManualNetworkSelection=false(automatic), getRilVoiceRadioTechnology=0(Unknown), getRilDataRadioTechnology=0(Unknown), mCssIndicator=unsupported, mNetworkId=-1, mSystemId=-1, mCdmaRoamingIndicator=-1, mCdmaDefaultRoamingIndicator=-1, mIsEmergencyOnly=false, isUsingCarrierAggregation=false, mArfcnRsrpBoost=0, mNetworkRegistrationInfos=[NetworkRegistrationInfo{ domain=CS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=PS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=PS transportType=WLAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}], mNrFrequencyRange=0, mOperatorAlphaLongRaw=Three.co.uk, mOperatorAlphaShortRaw=3, mIsDataRoamingFromRegistration=false, mIsIwlanPreferred=false}
08-02 00:04:31.223  2202  2202 D SST     : [0] Could not set ServiceState channel number. CellIdentity null
08-02 00:04:31.224  2202  2202 D SST     : [0] Poll ServiceState done:  oldSS=[{mVoiceRegState=1(OUT_OF_SERVICE), mDataRegState=1(OUT_OF_SERVICE), mChannelNumber=-1, duplexMode()=0, mCellBandwidths=[], mOperatorAlphaLong=null, mOperatorAlphaShort=null, isManualNetworkSelection=false(automatic), getRilVoiceRadioTechnology=0(Unknown), getRilDataRadioTechnology=0(Unknown), mCssIndicator=unsupported, mNetworkId=-1, mSystemId=-1, mCdmaRoamingIndicator=-1, mCdmaDefaultRoamingIndicator=-1, mIsEmergencyOnly=false, isUsingCarrierAggregation=false, mArfcnRsrpBoost=0, mNetworkRegistrationInfos=[NetworkRegistrationInfo{ domain=CS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=PS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=PS transportType=WLAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}], mNrFrequencyRange=0, mOperatorAlphaLongRaw=null, mOperatorAlphaShortRaw=null, mIsDataRoamingFromRegistration=false, mIsIwlanPreferred=false}] newSS=[{mVoiceRegState=3(POWER_OFF), mDataRegState=1(OUT_OF_SERVICE), mChannelNumber=-1, duplexMode()=0, mCellBandwidths=[], mOperatorAlphaLong=Three.co.uk, mOperatorAlphaShort=3, isManualNetworkSelection=false(automatic), getRilVoiceRadioTechnology=0(Unknown), getRilDataRadioTechnology=0(Unknown), mCssIndicator=unsupported, mNetworkId=-1, mSystemId=-1, mCdmaRoamingIndicator=-1, mCdmaDefaultRoamingIndicator=-1, mIsEmergencyOnly=false, isUsingCarrierAggregation=false, mArfcnRsrpBoost=0, mNetworkRegistrationInfos=[NetworkRegistrationInfo{ domain=PS transportType=WLAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=CS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=PS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}], mNrFrequencyRange=0, mOperatorAlphaLongRaw=Three.co.uk, mOperatorAlphaShortRaw=3, mIsDataRoamingFromRegistration=false, mIsIwlanPreferred=false}] oldMaxDataCalls=1 mNewMaxDataCalls=1 oldReasonDataDenied=-1 mNewReasonDataDenied=-1
08-02 00:04:31.229  2202  2202 D SST     : [0] pollStateDone: hasRegistered = false hasDeregistered = false hasDataAttached = {1=false, 2=false} hasDataDetached = {1=false, 2=false} hasDataRegStateChanged = {1=false, 2=false} hasRilVoiceRadioTechnologyChanged = false hasRilDataRadioTechnologyChanged = {1=true, 2=true} hasDataTransportPreferenceChanged = false hasChanged = true hasVoiceRoamingOn = false hasVoiceRoamingOff = false hasDataRoamingOn =false hasDataRoamingOff = false hasLocationChanged = false has4gHandoff = false hasMultiApnSupport = false hasLostMultiApnSupport = false hasCssIndicatorChanged = false hasNrFrequencyRangeChanged = false hasNrStateChanged = false hasBandwidthChanged = true hasAirplaneModeOnlChanged = true
08-02 00:04:31.230  2202  2202 D SST     : [0] updateSpnDisplayLegacy+
08-02 00:04:31.232  2202  2202 D SST     : [0] updateSpnDisplay: radio is off w/ showPlmn=true plmn=null
08-02 00:04:31.232  2202  2399 D RILJ    : [0050]< GET_BARRING_INFO BarringInfo {mCellIdentity=CellIdentityLte:{ mCi=0 mPci=0 mTac=0 mEarfcn=0 mBands=[] mBandwidth=0 mMcc=null mMnc=null mAlphaLong= mAlphaShort= mAdditionalPlmns={} mCsgInfo=null}, mBarringServiceInfos={0=android.telephony.BarringInfo$BarringServiceInfo@203b16}} [PHONE0]
08-02 00:04:31.233  2202  2202 D SST     : [0] updateSpnDisplay: rawSpn =
08-02 00:04:31.234  2202  2202 D SST     : [0] updateSpnDisplay: updateSpnDisplay: changed sending intent, rule=2, showPlmn='true', plmn='null', showSpn='false', spn='null', dataSpn='', subId='-1'
08-02 00:04:31.235  2202  2202 D SubscriptionManager: putPhoneIdAndSubIdExtra: no valid subs
08-02 00:04:31.238  2202  2202 D SubscriptionController: [setPlmnSpn] No valid subscription to store info
08-02 00:04:31.239  2202  2202 D SubscriptionController: notifySubscriptionInfoChanged:
08-02 00:04:31.245  2202  2202 D SST     : [0] updateSpnDisplayLegacy-
08-02 00:04:31.246  2202  2202 D LocaleTracker-0: Operator numeric changes to "23420"
08-02 00:04:31.251  2202  2202 D LocaleTracker-0: updateLocale: countryIso = gb, countryIsoDebugInfo = OperatorNumeric(23420): MccTable.geoCountryCodeForMccMnc("MccMnc{mcc='234', mnc='20'}")
08-02 00:04:31.251  2202  2202 D LocaleTracker-0: updateLocale: Change the current country to "gb", countryIsoDebugInfo = OperatorNumeric(23420): MccTable.geoCountryCodeForMccMnc("MccMnc{mcc='234', mnc='20'}"), mCellInfoList = null
08-02 00:04:31.256  2202  2202 D LocaleTracker-0: update country iso in sharedPrefs gb
08-02 00:04:31.258  2202  2202 D SubscriptionManager: putPhoneIdAndSubIdExtra: no valid subs
08-02 00:04:31.259  2202  2202 D LocaleTracker-0: updateLocale: timeZoneCountryIso = gb, timeZoneCountryIsoDebugInfo = OperatorNumeric(23420): MccTable.geoCountryCodeForMccMnc("MccMnc{mcc='234', mnc='20'}")
08-02 00:04:31.260  2202  2202 D NitzStateMachineImpl: handleCountryDetected: countryIsoCode=gb, mLatestNitzSignal=null
08-02 00:04:31.273  2202  2202 D NitzStateMachineImpl: doTimeZoneDetection: countryIsoCode=gb, nitzSignal=null, suggestion=TelephonyTimeZoneSuggestion{mSlotIndex=0, mZoneId='Europe/London', mMatchType=2, mQuality=1, mDebugInfo=[findTimeZoneFromNetworkCountryCode: whenMillis=1659398671260, countryIsoCode=gb, findTimeZoneFromNetworkCountryCode: lookupResult=CountryResult{zoneId='Europe/London', quality=1, mDebugInfo=One effective time zone found at whenMillis=1659398671260}, Detection reason=handleCountryDetected("gb")]}, reason=handleCountryDetected("gb")
08-02 00:04:31.277  2202  2202 D SST     : [0] Broadcasting ServiceState : {mVoiceRegState=3(POWER_OFF), mDataRegState=1(OUT_OF_SERVICE), mChannelNumber=-1, duplexMode()=0, mCellBandwidths=[], mOperatorAlphaLong=Three.co.uk, mOperatorAlphaShort=3, isManualNetworkSelection=false(automatic), getRilVoiceRadioTechnology=0(Unknown), getRilDataRadioTechnology=0(Unknown), mCssIndicator=unsupported, mNetworkId=-1, mSystemId=-1, mCdmaRoamingIndicator=-1, mCdmaDefaultRoamingIndicator=-1, mIsEmergencyOnly=false, isUsingCarrierAggregation=false, mArfcnRsrpBoost=0, mNetworkRegistrationInfos=[NetworkRegistrationInfo{ domain=PS transportType=WLAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=CS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=PS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}], mNrFrequencyRange=0, mOperatorAlphaLongRaw=Three.co.uk, mOperatorAlphaShortRaw=3, mIsDataRoamingFromRegistration=false, mIsIwlanPreferred=false}
08-02 00:04:31.279  2202  2202 D DefaultPhoneNotifier: notifyServiceStateForSubId: mRegistryMgr=android.telephony.TelephonyRegistryManager@51ca98c ss={mVoiceRegState=3(POWER_OFF), mDataRegState=1(OUT_OF_SERVICE), mChannelNumber=-1, duplexMode()=0, mCellBandwidths=[], mOperatorAlphaLong=Three.co.uk, mOperatorAlphaShort=3, isManualNetworkSelection=false(automatic), getRilVoiceRadioTechnology=0(Unknown), getRilDataRadioTechnology=0(Unknown), mCssIndicator=unsupported, mNetworkId=-1, mSystemId=-1, mCdmaRoamingIndicator=-1, mCdmaDefaultRoamingIndicator=-1, mIsEmergencyOnly=false, isUsingCarrierAggregation=false, mArfcnRsrpBoost=0, mNetworkRegistrationInfos=[NetworkRegistrationInfo{ domain=PS transportType=WLAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=CS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=PS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}], mNrFrequencyRange=0, mOperatorAlphaLongRaw=Three.co.uk, mOperatorAlphaShortRaw=3, mIsDataRoamingFromRegistration=false, mIsIwlanPreferred=false} sender=Handler (com.android.internal.telephony.GsmCdmaPhone) {90720e9} phondId=0 subId=-1
08-02 00:04:31.282   695   762 D TelephonyRegistry: notifyServiceStateForSubscriber: INVALID phoneId=0 or subId=-1
08-02 00:04:31.284  2202  2399 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:31.286   695   762 E PHONE   : ServiceState.getRadioTechnology() DEPRECATED will be removed *******
08-02 00:04:31.293   695   762 E PHONE   : ServiceState.getRadioTechnology() DEPRECATED will be removed *******
08-02 00:04:31.326  2202  2202 D SST     : [0] notifyVoiceRegStateRilRadioTechnologyChanged: vrs=3 rat=0
08-02 00:04:31.326  2202  2202 D GsmCdmaCallTracker: Event EVENT_POLL_CALLS_RESULT Received
08-02 00:04:31.326  2202  2202 D GsmCdmaCallTracker: [0] update phone state, old=IDLE new=IDLE
08-02 00:04:31.327  2202  2202 D SmsDispatchersController: IMS registration state: false format: 3gpp
08-02 00:04:31.327  2202  2202 D GsmCdmaPhone: [0] EVENT_REQUEST_VOICE_RADIO_TECH_DONE: newVoiceTech=0
08-02 00:04:31.328  2202  2202 D GsmCdmaPhone: [0] phoneObjectUpdater: newVoiceRadioTech=0
08-02 00:04:31.329  2202  2202 D GsmCdmaPhone: [0] phoneObjectUpdater: volteReplacementRat=0
08-02 00:04:31.329  2202  2202 E GsmCdmaPhone: [0] phoneObjectUpdater: newVoiceRadioTech=0 doesn't match either CDMA or GSM - error! No phone change
08-02 00:04:31.335  2202  2202 D RILJ    : [0052]> SET_SIGNAL_STRENGTH_REPORTING_CRITERIA [PHONE0]
08-02 00:04:31.336  2202  2202 D SSCtr   : setSignalStrengthReportingCriteria consolidatedSignalThresholdInfos=[SignalThresholdInfo{mRan=1 mSignalMeasurementType=1 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[-107, -103, -97, -89] mIsEnabled=true}, SignalThresholdInfo{mRan=2 mSignalMeasurementType=2 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[-115, -105, -95, -85] mIsEnabled=true}, SignalThresholdInfo{mRan=3 mSignalMeasurementType=3 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[-128, -118, -108, -98] mIsEnabled=true}, SignalThresholdInfo{mRan=3 mSignalMeasurementType=4 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}, SignalThresholdInfo{mRan=3 mSignalMeasurementType=5 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}, SignalThresholdInfo{mRan=6 mSignalMeasurementType=6 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[-110, -90, -80, -65] mIsEnabled=true}, SignalThresholdInfo{mRan=6 mSignalMeasurementType=7 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}, SignalThresholdInfo{mRan=6 mSignalMeasurementType=8 mHysteresisMs=3000 mHysteresisDb=2 mThresholds=[] mIsEnabled=false}]
08-02 00:04:31.336  2202  2202 D CdmaSSM : CDMA_SUBSCRIPTION_SOURCE event = 2
08-02 00:04:31.337  2202  2399 D RILJ    : [0052]< SET_SIGNAL_STRENGTH_REPORTING_CRITERIA  [PHONE0]
08-02 00:04:31.344  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=7, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1000 RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:31.338, evaluation result=null] shouldApply false
08-02 00:04:31.345  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=27, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1001 RequestorUid: 1001 RequestorPkg: com.android.phone UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:31.345, evaluation result=null] shouldApply false
08-02 00:04:31.346  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=1, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VPN&NOT_VCN_MANAGED RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:31.346, evaluation result=null] shouldApply false
08-02 00:04:31.347  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=16, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1073 RequestorUid: 1073 RequestorPkg: com.android.networkstack UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:31.346, evaluation result=null] shouldApply false
08-02 00:04:31.347  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=14, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1000 RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:31.347, evaluation result=null] shouldApply false
08-02 00:04:31.348  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=21, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 10062 RequestorUid: 10062 RequestorPkg: com.android.systemui UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:31.348, evaluation result=null] shouldApply false
08-02 00:04:31.349  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=23, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 10062 RequestorUid: 10062 RequestorPkg: com.android.systemui UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:31.348, evaluation result=null] shouldApply false
08-02 00:04:31.350  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ BACKGROUND_REQUEST id=2, [ Transports: CELLULAR Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VPN&NOT_VCN_MANAGED RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:31.350, evaluation result=null] shouldApply false
08-02 00:04:31.350  2202  2202 D UiccProfile: iccOpenLogicalChannel: A00000015141434C00 , 0 by pid:2202 uid:1001
08-02 00:04:31.354  2202  2202 D RILJ    : [0053]> SIM_OPEN_CHANNEL aid = A00000015141434C00 p2 = 0 [PHONE0]
08-02 00:04:31.356  2202  2399 D RILJ    : [0053]< SIM_OPEN_CHANNEL error 6 [PHONE0]
08-02 00:04:31.357  2202  2399 D RilRequest: [0053]< SIM_OPEN_CHANNEL error: com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED ret= result={ when=-3m5s550ms what=8 obj={ when=-3m5s550ms what=1 arg2=1 target=com.android.internal.telephony.uicc.UiccCarrierPrivilegeRules } target=com.android.internal.telephony.uicc.UiccProfile$4 }
08-02 00:04:31.358  2202  2202 D DRM-0   : Remove all retry and throttling entries, reason=DATA_SERVICE_BOUND
08-02 00:04:31.359  2202  2202 D TelephonyNetworkFactory[0]: onActivePhoneSwitch
08-02 00:04:31.360  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=29, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1001 RequestorUid: 1001 RequestorPkg: com.android.phone UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:31.359, evaluation result=null] shouldApply false
08-02 00:04:31.362  2202  2202 D PhoneSwitcher: onDdsSwitchResponse: DDS switch success on phoneId = 0
08-02 00:04:31.362  2202  2202 D PhoneSwitcher: notifyPreferredDataSubIdChanged to -1
08-02 00:04:31.363   695   762 D TelephonyRegistry: notifyActiveDataSubIdChanged: activeDataSubId=-1
08-02 00:04:31.365  2202  2202 D DNC-0   : onServiceStateChanged: changed to {mVoiceRegState=3(POWER_OFF), mDataRegState=1(OUT_OF_SERVICE), mChannelNumber=-1, duplexMode()=0, mCellBandwidths=[], mOperatorAlphaLong=Three.co.uk, mOperatorAlphaShort=3, isManualNetworkSelection=false(automatic), getRilVoiceRadioTechnology=0(Unknown), getRilDataRadioTechnology=0(Unknown), mCssIndicator=unsupported, mNetworkId=-1, mSystemId=-1, mCdmaRoamingIndicator=-1, mCdmaDefaultRoamingIndicator=-1, mIsEmergencyOnly=false, isUsingCarrierAggregation=false, mArfcnRsrpBoost=0, mNetworkRegistrationInfos=[NetworkRegistrationInfo{ domain=PS transportType=WLAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=CS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}, NetworkRegistrationInfo{ domain=PS transportType=WWAN registrationState=UNKNOWN mInitialRegistrationState=UNKNOWN roamingType=NOT_ROAMING accessNetworkTechnology=UNKNOWN rejectCause=0 emergencyEnabled=false availableServices=[] cellIdentity=null voiceSpecificInfo=null dataSpecificInfo=null nrState=NONE rRplmn= isUsingCarrierAggregation=false}], mNrFrequencyRange=0, mOperatorAlphaLongRaw=Three.co.uk, mOperatorAlphaShortRaw=3, mIsDataRoamingFromRegistration=false, mIsIwlanPreferred=false}
08-02 00:04:31.366  2202  2202 D DNC-0   : onServiceStateChanged: [WWAN: UNKNOWN->UNKNOWN, UNKNOWN->UNKNOWN] [WLAN: UNKNOWN->UNKNOWN, UNKNOWN->UNKNOWN] . Evaluating network requests is not needed, evaluating existing data networks is not needed.
08-02 00:04:31.366  2202  2202 D NetworkTypeController: [0] LegacyState: process EVENT_BANDWIDTH_CHANGED
08-02 00:04:31.366  2202  2202 D NetworkTypeController: [0] Reset timers since NR is not allowed.
08-02 00:04:31.367  2202  2202 D NetworkTypeController: [0] DefaultState: process EVENT_BANDWIDTH_CHANGED
08-02 00:04:31.367  2202  2202 D GsmCdmaPhone: [0] Event BarringInfoChanged Received
08-02 00:04:31.370  2202  2202 D SST     : [0] SubscriptionListener.onSubscriptionInfoChanged
08-02 00:04:31.375  2202  2202 D Phone   : isImsRegistered =false
08-02 00:04:31.376  2202  2202 E PhoneSubInfoController: getLine1Number phone is null for Subscription:-1
08-02 00:04:31.390  2202  2202 D SST     : [0] updateSpnDisplayLegacy+
08-02 00:04:31.391  2202  2202 D SST     : [0] updateSpnDisplay: radio is off w/ showPlmn=true plmn=null
08-02 00:04:31.392  2202  2202 D SST     : [0] updateSpnDisplay: rawSpn =
08-02 00:04:31.393  2202  2202 D SST     : [0] updateSpnDisplayLegacy-
08-02 00:04:31.393  2202  2202 D EmergencyNumberTracker: ACTION_NETWORK_COUNTRY_CHANGED: PhoneId: 0 CountryIso: gb
08-02 00:04:31.396  2202  2202 D Phone   : isImsRegistered =false
08-02 00:04:31.397  2202  2202 E PhoneSubInfoController: getLine1Number phone is null for Subscription:-1
08-02 00:04:31.416  2202  2202 D LocaleTracker-0: updateLocale: countryIso = gb, countryIsoDebugInfo = OperatorNumeric(23420): MccTable.geoCountryCodeForMccMnc("MccMnc{mcc='234', mnc='20'}")
08-02 00:04:31.416  2202  2202 D LocaleTracker-0: updateLocale: timeZoneCountryIso = gb, timeZoneCountryIsoDebugInfo = OperatorNumeric(23420): MccTable.geoCountryCodeForMccMnc("MccMnc{mcc='234', mnc='20'}")
08-02 00:04:31.417  2202  2202 D NitzStateMachineImpl: handleCountryDetected: countryIsoCode=gb, mLatestNitzSignal=null
08-02 00:04:31.419  2202  2202 D NetworkTypeController: [0] LegacyState: process EVENT_DATA_RAT_CHANGED
08-02 00:04:31.419  2202  2202 D NetworkTypeController: [0] Reset timers since NR is not allowed.
08-02 00:04:31.419  2202  2202 D NetworkTypeController: [0] Reset timers since 2G and 3G don't need NR timers.
08-02 00:04:31.420  2202  2202 D GsmCdmaPhone: [0] onVoiceRegStateOrRatChanged
08-02 00:04:31.420  2202  2202 D GsmCdmaPhone: [0] getCsCallRadioTech, current vrs=3, vrat=0
08-02 00:04:31.420  2202  2202 D GsmCdmaPhone: [0] getCsCallRadioTech, result calcVrat=0
08-02 00:04:31.420  2202  2202 E CarrierActionAgent: [0]Unsupported action: 7
08-02 00:04:31.427  2202  2202 D UiccProfile: handleMessage: Received OPEN_LOGICAL_CHANNEL_DONE for phoneId 0
08-02 00:04:31.427  2202  2202 D UiccProfile: handleMessage: Error in SIM access with exception com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED
08-02 00:04:31.428  2202  2202 D PinStorage: SIM card/application changed[0]: PRESENT
08-02 00:04:31.428  2202  2202 D LocaleTracker-0: updateLocale: countryIso = gb, countryIsoDebugInfo = OperatorNumeric(23420): MccTable.geoCountryCodeForMccMnc("MccMnc{mcc='234', mnc='20'}")
08-02 00:04:31.428  2202  2202 D LocaleTracker-0: updateLocale: timeZoneCountryIso = gb, timeZoneCountryIsoDebugInfo = OperatorNumeric(23420): MccTable.geoCountryCodeForMccMnc("MccMnc{mcc='234', mnc='20'}")
08-02 00:04:31.428  2202  2202 D NitzStateMachineImpl: handleCountryDetected: countryIsoCode=gb, mLatestNitzSignal=null
08-02 00:04:31.429  2202  2202 D DNC-0   : onSimStateChanged: state=PRESENT
08-02 00:04:31.429  2202  2202 D TelephonyNetworkFactory[0]: onActivePhoneSwitch
08-02 00:04:31.431  2202  2202 D EmergencyNumberTracker: updateEmergencyNumberListDatabaseAndNotify(): receiving countryIso: gb
08-02 00:04:31.443  2202  2202 D EmergencyNumberTracker: gb asset emergency database is loaded. Ver: 1 Phone Id: 0
08-02 00:04:31.445  2202  2202 E EmergencyNumberTracker: Cache ota emergency database IOException: java.io.FileNotFoundException: /data/misc/emergencynumberdb/emergency_number_db: open failed: ENOENT (No such file or directory)
08-02 00:04:31.445  2202  2202 D EmergencyNumberTracker: Using Asset Emergency database. Version: 1
08-02 00:04:31.446  2202  2202 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:31.447  2202  2202 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:31.448  2202  2202 E EmergencyNumberTracker: getEmergencyNumberListFromEccListDatabaseAndTest: radio indication is unavailable in 1.4 HAL.
08-02 00:04:31.448  2202  2202 E EmergencyNumber: Found unexpected duplicate numbers: EmergencyNumber:Number-999|CountryIso-gb|Mnc-|ServiceCategories-111|Urns-[]|Sources-10000|Routing-0 vs EmergencyNumber:Number-999|CountryIso-gb|Mnc-|ServiceCategories-111|Urns-[]|Sources-10000|Routing-0
08-02 00:04:31.451  2202  2202 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:31.451  2202  2202 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:31.451  2202  2202 E EmergencyNumberTracker: getEmergencyNumberListFromEccListDatabaseAndTest: radio indication is unavailable in 1.4 HAL.
08-02 00:04:31.452  2202  2202 E EmergencyNumber: Found unexpected duplicate numbers: EmergencyNumber:Number-999|CountryIso-gb|Mnc-|ServiceCategories-111|Urns-[]|Sources-10000|Routing-0 vs EmergencyNumber:Number-999|CountryIso-gb|Mnc-|ServiceCategories-111|Urns-[]|Sources-10000|Routing-0
08-02 00:04:31.452  2202  2202 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:31.452  2202  2202 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:31.453  2202  2202 E EmergencyNumberTracker: getEmergencyNumberListFromEccListDatabaseAndTest: radio indication is unavailable in 1.4 HAL.
08-02 00:04:31.453  2202  2202 E EmergencyNumber: Found unexpected duplicate numbers: EmergencyNumber:Number-999|CountryIso-gb|Mnc-|ServiceCategories-111|Urns-[]|Sources-10000|Routing-0 vs EmergencyNumber:Number-999|CountryIso-gb|Mnc-|ServiceCategories-111|Urns-[]|Sources-10000|Routing-0
08-02 00:04:31.456  2202  2202 D EmergencyNumberTracker: notifyEmergencyNumberList(): notified
08-02 00:04:31.458  2202  2202 E PhoneSubInfoController: getLine1Number phone is null for Subscription:-1
08-02 00:04:31.672  2202  2202 D UiccPkcs15: Creating UiccPkcs15
08-02 00:04:31.672  2202  2202 D UiccProfile: iccOpenLogicalChannel: A000000063504B43532D3135 , 4 by pid:2202 uid:1001
08-02 00:04:31.675  2202  2202 D RILJ    : [0054]> SIM_OPEN_CHANNEL aid = A000000063504B43532D3135 p2 = 4 [PHONE0]
08-02 00:04:31.677  2202  2399 D RILJ    : [0054]< SIM_OPEN_CHANNEL error 6 [PHONE0]
08-02 00:04:31.678  2202  2399 D RilRequest: [0054]< SIM_OPEN_CHANNEL error: com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED ret= result={ when=-3m5s870ms what=8 obj={ when=-3m5s870ms what=201 target=com.android.internal.telephony.uicc.UiccPkcs15$Pkcs15Selector } target=com.android.internal.telephony.uicc.UiccProfile$4 }
08-02 00:04:31.679  2202  2202 D UiccProfile: handleMessage: Received OPEN_LOGICAL_CHANNEL_DONE for phoneId 0
08-02 00:04:31.679  2202  2202 D UiccProfile: handleMessage: Error in SIM access with exception com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED
08-02 00:04:31.680  2202  2202 D UiccPkcs15: handleMessage: 201
08-02 00:04:31.680  2202  2202 D UiccPkcs15: error: com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED
08-02 00:04:31.680  2202  2202 D UiccPkcs15: handleMessage: 1
08-02 00:04:31.681  2202  2202 D UiccPkcs15: select pkcs15 failed: com.android.internal.telephony.CommandException: REQUEST_NOT_SUPPORTED
08-02 00:04:31.681  2202  2202 D UiccProfile: handleMessage: Received CARRIER_PRIVILEGES_LOADED for phoneId 0
08-02 00:04:31.699  2202  2202 D UiccProfile: setExternalState: !override and newstate unchanged from NOT_READY
08-02 00:04:32.117  2202  2400 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:32.381  2202  2426 E PhoneSubInfoController: getLine1Number phone is null for Subscription:-1
08-02 00:04:34.650  2202  2202 D SmsBroadcastUndelivered: Received broadcast android.intent.action.USER_UNLOCKED
08-02 00:04:34.682  2202  2202 D SmsDispatchersController: Received broadcast android.intent.action.USER_UNLOCKED
08-02 00:04:34.690  2202  2585 D SmsBroadcastUndelivered: scanning raw table for undelivered messages
08-02 00:04:35.175  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=31, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1000 RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ]
08-02 00:04:35.180  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=31, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1000 RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:35.177, evaluation result=null] shouldApply false
08-02 00:04:35.197  2202  2585 D SmsBroadcastUndelivered: finished scanning raw table in 506 ms
08-02 00:04:35.374  2202  2368 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:35.404  2202  2202 D SubscriptionController: [getActiveSubscriptionInfo]- subId=-1 subList=[] subInfo=null
08-02 00:04:35.411  2202  2202 D DSMGR-0 : mIsDataEnabled=true, prevDataEnabled=false
08-02 00:04:35.411  2202  2202 D DSMGR-0 : notifyDataEnabledChanged: enabled=true, reason=UNKNOWN, callingPackage=com.android.phone
08-02 00:04:35.422  2202  2202 D DSRM-0  : onMobileDataEnabledChanged: DataEnabled:true,DataStalled:false
08-02 00:04:35.422  2202  2202 D DNC-0   : onDataEnabledChanged: enabled=true
08-02 00:04:35.425  2202  2202 D DNC-0   : Re-evaluating 0 unsatisfied network requests in 0 groups,  due to DATA_ENABLED_CHANGED
08-02 00:04:35.629  2202  2368 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:36.156  2202  2202 D TelephonyNetworkFactory[0]: onReleaseNetworkFor [NetworkRequest [ REQUEST id=29, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 1001 RequestorUid: 1001 RequestorPkg: com.android.phone UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:36.154, evaluation result=null] applied false
08-02 00:04:39.929  2202  2398 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:39.931  2202  2398 D SubscriptionController: [getSlotIndex]- subId invalid
08-02 00:04:58.404  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=33, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 10024 RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ]
08-02 00:04:58.407  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=33, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 10024 RequestorUid: 1000 RequestorPkg: android UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:58.405, evaluation result=null] shouldApply false
08-02 00:04:58.531  2202  2202 D TelephonyNetworkFactory[0]: got request NetworkRequest [ REQUEST id=35, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 10024 RequestorUid: 10024 RequestorPkg: com.android.statementservice UnderlyingNetworks: Null] ]
08-02 00:04:58.533  2202  2202 D TelephonyNetworkFactory[0]: onNeedNetworkFor [NetworkRequest [ REQUEST id=35, [ Capabilities: INTERNET&NOT_RESTRICTED&TRUSTED&NOT_VCN_MANAGED Uid: 10024 RequestorUid: 10024 RequestorPkg: com.android.statementservice UnderlyingNetworks: Null] ], mPriority=20, state=UNSATISFIED, mAttachedDataNetwork=null, isMetered=true, created time=00:04:58.532, evaluation result=null] shouldApply false
08-02 00:31:25.872  2202  2202 D RILJ    : [0055]> GET_ACTIVITY_INFO [PHONE0]
08-02 00:31:25.881  2202  2236 D RILJ    : [0055]< GET_ACTIVITY_INFO ModemActivityInfo{ mTimestamp=1800073 mSleepTimeMs=0 mIdleTimeMs=0 mTxTimeMs[]=[0, 5, 10, 15, 20] mRxTimeMs=10} [PHONE0]
```
