/*
                             Protocoale de Comunicatii
                                      Tema 2
                               Aplicatie Client-Server
                            Grigore Lucian-Florin 324CD
                                 -- SUBSCRIBER --
*/
#include "helpers.h"

// functia care indica utilizarea corecta a executabilului
void usage(char* file)
{
	fprintf(stderr,"Usage: %s <ID_Client> <IP_Server> <Port_Server>\n",file);
	exit(0);
}

// functie care verifica input-ul de la stdin
int check_message_format(char *msg, char **command, char **topic_name, int *sf) {
    // creeaza o copie a inputului
    char *msg_copy = (char *)malloc(strlen(msg));
    memcpy(msg_copy, msg, strlen(msg));

    // o imparte in token-uri
    char *arg = strtok(msg_copy, " \n");
    if(arg == NULL) {
        perror("!Please use spaces betweeen arguments !");
        return -1;
    }

    // commanda se refera la "subscribe" sau "unsubscribe"
    *command = (char *) malloc(strlen(arg));
    bzero(*command, strlen(arg));
    memcpy(*command, arg, strlen(arg));
    arg = strtok(NULL, " \n");
    if(strcmp(*command, SUBSCRIBE_COMMAND) != 0 && strcmp(*command, UNSUBSCRIBE_COMMMAND) != 0) {
        perror("! Subscribe/Unsubscribe option error!");
        return -1;
    }
    if(arg == NULL) {
        perror("! Topic name missing !");
        return -1;
    }

    // numele topicului
    *topic_name = (char *)malloc(strlen(msg));
    bzero(*topic_name, strlen(arg));
    memcpy(*topic_name, arg, strlen(arg));
    arg = strtok(NULL, " \n");
    if(arg != NULL) {
        int sf_op = atoi(arg);
        if(sf_op != 1 && sf_op != 0) {
            perror("! Store&Forward option error !");
            return -1;
        }
        *sf = sf_op;
        arg = strtok(NULL, " \n");
        if(arg != NULL) {
            // daca mesajul contine si altceva in afara de argumentele necesare
            perror("! Longer message than needed !");
            return -1;
        }
    } else if (strcmp(*command, SUBSCRIBE_COMMAND) == 0) {
        // optiunea store & forward nu a fost setata pentru subscribe
        return -1;
    }
    return 0;
}

// functie care formateaza mesajul conform protoclului dintre server si client
struct tcp_message format_message(struct tcp_message tm, char *str, char* instr, char *tname, int sf_op, FLAG flag) {
    bzero(&tm, sizeof(struct tcp_message));
    if(flag == MTYPE_ID) {
        // se doreste doar comunicarea id-ului utilizatorului
        tm.hdr.type = MTYPE_ID;
        memcpy(&tm.data, str, strlen(str));
        tm.hdr.len = strlen(str);
    } else {
        if(strncmp(instr, SUBSCRIBE_COMMAND, SUBSCRIBE_COMMAND_LEN) == 0) {
            // daca se doreste abonarea la un topic
            tm.hdr.type = MTYPE_SUBSCRIBE;

            struct tcp_subscribe s;
            bzero(&s, sizeof(struct tcp_subscribe));
            memcpy(&s.topic_name, tname, strlen(tname));
            s.sf_op = sf_op;
            memcpy(&tm.data, &s, sizeof(struct tcp_subscribe));

            tm.hdr.len = sizeof(struct tcp_subscribe);
        } else {
            // daca se doreste dezabonarea de la un topic
            tm.hdr.type = MTYPE_UNSUBSCRIBE;

            struct tcp_unsubscribe u;
            bzero(&u, sizeof(struct tcp_unsubscribe));
            memcpy(&u.topic_name, tname, strlen(tname));
            memcpy(&tm.data, &u, sizeof(struct tcp_unsubscribe));

            tm.hdr.len = sizeof(struct tcp_unsubscribe);
        }
    }
    return tm;
}

// functie care parseaza mesajul de la server
void parse_received_message(int socketfd, char *buffer) {
    struct tcp_header thdr;
    bzero(&thdr, sizeof(struct tcp_header));
    memcpy(&thdr, buffer, sizeof(struct tcp_header));

    if(thdr.type == MTYPE_UPDATE) {
        // mesajul reprezinta o postare la un topic la care clientul este abonat
        struct tcp_topic_update tup;
        bzero(&tup, sizeof(struct tcp_topic_update));
        bzero(buffer, BUFLEN);

        int nbytes_read = 0;
        do {
            nbytes_read += recv(socketfd, buffer, thdr.len, 0);
        } while (nbytes_read < thdr.len);

        memcpy(&tup, buffer, thdr.len);
        uint16_t portn_no = tup.port;
        uint32_t addr_no = tup.addr;
        struct in_addr in;
        bzero(&in, sizeof(struct in_addr));
        in.s_addr = addr_no;
        printf("%s:%d - %s - %s - %s\n", inet_ntoa(in), ntohs(portn_no), tup.topic, tup.msg_type, tup.msg);
    } else {
        // mesajul este unul de eroare
        char *buf = (char *) malloc(thdr.len);
        bzero(buf, thdr.len);

        int nbytes_read = 0;
        do {
            nbytes_read += recv(socketfd, buf, thdr.len, 0);
        } while (nbytes_read < thdr.len);

        if(nbytes_read < 0) {
            perror("error receiving message from server");
            return;
        }
        printf("Error received from server <%s>\n", buf);
        // free(buf);
    }
}

int main(int argc, char* argv[]) {
    // verificare argumente in linia de comanda
    if(argc != 4) { 
        usage(argv[0]);
    }

    // variabilele utilizate
    int socketfd, ret, fd_max;
    struct sockaddr_in server_addr;
    char *buffer = (char *) malloc(BUFLEN);
    struct tcp_message tm;

    // deschiderea socketului
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    DIE(socketfd < 0, "socket");
    int optval = 1;
    ret = setsockopt(socketfd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
    DIE(ret < 0, "set socket option err");

    // setarea adresei serverului
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[3]));
    ret = inet_aton(argv[2], &server_addr.sin_addr);
    DIE(ret == 0, "inet_aton");

    // conectarea la socket
    ret = connect(socketfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    bzero(buffer, BUFLEN);
    memcpy(buffer, argv[1], strlen(argv[1]));

    // formatarea mesajului
    tm = format_message(tm, buffer, NULL, NULL, 0, MTYPE_ID);
    bzero(buffer, BUFLEN);
    memcpy(buffer, &tm, sizeof(struct tcp_header) + tm.hdr.len);
    
    // trimiterea id-ului
    ret = send(socketfd, buffer, sizeof(buffer), 0);
    DIE(ret < 0, "send id fail");

    // setarea setului de descriptori
    fd_set fds;
    fd_set temp_fds;
    FD_SET(socketfd, &fds);
    FD_SET(0, &fds);
    fd_max = socketfd;

    while(1) {
        temp_fds = fds;
        ret = select(fd_max + 1, &temp_fds, NULL, NULL, NULL);
        DIE(ret < 0, "select");

        if(FD_ISSET(0, &temp_fds)) { // stim ca inputul vine de la tastatura
            memset(buffer, 0, BUFLEN);
            fgets(buffer, BUFLEN - 1, stdin);

            if((strncmp(buffer, "exit", 4) == 0)) { // daca se doreste inchiderea clientului
                close(socketfd);
                break;
            }
            char *command = NULL;
            char *topic_name = NULL;
            int sf_op = -1;

            // se verifica formatul inputul de la stdin
            ret = check_message_format(buffer, &command, &topic_name, &sf_op);

            // daca este corect, mesajul este construit
            tm = format_message(tm, buffer, command, topic_name, sf_op, MTYPE_SB_UNSB);

            bzero(buffer, BUFLEN);
            memcpy(buffer, &tm, sizeof(struct tcp_header) + tm.hdr.len);
            if(ret == 0) {
                // trimiterea catre server a cererii
                ret = send(socketfd, buffer, sizeof(struct tcp_header) + tm.hdr.len, 0);
                DIE(ret < 0, "send");
                printf("%sd %s\n", command, topic_name);
            } else {
                // inputul nu a fost validat
                printf("\n---------------------\n-- Subscriber commands must respect the following structure --\n\t\"<command> <topic_name> <sf_option>\"\n");
                printf("where:\n\t<command> can be either \"subscribe\" or \"unsubscribe\"\n\t<topic> is the name of the topic\n");
                printf("\t<sf_option> can have value 0 (Store&Forward option OFF) or 1 (Store&Forward option ON)\n---------------------\n\n");
            }
            bzero(buffer, BUFLEN);
        } else {
            // primirea unui input de la server
            memset(buffer, 0, BUFLEN);
            ret = recv(socketfd, buffer, sizeof(struct tcp_header), 0);
            DIE(ret < 0, "subscriber receive error");

            if(ret == 0 || strncmp(buffer, SERVER_CLOSE, SERVER_CLOSE_LEN) == 0) {
                // daca serverul s-a inchis
                close(socketfd);
                FD_CLR(socketfd, &fds);
                break;
            } else {
                // se parseaza mesajul
                parse_received_message(socketfd, buffer);
            }
            bzero(buffer, BUFLEN);
        }
    }

    // se inchide socket-ul
    close(socketfd);

    // se elibereaza memoria
    //free(buffer);
    return 0;
}