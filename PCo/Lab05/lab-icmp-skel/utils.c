#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <ifaddrs.h>

#include "utils.h"

const char *IFNAME = _IFNAME;

void init_packet(struct packet *pkt)
{
	memset(pkt->payload, 0, sizeof(pkt->payload));
	pkt->size = 0;
}

char *dns_lookup(char *addr_host)
{
	struct hostent *host_entity;
	char *ip = malloc(NI_MAXHOST * sizeof(char));
	DIE(!ip, "malloc");

	if ((host_entity = gethostbyname(addr_host)) == NULL) {
		return NULL;
	}

	// filling up address structure
	strcpy(ip, inet_ntoa(*(struct in_addr *)host_entity->h_addr));
	return ip;

}

uint32_t get_default_gateway_ip(void)
{
	// ugly, but seems the prettiest...
	FILE *fp = popen("ip route | grep default | awk '{print $3}'", "r");
	DIE(fp == NULL, "popen");

	char result[64];
	char *res;
	res = fgets(result, sizeof(result), fp);
	DIE(res == NULL, "fgets");

	// get rid of trailing newline
	result[strlen(result) - 1] = 0;

	uint32_t addr;
	int ret;
	ret = inet_pton(AF_INET, result, &addr);
	DIE(ret != 1, "inet_pton");

	return addr;
}

// Unfortunatey, our raw socket gets all packets...
int relevant_packet(int sockfd, struct packet *orig, struct packet *reply)
{
	struct ether_header *eth_hdr = (struct ether_header *)reply->payload;
	uint8_t own_mac[ETH_ALEN];
	get_interface_mac(sockfd, IFNAME, own_mac);

	// Discard packets that aren't for this machine
	if (memcmp(own_mac, eth_hdr->ether_dhost, ETH_ALEN))
		return 0;

	// Discard non-IP packets
	if (ntohs(eth_hdr->ether_type) != ETHERTYPE_IP)
		return 0;

	struct iphdr *ip_hdr = (struct iphdr *)(reply->payload + IP_OFF);
	// Discard non-ICMP packets
	if (ip_hdr->protocol != IPPROTO_ICMP)
		return 0;

	return 1;
}

double time_packet(int sockfd, struct packet *pkt, struct packet *reply)
{
	struct timespec start, end;

	int res = clock_gettime(CLOCK_MONOTONIC, &start);
	DIE(res == -1, "clock_gettime");

	res = send(sockfd, pkt->payload, pkt->size, 0);
	DIE(res == -1, "send");

	do {
		res = recv(sockfd, reply->payload, sizeof(reply->payload), 0);
		DIE(res == -1, "recv");
		reply->size = res;
	} while (!relevant_packet(sockfd, pkt, reply));

	/*printf("Length: %zu\n", reply->size);*/
	/*hex_dump(reply->payload, reply->size);*/
	/*puts("");*/

	clock_gettime(CLOCK_MONOTONIC, &end);

	return (double)(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

void hex_dump(const void* data, size_t size)
{
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

uint16_t checksum(void *vdata, size_t length) {
	// Cast the data pointer to one that can be indexed.
	char* data=(char*)vdata;

	// Initialise the accumulator.
	uint64_t acc=0xffff;

	// Handle any partial block at the start of the data.
	unsigned int offset=((uintptr_t)data)&3;
	if (offset) {
		size_t count=4-offset;
		if (count>length) count=length;
		uint32_t word=0;
		memcpy(offset+(char*)&word,data,count);
		acc+=ntohl(word);
		data+=count;
		length-=count;
	}

	// Handle any complete 32-bit blocks.
	char* data_end=data+(length&~3);
	while (data!=data_end) {
		uint32_t word;
		memcpy(&word,data,4);
		acc+=ntohl(word);
		data+=4;
	}
	length&=3;

	// Handle any partial block at the end of the data.
	if (length) {
		uint32_t word=0;
		memcpy(&word,data,length);
		acc+=ntohl(word);
	}

	// Handle deferred carries.
	acc=(acc&0xffffffff)+(acc>>32);
	while (acc>>16) {
		acc=(acc&0xffff)+(acc>>16);
	}

	// If the data began at an odd byte address
	// then reverse the byte order to compensate.
	if (offset&1) {
		acc=((acc&0xff00)>>8)|((acc&0x00ff)<<8);
	}

	// Return the checksum in network byte order.
	return htons(~acc);
}

void get_interface_mac(int sockfd, const char *ifname, uint8_t *mac)
{
	int res;
	struct ifreq ifr;
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", ifname);
	res = ioctl(sockfd, SIOCGIFHWADDR, &ifr);
	DIE(res == -1, "ioctl SIOCGIFHWADDR");
	memcpy(mac, ifr.ifr_addr.sa_data, ETH_ALEN);
}

void get_interface_ip(int sockfd, const char *ifname, uint32_t *ip)
{
	struct ifreq ifr;
	snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", ifname);
	int res = ioctl(sockfd, SIOCGIFADDR, &ifr);
	DIE(res == -1, "ioctl SIOCGIFADDR");

	*ip = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr.s_addr;
}
