/*
 * Protocoale de comunicatii
 * Laborator 11 - E-mail
 * send_mail.c
 */

#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>  
#include <unistd.h>     
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define SMTP_PORT 25
#define MAXLEN 500

/**
 * Citeste maxim maxlen octeti de pe socket-ul sockfd in
 * buffer-ul vptr. Intoarce numarul de octeti cititi.
 */
ssize_t read_line(int sockd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *buffer;

    buffer = vptr;

    for (n = 1; n < maxlen; n++) {
        if ((rc = read(sockd, &c, 1)) == 1) {
            *buffer++ = c;

            if (c == '\n') {
                break;
            }
        } else if (rc == 0) {
            if (n == 1) {
                return 0;
            } else {
                break;
            }
        } else {
            if (errno == EINTR) {
                continue;
            }

            return -1;
        }
    }

    *buffer = 0;
    return n;
}

/**
 * Trimite o comanda SMTP si asteapta raspuns de la server. Comanda
 * trebuie sa fie in buffer-ul sendbuf. Sirul expected contine
 * inceputul raspunsului pe care trebuie sa-l trimita serverul
 * in caz de succes (de exemplu, codul 250). Daca raspunsul
 * semnaleaza o eroare, se iese din program.
 */
void send_command(int sockfd, const char sendbuf[], char *expected)
{
    char recvbuf[MAXLEN];
    int nbytes;
    char CRLF[2] = {13, 10};

    printf("Trimit: %s\n", sendbuf);
    write(sockfd, sendbuf, strlen(sendbuf));
    write(sockfd, CRLF, sizeof(CRLF));

    nbytes = read_line(sockfd, recvbuf, MAXLEN - 1);
    recvbuf[nbytes] = 0;
    printf("Am primit: %s", recvbuf);

    if (strstr(recvbuf, expected) != recvbuf) {
        printf("Am primit mesaj de eroare de la server!\r\n");
        exit(-1);
    }
}

int main(int argc, char **argv) {
    int sockfd;
    int port = SMTP_PORT;
    struct sockaddr_in servaddr;
    char server_ip[INET_ADDRSTRLEN];
    char sendbuf[MAXLEN]; 
    char recvbuf[MAXLEN];

    if (argc != 3) {
        printf("Utilizare: ./send_msg adresa_server nume_fisier\r\n");
        exit(-1);
    }

    strncpy(server_ip, argv[1], INET_ADDRSTRLEN);

    // TODO 1: creati socket-ul TCP client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("socket err");
        exit(1);
    }

    // // TODO 2: completati structura sockaddr_in cu
    // // portul si adresa IP ale serverului SMTP
    // bzero(&servaddr, sizeof(struct sockaddr_in));
    // servaddr.sin_family = AF_INET;
    // servaddr.sin_port = htons(port);
    // int status = inet_aton(argv[1], &servaddr.sin_addr);
    // if(status < 0) {
    //     perror("inet aton err");
    //     exit(1);
    // }
    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2525);
    int status = inet_aton(argv[1], &servaddr.sin_addr);
    if(status < 0) {
        perror("inet aton err");
        exit(1);
    }

    // // TODO 3: conectati-va la server
    // status = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr));
    // if(status < 0) {
    //     perror("connect err");
    //     exit(1);
    // }
    status = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr));
    if(status < 0) {
        perror("connect err");
        exit(1);
    }

    // // se primeste mesajul de conectare de la server
    // read_line(sockfd, recvbuf, MAXLEN -1);
    // printf("Am primit: %s\n", recvbuf);
    read_line(sockfd, recvbuf, MAXLEN -1);
    printf("Am primit: %s\n", recvbuf);

    // // se trimite comanda de HELO
    // sprintf(sendbuf, "HELO localhost");
    // send_command(sockfd, sendbuf, "250");
    sprintf(sendbuf, "HELO localhost");
    send_command(sockfd, sendbuf, "250");

    // // TODO 4: trimiteti comanda de MAIL FROM
    // bzero(sendbuf, MAXLEN);
    // sprintf(sendbuf, "MAIL FROM: <profesor@upb.ro>");
    // send_command(sockfd, sendbuf, "250");
    sprintf(sendbuf, "AUTH LOGIN");
    send_command(sockfd, sendbuf, "334");

    sprintf(sendbuf, "NDQ2MDU5NzU1NjlkY2Y=");
    send_command(sockfd, sendbuf, "334");

    sprintf(sendbuf, "NzQ3NGFkMjZjZDZiMzE=");
    send_command(sockfd, sendbuf, "235");

    sprintf(sendbuf, "MAIL FROM: <lucian.grigore@upb.ro>");
    send_command(sockfd, sendbuf, "250");

    // // TODO 5: trimiteti comanda de RCPT TO
    // bzero(sendbuf, MAXLEN);
    // sprintf(sendbuf, "RCPT TO: <student@upb.ro>");
    // send_command(sockfd, sendbuf, "250");

    sprintf(sendbuf, "RCPT TO: <valeriu.stanciu@upb.ro>");
    send_command(sockfd, sendbuf, "250");

    // // TODO 6: trimiteti comanda de DATA
    // bzero(sendbuf, MAXLEN);
    // sprintf(sendbuf, "DATA");
    // send_command(sockfd, sendbuf, "354");
    sprintf(sendbuf, "DATA");
    send_command(sockfd, sendbuf, "354");

    // // TODO 7: trimiteti e-mail-ul (antete + corp + atasament)
    // bzero(sendbuf, MAXLEN);
    // strcat(sendbuf, "MIME-Version: 1.0\r\n");
    // strcat(sendbuf, "From: Profu <profesor@upb.ro>\r\n");    
    // strcat(sendbuf, "To: Stud <student@upb.ro>\r\n");
    // strcat(sendbuf, "Subject: Tema\r\n");
    // strcat(sendbuf, "Content-Type: multipart/mixed; boundary=desp\r\n\r\n");
    // strcat(sendbuf, "--desp\r\n");
    // strcat(sendbuf, "Content-Type: text/plain\r\n");
    // strcat(sendbuf, "\r\n");
    // strcat(sendbuf, "Draga student,\r\n");
    // strcat(sendbuf, "\r\n");
    // strcat(sendbuf, "Fa-ti tema!\r\n");
    // strcat(sendbuf, "\r\n");
    // strcat(sendbuf, "Cu bine,\r\n");
    // strcat(sendbuf, "Profesorul.\r\n");
    // strcat(sendbuf, "--desp\r\n");
    // strcat(sendbuf, "Content-Type: text/plain\r\n");
    // strcat(sendbuf, "Content-Disposition: attachment; filename=\"file.txt\"\r\n\r\n");
    // FILE *file = fopen(argv[2], "r");
    // ssize_t read;
    // char *line = NULL;
    // size_t len;

    // while((read = getline(&line, &len, file)) != -1) {
    //     strcat(sendbuf, line);
    // }

    // // strcat(sendbuf, "\r\n");
    // // strcat(sendbuf, "This is an attachment.\r\n\r\n");
    // strcat(sendbuf, "\r\n--desp\r\n");
    // strcat(sendbuf, ".");
    // send_command(sockfd, sendbuf, "250");
    bzero(sendbuf, MAXLEN);
    strcat(sendbuf, "MIME-Version: 1.0\r\n");
    strcat(sendbuf, "From: Grigore Lucian <grigore.lucian@upb.ro>\r\n");    
    strcat(sendbuf, "To: Valeriu Stanciu <valeriu.stanciu@upb.ro>\r\n");
    strcat(sendbuf, "Subject: Laborator E-mail\r\n");
    strcat(sendbuf, "Content-Type: plain/text\r\n\r\nexcursie la kaufland\r\n.");
    send_command(sockfd, sendbuf, "250");

    // // TODO 8: trimiteti comanda de QUIT
    // bzero(sendbuf, MAXLEN);
    // sprintf(sendbuf, "QUIT");
    // send_command(sockfd, sendbuf, "221");
    bzero(sendbuf, MAXLEN);
    sprintf(sendbuf, "QUIT");
    send_command(sockfd, sendbuf, "221");

    // TODO 9: inchideti socket-ul TCP client
    close(sockfd);

    return 0;
}
