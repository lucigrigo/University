/*
                             Protocoale de Comunicatii
                                      Tema 2
                               Aplicatie Client-Server
                            Grigore Lucian-Florin 324CD
                                   -- SERVER --
*/
#include "helpers.h"

// indexul log-ului
unsigned int LOG_NUMBER = 1;

// formatul utilizatii corecte
void usage(char *file)
{
    fprintf(stderr, "Usage: %s <Port_Server>\n", file);
    exit(0);
}

// functie de comparare folosita la sortarea clientilor
int ccomp(const void *p, const void *q) {
    return (*(struct client **)p)->client_fd - (*(struct client **)q)->client_fd;
}

// functie de comparare folosita la sortarea topicurilor
int tcomp(const void *p, const void *q) {
    return (*(struct topic **)p)->name - (*(struct topic **)q)->name;
}

// functie care creeaza un client nou
struct client* new_client(int c_fd, char* c_id, struct sockaddr_in *c_addr, socklen_t c_addr_len) {
    struct client *c = (struct client*)malloc(sizeof(struct client));
    c->client_fd = c_fd;
    c->status = CLIENT_CONNECT;
    c->addr = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
    memcpy(c->addr, c_addr, sizeof(struct sockaddr_in));
    c->client_id = (char *)malloc(strlen(c_id));
    strcpy(c->client_id, c_id);
    c->topics = (struct topic_sub **) malloc(MAX_TOPICS * sizeof(struct topic_sub *));
    c->n_topics = 0;
    c->q_msg = (struct queued_message **) malloc(MAX_TOPICS * sizeof(struct queued_message *));
    c->n_queued_messages = 0;
    return c;
}

// functie care creeaza un nou topic
struct topic *new_topic(char *topic_name) {
    struct topic *t = (struct topic *) malloc(sizeof(struct topic));
    t->name = (char *) malloc(strlen(topic_name));
    memcpy(t->name, topic_name, strlen(topic_name));
    printf("LA CREARE %s vs %s\n", topic_name, t->name);
    t->subscribers = (struct client **) malloc(MAX_CLIENTS * sizeof(struct client *));
    t->n_subs = 0;
    return t;
}

// functie care elibereaza memoria ocupata de un client
void delete(struct client *c) {
    free(c->addr);
    free(c->topics);
    free(c->client_id);
    free(c);
}

// functie care cauta dupa socket descriptor un client in lista de clienti
struct client *search_client(int cfd, struct client **clients, int l, int r, const FLAG purpose) {
    if(clients == NULL || l > r){
        return NULL;
    }
    int m = (l + r) / 2;
    if(cfd == clients[m]->client_fd) {
        return clients[m];
    } else if(cfd > clients[m]->client_fd) {
        return search_client(cfd, clients, m + 1, r, purpose);
    }
    return search_client(cfd, clients, l, m - 1, purpose);
}

// functie care cauta dupa nume un client in lista de clienti
struct client *search_client_by_name(char *cname, struct client **clients, int l, int r, const FLAG purpose) {
    if(clients == NULL) {
        return NULL;
    }
    int i;
    for(i = 0; i < r; ++i) {
        if(clients[i] != NULL && strcmp(clients[i]->client_id, cname) == 0) {
            return clients[i];
        }
    }
    return NULL;
}

// functie care cauta dupa nume un topic in lista de topicuri
struct topic *search_topic(char *tname, struct topic **topics, int l, int r) {
    if(topics == NULL) {
        return NULL;
    }
    if(l > r) {
        return NULL;
    }
    int m = (l + r) / 2;
    if(strcmp(topics[m]->name, tname) == 0) {
        return topics[m];
    } else if(strcmp(topics[m]->name, tname) < 0) {
        return search_topic(tname, topics, m + 1, r);
    }
    return search_topic(tname, topics, l, m - 1);
}

// functie care insereaza un nou topic
struct topic **insert_new_topic(struct topic **topics, struct topic *new_topic, int *ntopics) {
    if(topics == NULL || *ntopics == 0) {
        topics = (struct topic **) malloc(MAX_TOPICS * sizeof(struct topic));
        topics[0] = new_topic;
        *ntopics = *ntopics + 1;
        return topics;
    }
    topics[*ntopics] = new_topic;
    *ntopics = *ntopics + 1;
    qsort(topics, *ntopics, sizeof(struct topic *), tcomp);
    return topics;
}

// functie care printeaza la stdout mesajul de conectarea al unui client
void print_connection_log(struct client* c) {
    // format: "New client (CLIENT_ID) connected from IP:PORT."
    char *msg = (char *)malloc(BUFLEN);
    bzero(msg, BUFLEN);
    char *cid = c->client_id;
    int cport = ntohs(c->addr->sin_port);
    struct in_addr cip = c->addr->sin_addr;
    sprintf(msg, "[SERVER_LOG#%d] New client (%s) connected from %s:%d.\n", LOG_NUMBER++, cid, inet_ntoa(cip), cport);
    printf("%s", msg);
    free(msg);
}

// functie care printeaza la stdout mesajul de deconectarea al unui client
void print_disconnection_log(int fd, struct client **clients, int nclients) {
    // format: "Client (CLIENT_ID) disconnected."
    struct client *c = search_client(fd, clients, 0, nclients - 1, CLIENT_DISCONNECT);
    DIE(c == NULL, "clients database error - unkown client");
    char *cid = c->client_id;
    char *msg = (char *) malloc(BUFLEN);
    bzero(msg, BUFLEN);
    sprintf(msg, "[SERVER_LOG#%d] Client (%s) disconnected.\n", LOG_NUMBER++, cid);
    printf("%s", msg);
    c->status = CLIENT_DISCONNECT;
    free(msg);
}

// functie care se ocupa de trimiterea unor mesaje puse in asteptare catre un client
struct queued_message **send_queued_messages(struct client *c, struct queued_message **queued_messages, int *nrqmessages) {
    int n_msg = c->n_queued_messages;
    int i;
    // printf("NUME %s n_msg %d\n", c->client_id, c->n_queued_messages);
    char *buffer = (char *) malloc(BUFLEN);

    // se parcurg mesajele puse in asteptare atribuite clientului
    for(i = 0; i < n_msg; ++i) {

        bzero(buffer, BUFLEN);
        memcpy(buffer, &c->q_msg[i]->m, sizeof(struct tcp_header) + c->q_msg[i]->m.hdr.len);
        // printf("%lu\n", sizeof(struct tcp_header) + c->q_msg[i]->m.hdr.len);
        int status = send(c->client_fd, buffer, sizeof(struct tcp_header) + c->q_msg[i]->m.hdr.len, 0);
        
        if(status < 0) { // daca a avut loc o eroare la trimitere
            perror("err sending q'd message\n");
        }
        if(c->q_msg[i]->senders_left == 1) { // daca mesajul nu mai trebuie trimis nimanui
            // TODO delete no longer needed message
        } else { // se actualizeaza numarul de destinatari ramasi pentru mesaj
            c->q_msg[i]->senders_left = c->q_msg[i]->senders_left - 1;
        }
        // printf("trece de send?\n");
    }
    if(buffer != NULL) { // se elibereaza
        // free(buffer);
    }
    return queued_messages;
}

struct client** insert_new_client(struct client **clients, struct client *new_client, int *nclients) {
    if(*nclients == 0 || clients == NULL) {
        clients = (struct client**)malloc(sizeof(struct client*) * MAX_CLIENTS);
        clients[0] = new_client;
        *nclients = *nclients + 1;
        return clients;
    }
    struct client *sc = search_client_by_name(new_client->client_id, clients, 0, *nclients - 1, CLIENT_CONNECT);
    if(sc == NULL) {
        // insert new client to the list
        clients[*nclients] = new_client;
        *nclients = *nclients + 1;
        qsort(clients, *nclients, sizeof(struct client *), ccomp);
    } else {
        // the client already exists
        // we check for possible queued message that have to be sent
        delete(new_client);
        // send_queued_messages(sc);
    }
    return clients;
}

struct tcp_message compute_message(char *topic_name, struct sockaddr_in cl_addr, DATATYPE type, char *msg) {
    struct tcp_message m;
    uint16_t sender_port = cl_addr.sin_port;
    uint32_t sender_addr = cl_addr.sin_addr.s_addr;
    m.hdr.type = MTYPE_UPDATE;
    struct tcp_topic_update tup;
    bzero(&tup, sizeof(struct tcp_topic_update));
    tup.addr = sender_addr;
    tup.port = sender_port;
    memcpy(&tup.topic, topic_name, strlen(topic_name));
    memcpy(&tup.msg, msg, strlen(msg));

    if(type == INT) {
        memcpy(&tup.msg_type, "INT", strlen("INT"));
    } else if(type == SHORT_REAL) {
        memcpy(&tup.msg_type, "SHORT_REAL", strlen("SHORT_REAL"));
    } else if(type == FLOAT) {
        memcpy(&tup.msg_type, "FLOAT", strlen("FLOAT"));
    } else {
        memcpy(&tup.msg_type, "STRING", strlen("STRING"));
    }

    m.hdr.len = sizeof(struct tcp_topic_update);
    memcpy(&m.data, &tup, sizeof(struct tcp_topic_update));
    return m;
}

struct queued_message **notify_subscribers(struct topic *topic, struct sockaddr_in cl_addr, DATATYPE type, char *msg, struct queued_message **queued_messages, int *nqmessages) {
    struct tcp_message m = compute_message(topic->name, cl_addr, type, msg);
    struct queued_message *new_m = (struct queued_message *) malloc(sizeof(struct queued_message));
    new_m->dest = (struct client **) malloc(MAX_CLIENTS * sizeof(struct client *));
    int dest = 0;
    bzero(&new_m->m, sizeof(struct tcp_message));
    memcpy(&new_m->m, &m, sizeof(struct tcp_message));

    int n_subs = topic->n_subs;
    int i;
    // printf("abonati conectati %d\n", n_subs);
    for(i = 0; i < n_subs; ++i) {
        struct client *sub = topic->subscribers[i];
        // printf("subber %s\n", sub->client_id);
        if(sub != NULL) {
            if(sub->status == CLIENT_CONNECT) {
                // printf("conectat\n");
                char *temp_buf = (char *) malloc(BUFLEN);
                bzero(temp_buf, BUFLEN);
                memcpy(temp_buf, &m, sizeof(struct tcp_header) + m.hdr.len);

                int status = send(sub->client_fd, temp_buf, sizeof(struct tcp_header) + m.hdr.len, 0);
                if(status < 0) {
                    perror("sending topic update err\n");
                }
                // printf("mesaj trimis\n");

                free(temp_buf);
            } else if(sub->status == CLIENT_DISCONNECT) {
                // printf("nu este conectat\n");
                // check for s&f option on disconnected client
                int n_topics = sub->n_topics;
                int j;
                while(j < n_topics) {
                    if(strcmp(sub->topics[j]->t->name, topic->name) == 0) {
                        //printf("nu aici?\n");
                        if(sub->topics[j]->sf_op == 1) {
                            new_m->dest[dest] = sub;
                            dest++;
                            sub->q_msg[sub->n_queued_messages] = new_m;
                            sub->n_queued_messages = sub->n_queued_messages + 1;
                        }
                        // printf("///////// no msg %d\n", sub->n_queued_messages);
                        break;
                    }
                    ++j;
                }
            }
        } else {
            perror("null sub\n");
        }
    }
    if(dest != 0) {
        new_m->senders_left = dest;
        queued_messages[*nqmessages] = new_m;
        *nqmessages = *nqmessages + 1;
    } else {
        free(new_m->dest);
        free(new_m);
    }
    // printf("%d\n", queued_messages[0]->senders_left);
    return queued_messages;
}

struct queued_message **parse_udp_client_message(char *buf, struct topic **topics, int ntopics, struct sockaddr_in cl_addr, struct queued_message **queued_messages, int *nqmessages) {
    // parse udp client message
    struct datagram dg;
    memcpy(&dg, buf, sizeof(struct datagram));
    char *topic_name = (char *) malloc(MAX_TOPIC_DIM);
    bzero(topic_name, MAX_TOPIC_DIM);
    memcpy(topic_name, dg.topic, sizeof(dg.topic));
    struct topic *tc = search_topic(topic_name, topics, 0, ntopics - 1);
    if(tc == NULL) {
        // printf("i guess aici\n");
        return queued_messages;
    }
    DATATYPE type = dg.datatype;
    char *msg = (char *)malloc(MAX_PAYLOAD_DIM);

    if(type == INT) {
        uint8_t psign = dg.payload[0];
        uint32_t pn;
        memcpy(&pn, &dg.payload[1], sizeof(uint32_t));
        int pnr = pow(-1, psign) * ntohl(pn);
        // printf("topic name = %s payload type = INT\n\tnr = %d\n", topic_name, pnr);
        sprintf(msg, "%d", pnr);
    } else if(type == SHORT_REAL) {
        uint16_t pn;
        memcpy(&pn, &dg.payload[0], sizeof(uint16_t));
        float pnr = ntohs(pn) / (float)100;
        // printf("topic name = %s payload type = SHORT_REAL\n\tnr = %.2f\n", topic_name, pnr);
        sprintf(msg, "%.2f", pnr);
    } else if(type == FLOAT) {
        uint8_t psign = dg.payload[0];
        uint32_t pn;
        memcpy(&pn, &dg.payload[sizeof(uint8_t)], sizeof(uint32_t));
        uint8_t ppow;
        memcpy(&ppow, &dg.payload[sizeof(uint8_t) + sizeof(uint32_t)], sizeof(uint8_t));
        float pnr = pow(-1, psign) * ntohl(pn) * pow(10, (-1) * ppow);
        // printf("topic name = %s payload type = FLOAT\n\tnr = %f\n", topic_name, pnr);
        sprintf(msg, "%f", pnr);
    } else if(type == STRING) {
        strncpy(msg, (char *)dg.payload, strlen((char *) dg.payload));
        // printf("mesaj=%s\n", msg);
    } else {
        perror("unknown msg type\n");
    }

    return notify_subscribers(tc, cl_addr, type, msg, queued_messages, nqmessages);
}

struct topic **parse_client_message(struct tcp_header thdr, int clientfd, struct client **clients, int nclients, struct topic **topics, int *ntopics) {
    // parse tcp client message
    if(thdr.type == MTYPE_SUBSCRIBE) {
        char *buf = (char *) malloc(BUFLEN);
        bzero(buf, BUFLEN);

        int nbytes_read = 0; 
        do {
            nbytes_read += recv(clientfd, buf, sizeof(struct tcp_subscribe), 0);
        } while(nbytes_read < thdr.len);

        struct tcp_subscribe s;
        bzero(&s, sizeof(struct tcp_subscribe));
        memcpy(&s, buf, sizeof(struct tcp_subscribe));
        char *topic_name = (char *) malloc(MAX_TOPIC_DIM);
        memcpy(topic_name, &s.topic_name, strlen(s.topic_name));

        struct client *c = search_client(clientfd, clients, 0, nclients - 1, CLIENT_SUBSCRIBE);
        if(c != NULL) {
            int i = 0;
            while(i < c->n_topics) {
                if(strcmp(c->topics[i]->t->name, topic_name) == 0) {
                    // send error msg back
                    char *buf = (char *) malloc(BUFLEN);
                    bzero(buf, BUFLEN);
                    struct tcp_message tm;
                    tm.hdr.type = MTYPE_SERVER_ERR;

                    memcpy(&tm.data, "Already subbed to this topic!", strlen("Already subbed to this topic!"));
                    tm.hdr.len = strlen("Already subbed to this topic!");
                    memcpy(buf, &tm, sizeof(struct tcp_header) + tm.hdr.len);
                    int status = send(clientfd, buf, sizeof(struct tcp_header) + tm.hdr.len, 0);
                    // printf("here is %s\n", tm.data);
                    if(status < 0) {
                        perror("error sending message back to server");
                    }
                    free(buf);
                    return topics;
                }
                i++;
            }

            struct topic *t = search_topic(topic_name, topics, 0, *ntopics - 1);    
            if(t != NULL) {
                c->topics[c->n_topics] = (struct topic_sub *) malloc(sizeof(struct topic_sub));
                c->topics[c->n_topics]->t = t;
                c->topics[c->n_topics]->sf_op = s.sf_op;
                c->n_topics = c->n_topics + 1;
                t->subscribers[t->n_subs] = c;
                t->n_subs = t->n_subs + 1;
            } else {
                t = new_topic(topic_name);
                topics = insert_new_topic(topics, t, ntopics);
                c->topics[c->n_topics] = (struct topic_sub *) malloc(sizeof(struct topic_sub));
                c->topics[c->n_topics]->t = t;
                c->topics[c->n_topics]->sf_op = s.sf_op;
                c->n_topics = c->n_topics + 1;
                t->subscribers[0] = c;
                t->n_subs = 1;
            }
        } else {
            perror("clients database err\n");
            return topics;
        }

        free(topic_name);
        free(buf);
    } else if(thdr.type == MTYPE_UNSUBSCRIBE) {
        char *buf = (char *) malloc(BUFLEN);
        bzero(buf, BUFLEN);

        int nbytes_read = 0; 
        do {
            nbytes_read += recv(clientfd, buf, sizeof(struct tcp_unsubscribe), 0);
            // printf("BUF %s\n", buf);
        } while(nbytes_read < sizeof(struct tcp_unsubscribe));

        struct tcp_unsubscribe u;
        bzero(&u, sizeof(struct tcp_unsubscribe));
        memcpy(&u, buf, sizeof(struct tcp_unsubscribe));
        char *topic_name = (char *) malloc(MAX_TOPIC_DIM);
        memcpy(topic_name, &u.topic_name, strlen(u.topic_name));
        // printf("tname %s\n", topic_name);

        struct client *c = search_client(clientfd, clients, 0, nclients - 1, CLIENT_UNSUBSCRIBE);
        if(c != NULL) {
            int i = 0;
            int found = 0;
           // printf("abonat la %d topicuri\n", c->n_topics);
            while(i < c->n_topics) {
               // printf("iter %d (%s) vs (%s) %lu\n", i, c->topics[i]->t->name, topic_name, strlen(c->topics[i]->t->name));
                if(strncmp(c->topics[i]->t->name, topic_name, strlen(topic_name)) == 0) {
                   // printf("%s\n", c->topics[i]->t->name);
                    int j = 0;
                    while(j < c->topics[i]->t->n_subs) {
                        if(strncmp(c->topics[i]->t->subscribers[j]->client_id, c->client_id, strlen(topic_name)) == 0) {
                            c->topics[i]->t->subscribers[j] = c->topics[i]->t->subscribers[c->topics[i]->t->n_subs - 1];
                            c->topics[i]->t->n_subs = c->topics[i]->t->n_subs - 1;
                            c->topics[i] = c->topics[c->n_topics - 1];
                            c->n_topics = c->n_topics - 1;
                            break;
                        }
                        j++;
                    }
                    found = 1;
                    break;
                }
                i++;
            }
            if(found == 0) {
                // printf("aici da?\n");
                // send err message back
                char *buf = (char *) malloc(BUFLEN);
                bzero(buf, BUFLEN);
                struct tcp_message tm;
                tm.hdr.type = MTYPE_SERVER_ERR;

                memcpy(&tm.data, "You are not subbed to the specified topic!", strlen("You are not subbed to the specified topic!"));
                tm.hdr.len = strlen("You are not subbed to the specified topic!");
                memcpy(buf, &tm, sizeof(struct tcp_header) + tm.hdr.len);

                int status = send(clientfd, buf, sizeof(struct tcp_header) + tm.hdr.len, 0);
                if(status < 0) {
                    perror("error sending message back to server");
                }
                free(buf);
                return topics;
            }
        } else {
            perror("clients database err\n");
            return topics;
        }

        free(topic_name);
        free(buf);
    }
    return topics;
}

int main(int argc, char *argv[])
{
    // checking usage
    if (argc != 2)
    {
        usage(argv[0]);
    }

    // creating variables
    struct sockaddr_in server_addr, client_addr;
    char *buffer = (char *) malloc(BUFLEN * sizeof(char));
    int nport, socketfd, ret, udpfd, fd_max, i, new_socketfd, nclients = 0, ntopics = 0, nqmessages = 0;
    socklen_t client_addr_len;
    struct client** clients = NULL;
    struct topic **topics = NULL;
    struct queued_message **queued_messages = (struct queued_message **) malloc(MAX_TOPICS * sizeof(struct queued_message *));

    // creating socket sets
    fd_set temp_fds;
    fd_set input_fds;

    // emptying file descriptors
    FD_ZERO(&input_fds);
    FD_ZERO(&temp_fds);

    // parsing port number
    nport = atoi(argv[1]);
    DIE(nport == 0, "port_no = 0");

    // setting server address
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(nport);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // creating TCP socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    DIE(socketfd < 0, "socket");
    int optval = 1;
    ret = setsockopt(socketfd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
    DIE(ret < 0, "set socket option err");

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

    // max socket value
    fd_max = max(socketfd, udpfd);

    printf("[SERVER_LOG#%d] ----------- SERVER OPENED -----------\n", LOG_NUMBER++);
    while (1)
    {
        temp_fds = input_fds;

        // int j = 0;
        // printf("\n\n-------------\n");
        // while(j < nclients) {
        //     printf("\tClient #%d ID=%s TOPICS:\n", j, clients[j]->client_id);
        //     int u = 0;
        //     while(u < clients[j]->n_topics) {
        //         printf("\t\ttopic_name=%s sf=%d\n", clients[j]->topics[u]->t->name, clients[j]->topics[u]->sf_op);
        //         u++;
        //     }
        //     j++;
        // }
        // printf("-------------\nntopics no. %d\n", ntopics);
        // j = 0;
        // while(j < ntopics) {
        //     printf("\tTOPIC %s cu %d subs\n", topics[j]->name, topics[j]->n_subs);
        //     j++;
        // }
        // printf("-------------\n\n");

        ret = select(fd_max + 1, &temp_fds, NULL, NULL, NULL);
        DIE(ret < 0, "select");

        if (FD_ISSET(0, &temp_fds))
        {
            // handle server close action
            memset(buffer, 0, BUFLEN);
            fgets(buffer, BUFLEN - 1, stdin);

            if (strncmp(buffer, "exit", 4) == 0)
            {
                // close connections with all clients
                for(i = 1; i <= fd_max; ++i) {
                    if(FD_ISSET(i, &input_fds) && (i != socketfd) && (i != udpfd)) {
                        bzero(buffer, BUFLEN);
                        memcpy(buffer, SERVER_CLOSE, SERVER_CLOSE_LEN);
                        ret = send(i, buffer, strlen(buffer), 0);
                        DIE(ret < 0, "server close notification send error");
                        close(i);
                        FD_CLR(i, &input_fds);
                        struct client *c = search_client(i, clients, 0, nclients - 1, SERVER_CLOSE_ID);
                        if(c != NULL) {
                            printf("[SERVER_LOG#%d] Client (%s) is disconnected.\n", LOG_NUMBER++, c->client_id);
                            delete(c);
                        }
                    }
                }
                close(socketfd);
                close(udpfd);
                free(clients);
                break;
            } else {
                printf("[SERVER_WARNING] Only \"exit\" command can be used on the server!\n");
                memset(buffer, 0, BUFLEN);
                continue;
            }
        }

        for (i = 0; i <= fd_max; ++i)
        {
            if (FD_ISSET(i, &temp_fds))
            {
                if (i == socketfd)
                {
                    // handle connection request on listening socket
                    // & print relevant message
                    bzero(buffer, BUFLEN);

                    // accepting connection request
                    client_addr_len = sizeof(client_addr);
                    new_socketfd = accept(socketfd, (struct sockaddr *) &client_addr, &client_addr_len);
                    DIE(new_socketfd < 0, "tcp accept");

                    // adding new socket to the set
                    FD_SET(new_socketfd, &input_fds);
                    fd_max = max(fd_max, new_socketfd);

                    // parse connection request
                    char *c_id = (char *)malloc(MAX_ID_LENGTH * sizeof(char));
                    bzero(buffer, BUFLEN);
                    bzero(c_id, MAX_ID_LENGTH);

                    // follow message structure
                    ret = recv(new_socketfd, buffer, sizeof(struct tcp_header), 0);
                    DIE(ret < 0, "receive connection request");
                    struct tcp_header thdr;
                    bzero(&thdr, sizeof(struct tcp_header));
                    memcpy(&thdr, buffer, sizeof(struct tcp_header));
                    if(thdr.type != MTYPE_ID) {
                        free(c_id);
                        continue;
                    }
                    bzero(buffer, BUFLEN);
                    ret = recv(new_socketfd, buffer, thdr.len, 0);
                    strncpy(c_id, buffer, strlen(buffer));
                    struct client *c = new_client(new_socketfd, c_id, &client_addr, client_addr_len);

                    // check the usage of the id
                    struct client *ac = search_client_by_name(c->client_id, clients, 0, nclients, CLIENT_CONNECT);
                    if(ac != NULL) {
                        if(ac->status == CLIENT_CONNECT) {
                            // client with the same name is already connected
                            struct tcp_message tm;
                            tm.hdr.type = MTYPE_SERVER_ERR;
                            strcpy(tm.data, "User with same ID is connected to the server!");
                            tm.hdr.len = strlen("User with same ID is connected to the server!");

                            bzero(buffer, BUFLEN);
                            memcpy(buffer, &tm, sizeof(struct tcp_header) + tm.hdr.len);

                            // send err message back
                            ret = send(new_socketfd, buffer, sizeof(struct tcp_header) + tm.hdr.len, 0);
                            if(ret < 0) {
                                perror("error sending id err message to client");
                            }
                            close(new_socketfd);
                            FD_CLR(new_socketfd, &input_fds);
                            delete(c);
                        } else {
                            // client has reconnected
                            ac->status = CLIENT_CONNECT;

                            // refresh socket descriptor value
                            ac->client_fd = new_socketfd;

                            // forward any message to him
                            queued_messages = send_queued_messages(ac, queued_messages, &nqmessages);
                            print_connection_log(c);
                        }
                    } else {
                        // add client to clients list
                        clients = insert_new_client(clients, c, &nclients);
                        print_connection_log(c);
                    }
                    // clearing buffer
                    bzero(buffer, BUFLEN);
                } else if(i == udpfd) {
                    // for UDP socket updates
                    // handle connection requests
                    // parse their messages
                    bzero(buffer, BUFLEN);
                    bzero(&client_addr, sizeof(struct sockaddr_in));
                    int bytes_to_read = recvfrom(udpfd, buffer, BUFLEN, 0, (struct sockaddr *) &client_addr, &client_addr_len);
                    if(bytes_to_read != 0) {
                        queued_messages = parse_udp_client_message(buffer, topics, ntopics, client_addr, queued_messages, &nqmessages);
                    }
                    bzero(buffer, BUFLEN);
                } else {
                        // TODO for TCP sockets
                        //      handle exit requests
                        //      handle subscribe requests
                        //      handle unsubscribe requests
                        //      & print relevant messages
                        bzero(buffer, BUFLEN);
                        ret = recv(i, buffer, sizeof(struct tcp_header), 0);
                        DIE(ret < 0, "server recv from tcp");
                        struct tcp_header thdr;
                        bzero(&thdr, sizeof(struct tcp_header));
                        memcpy(&thdr, buffer, sizeof(struct tcp_header));

                        if(ret == 0 || thdr.type == MTYPE_DISCONNECT) {
                            // print disconnection log
                            close(i);
                            FD_CLR(i, &input_fds);
                            print_disconnection_log(i, clients, nclients);
                        } else {
                            // parse client message
                            topics = parse_client_message(thdr, i, clients, nclients, topics, &ntopics);
                        }
                        memset(buffer, 0, BUFLEN);
                        ret = 1;
                }
            }
        }
    }

    printf("[SERVER_LOG#%d] ----------- SERVER CLOSED -----------\n", LOG_NUMBER);
    close(socketfd);
    // TODO eliberarea memoriei alocate
    if(buffer != NULL) {
        free(buffer);
    }
    return 0;
}