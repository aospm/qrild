#pragma once

#include "libqril.h"

namespace libqril {

class ILibQrilClient {
private:
    static void on_modem_state_change(ILibQrilClient *client, enum modem_state newstate);
    static bool on_qmi_indication(ILibQrilClient *client, struct qmi_header *buf, size_t len);
    static void on_service_new(ILibQrilClient *client, enum qmi_service service);
    static void on_service_goodbye(ILibQrilClient *client, enum qmi_service service);
public:
    virtual ~ILibQrilClient() = default;
    virtual void processIndication(struct qmi_header *buf, size_t len) = 0;
};

/**
 * @brief decode ICCID byte stream from modem
 */
std::string decode_iccid(uint8_t *bcd, uint8_t len);

/**
 * @brief decode EID byte stream from modem
 */
std::string decode_eid(uint8_t *eid, uint8_t len);

/**
 * @brief bytes to hex ASCII string, returns c++ string
 */
std::string bytes_to_hex(uint8_t *bytes, size_t len);

}
