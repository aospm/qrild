#ifndef __QRILD_QMI_H__
#define __QRILD_QMI_H__

#include "qmi_uim.h"
#include "qmi_nas.h"
#include "qmi_dms.h"

__BEGIN_DECLS

#define QMI_RESULT_SUCCESS 0
#define QMI_RESULT_FAILURE 1
#define QMI_ERR_NONE 0
#define QMI_ERR_INTERNAL 3
#define QMI_ERR_MALFORMED_MSG 1
#define QMI_ERR_QRILD 0xFFFF

// uint8_t *qmi_qmux_add_header(struct qmi_service_info *service,
//			 uint8_t *data, size_t *len);
//int qrild_qmi_ctl_allocate_cid(struct rild_state *state);
int qrild_qmi_dms_get_operating_mode(struct rild_state *state);
struct qmi_response_type_v01 qrild_qmi_dms_set_operating_mode(struct rild_state *state, uint8_t mode);
int qrild_qmi_powerup(struct rild_state *state);
int qrild_qmi_dms_get_revision(struct rild_state *state, char *revision, size_t buflen);
int qrild_qmi_dms_get_ids(struct rild_state *state, struct dms_ids *ids);
int qrild_qmi_nas_register_indications(struct rild_state *state);
int qrild_qmi_uim_get_card_status(struct rild_state *state);
int qrild_qmi_uim_get_slot_status(struct rild_state *state,
				  struct uim_slot_status_msg *slot_status);
int qrild_qmi_uim_set_provisioning(struct rild_state *state);
int qrild_qmi_dpm_open_port(struct rild_state *state);
int qrild_qmi_wda_set_data_format(struct rild_state *state);
int qrild_qmi_wds_bind_subscription(struct rild_state *state);
int qrild_qmi_wds_bind_mux_data_port(struct rild_state *state);
int qrild_qmi_nas_get_signal_strength(struct rild_state *state,
				      struct nas_signal_strength *strength, int16_t *lte_snr);
int qrild_qmi_nas_show_signal_strength(struct rild_state *state);
int qrild_qmi_wds_start_network_interface(struct rild_state *state);
int qrild_qmi_wds_get_current_settings(struct rild_state *state);

const char *qmi_service_to_string(enum qmi_service service, bool short_name);

int qrild_qmi_idle(struct rild_state *state);
int qrild_qmi_process_indications(struct rild_state *state);

__END_DECLS
#endif
