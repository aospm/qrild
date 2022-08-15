#ifndef __QRILD_QMI_H__
#define __QRILD_QMI_H__

#include <arpa/inet.h>

#include "qmi_uim.h"
#include "qmi_nas.h"
#include "qmi_dms.h"
#include "qmi_wds.h"

__BEGIN_DECLS

#define QMI_RESULT_SUCCESS 0
#define QMI_RESULT_FAILURE 1

struct wds_data_settings {
	int mtu;
	struct in_addr ip;
	struct in_addr brd;
	struct in_addr sub;
	uint8_t ip_family;
};

// uint8_t *qmi_qmux_add_header(struct qmi_service_info *service,
//			 uint8_t *data, size_t *len);
//int qrild_qmi_ctl_allocate_cid(struct rild_state *state);
int qrild_qmi_dms_get_operating_mode(struct rild_state *state);
struct qmi_response_type_v01 qrild_qmi_dms_set_operating_mode(struct rild_state *state,
							      uint8_t mode);
int qrild_qmi_powerup(struct rild_state *state);
int qrild_qmi_dms_get_revision(struct rild_state *state, char **revision);
int qrild_qmi_dms_get_ids(struct rild_state *state, struct dms_get_ids_resp_data *ids);
int qrild_qmi_nas_register_indications(struct rild_state *state);
int qrild_qmi_uim_get_card_status(struct rild_state *state,
				  struct uim_get_card_status_resp_data *data);
int qrild_qmi_uim_get_slot_status(struct rild_state *state,
				  struct uim_get_slot_status_resp_data *slot_status);
int qrild_qmi_uim_set_provisioning(struct rild_state *state, int slot, uint8_t *aid,
				   uint8_t aid_len);
int qrild_qmi_uim_icc_open_logical_channel(struct rild_state *state, int slot, const char *aid,
					   int fileControl,
					   struct uim_icc_open_logical_channel_resp_data *resp_data);
int qrild_qmi_dpm_open_port(struct rild_state *state);
int qrild_qmi_wda_set_data_format(struct rild_state *state);
int qrild_qmi_wds_bind_subscription(struct rild_state *state);
int qrild_qmi_wds_bind_mux_data_port(struct rild_state *state);
int qrild_qmi_nas_get_signal_strength(struct rild_state *state,
				      struct nas_get_signal_strength_resp_data *data);
int qrild_qmi_nas_show_signal_strength(struct nas_get_signal_strength_resp_data *data);
int qrild_qmi_nas_get_cell_loc_info(struct rild_state *state,
				    struct nas_get_cell_loc_info_data *data);
int qrild_qmi_nas_get_lte_cphy_ca_info(struct rild_state *state,
				       struct nas_get_lte_cphy_ca_info_resp_data *data);
int qrild_qmi_nas_get_system_prefs(struct rild_state *state,
				   struct nas_get_system_prefs_data *data);
int qrild_qmi_nas_network_register(struct rild_state *state, uint8_t action);
int qrild_qmi_nas_get_serving_system(struct rild_state *state,
				     struct nas_serving_system_resp_data *data);
int qrild_qmi_dms_uim_get_imsi(struct rild_state *state, struct dms_uim_get_imsi_data *data);
int qrild_qmi_dms_get_msisdn(struct rild_state *state, struct dms_get_msisdn_data *data);
int qrild_qmi_nas_get_operator_name(struct rild_state *state,
				    struct nas_get_operator_name_resp_data *data);
int qrild_qmi_nas_get_plmn_name(struct rild_state *state,
				struct nas_get_plmn_name_req_data *req_data,
				struct nas_get_plmn_name_resp_data *data);
int qrild_qmi_wds_start_network_interface(struct rild_state *state,
					  struct wds_start_network_interface_resp_data *data);
int qrild_qmi_wds_get_current_settings(struct rild_state *state,
				       struct wds_data_settings *settings);

const char *qmi_service_to_string(enum qmi_service service, bool short_name);
const char *qmi_error_string(uint16_t err);

int qrild_qmi_idle(struct rild_state *state);
int qrild_qmi_process_indications(struct rild_state *state);

__END_DECLS
#endif
