#ifndef __QMI_TLV_H__
#define __QMI_TLV_H__

__BEGIN_DECLS

struct qmi_result {
	uint16_t result;
	uint16_t error;
};

struct qmi_tlv;

struct qmi_tlv *qmi_tlv_init(unsigned txn, unsigned msg_id, unsigned msg_type);
void *qmi_tlv_encode(struct qmi_tlv *tlv, size_t *len);
struct qmi_tlv *qmi_tlv_decode(void *buf, size_t len, unsigned *txn,
			       unsigned msg_type);
void qmi_tlv_free(struct qmi_tlv *tlv);
void qmi_tlv_dump(struct qmi_tlv *tlv);

__END_DECLS

#endif