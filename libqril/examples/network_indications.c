/*
 * Copyright (C) 2022, Linaro Ltd.
 * Author: Caleb Connolly <caleb.connolly@linaro.org>
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
#include <errno.h>
#include <linux/qrtr.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>

#include "libqril.h"
#include "libqrtr.h"

#include "qmi_uim.h"
#include "qmi_nas.h"

void show_nas_serving_system_report(struct nas_serving_system_ind *rep)
{
	log_info("Got serving system report:\n"
		 "\treg state: %u\n"
		 "\tlac: 0x%x, cid: 0x%x",
			rep->system_valid ? rep->system.registration_state : 0xff,
			rep->lac, rep->cid);
	if (rep->plmn_valid)
		log_info("\tcurrent_plmn: %03d%02d %s", rep->plmn.mcc, rep->plmn.mnc, rep->plmn.description);
}

void handle_qmi_indication(void *data, enum qmi_service service, struct qmi_header *buf, size_t len)
{
	int rc;
	log_info("Got QMI indication for service %s, msg_id: 0x%04x, txn_id: 0x%04x",
		 libqril_qmi_service_name(service), buf->msg_id, buf->txn_id);

	switch (service) {
	case QMI_SERVICE_NAS:
		if (buf->msg_id == QMI_NAS_SERVING_SYSTEM_REPORT) {
			struct nas_serving_system_ind *ind = NAS_SERVING_SYSTEM_IND_NEW;

			rc = qmi_decode_message2(buf, len, ind);
			if (rc < 0) {
				log_error("Couldn't decode NAS serving system report: %s", strerror(rc));
			}
			show_nas_serving_system_report(ind);
			free(ind);
		}
		break;
	default:
		break;
	}
}

static struct libqril_events network_indications_handler = {
	.on_qmi_indication = handle_qmi_indication,
};

void register_network_indications()
{
	struct nas_register_indications_req *req = NAS_REGISTER_INDICATIONS_REQ_NEW;
	int rc;

	req->system_selection_preference = false;
	req->ddtm_events = true;
	req->serving_system_events = true;
	req->dual_standby_preference = false;
	req->subscription_info = true;
	req->network_time = true;
	req->system_info = false;
	req->signal_info = true;
	req->error_rate = true;
	req->hdr_new_uati_assigned = false;
	req->hdr_session_closed = false;
	req->managed_roaming = true;
	req->current_plmn_name = true;
	req->embms_status = false;
	req->rf_band_information = false;
	req->network_reject_information.enable_network_reject_indications = true;
	req->network_reject_information.suppress_system_info_indications = false;

	rc = libqril_send_message_ack_sync(req);
	log_info("Registered network indications, got response: %d", rc);

	free(req);
}

// Get the first available application ID on the first available SIM card
// AID is assumed to be at least 16 bytes in length
int get_first_available_aid(uint8_t *aid, int *aid_len, int *card_slot)
{
	struct uim_get_card_status_resp *resp = UIM_GET_CARD_STATUS_RESP_NEW;
	struct uim_card_status *status = &resp->status;
	int rc;

	// The get card status request doesn't require any arguments, so we use basic request helper
	rc = libqril_send_basic_request_sync(QMI_SERVICE_UIM, QMI_UIM_GET_CARD_STATUS, &resp->hdr);
	if (rc) {
		log_error("Failed to get card status: %d, %s", rc, libqril_strerror(rc));
		free(resp);
		return rc;
	}

	if (!resp->status_valid) {
		log_error("Response card status is invalid");
		free(resp);
		return -EINVAL;
	}

	for (size_t i = 0; i < status->cards_len; i++) {
		struct uim_card_status_cards *card = &status->cards[i];
		for (size_t j = 0; j < card->applications_len; j++) {
			struct uim_card_status_cards_applications *appn = &card->applications[i];
			if (appn->application_identifier_value_len > 16) {
				log_error("Invalid AID length: %d", appn->application_identifier_value_len);
				return -EINVAL; // definitely the wrong error
			}
			memcpy(aid, appn->application_identifier_value, appn->application_identifier_value_len);
			*aid_len = appn->application_identifier_value_len;
			*card_slot = i + 1;
			log_info("Found AID: %s on card slot %d", bytes_to_hex_string(aid, *aid_len), *card_slot);
			free(resp);
			return 0;
		}
	}

	free(resp);
	return -ENODATA;
}

int provision_first_sim()
{
	struct uim_change_provisioning_session_req *req = UIM_CHANGE_PROVISIONING_SESSION_REQ_NEW;
	uint8_t aid[16];
	int aid_len, slot;
	int rc;

	rc = get_first_available_aid((uint8_t*)aid, &aid_len, &slot);
	if (rc) {
		log_error("Failed to find any valid SIM application, do you have a SIM inserted?");
		free(req);
		return rc;
	}

	req->session_change_valid = true;
	req->session_change.activate = true;
	req->session_change.session_type = QMI_UIM_SESSION_TYPE_PRIMARY_GW_PROVISIONING;

	req->application_information_valid = true;
	req->application_information.slot = slot;
	memcpy((uint8_t*)req->application_information.application_identifier_value, aid, aid_len);
	req->application_information.application_identifier_value_len = aid_len;

	rc = libqril_send_message_ack_sync(req);

	free(req);
	return rc;
}

int main(int argc, char **argv)
{
	int rc;

	libqril_init();

	libqril_register_event_handlers(&network_indications_handler, NULL);

	// Block until all QMI services are discovered
	libqril_wait_for_service_discovery();
	log_info("Services discovered");

	// Libqril contains a few high level helpers for standard
	// tasks like ensuring the modem is online
	rc = libqril_modem_activate();
	if (rc < 0) {
		log_error("Failed to power up the modem!: %d", rc);
		return 1;
	}

	register_network_indications();

	rc = provision_first_sim();
	if (rc) {
		log_error("Failed to provision SIM card: %s", libqril_strerror(rc));
		return 0;
	}
	sleep(10000);

	return 0;
}