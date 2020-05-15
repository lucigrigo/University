/*
                    Protocoale de Comunicatie
                              Tema 3
                 Client Web. Comunicare cu REST API.
                    Grigore Lucian-Florin 324CD
*/
#include "helpers.h"

// functia care trimite POST request pentru crearea unui cont nou pe server
void server_register(int socketfd, char *username, char *password) {
    // payload-ul request-ului
    char **data = (char **) malloc(2 * sizeof(char *));
    data[0] = (char *) malloc(IDLEN);
    // crearea unei copii a username-ului
    char *username_copy = (char *) malloc(strlen(username));
    memcpy(username_copy, username, strlen(username));
    char *token_usr = strtok(username_copy, "\r\n\t\0");
    // respectarea formatului JSON
    sprintf(data[0], "\"username\":\"%s\"", token_usr);
    data[1] = (char *) malloc(IDLEN);
    // crearea unei copii a parolei
    char *password_copy = (char *) malloc(strlen(password));
    memcpy(password_copy, password, strlen(password));
    char *token_pass = strtok(password_copy, "\r\n\t\0");
    // respectarea formatului JSON
    sprintf(data[1], "\"password\":\"%s\"", token_pass);

    // crearea mesajului POST
    char *msg = compute_post_request(HOST, URL_REGISTER, APP_JSON, data, 2, NULL, 0, NULL, 0);
    // trimiterea la server
    send_to_server(socketfd, msg);
    // golirea buffer-ului
    bzero(msg, BUFLEN);
    // asteptarea raspunsului de la server
    msg = receive_from_server(socketfd);

    // verificarea daca inregistrarea s-a efectuat cu succes
    if(strstr(msg, "Created") != NULL) {
        printf("Inregistrarea a fost efectuata cu succes!\n");
    } else {
        printf("A avut loc o eroare la inregistrare!\n");
    }

    // eliberarea memoriei
    free(data[1]);
    free(data[0]);
    free(data);
    free(username_copy);
    free(password_copy);
    free(msg);
}

// functia care creeaza un POST request pentru login
void server_login(int socketfd, char *username, char *password, char **auth_token) {
    // payload-ul request-ului
    char **data = (char **) malloc(2 * sizeof(char *));
    data[0] = (char *) malloc(IDLEN);
    // crearea unei copii a numelui de utilizator
    char *username_copy = (char *) malloc(strlen(username));
    memcpy(username_copy, username, strlen(username));
    char *token_usr = strtok(username_copy, "\r\n\t\0");
    // respectarea formatului JSON
    sprintf(data[0], "\"username\":\"%s\"", token_usr);
    data[1] = (char *) malloc(IDLEN);
    // crearea unei copii a parolei
    char *password_copy = (char *) malloc(strlen(password));
    memcpy(password_copy, password, strlen(password));
    char *token_pass = strtok(password_copy, "\r\n\t\0");
    // respectarea formatului JSON
    sprintf(data[1], "\"password\":\"%s\"", token_pass);

    // crearea mesajului
    char *msg = compute_post_request(HOST, URL_LOGIN, APP_JSON, data, 2, NULL, 0, NULL, 0);
    // trimiterea la server
    send_to_server(socketfd, msg);
    // golirea buffer-ului
    bzero(msg, BUFLEN);
    // asteptarea raspunsului de la server
    msg = receive_from_server(socketfd);

    // verificarea daca logarea a avut loc cu succes
    if(strstr(msg, "OK") != NULL) {
        printf("Logarea a fost efectuata cu success!\n");
        // extragerea token-ului de autentificare din raspuns
        if(*auth_token == NULL) {
            *auth_token = (char *) malloc(LINELEN);
            char *t = strstr(msg, "Set-Cookie:");
            if(t != NULL) {
                printf("Tokenul de autentificare a fost extras cu success!\n");
                char *tt = strtok(t, " ;");
                tt = strtok(NULL, " ;");
                memcpy(*auth_token, tt, strlen(tt));
            } else {
                printf("A avut loc o eroare la extragerea tokenului de autentificare!\n");
            }
        }
    } else { // daca a avut loc o eroare la procesarea comenzii
        free(username);
        free(password);
        username = NULL;
        password = NULL;
        printf("A avut loc o eroare la login!\n");
        // tratarea erorilor transmise in raspuns
        if(strstr(msg, "No account with this username") != NULL) {
            printf("ID-ul de utilizator introdus nu a fost gasit!\n");
        } else if (strstr(msg, "Credentials are not good") != NULL) {
            printf("Parola introduse nu este corecta!\n");
        }
    }
    
    // eliberarea memoriei
    free(data[1]);
    free(data[0]);
    free(data);
    free(username_copy);
    free(password_copy);
    free(msg);
}

// functia care cere accesul in biblioteca virtuala
void server_enter_lib(int socketfd, char *auth_token, char **lib_token) {
    // daca tokenul JWT a fost obtinut deja pentru sesiunea curenta
    if(*lib_token != NULL) {
        printf("Ati obtinut deja access la biblioteca!\n");
        return;
    }
    // adaugarea tokenului de sesiune pentru login
    char **cookies = (char **) malloc(1 *sizeof(char *));
    cookies[0] = (char *) malloc(strlen(auth_token));
    memcpy(cookies[0], auth_token, strlen(auth_token));

    // crearea mesajului
    char *msg = compute_get_request(HOST, URL_ENTERLIB, NULL, NULL, 0, cookies, 1, 0);
    // trimiterea la server
    send_to_server(socketfd, msg);
    // golirea buffer-ului
    bzero(msg, BUFLEN);
    // asteptarea raspunsului de la server
    msg = receive_from_server(socketfd);
    
    // verificarea daca comanda a fost procesata cu succes
    if(strstr(msg, "OK") != NULL) {
        printf("Accesul in biblioteca obtinut!\n");
        // extragerea si memorarea tokenului JWT
        *lib_token = (char *) malloc(LINELEN);
        char *t = strstr(msg, "\"token\"");
        char *tt = strtok(t, "\":");
        tt = strtok(NULL, "\":");
        memcpy(*lib_token ,tt, strlen(tt));
    } else {
        printf("Accesul in biblioteca NU a fost obtinut!\n");
    }

    // eliberarea memoriei
    free(cookies[0]);
    free(cookies);
    free(msg);
}

// functia care trimite GET request-ul pentru obtinerea tuturor cartilor
void server_get_books(int socketfd, char *lib_token) {
    // verifica daca token-ul JWT nu a fost obtinut inainte
    if(lib_token == NULL) {
        printf("Accesul in biblioteca nu a fost realizat!\n");
        return;
    }
    // adaugarea header-ului cu token-ul JWT
    char **headers = (char **) malloc(1 * sizeof(char *));
    headers[0] = (char *) malloc(LINELEN);
    sprintf(headers[0], "Authorization: Bearer %s", lib_token);

    // crearea mesajului
    char *msg = compute_get_request(HOST, URL_BOOKS, NULL, headers, 1, NULL, 0, 0);
    // trimiterea la server
    send_to_server(socketfd, msg);
    // golirea buffer-ului
    bzero(msg, BUFLEN);
    // asteptarea raspunsului de la server
    msg = receive_from_server(socketfd);

    // verificarea daca comanda a fost procesata cu succes
    if(strstr(msg, "OK") != NULL) {
        printf("Comanda a fost procesata cu success!\n");
        // afisarea cartilor intoarse
        // TODO parse json object list returned
        char *lst = strstr(msg, "[");
        printf("\n===%s===\n", lst);
    } else {
        printf("A avut loc o eroare la procesarea comenzii de catre server!\n");
    }

    // eliberarea memoriei
    free(headers[0]);
    free(headers);
    free(msg);
}

// functia care trimite GET request-ul pentru a obtine doar o carte din biblioteca
void server_get_book(int socketfd, char *lib_token, int bookid) {
    // verifica daca accesul in biblioteca nu a fost realizat inainte
    if(lib_token == NULL) {
        printf("Accesul in biblioteca nu a fost realizat!\n");
        return;
    }
    // adaugarea header-ului cu token-ul JWT
    char **headers = (char **) malloc(1 * sizeof(char *));
    headers[0] = (char *) malloc(LINELEN);
    sprintf(headers[0], "Authorization: Bearer %s", lib_token);
    // crearea url-ului cu id-ul introdus
    char *new_url = (char *) malloc(LINELEN);
    sprintf(new_url, "%s/%d", URL_BOOKS, bookid);

    // crearea request-ului
    char *msg = compute_get_request(HOST, new_url, NULL, headers, 1, NULL, 0, 0);
    // trimiterea la server
    send_to_server(socketfd, msg);
    // golirea buffer-ului
    bzero(msg, BUFLEN);
    // asteptarea raspunsului de la server
    msg = receive_from_server(socketfd);

    // verificarea daca comanda a fost procesata cu succes
    if(strstr(msg, "OK") != NULL) {
        printf("Cartea a fost gasita!\n");
        // afisarea cartii intoarse
        // TODO parse json object returned
        char *lst = strstr(msg, "{");
        printf("\n===%s===\n", lst);
    } else {
        printf("A avut loc o eroare la procesarea comenzii de catre server!\n");
        // verificarea daca cartea cu id-ul introdus nu a fost gasita
        if(strstr(msg, "Not Found") != NULL) {
            printf("Cartea cu id-ul introdus nu a fost gasita!\n");
        }
    }

    // eliberarea memoriei
    free(headers[0]);
    free(headers);
    free(msg);
}

// functia care creeaza POST request-ul in care se adauga o carte la biblioteca
void server_add_book(int socketfd, char *lib_token, char *title, char *author,
                    char *genre, char *publisher, int page_count) {
    // verificarea daca accesul in biblioteca nu a fost efectuat inainte
    if(lib_token == NULL) {
        printf("Accesul in biblioteca nu a fost realizat!\n");
        return;
    }
    // adaugarea header-ului cu token-ul JWT
    char **headers = (char **) malloc(1 * sizeof(char *));
    headers[0] = (char *) malloc(LINELEN);
    sprintf(headers[0], "Authorization: Bearer %s", lib_token);

    // adaugarea in payload a informatiilor despre carte
    char **data = (char **) malloc(5 * sizeof(char *));
    data[0] = (char *) malloc(LINELEN);
    sprintf(data[0], "\"title\":\"%s\"", strtok(title, "\n"));
    data[1] = (char *) malloc(LINELEN);
    sprintf(data[1], "\"author\":\"%s\"", strtok(author, "\n"));
    data[2] = (char *) malloc(LINELEN);
    sprintf(data[2], "\"genre\":\"%s\"", strtok(genre, "\n"));
    data[3] = (char *) malloc(LINELEN);
    sprintf(data[3], "\"page_count\":%d", page_count);
    data[4] = (char *) malloc(LINELEN);
    sprintf(data[4], "\"publisher\":\"%s\"", strtok(publisher, "\n"));
    
    // crearea mesajului
    char *msg = compute_post_request(HOST, URL_BOOKS, APP_JSON, data, 5, NULL, 0, headers, 1);
    // trimiterea catre server
    send_to_server(socketfd, msg);
    // golirea buffer-ului
    bzero(msg, BUFLEN);
    // asteptarea raspunsului de la server
    msg = receive_from_server(socketfd);

    // verificarea daca comanda a fost procesata cu succes
    if(strstr(msg, "OK") != NULL) {
        printf("Cartea a fost adaugata cu success!\n");
    } else {
        printf("A avut loc o eroare la procesarea comenzii de catre server!\n");
    }

    // eliberarea memoriei
    int i;
    for(i = 0; i < 5; ++i)
        free(data[i]);
    free(data);
    free(headers[0]);
    free(headers);
    free(msg);
}

// functia care trimite DELETE request-ul pentru a sterge o carte
void server_del_book(int socketfd, char *lib_token, int bookid) {
    // verifica daca accesul in biblioteca nu s-a efectuat inainte
    if(lib_token == NULL) {
        printf("Accesul in biblioteca nu a fost realizat!\n");
        return;
    }
    // adaugarea header-ului cu token-ul JWT
    char **headers = (char **) malloc(1 * sizeof(char *));
    headers[0] = (char *) malloc(LINELEN);
    sprintf(headers[0], "Authorization: Bearer %s", lib_token);
    // crearea noului url cu id-ul introdus al cartii
    char *new_url = (char *) malloc(LINELEN);
    sprintf(new_url, "%s/%d", URL_BOOKS, bookid);

    // crearea mesajului
    char *msg = compute_get_request(HOST, new_url, NULL, headers, 1, NULL, 0, 1);
    // trimiterea la server
    send_to_server(socketfd, msg);
    // golirea buffer-ului
    bzero(msg, BUFLEN);
    // asteptarea raspunsului de la server
    msg = receive_from_server(socketfd);

    // verifica daca stergerea cartii a avut loc cu succes
    if(strstr(msg, "OK") != NULL) {
        printf("Cartea a fost stearsa cu success!\n");
    } else {
        printf("A avut loc o eroare la procesarea comenzii de catre server!\n");
        // verifica daca cartea nu a fost gasita
        if(strstr(msg, "Not Found") != NULL) {
            printf("Cartea cu id-ul introdus nu a fost gasita!\n");
        }
    }

    // eliberarea memoriei
    free(headers[0]);
    free(headers);
    free(msg);
}

// functia care trimite GET request-ul pentru delogarea unui utilizator
void server_logout(int socketfd, char *auth_token) {
    // adaugarea tokenului de sesiune
    char **cookies = (char **) malloc(1 *sizeof(char *));
    cookies[0] = (char *) malloc(strlen(auth_token));
    memcpy(cookies[0], auth_token, strlen(auth_token));

    // crearea mesajului
    char *msg = compute_get_request(HOST, URL_LOGOUT, NULL, NULL, 0, cookies, 1, 0);
    // trimiterea la server
    send_to_server(socketfd, msg);
    // golirea buffer-ului
    bzero(msg, BUFLEN);
    // asteptarea raspunsului
    msg = receive_from_server(socketfd);

    // daca delogarea s-a realizat cu succes
    if(strstr(msg, "OK") != NULL) {
        printf("Ati fost delogat cu success!\n");
    } else {
        printf("A avut loc o eroare la procesarea comenzii de catre server!\n");
    }

    // eliberarea memoriei
    free(cookies[0]);
    free(cookies);
    free(msg);
}

// functia care parseaza input-ul de la STDIN al utilizatorului
COMMAND parse_input(char *buf, int buflen) {
    if(strncmp(buf, "exit", 4) == 0) {
        return CMD_EXIT;
    } else if(strncmp(buf, "register", 8) == 0) {
        return CMD_REGISTER;
    } else if(strncmp(buf, "login", 5) == 0) {
        return CMD_LOGIN;
    } else if(strncmp(buf, "enter_library", 13) == 0) {
        return CMD_ENTERLIB;
    } else if(strncmp(buf, "get_books", 9) == 0) {
        return CMD_GETBOOKS;
    } else if(strncmp(buf, "get_book", 8) == 0) {
        return CMD_GETBOOK;
    } else if(strncmp(buf, "add_book", 8) == 0) {
        return CMD_ADDBOOK;
    } else if(strncmp(buf, "delete_book", 11) == 0) {
        return CMD_DELBOOK;
    } else if(strncmp(buf, "logout", 6) == 0) {
        return CMD_LOGOUT;
    } else {
        return CMD_ERR;
    }
}

// functia care deschide o conexiune cu serverul
int open_connection() {
    // crearea socketului de conectare
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd < 0) {
        perror("socket err");
        exit(1);
    }

    // datele despre server
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_aton(HOST_IP, &server_addr.sin_addr);

    // conectarea la server
    int ret = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret < 0) {
        perror("connect to server err");
        exit(1);
    }
    
    // descriptorul socketului care comunica cu serverul
    return socketfd;
}

int main() 
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int socketfd = -1;
  
    // interactionarea cu utilizatorul
    char buffer[BUFLEN];
    bzero(buffer, BUFLEN);
    COMMAND user_cmd;
    char *username = NULL;
    char *password = NULL;
    int bookid = -1;
    char *auth_token = NULL;
    char *lib_token = NULL;

    printf("-> Introduceti comanda dorita:");
    while(read(STDIN_FILENO, buffer, BUFLEN - 1)) { // citirea comenzii introduse
        printf("Comanda primita:%s", buffer);
        // parsarea input-ului
        user_cmd = parse_input(buffer, strlen(buffer));
        
        if(user_cmd == CMD_ERR) { // daca input-ul introdus nu este o comanda valida 
            printf("Comanda invalida!\n");
        } else if(user_cmd == CMD_EXIT) { // daca programul a primit comanda de inchidere
            if(auth_token != NULL && socketfd != -1) { // delogarea, daca este cazul
                socketfd = open_connection();
                server_logout(socketfd, auth_token);
            }
            break;
        } else if(user_cmd == CMD_LOGOUT) { // executarea comenzii de delogare
            if(username == NULL) { // daca utilizatorul nu este logat
                printf("Nu sunteti logat!\n");
            } else {
                // delogarea de la server
                socketfd = open_connection();
                server_logout(socketfd, auth_token);
                // restaurarea valorilor default pentru token-uri si credentiale
                free(username);
                free(password);
                free(auth_token);
                free(lib_token);
                username = NULL;
                password = NULL;
                auth_token = NULL;
                lib_token = NULL;
            }
        } else {
            // verifica daca utilizatorul doreste sa execute o comanda fara a fi logat
            if(username == NULL && user_cmd != CMD_REGISTER && user_cmd != CMD_LOGIN) {
                printf("Trebuie sa fiti inregistrati si sa va logati pe server!\n");
            } else {
                if(user_cmd == CMD_REGISTER) { // executarea inregistrarii
                    // citirea numelui de utilizator
                    username = (char *) malloc(IDLEN);
                    printf("Introduce numele de utilizator:");
                    int bytes_read = read(STDIN_FILENO, username, IDLEN - 1);
                    if(bytes_read < 0) {
                        perror("username error");
                    }

                    // citirea parolei
                    password = (char *) malloc(IDLEN);
                    printf("Introduceti parola:");
                    bytes_read = read(STDIN_FILENO, password, IDLEN - 1);
                    if(bytes_read < 0) {
                        perror("password error");
                    }

                    // trimiterea inregistrarii la server
                    socketfd = open_connection();
                    server_register(socketfd, username, password);
                }
                if(user_cmd == CMD_LOGIN) { // executarea login-ului
                    if(auth_token != NULL) { // daca utilizatorul este autentificat deja
                        printf("Sunteti deja autentificat!\n");
                    } else {
                        // citirea numelui de utilizator
                        username = (char *) malloc(IDLEN);
                        printf("Introduce numele de utilizator:");
                        int bytes_read = read(STDIN_FILENO, username, IDLEN - 1);
                        if(bytes_read < 0) {
                            perror("username error");
                        }

                        // citirea parolei
                        password = (char *) malloc(IDLEN);
                        printf("Introduceti parola:");
                        bytes_read = read(STDIN_FILENO, password, IDLEN - 1);
                        if(bytes_read < 0) {
                            perror("password error");
                        }

                        // logarea la server
                        socketfd = open_connection();
                        server_login(socketfd, username, password, &auth_token);
                    }
                }
                if(user_cmd == CMD_ENTERLIB) { // obtinerea accesului la biblioteca
                    socketfd = open_connection();
                    server_enter_lib(socketfd, auth_token, &lib_token);
                }
                if(user_cmd == CMD_GETBOOKS) { // obtinerea tuturor cartilor din biblioteca
                    socketfd = open_connection();
                    server_get_books(socketfd, lib_token);
                }
                if(user_cmd == CMD_GETBOOK) { // obtinerea unei singure carti din biblioteca
                    // citirea id-ului cartii
                    bzero(buffer, BUFLEN);
                    printf("Introduceti id-ul cartii dorite:");
                    int bytes_read = read(STDIN_FILENO, buffer, BUFLEN - 1);
                    if(bytes_read < 0) {
                        perror("book id error");
                    }
                    bookid = atoi(buffer);

                    // trimiterea cererii spre server
                    socketfd = open_connection();
                    server_get_book(socketfd, lib_token, bookid);
                }
                if(user_cmd == CMD_ADDBOOK) { // adaugarea unei noi carti in biblioteca
                    char *title = (char *) malloc(LINELEN);
                    char *author = (char *) malloc(LINELEN);
                    char *genre = (char *) malloc(LINELEN);
                    char *publisher = (char *) malloc(LINELEN);
                    char *page_count_str = (char *) malloc(LINELEN);

                    // citirea titlului
                    printf("Introduceti titlul cartii:");
                    int bytes_read = read(STDIN_FILENO, title, LINELEN - 1);
                    if(bytes_read < 0) {
                        perror("book title error");
                    }
                    
                    // citirea autorului
                    printf("Introduceti autorul cartii:");
                    bytes_read = read(STDIN_FILENO, author, LINELEN - 1);
                    if(bytes_read < 0) {
                        perror("book author error");
                    }
                    
                    // citirea genului
                    printf("Introduceti genul cartii:");
                    bytes_read = read(STDIN_FILENO, genre, LINELEN - 1);
                    if(bytes_read < 0) {
                        perror("book genre error");
                    }
                    
                    // citirea editorului
                    printf("Introduceti publisher-ul cartii:");
                    bytes_read = read(STDIN_FILENO, publisher, LINELEN - 1);
                    if(bytes_read < 0) {
                        perror("book publisher error");
                    }
                    
                    // citirea numarului de pagini
                    printf("Introduceti numarul de pagini:");
                    bytes_read = read(STDIN_FILENO, page_count_str, LINELEN - 1);
                    if(bytes_read < 0) {
                        perror("book page count error");
                    }
                    int page_count = atoi(page_count_str);

                    // trimiterea cererii catre server
                    socketfd = open_connection();
                    server_add_book(socketfd, lib_token, title, author, genre, publisher, page_count);
                }
                if(user_cmd == CMD_DELBOOK) { // stergerea unei carti din biblioteca
                    // citirea id-ului
                    bzero(buffer, BUFLEN);
                    printf("Introduceti id-ul cartii dorite:");
                    int bytes_read = read(STDIN_FILENO, buffer, IDLEN - 1);
                    if(bytes_read < 0) {
                        perror("book id error");
                    }
                    bookid = atoi(buffer);

                    // trimiterea cererii catre server
                    socketfd = open_connection();
                    server_del_book(socketfd, lib_token, bookid);
                }
            }
        }
   
        // golirea buffer-ului si asteptarea comenzii urmatoare
        bzero(buffer, BUFLEN);
        printf("-> Introduceti comanda dorita:");
    }

    // inchiderea conexiunii cu serverul
    if(socketfd != -1) {
      close(socketfd);
      printf("Conexiunea cu serverul a fost inchisa.\n");
    } else {
        printf("Conexiunea cu serverul nu a fost deschisa!\n");
    }
  
    // eliberarea memoriei
    if(username != NULL) {
        free(username);
    }
    if(password != NULL) {
        free(password);
    }
    return 0;
}
