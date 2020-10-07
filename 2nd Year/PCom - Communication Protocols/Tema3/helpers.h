#ifndef _HELPERS_
#define _HELPERS_

// bibliotecile utilizate
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include "buffers.h"
#include "parson.h"

// datele despre server
#define HOST "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com"
#define HOST_IP "3.8.116.10"
#define PORT 8080

// tipul de content 
#define APP_JSON "application/json"

// URL-urile server-ului care vor fi utilizate
#define URL_REGISTER "/api/v1/tema/auth/register"
#define URL_LOGIN "/api/v1/tema/auth/login"
#define URL_ENTERLIB "/api/v1/tema/library/access"
#define URL_BOOKS "/api/v1/tema/library/books"
#define URL_LOGOUT "/api/v1/tema/auth/logout"

// macro-uri despre dimensiunile buffer-elor
#define BUFLEN 8192
#define LINELEN 500
#define IDLEN 100

// macro-uri despre tipurile de comenzi pasate de la utilizator
#define COMMAND int

#define CMD_ERR -1
#define CMD_EXIT 0
#define CMD_REGISTER 1
#define CMD_LOGIN 2
#define CMD_ENTERLIB 3
#define CMD_GETBOOKS 4
#define CMD_GETBOOK 5
#define CMD_ADDBOOK 6
#define CMD_DELBOOK 7
#define CMD_LOGOUT 8

// macro-uri despre crearea header-elor
#define HEADER_TERMINATOR "\r\n\r\n"
#define HEADER_TERMINATOR_SIZE (sizeof(HEADER_TERMINATOR) - 1)
#define CONTENT_LENGTH "Content-Length: "
#define CONTENT_LENGTH_SIZE (sizeof(CONTENT_LENGTH) - 1)

// creeaza mesajul pentru un GET request (sau DELETE)
char *compute_get_request(char *host, char *url, char *query_params, char **headers, int headers_count,
                          char **cookies, int cookies_count, int toDelete);

// creeaza mesajul pentru un POST request
char *compute_post_request(char *host, char *url, char *content_type,
                            char **body_data, int body_data_fields_count,
                            char **cookies, int cookies_count,
                            char **headers, int headers_count);

// trimite un mesaj la server
void send_to_server(int sockfd, char *message);

// primeste un mesaj de la server
char *receive_from_server(int sockfd);

// adauga o linie la un mesaj
void compute_message(char *message, const char *line);

#endif
