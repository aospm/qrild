#ifndef __QRILD_QMI_H__
#define __QRILD_QMI_H__

__BEGIN_DECLS

// uint8_t *qmi_qmux_add_header(struct qmi_service_info *service,
//			 uint8_t *data, size_t *len);
//int qrild_qmi_ctl_allocate_cid(struct rild_state *state);
int qrild_qmi_powerup(struct rild_state *state);
int qrild_qmi_nas_register_indications(struct rild_state *state);
int qrild_qmi_uim_get_card_status(struct rild_state *state);
int qrild_qmi_uim_set_provisioning(struct rild_state *state);
int qrild_qmi_dpm_open_port(struct rild_state *state);
int qrild_qmi_wda_set_data_format(struct rild_state *state);
int qrild_qmi_wds_bind_subscription(struct rild_state *state);
int qrild_qmi_wds_bind_mux_data_port(struct rild_state *state);
int qrild_qmi_nas_get_signal_strength(struct rild_state *state);
int qrild_qmi_wds_start_network_interface(struct rild_state *state);
int qrild_qmi_wds_get_current_settings(struct rild_state *state);

const char* qmi_service_to_string(enum qmi_service service, bool short_name);

int qrild_qmi_process_indications(struct rild_state *state);

__END_DECLS
#endif
