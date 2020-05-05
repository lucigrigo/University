/*
                             Protocoale de Comunicatii
                                      Tema 2
                               Aplicatie Client-Server
                            Grigore Lucian-Florin 324CD
                                 -- SUBSCRIBER --
*/
#include <stdio.h>
#include <stdlib.h>

void usage(char* file)
{
	fprintf(stderr,"Usage: %s <ID_Client> <IP_Server> <Port_Server>\n",file);
	exit(0);
}

int main(int argc, char* argv) {
    if(argc != 4) { // checking usage
        usage(argv[0]);
    }
    return 0;
}