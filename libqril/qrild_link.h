#ifndef __QRILD_LINK_H__
#define __QRILD_LINK_H__

#include <arpa/inet.h>

__BEGIN_DECLS

int qrild_link_configure(struct in_addr *addr, struct in_addr *mask, struct in_addr *gateway);
/**
 * @brief convert a subnet mask to CIDR notation
 */
uint32_t mask_to_prefix(struct in_addr *mask);

__END_DECLS
#endif
