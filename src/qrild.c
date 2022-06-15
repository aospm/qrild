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

// FIXME: add these headers for building on Linux too
#ifdef ANDROID
#include <telephony/ril.h>
#endif

#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>
#include <linux/qrtr.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "libqrtr.h"
#include "logging.h"

#include "qrild.h"
#include "qrild_link.h"
#include "qrild_qrtr.h"
#include "qrild_qmi.h"
#include "util.h"

static int process_pending(struct rild_state *state) {
	int rc;
	switch (state->state) {
	case QRILD_ACTION_POWERUP:
		rc = qrild_qmi_powerup(state);
		break;
	case QRILD_ACTION_SLOT_STATUS:
		rc = qrild_qmi_uim_get_card_status(state);
		break;
	case QRILD_ACTION_PROVISION:
		rc = qrild_qmi_uim_set_provisioning(state);
		break;
	case QRILD_ACTION_OPEN_PORT:
		rc = qrild_qmi_dpm_open_port(state);
		break;
	case QRILD_ACTION_SET_DATA_FORMAT:
		rc = qrild_qmi_wda_set_data_format(state);
		break;
	case QRILD_ACTION_BIND_SUBSCRIPTION:
		rc = qrild_qmi_wds_bind_subscription(state);
		break;
	case QRILD_ACTION_MUX_DATA_PORT:
		rc = qrild_qmi_wds_bind_mux_data_port(state);
		break;
	case QRILD_ACTION_START_NET_IFACES:
		rc = qrild_qmi_wds_start_network_interface(state);
		break;
	case QRILD_ACTION_GET_RUNTIME_SETTINGS:
		rc = qrild_qmi_wds_get_current_settings(state);
		break;
	// case QRILD_ACTION_NETLINK:
	// 	rc = qrild_qmi_wds_get_current_settings(state);
	// 	break;
	case QRILD_ACTION_HALT:
		printf("Sleeping to keep port open\n");
		rc = QRILD_STATE_DONE;
		sleep(100000);
		break;
	default:
		fprintf(stderr, "[STATE] unknown state %d\n", state->state);
		return -1;
	}

	switch(rc) {
	case QRILD_STATE_PENDING:
		break;
	case QRILD_STATE_ERROR:
		fprintf(stderr, "ERROR: failed in state %d\n", state->state);
		return rc;
	case QRILD_STATE_DONE:
		state->state++;
		printf("[STATE] switch to state %d\n", state->state);
		break;
	}

	return 0;
}

void usage() {
	fprintf(stderr, "qrild: QRTR modem interface / RIL\n");
	fprintf(stderr, "--------------------------------------\n");
	fprintf(stderr, "qrild [-h] [-i IP -g GATEWAY]\n");
	fprintf(stderr, "    -h               This help message\n");
	fprintf(stderr, "    -n               Don't configure network interfaces automatically\n");
	fprintf(stderr, "    -i IP            IP address to configure\n");
	fprintf(stderr, "    -g GATEWAY       Gateway address to use\n\n");
	fprintf(stderr, "When the IP address and gateway are specified qrild will not\n");
	fprintf(stderr, "talk to the modem but just configure the rmnet interface.\n");

	exit(1);
}

int main(int argc, char **argv) {
	struct rild_state state;
	int rc;
	int opt;
	const char *progname = basename(argv[0]);
	const char *ip_str = NULL, *gateway_str = NULL;
	struct in_addr ip, mask, gateway;

	(void)argc;

	qlog_setup(progname, false);
	qlog_set_min_priority(LOG_DEBUG);

	memset(&state, 0, sizeof(state));

	state.sock = -1;
	state.txn = 4;
	list_init(&state.services);
	list_init(&state.resp_queue);
	state.started = false;
	state.no_configure_inet = false;

	while ((opt = getopt(argc, argv, "hni:g:")) != -1) {
		switch (opt) {
		case 'n':
			state.no_configure_inet = true;
			break;
		case 'i':
			ip_str = optarg;
			break;
		case 'g':
			gateway_str = optarg;
			break;
		case 'h':
		default:
			usage();
		}
	}

	if ((ip_str && !gateway_str) || (gateway_str && !ip_str)) {
		fprintf(stderr, "You must pass both '-i' and '-g' or none of them\n");
		return EXIT_FAILURE;
	}

	if (ip_str) {
		printf("Got IP: %s, gateway: %s\n", ip_str, gateway_str);
		rc = inet_aton(ip_str, &ip);
		if (rc == 0) {
			fprintf(stderr, "Invalid IP address: '%s'\n", ip_str);
			return EXIT_FAILURE;
		}
		rc = inet_aton(gateway_str, &gateway);
		if (rc == 0) {
			fprintf(stderr, "Invalid gateway address: '%s'\n", ip_str);
			return EXIT_FAILURE;
		}
		printf("Both inet_aton success\n");

		// hardcode the mask for now when setting manually, it's always /29 anyway
		mask.s_addr = htonl(0xfffffff8);

		rc = qrild_link_configure(&ip, &mask, &gateway);
		if (rc < 0) {
			fprintf(stderr, "Failed to configure rmnet interface\n");
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	state.sock = qrtr_open(0);
	if (state.sock < 0) {
		LOGE("Failed to open QRTR socket: %d", state.sock);
		return EXIT_FAILURE;
	}

	// Find all QRTR services
	qrild_qrtr_do_lookup(&state);

	while (state.state != QRILD_ACTION_EXIT) {
		rc = qrtr_poll(state.sock, 500);
		if (rc < 0)
			PLOGE_AND_EXIT("Failed to poll");

		if (rc)
			qrild_qrtr_recv(&state);
		else
			printf("Pending...\n");

		if (process_pending(&state) < 0)
			break;

		// // If we haven't receieved any packets and
		// // nothing will process the one we do have
		// // then just dump it
		// if (state.buf_invalidate && state.buf) {
		// 	printf("Dumping QMI message with ID %d\n", state.msg_id);
		// 	free(state.buf);
		// 	state.msg_id = 0;
		// 	state.buf_invalidate = false;
		// }

		// // Mark the current message to be invalidated on the next loop
		// if (state.msg_id)
		// 	state.buf_invalidate = true;
	}

	qrtr_close(state.sock);

	return 0;
}
