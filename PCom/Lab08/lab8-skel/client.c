
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "helpers.h"

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_address server_port\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, n, ret;
	struct sockaddr_in serv_addr;
	char buffer[BUFLEN];

	if (argc < 3) {
		usage(argv[0]);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	ret = inet_aton(argv[1], &serv_addr.sin_addr);
	DIE(ret == 0, "inet_aton");

	ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "connect");

	fd_set fds;
	fd_set temp_fds;
	FD_SET(sockfd, &fds);
	FD_SET(0, &fds);
	int fdmax = sockfd;

	while (1) {
		temp_fds = fds;
		int s = select(fdmax + 1, &temp_fds, NULL, NULL, NULL);
		DIE(s < 0, "select error\n");

		if(FD_ISSET(0, &temp_fds)) {
			// se citeste de la tastatura
			memset(buffer, 0, BUFLEN);
			fgets(buffer, BUFLEN - 1, stdin);

			if (strncmp(buffer, "exit", 4) == 0) {
				break;
			}

			// se trimite mesaj la server
			n = send(sockfd, buffer, strlen(buffer), 0);
			DIE(n < 0, "send");
		} else {
			memset(buffer, 0, BUFLEN);
			int rcv = recv(sockfd, buffer, BUFLEN, 0);
			DIE(rcv < 0, "receive error");
			printf("Message received: %s\n", buffer);
		}

	}

	close(sockfd);

	return 0;
}
