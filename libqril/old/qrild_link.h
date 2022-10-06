#ifndef __QRILD_LINK_H__
#define __QRILD_LINK_H__

#include <arpa/inet.h>

#ifdef __cplusplus
extern "C" {
#endif

int qrild_link_configure(struct in_addr *addr, struct in_addr *mask, struct in_addr *gateway);
/**
 * @brief convert a subnet mask to CIDR notation
 */
uint32_t mask_to_prefix(struct in_addr *mask);

#ifdef __cplusplus
}
#endif
#endif
