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

#include <telephony/ril.h>

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

#include "libqrtr.h"
#include "logging.h"

#include "qrild.h"
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

int main(int argc, char **argv) {
	struct rild_state state;
	int len, rc;
	const char *progname = basename(argv[0]);

	(void)argc;

	qlog_setup(progname, false);
	qlog_set_min_priority(LOG_DEBUG);

	memset(&state, 0, sizeof(state));

	state.sock = -1;
	state.txn = 1;
	list_init(&state.services);
	list_init(&state.resp_queue);

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

		if (!rc) // timeout
			continue;

		qrild_qrtr_recv(&state);

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