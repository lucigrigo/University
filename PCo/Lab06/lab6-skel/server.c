/*
*  	Protocoale de comunicatii:
*  	Laborator 6: UDP
*	mini-server de backup fisiere
*/

#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

#include "helpers.h"


void usage(char*file)
{
	fprintf(stderr,"Usage: %s server_port file\n",file);
	exit(0);
}

/*
*	Utilizare: ./server server_port nume_fisier
*/
int main(int argc,char**argv)
{
	int fd;

	if (argc!=3)
		usage(argv[0]);

	char buf[BUFLEN];

	struct sockaddr_in from_station;
	/*Deschidere socket*/
	int socketfd = socket(PF_INET, SOCK_DGRAM, 0);

	if(socketfd == -1) {
		printf("socket error\n");
		exit(1);
	}

	/*Setare struct sockaddr_in pentru a asculta pe portul respectiv */
	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(atoi(argv[1]));

	struct in_addr adr;
	adr.s_addr = INADDR_ANY;
	addr_in.sin_addr = adr;

	/* Legare proprietati de socket */
	int bs = bind(socketfd, (struct sockaddr *)&addr_in, sizeof(addr_in));

	if(bs < 0) {
		printf("bind error\n");
		exit(2);
	}

	/* Deschidere fisier pentru scriere */
	DIE((fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1,"open file");

	// printf("aici\n");
	/*
	*  cat_timp  mai_pot_citi
	*		citeste din socket
	*		pune in fisier
	*/
	socklen_t leng;
	int bytes_read = recvfrom(socketfd, buf, BUFLEN, 0, (struct sockaddr *)&from_station, &leng);

	while(bytes_read != 0){
		write(fd, buf, bytes_read);
		bytes_read = recvfrom(socketfd, buf, BUFLEN, 0, (struct sockaddr *)&from_station, leng);
	}

	/*Inchidere socket*/
	int socket_close = close(socketfd);

	if(socket_close == -1) {
		printf("error socket close\n");
		exit(4);
	}

	/*Inchidere fisier*/
	close(fd);

	return 0;
}
