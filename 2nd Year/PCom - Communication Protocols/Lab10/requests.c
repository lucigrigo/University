#include "requests.h"
#include "helpers.h"
#include <arpa/inet.h>
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdio.h>
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>     /* read, write, close */

char *compute_get_request(char *host, char *url, char *query_params,
                          char **cookies, int cookies_count) {
  char *message = calloc(BUFLEN, sizeof(char));
  char *line = calloc(LINELEN, sizeof(char));

  // Step 1: write the method name, URL, request params (if any) and protocol
  // type
  if (query_params != NULL) {
    sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
  } else {
    sprintf(line, "GET %s HTTP/1.1", url);
  }
  compute_message(message, line);

  // Step 2: add the host
  bzero(line, LINELEN);
  if (host == NULL) {
    perror("host name null\n");
    exit(1);
  }
  sprintf(line, "Host: %s", host);
  compute_message(message, line);

  // Step 3 (optional): add headers and/or cookies, according to the protocol
  // format
  if (cookies != NULL) {
    bzero(line, LINELEN);
    int i;
    sprintf(line, "Cookie: ");
    for (i = 0; i < cookies_count; ++i) {
      char *cookie = cookies[i];
      strcat(line, cookie);
      if (i != (cookies_count - 1)) {
        strcat(line, "; ");
      }
    }
    compute_message(message, line);
  }

  // Step 4: add final new line
  compute_message(message, "");
  printf("\n--- MESSAGE ---\n%s\n", message);
  return message;
}

char *compute_post_request(char *host, char *url, char *content_type,
                           char **body_data, int body_data_fields_count,
                           char **cookies, int cookies_count) {
  char *message = calloc(BUFLEN, sizeof(char));
  char *line = calloc(LINELEN, sizeof(char));
  char *body_data_buffer = calloc(LINELEN, sizeof(char));

  // Step 1: write the method name, URL and protocol type
  sprintf(line, "POST %s HTTP/1.1", url);
  compute_message(message, line);

  // Step 2: add the host
  bzero(line, LINELEN);
  if (host == NULL) {
    perror("host name null\n");
    exit(1);
  }
  sprintf(line, "Host: %s", host);
  compute_message(message, line);

  /* Step 3: add necessary headers (Content-Type and Content-Length are
     mandatory) in order to write Content-Length you must first compute the
     message size
  */
  bzero(line, LINELEN);
  sprintf(line, "Content-Type: %s", content_type);
  compute_message(message, line);

  // Step 4 (optional): add cookies
  if (cookies != NULL) {
    bzero(line, LINELEN);
    int i;
    sprintf(line, "Cookie: ");
    for (i = 0; i < cookies_count; ++i) {
      char *cookie = cookies[i];
      strcat(line, cookie);
      if (i != (cookies_count - 1)) {
        strcat(line, "; ");
      }
    }
  }
  char *s = (char *)malloc(strlen(line));
  strcpy(s, line);

  // Step 5: add new line at end of header

  // Step 6: add the actual payload data
  // memset(line, 0, LINELEN);
  int i;
  bzero(body_data_buffer, LINELEN);
  for (i = 0; i < body_data_fields_count; ++i) {
    strcat(body_data_buffer, body_data[i]);
    if (i != (body_data_fields_count - 1)) {
      strcat(body_data_buffer, "&");
    }
  }
  bzero(line, LINELEN);
  int len = strlen(body_data_buffer);
  sprintf(line, "Content-length: %d", len);
  compute_message(message, line);
  compute_message(message, "");
  compute_message(message, body_data_buffer);

  free(line);
  return message;
}
