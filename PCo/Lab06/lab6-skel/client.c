/*
*  	Protocoale de comunicatii:
*  	Laborator 6: UDP
*	client mini-server de backup fisiere
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
#include <arpa/inet.h>

void usage(char*file)
{
	fprintf(stderr,"Usage: %s ip_server port_server file\n",file);
	exit(0);
}

/*
*	Utilizare: ./client ip_server port_server nume_fisier_trimis
*/
int main(int argc,char**argv)
{
	if (argc!=4)
		usage(argv[0]);

	int fd;
	char buf[BUFLEN];

	/*Deschidere socket*/
	int socketfd = socket(PF_INET, SOCK_DGRAM, 0);

	if(socketfd == -1) {
		printf("socket error\n");
		exit(1);
	}

	/* Deschidere fisier pentru citire */
	DIE((fd=open(argv[3],O_RDONLY))==-1,"open file");

	/*Setare struct sockaddr_in pentru a specifica unde trimit datele*/
	struct sockaddr_in to_station;
	to_station.sin_family = AF_INET;
	to_station.sin_port = htons(atoi(argv[2]));

	inet_aton(argv[1], &(to_station.sin_addr));

	/*
	*  cat_timp  mai_pot_citi
	*		citeste din fisier
	*		trimite pe socket
	*/
	int read_bytes = read(fd, buf, BUFLEN);
	while(read_bytes != 0){
		// printf("sent bytes %d\n", read_bytes);
		int nbytes_sent = sendto(socketfd, buf, read_bytes, 0, (struct sockaddr *)&to_station, sizeof(to_station));
		printf("bytes sent: %d\n", nbytes_sent);
		read_bytes = read(fd, buf, BUFLEN);
	}

	/*Inchidere socket*/
	close(socketfd);

	/*Inchidere fisier*/
	close(fd);
	return 0;
}
