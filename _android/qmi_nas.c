#include <errno.h>
#include <string.h>
#include "qmi_nas.h"

struct qmi_elem_info nas_signal_strength_ei[] = {
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.offset = offsetof(struct nas_signal_strength, strength),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.offset = offsetof(struct nas_signal_strength, interface),
	},
	{}
};

struct qmi_elem_info nas_ss_value_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_ss_value, val),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.offset = offsetof(struct nas_ss_value, interface),
	},
	{}
};

struct qmi_elem_info nas_network_reject_info_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_network_reject_info, enable_network_reject_indications),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_network_reject_info, suppress_system_info_indications),
	},
	{}
};

struct qmi_elem_info nas_lte_cphy_agg_scell_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_lte_cphy_agg_scell, pci),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_lte_cphy_agg_scell, rx_chan),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct nas_lte_cphy_agg_scell, dl_bandwidth),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_lte_cphy_agg_scell, lte_band),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct nas_lte_cphy_agg_scell, state),
	},
	{}
};

struct qmi_elem_info nas_serving_system_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_serving_system, registration_state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_serving_system, cs_attach_state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_serving_system, ps_attach_state),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_serving_system, selected_network),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_serving_system, radio_interfaces_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_serving_system, radio_interfaces),
	},
	{}
};

struct qmi_elem_info nas_current_plmn_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_current_plmn, mcc),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_current_plmn, mnc),
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.offset = offsetof(struct nas_current_plmn, description)
	},
	{}
};

struct qmi_elem_info nas_service_status_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_service_status, status),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_service_status, capability),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_service_status, hdr_status),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_service_status, hdr_hybrid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_service_status, forbidden),
	},
	{}
};

struct qmi_elem_info nas_service_provider_name_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_service_provider_name, display_condition),
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.offset = offsetof(struct nas_service_provider_name, name)
	},
	{}
};

struct qmi_elem_info nas_operator_plmn_ei[] = {
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 3,
		.array_type = STATIC_ARRAY,
		.elem_size = sizeof(char),
		.offset = offsetof(struct nas_operator_plmn, mcc),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 3,
		.array_type = STATIC_ARRAY,
		.elem_size = sizeof(char),
		.offset = offsetof(struct nas_operator_plmn, mnc),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_operator_plmn, lac1),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_operator_plmn, lac2),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn, name_record_indicator),
	},
	{}
};

struct qmi_elem_info nas_operator_plmn_arr_operators_ei[] = {
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 3,
		.array_type = STATIC_ARRAY,
		.elem_size = sizeof(char),
		.offset = offsetof(struct nas_operator_plmn_arr_operators, mcc),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 3,
		.array_type = STATIC_ARRAY,
		.elem_size = sizeof(char),
		.offset = offsetof(struct nas_operator_plmn_arr_operators, mnc),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_operator_plmn_arr_operators, lac1),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_operator_plmn_arr_operators, lac2),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_arr_operators, name_record_indicator),
	},
	{}
};

struct qmi_elem_info nas_operator_plmn_arr_ei[] = {
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_operator_plmn_arr, operators_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct nas_operator_plmn_arr),
		.offset = offsetof(struct nas_operator_plmn_arr, operators),
		.ei_array = &nas_operator_plmn_arr_operators_ei,
	},
	{}
};

struct qmi_elem_info nas_operator_plmn_name_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name, name_encoding),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name, short_country_initials),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name, long_name_spare_bits),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name, short_name_spare_bits),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name, long_name_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name, long_name),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name, short_name_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name, short_name),
	},
	{}
};

struct qmi_elem_info nas_operator_plmn_name_arr_operators_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name_arr_operators, name_encoding),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name_arr_operators, short_country_initials),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name_arr_operators, long_name_spare_bits),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name_arr_operators, short_name_spare_bits),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name_arr_operators, long_name_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name_arr_operators, long_name),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name_arr_operators, short_name_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name_arr_operators, short_name),
	},
	{}
};

struct qmi_elem_info nas_operator_plmn_name_arr_ei[] = {
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_operator_plmn_name_arr, operators_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct nas_operator_plmn_name_arr),
		.offset = offsetof(struct nas_operator_plmn_name_arr, operators),
		.ei_array = &nas_operator_plmn_name_arr_operators_ei,
	},
	{}
};

struct qmi_elem_info nas_network_selection_pref_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_network_selection_pref, mode),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_network_selection_pref, mcc),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_network_selection_pref, mnc),
	},
	{}
};

struct qmi_elem_info nas_geran_info_cells_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct nas_geran_info_cells, cell_id),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 3,
		.array_type = STATIC_ARRAY,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_geran_info_cells, plmn),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_geran_info_cells, lac),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_geran_info_cells, abs_channel_num),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_geran_info_cells, bsic),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_geran_info_cells, rx_level),
	},
	{}
};

struct qmi_elem_info nas_geran_info_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct nas_geran_info, cell_id),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 3,
		.array_type = STATIC_ARRAY,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_geran_info, plmn),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_geran_info, lac),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_geran_info, abs_channel_num),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_geran_info, bsic),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct nas_geran_info, timing_advance),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_geran_info, rx_level),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_geran_info, cells_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct nas_geran_info),
		.offset = offsetof(struct nas_geran_info, cells),
		.ei_array = &nas_geran_info_cells_ei,
	},
	{}
};

struct qmi_elem_info nas_umts_info_cells_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_umts_info_cells, abs_channel_num),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_umts_info_cells, psc),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_umts_info_cells, rscp),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_umts_info_cells, ecio),
	},
	{}
};

struct qmi_elem_info nas_umts_info_gerans_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_umts_info_gerans, abs_channel_num),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_umts_info_gerans, network_color_code),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_umts_info_gerans, base_station_color_code),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.offset = offsetof(struct nas_umts_info_gerans, rssi),
	},
	{}
};

struct qmi_elem_info nas_umts_info_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_umts_info, cell_id),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 3,
		.array_type = STATIC_ARRAY,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_umts_info, plmn),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_umts_info, lac),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_umts_info, abs_channel_num),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_umts_info, psc),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_umts_info, rscp),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_umts_info, ecio),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_umts_info, cells_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct nas_umts_info),
		.offset = offsetof(struct nas_umts_info, cells),
		.ei_array = &nas_umts_info_cells_ei,
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_umts_info, gerans_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct nas_umts_info),
		.offset = offsetof(struct nas_umts_info, gerans),
		.ei_array = &nas_umts_info_gerans_ei,
	},
	{}
};

struct qmi_elem_info nas_cdma_info_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_cdma_info, system_id),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_cdma_info, network_id),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_cdma_info, bsid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_cdma_info, reference_pn),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct nas_cdma_info, latitude),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct nas_cdma_info, longitude),
	},
	{}
};

struct qmi_elem_info nas_intrafreq_lte_info_cells_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_intrafreq_lte_info_cells, pci),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_intrafreq_lte_info_cells, rsrq),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_intrafreq_lte_info_cells, rsrp),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_intrafreq_lte_info_cells, rssi),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_intrafreq_lte_info_cells, rx_level),
	},
	{}
};

struct qmi_elem_info nas_intrafreq_lte_info_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, ue_idle),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 3,
		.array_type = STATIC_ARRAY,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, plmn),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, tac),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, global_cell_id),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, abs_channel_num),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, serving_cell_id),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, crp),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, s_non_intra_search_threshold),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, serving_cell_low_threshold),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, s_intra_search_threshold),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_intrafreq_lte_info, cells_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 255,
		.array_type = VAR_LEN_ARRAY,
		.elem_size = sizeof(struct nas_intrafreq_lte_info),
		.offset = offsetof(struct nas_intrafreq_lte_info, cells),
		.ei_array = &nas_intrafreq_lte_info_cells_ei,
	},
	{}
};

struct qmi_elem_info nas_plmn_id_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_plmn_id, mcc),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.offset = offsetof(struct nas_plmn_id, mnc),
	},
	{}
};

struct qmi_elem_info nas_eons_plmn_name_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, sp_name_encoding),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, sp_name_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, sp_name),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, short_name_encoding),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, short_name_country_initials),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, short_name_spare_bits),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, short_name_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, short_name),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, long_name_encoding),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, long_name_country_initials),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, long_name_spare_bits),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, long_name_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_eons_plmn_name, long_name),
	},
	{}
};

struct qmi_elem_info nas_ss_cdma_ei[] = {
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.offset = offsetof(struct nas_ss_cdma, rssi),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_ss_cdma, ecio),
	},
	{}
};

struct qmi_elem_info nas_ss_hdr_ei[] = {
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.offset = offsetof(struct nas_ss_hdr, rssi),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_ss_hdr, ecio),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.offset = offsetof(struct nas_ss_hdr, sinr),
	},
	{
		.data_type = QMI_SIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int32_t),
		.offset = offsetof(struct nas_ss_hdr, io),
	},
	{}
};

struct qmi_elem_info nas_ss_wcdma_ei[] = {
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.offset = offsetof(struct nas_ss_wcdma, rssi),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_ss_wcdma, ecio),
	},
	{}
};

struct qmi_elem_info nas_ss_lte_ei[] = {
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.offset = offsetof(struct nas_ss_lte, rssi),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.offset = offsetof(struct nas_ss_lte, rsrq),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_ss_lte, rsrp),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.offset = offsetof(struct nas_ss_lte, snr),
	},
	{}
};

struct qmi_elem_info nas_ss_tdma_ext_ei[] = {
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.offset = offsetof(struct nas_ss_tdma_ext, rssi),
	},
	{
		.data_type = QMI_SIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int32_t),
		.offset = offsetof(struct nas_ss_tdma_ext, rscp),
	},
	{
		.data_type = QMI_SIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int32_t),
		.offset = offsetof(struct nas_ss_tdma_ext, ecio),
	},
	{
		.data_type = QMI_SIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int32_t),
		.offset = offsetof(struct nas_ss_tdma_ext, sinr),
	},
	{}
};

struct qmi_elem_info nas_register_indications_req_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 16,
		.offset = offsetof(struct nas_register_indications_req, system_selection_preference),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 18,
		.offset = offsetof(struct nas_register_indications_req, ddtm_events),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 19,
		.offset = offsetof(struct nas_register_indications_req, serving_system_events),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 20,
		.offset = offsetof(struct nas_register_indications_req, dual_standby_preference),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 21,
		.offset = offsetof(struct nas_register_indications_req, subscription_info),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 23,
		.offset = offsetof(struct nas_register_indications_req, network_time),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 24,
		.offset = offsetof(struct nas_register_indications_req, system_info),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 25,
		.offset = offsetof(struct nas_register_indications_req, signal_info),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 26,
		.offset = offsetof(struct nas_register_indications_req, error_rate),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 27,
		.offset = offsetof(struct nas_register_indications_req, hdr_new_uati_assigned),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 28,
		.offset = offsetof(struct nas_register_indications_req, hdr_session_closed),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 29,
		.offset = offsetof(struct nas_register_indications_req, managed_roaming),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 30,
		.offset = offsetof(struct nas_register_indications_req, current_plmn_name),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 31,
		.offset = offsetof(struct nas_register_indications_req, embms_status),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 32,
		.offset = offsetof(struct nas_register_indications_req, rf_band_information),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_network_reject_info),
		.tlv_type = 33,
		.offset = offsetof(struct nas_register_indications_req, network_reject_information),
		.ei_array = nas_network_reject_info_ei,
	},
	{}
};

struct qmi_elem_info nas_get_signal_strength_req_ei[] = {
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_signal_strength_req, mask),
	},
	{}
};

struct qmi_elem_info nas_get_signal_strength_resp_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 1,
		.offset = offsetof(struct nas_get_signal_strength_resp, strength_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_signal_strength),
		.tlv_type = 1,
		.offset = offsetof(struct nas_get_signal_strength_resp, strength),
		.ei_array = nas_signal_strength_ei,
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct nas_get_signal_strength_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_signal_strength_resp, strength_list_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_signal_strength_resp, strength_list_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 16,
		.elem_size = sizeof(struct nas_signal_strength),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_signal_strength_resp, strength_list),
		.ei_array = nas_signal_strength_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_signal_strength_resp, rssi_list_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_signal_strength_resp, rssi_list_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_value),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_signal_strength_resp, rssi_list),
		.ei_array = nas_ss_value_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_signal_strength_resp, ecio_list_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_signal_strength_resp, ecio_list_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_value),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_signal_strength_resp, ecio_list),
		.ei_array = nas_ss_value_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 19,
		.offset = offsetof(struct nas_get_signal_strength_resp, io_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 19,
		.offset = offsetof(struct nas_get_signal_strength_resp, io),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 20,
		.offset = offsetof(struct nas_get_signal_strength_resp, sinr_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 20,
		.offset = offsetof(struct nas_get_signal_strength_resp, sinr),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 21,
		.offset = offsetof(struct nas_get_signal_strength_resp, err_rate_list_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 21,
		.offset = offsetof(struct nas_get_signal_strength_resp, err_rate_list_len),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 16,
		.elem_size = sizeof(struct nas_ss_value),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 21,
		.offset = offsetof(struct nas_get_signal_strength_resp, err_rate_list),
		.ei_array = nas_ss_value_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 22,
		.offset = offsetof(struct nas_get_signal_strength_resp, rsrq_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_value),
		.tlv_type = 22,
		.offset = offsetof(struct nas_get_signal_strength_resp, rsrq),
		.ei_array = nas_ss_value_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 23,
		.offset = offsetof(struct nas_get_signal_strength_resp, lte_snr_valid),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.tlv_type = 23,
		.offset = offsetof(struct nas_get_signal_strength_resp, lte_snr),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 24,
		.offset = offsetof(struct nas_get_signal_strength_resp, lte_rsrp_valid),
	},
	{
		.data_type = QMI_SIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int16_t),
		.tlv_type = 24,
		.offset = offsetof(struct nas_get_signal_strength_resp, lte_rsrp),
	},
	{}
};

struct qmi_elem_info nas_initiate_network_register_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 1,
		.offset = offsetof(struct nas_initiate_network_register, action),
	},
	{}
};

struct qmi_elem_info nas_serving_system_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct nas_serving_system_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 1,
		.offset = offsetof(struct nas_serving_system_resp, system_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_serving_system),
		.tlv_type = 1,
		.offset = offsetof(struct nas_serving_system_resp, system),
		.ei_array = nas_serving_system_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct nas_serving_system_resp, data_service_cap_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct nas_serving_system_resp, data_service_cap_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 16,
		.elem_size = sizeof(uint8_t),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 17,
		.offset = offsetof(struct nas_serving_system_resp, data_service_cap),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct nas_serving_system_resp, plmn_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_current_plmn),
		.tlv_type = 18,
		.offset = offsetof(struct nas_serving_system_resp, plmn),
		.ei_array = nas_current_plmn_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 29,
		.offset = offsetof(struct nas_serving_system_resp, lac_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 29,
		.offset = offsetof(struct nas_serving_system_resp, lac),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 30,
		.offset = offsetof(struct nas_serving_system_resp, cid_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 30,
		.offset = offsetof(struct nas_serving_system_resp, cid),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 34,
		.offset = offsetof(struct nas_serving_system_resp, status_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_service_status),
		.tlv_type = 34,
		.offset = offsetof(struct nas_serving_system_resp, status),
		.ei_array = nas_service_status_ei,
	},
	{}
};

struct qmi_elem_info nas_serving_system_ind_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 1,
		.offset = offsetof(struct nas_serving_system_ind, system_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_serving_system),
		.tlv_type = 1,
		.offset = offsetof(struct nas_serving_system_ind, system),
		.ei_array = nas_serving_system_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct nas_serving_system_ind, data_service_cap_valid),
	},
	{
		.data_type = QMI_DATA_LEN,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 17,
		.offset = offsetof(struct nas_serving_system_ind, data_service_cap_len),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 16,
		.elem_size = sizeof(uint8_t),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 17,
		.offset = offsetof(struct nas_serving_system_ind, data_service_cap),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct nas_serving_system_ind, plmn_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_current_plmn),
		.tlv_type = 18,
		.offset = offsetof(struct nas_serving_system_ind, plmn),
		.ei_array = nas_current_plmn_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 29,
		.offset = offsetof(struct nas_serving_system_ind, lac_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 29,
		.offset = offsetof(struct nas_serving_system_ind, lac),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 30,
		.offset = offsetof(struct nas_serving_system_ind, cid_valid),
	},
	{
		.data_type = QMI_UNSIGNED_2_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint16_t),
		.tlv_type = 30,
		.offset = offsetof(struct nas_serving_system_ind, cid),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 34,
		.offset = offsetof(struct nas_serving_system_ind, status_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_service_status),
		.tlv_type = 34,
		.offset = offsetof(struct nas_serving_system_ind, status),
		.ei_array = nas_service_status_ei,
	},
	{}
};

struct qmi_elem_info nas_set_operating_mode_req_ei[] = {
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 1,
		.offset = offsetof(struct nas_set_operating_mode_req, mode),
	},
	{}
};

struct qmi_elem_info nas_set_operating_mode_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct nas_set_operating_mode_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{}
};

struct qmi_elem_info nas_set_system_prefs_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 22,
		.offset = offsetof(struct nas_set_system_prefs, network_selection_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_network_selection_pref),
		.tlv_type = 22,
		.offset = offsetof(struct nas_set_system_prefs, network_selection),
		.ei_array = nas_network_selection_pref_ei,
	},
	{}
};

struct qmi_elem_info nas_get_system_prefs_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct nas_get_system_prefs, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 22,
		.offset = offsetof(struct nas_get_system_prefs, network_selection_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 22,
		.offset = offsetof(struct nas_get_system_prefs, network_selection),
	},
	{}
};

struct qmi_elem_info nas_get_operator_name_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct nas_get_operator_name_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_operator_name_resp, provider_name_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_service_provider_name),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_operator_name_resp, provider_name),
		.ei_array = nas_service_provider_name_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_operator_name_resp, operator_plmns_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_operator_plmn_arr),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_operator_name_resp, operator_plmns),
		.ei_array = nas_operator_plmn_arr_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_operator_name_resp, operator_plmn_names_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_operator_plmn_name_arr),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_operator_name_resp, operator_plmn_names),
		.ei_array = nas_operator_plmn_name_arr_ei,
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 19,
		.offset = offsetof(struct nas_get_operator_name_resp, operator_string_name)
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 20,
		.offset = offsetof(struct nas_get_operator_name_resp, nitz_info_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_operator_plmn_name),
		.tlv_type = 20,
		.offset = offsetof(struct nas_get_operator_name_resp, nitz_info),
		.ei_array = nas_operator_plmn_name_ei,
	},
	{}
};

struct qmi_elem_info nas_operator_name_ind_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct nas_operator_name_ind, provider_name_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_service_provider_name),
		.tlv_type = 16,
		.offset = offsetof(struct nas_operator_name_ind, provider_name),
		.ei_array = nas_service_provider_name_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct nas_operator_name_ind, operator_plmns_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_operator_plmn_arr),
		.tlv_type = 17,
		.offset = offsetof(struct nas_operator_name_ind, operator_plmns),
		.ei_array = nas_operator_plmn_arr_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct nas_operator_name_ind, operator_plmn_names_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_operator_plmn_name_arr),
		.tlv_type = 18,
		.offset = offsetof(struct nas_operator_name_ind, operator_plmn_names),
		.ei_array = nas_operator_plmn_name_arr_ei,
	},
	{
		.data_type = QMI_STRING,
		.elem_len = 256,
		.elem_size = sizeof(char),
		.array_type = VAR_LEN_ARRAY,
		.tlv_type = 19,
		.offset = offsetof(struct nas_operator_name_ind, operator_string_name)
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 20,
		.offset = offsetof(struct nas_operator_name_ind, nitz_info_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_operator_plmn_name),
		.tlv_type = 20,
		.offset = offsetof(struct nas_operator_name_ind, nitz_info),
		.ei_array = nas_operator_plmn_name_ei,
	},
	{}
};

struct qmi_elem_info nas_get_cell_loc_info_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct nas_get_cell_loc_info, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_cell_loc_info, geran_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_geran_info),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_cell_loc_info, geran),
		.ei_array = nas_geran_info_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_cell_loc_info, umts_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_umts_info),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_cell_loc_info, umts),
		.ei_array = nas_umts_info_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_cell_loc_info, cdma_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_cdma_info),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_cell_loc_info, cdma),
		.ei_array = nas_cdma_info_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 19,
		.offset = offsetof(struct nas_get_cell_loc_info, intra_lte_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_intrafreq_lte_info),
		.tlv_type = 19,
		.offset = offsetof(struct nas_get_cell_loc_info, intra_lte),
		.ei_array = nas_intrafreq_lte_info_ei,
	},
	{}
};

struct qmi_elem_info nas_get_plmn_name_req_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_plmn_id),
		.tlv_type = 1,
		.offset = offsetof(struct nas_get_plmn_name_req, plmn),
		.ei_array = nas_plmn_id_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 22,
		.offset = offsetof(struct nas_get_plmn_name_req, send_all_info_valid),
	},
	{
		.data_type = QMI_UNSIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint8_t),
		.tlv_type = 22,
		.offset = offsetof(struct nas_get_plmn_name_req, send_all_info),
	},
	{}
};

struct qmi_elem_info nas_get_plmn_name_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct nas_get_plmn_name_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_plmn_name_resp, plmn_name_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_eons_plmn_name),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_plmn_name_resp, plmn_name),
		.ei_array = nas_eons_plmn_name_ei,
	},
	{}
};

struct qmi_elem_info nas_get_signal_info_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct nas_get_signal_info, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_signal_info, cdma_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_cdma),
		.tlv_type = 16,
		.offset = offsetof(struct nas_get_signal_info, cdma),
		.ei_array = nas_ss_cdma_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_signal_info, hdr_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_hdr),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_signal_info, hdr),
		.ei_array = nas_ss_hdr_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_signal_info, gsm_valid),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_signal_info, gsm),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 19,
		.offset = offsetof(struct nas_get_signal_info, wcdma_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_wcdma),
		.tlv_type = 19,
		.offset = offsetof(struct nas_get_signal_info, wcdma),
		.ei_array = nas_ss_wcdma_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 20,
		.offset = offsetof(struct nas_get_signal_info, lte_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_lte),
		.tlv_type = 20,
		.offset = offsetof(struct nas_get_signal_info, lte),
		.ei_array = nas_ss_lte_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 21,
		.offset = offsetof(struct nas_get_signal_info, tdma_valid),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.tlv_type = 21,
		.offset = offsetof(struct nas_get_signal_info, tdma),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 22,
		.offset = offsetof(struct nas_get_signal_info, tdma_ext_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_tdma_ext),
		.tlv_type = 22,
		.offset = offsetof(struct nas_get_signal_info, tdma_ext),
		.ei_array = nas_ss_tdma_ext_ei,
	},
	{}
};

struct qmi_elem_info nas_signal_info_ind_ei[] = {
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 16,
		.offset = offsetof(struct nas_signal_info_ind, cdma_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_cdma),
		.tlv_type = 16,
		.offset = offsetof(struct nas_signal_info_ind, cdma),
		.ei_array = nas_ss_cdma_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct nas_signal_info_ind, hdr_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_hdr),
		.tlv_type = 17,
		.offset = offsetof(struct nas_signal_info_ind, hdr),
		.ei_array = nas_ss_hdr_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct nas_signal_info_ind, gsm_valid),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.tlv_type = 18,
		.offset = offsetof(struct nas_signal_info_ind, gsm),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 19,
		.offset = offsetof(struct nas_signal_info_ind, wcdma_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_wcdma),
		.tlv_type = 19,
		.offset = offsetof(struct nas_signal_info_ind, wcdma),
		.ei_array = nas_ss_wcdma_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 20,
		.offset = offsetof(struct nas_signal_info_ind, lte_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_ss_lte),
		.tlv_type = 20,
		.offset = offsetof(struct nas_signal_info_ind, lte),
		.ei_array = nas_ss_lte_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 21,
		.offset = offsetof(struct nas_signal_info_ind, tdma_valid),
	},
	{
		.data_type = QMI_SIGNED_1_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(int8_t),
		.tlv_type = 21,
		.offset = offsetof(struct nas_signal_info_ind, tdma),
	},
	{}
};

struct qmi_elem_info nas_get_lte_cphy_ca_info_resp_ei[] = {
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct qmi_response_type_v01),
		.tlv_type = 2,
		.offset = offsetof(struct nas_get_lte_cphy_ca_info_resp, res),
		.ei_array = qmi_response_type_v01_ei,
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_lte_cphy_ca_info_resp, dl_bandwidth_valid),
	},
	{
		.data_type = QMI_UNSIGNED_4_BYTE,
		.elem_len = 1,
		.elem_size = sizeof(uint32_t),
		.tlv_type = 17,
		.offset = offsetof(struct nas_get_lte_cphy_ca_info_resp, dl_bandwidth),
	},
	{
		.data_type = QMI_OPT_FLAG,
		.elem_len = 1,
		.elem_size = sizeof(bool),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_lte_cphy_ca_info_resp, phy_scell_info_valid),
	},
	{
		.data_type = QMI_STRUCT,
		.elem_len = 1,
		.elem_size = sizeof(struct nas_lte_cphy_agg_scell),
		.tlv_type = 18,
		.offset = offsetof(struct nas_get_lte_cphy_ca_info_resp, phy_scell_info),
		.ei_array = nas_lte_cphy_agg_scell_ei,
	},
	{}
};

