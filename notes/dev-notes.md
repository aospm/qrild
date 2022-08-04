# Development notes

## Modem stuff

* From shed only seems to find GSM and UMTS connection, probably can find LTE if searching?
* Can modem be connected to multiple networks? If so, how do you get the signal strength for each one?
* Implement get operator name properly, CarrierConfig needs this to be correct.

## Android telephony stack

Telephony stack uses a "subscription ID" [quite a
lot](https://developer.android.com/guide/topics/connectivity/telecom/telephony-ids).
However, for some reason it's always -1. I suspect because the SIM card
application is never being provisioned and I don't properly report network state

* Improving RadioNetwork::getSignalStrength()
* Adding some indications to report more about modem state and hopefully encourage Android to go further.

## QMIC

* Support fixed length strings in structs (char array)
* Finish implementing message struct free()

