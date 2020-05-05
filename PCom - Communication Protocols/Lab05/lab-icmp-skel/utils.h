#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/ip_icmp.h>

#include <sys/types.h>
#include <sys/socket.h>

// TODO uncomment the line below and replace "eth0" with your interface name
#define _IFNAME "enp0s3"
#ifndef _IFNAME
#error "Fill in the '#define' above with the name of your interface"
#endif
extern const char *IFNAME;

#define DIE(condition, msg) \
	do { \
		if (condition) { \
			fprintf(stderr, "(%s:%d): %s\n", __FILE__, __LINE__, msg); \
			perror(""); \
			exit(1); \
		} \
	} while (0)

#define PACKET_LEN 1500

#define IP_OFF (sizeof(struct ether_header))
#define ICMP_OFF (IP_OFF + sizeof(struct iphdr))

struct packet {
	uint8_t payload[PACKET_LEN];
	size_t size;
};
void init_packet(struct packet *pkt);

char *dns_lookup(char *addr_host);

void get_interface_mac(int sockfd, const char *ifname, uint8_t *mac);
void get_interface_ip(int sockfd, const char *ifname, uint32_t *ip);
uint32_t get_default_gateway_ip(void);

/**
 * Trimite pachetul pkt; întoarce în reply răspunsul și returnează timpul
 * trecut de la trimitere până la primire.
 */
double time_packet(int sockfd, struct packet *pkt, struct packet *reply);

/**
 * Folosiți funcția pentru a inspecta conținutul pachetului:
 * hex_dump(packet.payload, packet.size);
 *
 * sau a unui header:
 * hex_dump(icmp_hdr, sizeof(struct icmphdr));
 */
void hex_dump(const void* data, size_t size);

/** Checksum și pentru IPv4 și pentru ICMP (În network-byte-order). */
uint16_t checksum(void* vdata,size_t length);

#endif /* _UTILS_H_ */
