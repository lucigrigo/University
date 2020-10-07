#include "helpers.h"

// functie care creeaza un GET / DELETE request
char *compute_get_request(char *host, char *url, char *query_params, char **headers, int headers_count,
                          char **cookies, int cookies_count, int toDelete) {
    // alocarea memoriei
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // adaugarea parametrilor de request, daca exista
    // si verificarea daca cererea trebuie sa fie de tip DELETE
    if (query_params != NULL) {
        if(toDelete == 1) {
            sprintf(line, "DELETE %s?%s HTTP/1.1", url, query_params);
        } else {
            sprintf(line, "GET %s?%s HTTP/1.1", url, query_params);
        }
    } else {
        if(toDelete == 1) {
            sprintf(line, "DELETE %s HTTP/1.1", url);
        } else {
            sprintf(line, "GET %s HTTP/1.1", url);
        }
    }
    compute_message(message, line);

    // adaugarea hostului
    bzero(line, LINELEN);
    if (host == NULL) {
        perror("host name null\n");
        exit(1); 
    }
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // adaugarea oricaror headere aditionale
    if(headers != NULL) {
        int i;
        for(i = 0; i < headers_count; ++i) {
            bzero(line, LINELEN);
            memcpy(line, headers[i], strlen(headers[i]));
            compute_message(message, line);
        }
    }
    
    // adaugarea cookiurilor
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

    // terminarea mesajului cu CRLF
    compute_message(message, "");
    return message;
}

// functie care creeaza un POST request
char *compute_post_request(char *host, char *url, char *content_type,
                            char **body_data, int body_data_fields_count,
                            char **cookies, int cookies_count,
                            char **headers, int headers_count) {
    // alocarea memoriei
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    char *body_data_buffer = calloc(LINELEN, sizeof(char));

    // adaugarea URL-ului
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    // adaugarea hostului
    bzero(line, LINELEN);
    if (host == NULL) {
        perror("host name null\n");
        exit(1);
    }
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // setarea tipului de date
    bzero(line, LINELEN);
    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);

    // adaugarea oricaror headere aditionale
    if(headers != NULL) {
        int i;
        for(i = 0; i < headers_count; ++i) {
            bzero(line, LINELEN);
            memcpy(line, headers[i], strlen(headers[i]));
            compute_message(message, line);
        }
    }
    
    // adaugarea cookiurilor
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

    // crearea segmentului de date
    int i;
    bzero(body_data_buffer, LINELEN);
    strcat(body_data_buffer, "{");
    for (i = 0; i < body_data_fields_count; ++i) {
        strcat(body_data_buffer, body_data[i]);
        if (i != (body_data_fields_count - 1)) {
        strcat(body_data_buffer, ", ");
        }
    }
    strcat(body_data_buffer, "}");
    bzero(line, LINELEN);
    int len = strlen(body_data_buffer);
    
    // adaugarea lungimii segmentului de date
    sprintf(line, "Content-Length: %d", len);
    compute_message(message, line);
    compute_message(message, "");
    
    // adaugarea datelor
    compute_message(message, body_data_buffer);

    free(line);
    return message;
}

void send_to_server(int sockfd, char *message)
{
    int bytes, sent = 0;
    int total = strlen(message);

    do
    {
        bytes = write(sockfd, message + sent, total - sent);
        if (bytes < 0) {
            perror("ERROR writing message to socket");
        }

        if (bytes == 0) {
            break;
        }

        sent += bytes;
    } while (sent < total);
}

char *receive_from_server(int sockfd)
{
    char response[BUFLEN];
    buffer buffer = buffer_init();
    int header_end = 0;
    int content_length = 0;

    do {
        int bytes = read(sockfd, response, BUFLEN);

        if (bytes < 0){
            perror("ERROR reading response from socket");
        }

        if (bytes == 0) {
            break;
        }

        buffer_add(&buffer, response, (size_t) bytes);
        
        header_end = buffer_find(&buffer, HEADER_TERMINATOR, HEADER_TERMINATOR_SIZE);

        if (header_end >= 0) {
            header_end += HEADER_TERMINATOR_SIZE;
            
            int content_length_start = buffer_find_insensitive(&buffer, CONTENT_LENGTH, CONTENT_LENGTH_SIZE);
            
            if (content_length_start < 0) {
                continue;           
            }

            content_length_start += CONTENT_LENGTH_SIZE;
            content_length = strtol(buffer.data + content_length_start, NULL, 10);
            break;
        }
    } while (1);
    size_t total = content_length + (size_t) header_end;
    
    while (buffer.size < total) {
        int bytes = read(sockfd, response, BUFLEN);

        if (bytes < 0) {
            perror("ERROR reading response from socket");
        }

        if (bytes == 0) {
            break;
        }

        buffer_add(&buffer, response, (size_t) bytes);
    }
    buffer_add(&buffer, "", 1);
    return buffer.data;
}

void compute_message(char *message, const char *line)
{
    strcat(message, line);
    strcat(message, "\r\n");
}
