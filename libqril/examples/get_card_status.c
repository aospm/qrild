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

#include "qmi_uim.h"

/**
 * @brief get the status of all installed SIM cards and dump them to stdout
 */
void get_card_status()
{
	// The initializer macro sets the response header so that libqril knows
	// how to decode it properly. This pointer does have to be free'd!
	struct uim_get_card_status_resp *resp = UIM_GET_CARD_STATUS_RESP_NEW;
	struct uim_card_status *status = &resp->status;
	int rc;

	// The get card status request doesn't require any arguments, so we use basic request helper
	rc = libqril_send_basic_request_sync(QMI_SERVICE_UIM, QMI_UIM_GET_CARD_STATUS, &resp->hdr);
	if (rc) {
		log_error("Failed to get card status: %d, %s", rc, libqril_strerror(rc));
		free(resp);
		return;
	}

	if (!resp->status_valid) {
		log_error("Response card status is invalid");
		free(resp);
		return;
	}

	log_info("UIM Card status:\n"
		 "\tPrimary GW: %u\n"
		 "\tPrimary 1X: %u\n"
		 "\tSecondary GW: %u\n"
		 "\tSecondary 1X: %u\n"
		 "\tCards: %u",
		 status->index_gw_primary, status->index_1x_primary, status->index_gw_secondary,
		 status->index_1x_secondary, status->cards_len);

	for (int i = 0; i < status->cards_len; i++) {
		struct uim_card_status_cards *card = &status->cards[i];
		log_info("\t\tState: %u, upin_state: %u, upin_retries: %u", card->card_state,
			 card->upin_state, card->upin_retries);
		log_info("\t\tApplications: %u", card->applications_len);
		for (int j = 0; j < card->applications_len; j++) {
			struct uim_card_status_cards_applications *appn = &card->applications[i];
			log_info("\t\t\ttype: %u, state: %u, AID: %s", appn->type, appn->state,
				 bytes_to_hex_string(appn->application_identifier_value,
						     appn->application_identifier_value_len));
		}
	}

	free(resp);
}

int main(int argc, char **argv)
{
	int rc;

	libqril_init();

	// Block until all QMI services are discovered
	libqril_wait_for_service_discovery();
	log_info("Services discovered");

	rc = libqril_modem_activate();
	if (rc < 0) {
		log_error("Failed to power up the modem!: %d", rc);
		return 1;
	}

	get_card_status();

	return 0;
}