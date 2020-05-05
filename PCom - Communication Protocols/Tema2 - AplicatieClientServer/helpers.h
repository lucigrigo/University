#ifndef _HELPER_LIB_
#define _HELPER_LIB_

#define RESTRICTED_CONTENT 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

#define BUFLEN 2000
#define MAX_CLIENTS 1000
#define MAX_TOPIC_DIM 50
#define MAX_PAYLOAD_DIM 1500
#define MAX_TOPICS 1000
#define MAX_ID_LENGTH 10
#define MAX_MSGTYPE_DIM 10
#define MAX_COMMAND_DIM 25
#define MAX_DATA_DIM 250

#define CLIENT_CONNECT 1
#define CLIENT_DISCONNECT -1
#define CLIENT_SUBSCRIBE 2
#define CLIENT_UNSUBSCRIBE 3

#define SERVER_CLOSE "server_close"
#define SERVER_CLOSE_ID 2
#define SERVER_CLOSE_LEN strlen(SERVER_CLOSE)

#define SUBSCRIBE_COMMAND "subscribe"
#define SUBSCRIBE_COMMAND_LEN strlen(SUBSCRIBE_COMMAND)
#define UNSUBSCRIBE_COMMMAND "unsubscribe"
#define UNSUBSCRIBE_COMMAND_LEN strlen(UNSUBSCRIBE_COMMAND)

#define MTYPE_DISCONNECT 0
#define MTYPE_ID 1
#define MTYPE_SUBSCRIBE 2
#define MTYPE_UNSUBSCRIBE 3
#define MTYPE_SB_UNSB 4
#define MTYPE_SUB 5
#define MTYPE_UNSUB 6
#define MTYPE_UPDATE 10
#define MTYPE_SERVER_ERR -1

#define INT 0
#define SHORT_REAL 1
#define FLOAT 2
#define STRING 3

#define SUBSCRIBERS_UPDATED 0

#define FLAG int
#define DATATYPE unsigned int

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
    uint8_t payload[MAX_PAYLOAD_DIM];
};

struct topic_sub {
    struct topic* t;
    uint8_t sf_op;
};

struct client
{
    char *client_id;
    int client_fd;
    int status;
    int n_topics;
    struct topic_sub **topics;
    struct sockaddr_in* addr;
    int n_queued_messages;
    struct queued_message **q_msg;
};

struct topic {
    char *name;
    int n_subs;
    struct client **subscribers;
};

struct tcp_topic_update{
    uint16_t port;
    uint32_t addr;
    char topic[MAX_TOPIC_DIM];
    char msg_type[20];
    char msg[1000];
};

struct tcp_unsubscribe{
    char topic_name[MAX_TOPIC_DIM];
};

struct tcp_subscribe{
    char topic_name[MAX_TOPIC_DIM];
    uint8_t sf_op;
};

struct tcp_header{
    uint16_t len;
    uint8_t type;
};

struct tcp_message {
    struct tcp_header hdr;
    char data[MAX_DATA_DIM];
};

struct queued_message {
    int senders_left;
    struct client **dest;
    struct tcp_message m;
};

#endif