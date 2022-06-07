#ifndef __QRILD_QMI_H__
#define __QRILD_QMI_H__

// uint8_t *qmi_qmux_add_header(struct qmi_service_info *service,
//			 uint8_t *data, size_t *len);
//int qrild_qmi_ctl_allocate_cid(struct rild_state *state);
int qrild_qmi_powerup(struct rild_state *state);
int qrild_qmi_uim_get_card_status(struct rild_state *state);
const char* qmi_service_to_string(enum qmi_service service, bool short_name);

#endif
