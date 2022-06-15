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
 * 
 * qrild_link.c: rmnet link configuration
 */

#include <arpa/inet.h>
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
#include <sys/ioctl.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>

#include <linux/rtnetlink.h>
#include <linux/netlink.h>
#include <linux/if_addr.h>
#define __USE_MISC
#include <net/if.h>
#include <net/if_arp.h>

#include "logging.h"

#include "qrild.h"
#include "util.h"

#define RMNET_DATA_TYPE "rmnet"

typedef struct bytearray nlmessage;

#define nl_new(extra) (nlmessage*)ba_init(extra);
#define nl_header(msg) ((struct nlmsghdr*)(msg->data))
#define nl_hdr_ifinfo(msg) ((struct ifinfomsg*)(((char*)(msg->data)) + NLMSG_HDRLEN))
#define nl_hdr_ifaddr(msg) ((struct ifaddrmsg*)(((char*)(msg->data)) + NLMSG_HDRLEN))
#define nl_hdr_rt(msg) ((struct rtmsg*)(((char*)(msg->data)) + NLMSG_HDRLEN))
#define nl_next_attr(msg) NLMSG_ALIGN(msg->len)
#define nl_tail(msg) ((void *)(((char*)(msg->data)) + NLMSG_ALIGN(nl_header(msg)->nlmsg_len)))
#define nl_free(nlm) ba_free(nlm)

static int sock_fd;
static int sndbuf = 32768;

/**
 * Get the CIDR / notation for a subnet mask
 */
static uint32_t mask_to_prefix(struct in_addr *mask) {
	uint32_t prefix = 0;
	uint32_t n = ntohl(mask->s_addr);

	for(prefix = 0; n & (1 << 31);) {
		prefix++;
		n = n << 1;
		if (prefix > 31)
			break;
	}

	return prefix;
}

static void nl_append_attr(nlmessage *msg, uint16_t type, const void *buf, size_t len) {
	struct rtattr *rta;
	size_t attr_len;

	attr_len = RTA_LENGTH(len);
	printf("Resizing from %zu to %zu\n", msg->len, NLMSG_ALIGN(msg->len) + RTA_ALIGN(attr_len));
	printf("Adding attr type %u\n", type);
	print_hex_dump("ATTR", buf, len);
	ba_set_size(msg, NLMSG_ALIGN(msg->len + attr_len));
	rta = nl_tail(msg);

	rta->rta_len = attr_len;
	rta->rta_type = type;

	if (buf) {
		memcpy(RTA_DATA(rta), buf, len);
	}

	nl_header(msg)->nlmsg_len = NLMSG_ALIGN(nl_header(msg)->nlmsg_len) + RTA_ALIGN(attr_len);
}

static void nl_append_str(nlmessage *msg, uint16_t type, const char* str) {
	size_t len = strlen(str);
	char* allocd = malloc(len + 1);
	strncpy(allocd, str, len);
	allocd[len] = '\0';

	nl_append_attr(msg, type, str, len + 1);
}

#define nl_append_nested(msg, type) nl_append_attr(msg, type, NULL, 0);
#define nl_append_val(msg, type, val) nl_append_attr(msg, type, &val, sizeof(val))

static nlmessage *nl_message_new(uint16_t type, uint16_t flags, size_t extra) {
	nlmessage *msg = nl_new(sizeof(struct nlmsghdr) + extra);
	struct nlmsghdr *hdr = nl_header(msg);

	hdr->nlmsg_len = msg->len;
	hdr->nlmsg_type = type;
	hdr->nlmsg_flags = NLM_F_REQUEST | flags;

	return msg;
}

static int qrild_link_open() {
	struct sockaddr_nl src_addr;
	int recvbuf = 1024 * 1024;

	sock_fd = socket(AF_NETLINK, SOCK_RAW | SOCK_CLOEXEC, NETLINK_ROUTE);
	if (sock_fd < 0)
		return QRILD_STATE_ERROR;

	if (setsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF,
		       &sndbuf, sizeof(sndbuf)) < 0) {
		PLOGE_AND_EXIT("SO_SNDBUF\n");
	}

	if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF,
		       &recvbuf, sizeof(recvbuf)) < 0) {
		PLOGE_AND_EXIT("SO_RCVBUF\n");
	}

	printf("Got sndbuf: %d and recvbuf: %d\n", sndbuf, recvbuf);

	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid(); /* self pid */

	if (bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr)) < 0) {
		PLOGE_AND_EXIT("Can't bind()\n");
	}

	return 0;
}

static int qrild_link_send(nlmessage *msg) {
	struct sockaddr_nl dest_addr;
	struct msghdr skmsg;
	struct nlmsghdr *hdr;
	struct iovec iov, resp;
	
	uint8_t *buf;
	size_t recv_len;

	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.nl_family = AF_NETLINK;

	printf("msg len: %zu, hdr_len: %u\n", msg->len, nl_header(msg)->nlmsg_len);
	if (msg->len != nl_header(msg)->nlmsg_len) {
		fprintf(stderr, "message length mismatch!\n");
		return -1;
	}
	print_hex_dump("LINK", msg->data, msg->len);
	iov.iov_base = (void *)msg->data;
	iov.iov_len = nl_header(msg)->nlmsg_len;
	memset(&skmsg, 0, sizeof(skmsg));
	skmsg.msg_name = (void *)&dest_addr;
	skmsg.msg_namelen = sizeof(dest_addr);
	skmsg.msg_iov = &iov;
	skmsg.msg_iovlen = 1;

	printf("Sending message to kernel (fd: %d)\n", sock_fd);
	if (sendmsg(sock_fd, &skmsg, 0) < 0) {
		PLOGE_AND_EXIT("Can't sendmsg()\n");
	}

	buf = malloc(sndbuf);
	resp.iov_base = buf;
	resp.iov_len = sndbuf;

	skmsg.msg_iov = &resp;
	skmsg.msg_iovlen = 1;

	/* Read message from kernel */
	// recv_len = recvmsg(sock_fd, &skmsg, 0);
	// print_hex_dump("RESP: First 8 bytes", resp.iov_base, recv_len);
	// hdr = (struct nlmsghdr*)resp.iov_base;
	// printf("Reply len: %u, type: %u, flags: %u, seq: %u, pid: %u\n", hdr->nlmsg_len, hdr->nlmsg_type, hdr->nlmsg_flags, hdr->nlmsg_seq, hdr->nlmsg_pid);
	// close(sock_fd);

	return QRILD_STATE_DONE;
}

/**
 * @brief: create an rmnet link
 *
 * @ifname: name of the new link (e.g rmnet_data0).
 * @base_ifindex: index of the iface to link to
 * @mux_id: rmnet mux to use
 */
int qrild_link_add_link(char* ifname, uint32_t base_ifindex, uint16_t mux_id) {
	nlmessage *msg;
	struct rtattr *link, *data;
	struct ifinfomsg *ifi;
	struct ifla_rmnet_flags  flags;
	uint32_t link_off, mux_off;

	//printf("Before create msg\n");
	msg = nl_message_new(RTM_NEWLINK, NLM_F_CREATE | NLM_F_EXCL, sizeof(struct ifinfomsg));
	//printf("before append base_ifindex, msg size: %zu\n", msg->len);
	nl_append_val(msg, IFLA_LINK, base_ifindex);
	//printf("before append ifname (%s)\n", ifname);
	nl_append_str(msg, IFLA_IFNAME, ifname);

	link = nl_tail(msg);
	//printf("before append IFLA_LINKINFO\n");
	nl_append_nested(msg, IFLA_LINKINFO);
	//printf("before append RMNET_DATA_TYPE\n");
	// This string ISN'T null terminated, i guess it's not really a "string"
	nl_append_attr(msg, IFLA_INFO_KIND, RMNET_DATA_TYPE, strlen(RMNET_DATA_TYPE));

	data = nl_tail(msg);
	//printf("before append IFLA_INFO_DATA\n");
	nl_append_nested(msg, IFLA_INFO_DATA);
	//printf("before append mux_id\n");
	nl_append_val(msg, IFLA_RMNET_MUX_ID, mux_id);

	flags.flags = RMNET_FLAGS_INGRESS_DEAGGREGATION |
		      RMNET_FLAGS_INGRESS_MAP_CKSUMV4 |
		      RMNET_FLAGS_EGRESS_MAP_CKSUMV4;
	flags.mask = flags.flags;
	//printf("before append IFLA_RMNET_FLAGS\n");
	nl_append_attr(msg, IFLA_RMNET_FLAGS, &flags, sizeof(struct ifla_rmnet_flags));
	// Inner nested data
	data->rta_len = (uint16_t)((char*)nl_tail(msg) - (char*)data);
	printf("data len: %u\n", data->rta_len);
	// Outer nested data
	link->rta_len = (uint16_t)((char*)nl_tail(msg) - (char*)link);
	printf("link len: %u\n", link->rta_len);

	ifi = nl_hdr_ifinfo(msg);
	//ifi->ifi_index = base_ifindex;
	ifi->ifi_family = PF_UNSPEC;
	ifi->ifi_type = 0;
	ifi->ifi_flags = 0;
	ifi->ifi_change = 0x0;

	qrild_link_send(msg);
	nl_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_link_set_addr(char* dev_ifname, struct in_addr *addr, struct in_addr *mask) {
	nlmessage *msg;
	struct ifaddrmsg *ifa;
	uint32_t dev_ifindex;

	msg = nl_message_new(RTM_NEWADDR, NLM_F_CREATE | NLM_F_EXCL, sizeof(struct ifaddrmsg));
	// Local address we're setting
	nl_append_val(msg, IFA_LOCAL, addr->s_addr);
	nl_append_val(msg, IFA_ADDRESS, addr->s_addr);

	dev_ifindex = if_nametoindex(dev_ifname);
	if (!dev_ifindex) {
		fprintf(stderr, "%s: Couldn't find dev '%s'\n", __func__, dev_ifname);
		nl_free(msg);
		return QRILD_STATE_ERROR;
	}

	ifa = nl_hdr_ifaddr(msg);
	// Index of device we're setting the address on
	ifa->ifa_index = dev_ifindex;
	// hardcode IPv4 for now
	ifa->ifa_family = AF_INET;
	// IPA should always give us a /29
	ifa->ifa_prefixlen = mask_to_prefix(mask);
	printf("Got subnet: %u\n", ifa->ifa_prefixlen);

	qrild_link_send(msg);
	nl_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_link_add_default_route(char* dev_ifname, struct in_addr *gateway) {
	nlmessage *msg;
	struct rtmsg *rt;
	uint32_t dev_ifindex;

	msg = nl_message_new(RTM_NEWROUTE, NLM_F_CREATE | NLM_F_EXCL, sizeof(struct rtmsg));

	rt = nl_hdr_rt(msg);
	rt->rtm_family = AF_INET; // good
	rt->rtm_table = RT_TABLE_MAIN; // good
	rt->rtm_protocol = RTPROT_BOOT; // good
	rt->rtm_scope = RT_SCOPE_UNIVERSE; // was RT_SCOPE_LINK which is wrong (not what iproute2 does anyway)
	rt->rtm_type = RTN_UNICAST; // good

	nl_append_val(msg, RTA_GATEWAY, gateway->s_addr);

	dev_ifindex = if_nametoindex(dev_ifname);
	if (!dev_ifindex) {
		fprintf(stderr, "%s: Couldn't find dev '%s'\n", __func__, dev_ifname);
		nl_free(msg);
		return QRILD_STATE_ERROR;
	}

	// Index of "output interface", it's rmnet_data0 here
	nl_append_val(msg, RTA_OIF, dev_ifindex);

	qrild_link_send(msg);
	nl_free(msg);

	return QRILD_STATE_DONE;
}

int qrild_link_set_up(char* dev_ifname) {
	struct ifreq ifr;
	int fd;
	int rc;

	strncpy(ifr.ifr_name, dev_ifname, IF_NAMESIZE);
	if (ifr.ifr_name[IF_NAMESIZE-1] != '\0') {
		ifr.ifr_name[IF_NAMESIZE-1] = '\0';
		fprintf(stderr, "Trunacted dev name to %s\n", ifr.ifr_name);
	}
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
		PLOGE_AND_EXIT("%s: failed to open socket\n", __func__);
	
	rc = ioctl(fd, SIOCGIFFLAGS, &ifr);
	if (rc)
		PLOGE_AND_EXIT("%s: ioctl(SIOCGIFFLAGS)\n", __func__);

	if (!(ifr.ifr_flags & IFF_UP)) {
		ifr.ifr_flags |= IFF_UP;
		rc = ioctl(fd, SIOCSIFFLAGS, &ifr);
		if (rc)
			PLOGE_AND_EXIT("%s: ioctl(SIOCSIFFLAGS)\n", __func__);
	}

	return QRILD_STATE_DONE;
}

int qrild_link_configure(struct in_addr *addr, struct in_addr *mask, struct in_addr *gateway) {
	int rc;
	uint32_t ipa0_index;

	qrild_link_open();

	printf("before qrild_link_add_link\n");
	ipa0_index = if_nametoindex("rmnet_ipa0");
	rc = qrild_link_add_link("rmnet_data0", ipa0_index, 1);

	printf("before qrild_link_set_addr\n");
	rc = rc ?: qrild_link_set_addr("rmnet_data0", addr, mask);

	printf("before qrild_link_set_up\n");
	rc = rc ?: qrild_link_set_up("rmnet_ipa0");
	printf("before qrild_link_set_up2\n");
	rc = rc ?: qrild_link_set_up("rmnet_data0");

	printf("before qrild_link_add_default_route\n");
	rc = rc ?: qrild_link_add_default_route("rmnet_data0", gateway);

	if (rc < 0) {
		fprintf(stderr, "Failed to configure netlink\n");
	}

	close(sock_fd);

	printf("DONE!\n");

	return rc;
}

