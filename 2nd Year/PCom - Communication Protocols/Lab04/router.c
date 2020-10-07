#include "skel.h"

int interfaces[ROUTER_NUM_INTERFACES];
struct route_table_entry *rtable;
int rtable_size;

struct arp_entry *arp_table;
int arp_table_len;

/*
 Returns a pointer (eg. &rtable[i]) to the best matching route
 for the given dest_ip. Or NULL if there is no matching route.
*/
struct route_table_entry *get_best_route(__u32 dest_ip) {
	/* TODO 1: Implement the function */
	int i = 0;
	uint32_t mask_max = -1;
	int index = -1;

	while(i < rtable_size) {
		uint32_t temp = rtable[i].mask & dest_ip;
		if(temp == rtable[i].prefix && rtable[i].mask > mask_max) {
			mask_max = rtable[i].mask;
			index = i;
		}
		i++;
	}

	return (index == -1) ? NULL : &rtable[index];
}

/*
 Returns a pointer (eg. &arp_table[i]) to the best matching ARP entry.
 for the given dest_ip or NULL if there is no matching entry.
*/
struct arp_entry *get_arp_entry(__u32 ip) {
    	/* TODO 2: Implement */
	int i = 0;
	int index = -1;

	while(i < arp_table_len) {
		if(ip == arp_table[i].ip) {
			index = i;
		}
		i++;
	}

    	return (index == -1) ? NULL : &arp_table[index];
}

int main(int argc, char *argv[])
{
	msg m;
	int rc;

	init();
	rtable = malloc(sizeof(struct route_table_entry) * 100);
	arp_table = malloc(sizeof(struct  arp_entry) * 100);
	DIE(rtable == NULL, "memory");
	rtable_size = read_rtable(rtable);
	parse_arp_table();
	/* Students will write code here */

	while (1) {
		rc = get_packet(&m);
		DIE(rc < 0, "get_message");
		struct ether_header *eth_hdr = (struct ether_header *)m.payload;
		struct iphdr *ip_hdr = (struct iphdr *)(m.payload + sizeof(struct ether_header));
		/* TODO 3: Check the checksum */
		if(ip_checksum(ip_hdr, sizeof(struct iphdr))) {
			printf("checksum error!\n");
			continue;
		}

		/* TODO 4: Check TTL >= 1 */
		if(!ip_hdr->ttl) {
			printf("ttl error!\n");
			continue;
		}

		/* TODO 5: Find best matching route (using the function you wrote at TODO 1) */
		uint32_t destination_ip = ip_hdr->daddr;
		struct route_table_entry *best_route = get_best_route(destination_ip);
		if(best_route == NULL) {
			printf("rtable_route wrong!\n");
			continue;	
		}

		/* TODO 6: Update TTL and recalculate the checksum */
		ip_hdr->ttl = ip_hdr->ttl - 1;
		ip_hdr->check = 0;
		ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

		/* TODO 7: Find matching ARP entry and update Ethernet addresses */
		struct arp_entry *best_arp_route = get_arp_entry(destination_ip);
		if(best_arp_route == NULL) {
			printf("arp route wrong!\n");
			continue;
		}
		memcpy(eth_hdr->ether_dhost, best_arp_route->mac, sizeof*eth_hdr->ether_dhost);

		/* TODO 8: Forward the pachet to best_route->interface */
		send_packet(best_route->interface, &m);
	}
}
