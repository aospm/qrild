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
#include <pthread.h>

#include "libqrtr.h"
#include "logging.h"

#include "qrild.h"
#include "qrild_link.h"
#include "qrild_msg.h"
#include "qrild_qmi.h"
#include "util.h"

#ifdef ANDROID
#include "qrild_android_interface.h"
#endif

static int process_pending(struct rild_state *state) {
	int rc = QRILD_STATE_PENDING;

	switch (state->state) {
	case QRILD_ACTION_POWERUP:
		rc = qrild_qmi_powerup(state);
		break;
	case QRILD_ACTION_REGISTER_INDICATIONS:
		rc = qrild_qmi_nas_register_indications(state);
		// Will actually end up in state QRILD_ACTION_HALT
		//state->state = QRILD_ACTION_GET_RUNTIME_SETTINGS;
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
	case QRILD_ACTION_GET_SIGNAL_STRENGTH:
		rc = qrild_qmi_nas_show_signal_strength(state);
		break;
	case QRILD_ACTION_START_NET_IFACES:
		rc = qrild_qmi_wds_start_network_interface(state);
		break;
	case QRILD_ACTION_GET_RUNTIME_SETTINGS:
		rc = qrild_qmi_wds_get_current_settings(state);
		break;
	// case QRILD_ACTION_NETLINK:
	// 	rc = qrild_qmi_wds_get_current_settings(state);
	// 	state->state++;
	// 	break;
	case QRILD_ACTION_IDLE:
		rc = qrild_qmi_idle(state);
		break;
	default:
		fprintf(stderr, "[STATE] unknown state %d\n", state->state);
		return -1;
	}

	switch(rc) {
	case QRILD_STATE_PENDING:
		msleep(TIMEOUT_DEFAULT / 3);
		break;
	case QRILD_STATE_ERROR:
		fprintf(stderr, "[STATE] ERROR: failed in state %d\n", state->state);
		return rc;
	case QRILD_STATE_DONE:
		state->state++;
		LOGD("[STATE] In state state %d\n", state->state);
		break;
	default:
		fprintf(stderr, "[STATE] ERROR: Invalid status %d\n", rc);
		return rc;
	}

	return 0;
}

void *msg_loop(void *x) {
	struct rild_state *state = (struct rild_state *)x;
	int rc;

	state->sock = qrtr_open(0);
	if (state->sock < 0) {
		LOGE("Failed to open QRTR socket: %d", state->sock);
		return NULL;
	}

	// Find all QRTR services
	qrild_qrtr_do_lookup(state);

	while (!state->exit) {
		rc = qrild_qrtr_send_queued(state);
		if (rc < 0) {
			LOGE("Failed to send queued messages! %d\n", rc);
			state->exit = true;
			break;
		}
		rc = qrtr_poll(state->sock, 50);
		if (rc < 0 && errno == EINTR)
			continue;
		if (rc < 0)
			PLOGE_AND_EXIT("Failed to poll");

		if (rc > 0)
			qrild_qrtr_recv(state);
		qrild_qmi_process_indications(state);
	}

	printf("Quitting loop!\n");
	qrtr_close(state->sock);

	return NULL;
}

void main_loop(struct rild_state *state)
{
	while (state->state != QRILD_ACTION_EXIT && !state->exit) {
		if (process_pending(state) < 0)
			break;
	}
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
	pthread_mutexattr_t mattr;
	pthread_condattr_t cattr;
	pthread_t msg_thread;

	(void)argc;

	qlog_setup(progname, false);
	qlog_set_min_priority(LOG_DEBUG);

	memset(&state, 0, sizeof(state));

	state.sock = -1;
	list_init(&state.services);
	list_init(&state.pending_rx);
	list_init(&state.pending_tx);
	state.no_configure_inet = false;
	state.exit = false;

	pthread_mutexattr_init(&mattr);
	pthread_condattr_init(&cattr);

	pthread_mutex_init(&state.services_mutex, &mattr);
	pthread_mutex_init(&state.msg_mutex, &mattr);
	pthread_cond_init(&state.msg_change, &cattr);
	pthread_cond_init(&state.pending_indications, &cattr);
	pthread_mutex_init(&state.connection_status_mutex, &mattr);
	pthread_cond_init(&state.connection_status_change, &cattr);

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

	if (pthread_create(&msg_thread, NULL, msg_loop, &state)) {
		LOGE("Failed to create msg thread!\n");
		return 1;
	}
#ifdef ANDROID
	qrild_android_main(&state);
#else
	main_loop(&state);
#endif
	state.exit = true;
	pthread_join(msg_thread, NULL);

	

	return 0;
}
