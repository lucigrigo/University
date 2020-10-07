/*
                             Protocoale de Comunicatii
                                      Tema 2
                               Aplicatie Client-Server
                            Grigore Lucian-Florin 324CD
                                   -- SERVER --
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFLEN 1024
#define MAX_CLIENTS 1000
#define MAX_TOPIC_DIM 50
#define MAX_PAYLOAD_DIM 1500

#define DIE(assertion, call_description)  \
    do                                    \
    {                                     \
        if (assertion)                    \
        {                                 \
            fprintf(stderr, "(%s, %d): ", \
                    __FILE__, __LINE__);  \
            perror(call_description);     \
            exit(EXIT_FAILURE);           \
        }                                 \
    } while (0)

struct datagram
{
    uint8_t topic[MAX_TOPIC_DIM];
    uint8_t datatype;
    uint8_t payload[MAX_PAYLOAD_DIM]
};

struct client
{
    char *client_id;
    int client_fd;
};

void usage(char *file)
{
    fprintf(stderr, "Usage: %s <Port_Server>\n", file);
    exit(0);
}

int main(int argc, char *argv[])
{
    // checking usage
    if (argc != 2)
    {
        usage(argv[0]);
    }

    // creating variables
    struct sockaddr_in server_addr;
    char buffer[BUFLEN];
    int nport, socketfd, ret, udpfd, fd_max, i;

    // creating socket sets
    fd_set temp_fds;
    fd_set input_fds;

    // emptying file descriptors
    FD_ZERO(&input_fds);
    FD_ZERO(&temp_fds);

    // parsing port number
    nport = atoi(argv[1]);
    DIE(nport == 0, "port_no = 0");

    // creating TCP socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    DIE(socketfd < 0, "socket");

    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(nport);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    ret = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    DIE(ret < 0, "tcp bind");

    ret = listen(socketfd, MAX_CLIENTS);
    DIE(ret < 0, "tcp listen");

    // creating UDP socket
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);

    ret = bind(udpfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    DIE(ret < 0, "udp bind");

    // adding them to the descriptor set
    FD_SET(socketfd, &input_fds);
    FD_SET(udpfd, &input_fds);
    FD_SET(0, &input_fds);

    fd_max = socketfd;

    while (1)
    {
        temp_fds = input_fds;

        ret = select(fd_max + 1, &temp_fds, NULL, NULL, NULL);
        DIE(ret < 0, "select");

        if (FD_ISSET(0, &temp_fds))
        {
            // handle server close action
            memset(buffer, 0, BUFLEN);
            fgets(buffer, BUFLEN - 1, stdin);

            if (strncmp(buffer, "exit", 4) == 0)
            {
                break;
            }
            break;
        }

        for (i = 0; i <= fd_max; ++i)
        {
            if (FD_ISSET(i, &temp_fds))
            {
                if (i == socketfd)
                {
                    // TODO handle connection request on listening socket
                    //      & print relevant message
                    printf("new client connection request\n");
                }
            }
            else
            {
                // TODO for TCP sockets
                //      handle exit requests
                //      handle subscribe requests
                //      handle unsubscribe requests
                //      & print relevant messages
                // TODO for UDP sockets
                //     handle new posts
                //     & print relevant message
            }
        }
    }
    return 0;
}