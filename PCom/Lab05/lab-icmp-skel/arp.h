#ifndef _ARP_H_
#define _ARP_H_ 0

#include <inttypes.h>

#include <linux/if_ether.h>

struct arpethhdr {
	uint8_t shwaddr[ETH_ALEN];	/* Sender hardware address.  */
	uint8_t sipaddr[4];		/* Sender IP address.  */
	uint8_t dhwaddr[ETH_ALEN];	/* Target hardware address.  */
	uint8_t dipaddr[4];		/* Target IP address.  */
};

void arp_resolve(int sockfd, uint32_t addr, uint8_t *mac);

#endif /* _ARP_H_ */
