# Development notes

## Modem stuff

* From shed only seems to find GSM and UMTS connection, probably can find LTE if searching?
* Can modem be connected to multiple networks? If so, how do you get the signal strength for each one?
* Implement get operator name properly, CarrierConfig needs this to be correct.

get file attributes (GET_RESPONSE):

```
<<<<<< RAW:
<<<<<<   length = 28
<<<<<<   data   = 01:1B:00:00:0B:01:00:01:00:24:00:0F:00:02:07:00:62:6F:04:00:3F:FF:7F:01:02:00:00:00

[22 Aug 2022, 13:39:11] [Debug] [qrtr://0] Sent generic request (translated)...
<<<<<< QMUX:
<<<<<<   length  = 27
<<<<<<   flags   = 0x00
<<<<<<   service = "uim"
<<<<<<   client  = 1
<<<<<< QMI:
<<<<<<   flags       = "none"
<<<<<<   transaction = 1
<<<<<<   tlv_length  = 15
<<<<<<   message     = "Get File Attributes" (0x0024)
<<<<<< TLV:
<<<<<<   type       = "File" (0x02)
<<<<<<   length     = 7
<<<<<<   value      = 62:6F:04:00:3F:FF:7F
<<<<<<   translated = [ file_id = '28514' file_path = '{ [0] = '0 ' [1] = '63 ' [2] = '255 ' [3] = '127 '}' ]
<<<<<< TLV:
<<<<<<   type       = "Session" (0x01)
<<<<<<   length     = 2
<<<<<<   value      = 00:00
<<<<<<   translated = [ session_type = 'primary-gw-provisioning' application_identifier = '{}' ]

[22 Aug 2022, 13:39:11] [Debug] [qrtr://0] Received message...
<<<<<< RAW:
<<<<<<   length = 91
<<<<<<   data   = 01:5A:00:00:0B:01:02:01:00:24:00:4E:00:02:04:00:00:00:00:00:13:04:00:01:00:00:00:11:38:00:0A:00:62:6F:00:00:00:00:00:00:00:00:01:00:00:00:00:00:01:00:00:01:00:00:1E:00:62:1C:82:02:41:21:83:02:6F:62:A5:03:80:01:71:8A:01:05:8B:03:6F:06:02:80:02:00:0A:88:01:98:10:02:00:90:00

[22 Aug 2022, 13:39:11] [Debug] [qrtr://0] Received generic response (translated)...
<<<<<< QMUX:
<<<<<<   length  = 90
<<<<<<   flags   = 0x00
<<<<<<   service = "uim"
<<<<<<   client  = 1
<<<<<< QMI:
<<<<<<   flags       = "response"
<<<<<<   transaction = 1
<<<<<<   tlv_length  = 78
<<<<<<   message     = "Get File Attributes" (0x0024)
<<<<<< TLV:
<<<<<<   type       = "Result" (0x02)
<<<<<<   length     = 4
<<<<<<   value      = 00:00:00:00
<<<<<<   translated = SUCCESS
<<<<<< TLV:
<<<<<<   type   = 0x13
<<<<<<   length = 4
<<<<<<   value  = 01:00:00:00
<<<<<< TLV:
<<<<<<   type       = "File Attributes" (0x11)
<<<<<<   length     = 56
<<<<<<   value      = 0A:00:62:6F:00:00:00:00:00:00:00:00:01:00:00:00:00:00:01:00:00:01:00:00:1E:00:62:1C:82:02:41:21:83:02:6F:62:A5:03:80:01:71:8A:01:05:8B:03:6F:06:02:80:02:00:0A:88:01:98
<<<<<<   translated = [ file_size = '10' file_id = '28514' file_type = 'transparent' record_size = '0' record_count = '0' read_security_attributes_logic = 'always' read_security_attributes = '(null)' write_security_attributes_logic = 'never' write_security_attributes = '(null)' increase_security_attributes_logic = 'always' increase_security_attributes = '(null)' deactivate_security_attributes_logic = 'never' deactivate_security_attributes = '(null)' activate_security_attributes_logic = 'never' activate_security_attributes = '(null)' raw_data = '{ [0] = '98 ' [1] = '28 ' [2] = '130 ' [3] = '2 ' [4] = '65 ' [5] = '33 ' [6] = '131 ' [7] = '2 ' [8] = '111 ' [9] = '98 ' [10] = '165 ' [11] = '3 ' [12] = '128 ' [13] = '1 ' [14] = '113 ' [15] = '138 ' [16] = '1 ' [17] = '5 ' [18] = '139 ' [19] = '3 ' [20] = '111 ' [21] = '6 ' [22] = '2 ' [23] = '128 ' [24] = '2 ' [25] = '0 ' [26] = '10 ' [27] = '136 ' [28] = '1 ' [29] = '152 '}' ]
<<<<<< TLV:
<<<<<<   type       = "Card result" (0x10)
<<<<<<   length     = 2
<<<<<<   value      = 90:00
<<<<<<   translated = [ sw1 = '144' sw2 = '0' ]

[(null)] Successfully got file 'qrtr://0' attributes from the UIM:
Card result:
	SW1: '0x90'
	SW2: '0x00'
File attributes:
	File size: 10
	File ID: 28514
	File type: transparent
	Record size: 0
	Record count: 0
	Read security attributes: (always) none
	Write security attributes: (never) none
	Increase security attributes: (always) none
	Deactivate security attributes: (never) none
	Activate security attributes: (never) none
	Raw: 	62:1C:82:02:41:21:83:02:6F:62:A5:03:80:01:71:8A:01:05:8B:03:6F:06:02:80:02:00:
	0A:88:01:98
```

## Android telephony stack

Telephony stack uses a "subscription ID" [quite a
lot](https://developer.android.com/guide/topics/connectivity/telecom/telephony-ids).
However, for some reason it's always -1. I suspect because the SIM card
application is never being provisioned and I don't properly report network state

* Improving RadioNetwork::getSignalStrength()
* Adding some indications to report more about modem state and hopefully encourage Android to go further.
* look at SetupDataCallResult, implement CellIdentity and CellInfo

Seems like I can just set up a data connection and tell Android with
IRadioDataIndication.dataCallListChanged() and it will handle the rest. I need
to create the interface and then just tell Android the IP addr, DNS etc.

### RadioCapability

Used to enable/disable different radio technologies? e.g. configure LTE only

* I guess this matches what I've seen in Android settings...
* Weird sequencing.
* Should stub for now, but need to implement better.

## QMIC

* Support fixed length strings in structs (char array)
* Finish implementing message struct free()

