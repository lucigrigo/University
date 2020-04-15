// Protocoale de comunicatii
// Laborator 9 - DNS
// dns.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME>\n\t%s -a <IP>\n", name, name);
	return 1;
}

// Receives a name and prints IP addresses
void get_ip(char* name)
{
	int ret;
	struct addrinfo hints, *result, *p;

	// TODO: set hints
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AF_UNSPEC;

	// TODO: get addresses
	ret = getaddrinfo(name, NULL, &hints, &result);
	if(ret != 0) {
		exit(1);
	}

	// TODO: iterate through addresses and print them
	int i = 1;
	for(p = result; p != NULL; p = p -> ai_next) {
		char *dest = malloc(max(sizeof(struct sockaddr_in), sizeof(struct sockaddr_in6)));
		if(p->ai_family == AF_INET) {
			inet_ntop(p->ai_family, &((struct sockaddr_in*)p->ai_addr)->sin_addr, dest, sizeof(struct sockaddr_in));
			printf("Rezultat #%d:\n\taddress = %s\n", i++, dest);
			printf("\tfamily = %d\n", AF_INET);
		} else {
			inet_ntop(p->ai_family, &((struct sockaddr_in6*)p->ai_addr)->sin6_addr, dest, sizeof(struct sockaddr_in6));
			printf("Rezultat #%d:\n\taddress = %s\n", i++, dest);
			printf("\tfamily = %d\n", AF_INET6);
		}
		// printf("Rezultat #%d:\n\taddress = %s\n", i++, dest);
		printf("\tprotocol = %d\n", p->ai_protocol);
		printf("\tsocktype = %d\n", p->ai_socktype);
		printf("\taddrlen = %d\n", p->ai_addrlen);
		printf("\tflags = %d\n", p->ai_flags);
		printf("\tcanoname = %s\n", p->ai_canonname);
		printf("\n");
		free(dest);
	}

	// TODO: free allocated data
	freeaddrinfo(result);
}

// Receives an address and prints the associated name and service
void get_name(char* ip)
{
	int ret;
	struct sockaddr_in addr;
	char host[1024];
	char service[20];

	// TODO: fill in address data
	memset(&addr, 0, sizeof(struct sockaddr_in));
	inet_aton(ip, &addr.sin_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);

	// TODO: get name and service
	ret = getnameinfo((struct sockaddr *)&addr, sizeof(struct sockaddr_in), host, 1024, service, 20, 0);

	if(ret != 0){
		exit(1);
	}
	// TODO: print name and service
	printf("Rezultat:\n\thost = %s\n\tservice = %s\n\n", host, service);
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		return usage(argv[0]);
	}

	if (strncmp(argv[1], "-n", 2) == 0) {
		get_ip(argv[2]);
	} else if (strncmp(argv[1], "-a", 2) == 0) {
		get_name(argv[2]);
	} else {
		return usage(argv[0]);
	}

	return 0;
}
