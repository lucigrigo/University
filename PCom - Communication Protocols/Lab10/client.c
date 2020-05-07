#include "helpers.h"
#include "requests.h"
#include <arpa/inet.h>
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <unistd.h>     /* read, write, close */

#define HOST_IP "3.8.116.10"
#define ADDRESS "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com"
#define URL "/api/v1/dummy"

int main(int argc, char *argv[]) {
  char *message;
  char *response;
  int sockfd;

  // Ex 1.1: GET dummy from main server
  sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
  message = compute_get_request(ADDRESS, URL, NULL, NULL, 0);
  send_to_server(sockfd, message);
  response = receive_from_server(sockfd);
  printf("\n--- RESPONSE ---\n%s", response);

  // Ex 1.2: POST dummy and print response from main server
  char **data = (char **)malloc(2 * sizeof(char *));
  char *content_type = "application/x-www-form-urlencoded";
  // contents[0] = (char *)malloc(strlen(content_type));
  // strcpy(contents[0], content_type);
  data[0] = (char *)malloc(10);
  strcpy(data[0], "salut!");
  message = compute_post_request(ADDRESS, URL, content_type, data, 1, NULL, 0);
  send_to_server(sockfd, message);
  bzero(response, strlen(response));
  response = receive_from_server(sockfd);
  printf("\n--- RESPONSE ---\n%s", response);

  // Ex 2: Login into main server
  char **new_data = (char **)malloc(2 * sizeof(char *));
  new_data[0] = (char *)malloc(32);
  strcpy(new_data[0], "username=student");
  new_data[1] = (char *)malloc(32);
  strcpy(new_data[1], "password=student");
  message = compute_post_request(ADDRESS, "/api/v1/auth/login", content_type,
                                 new_data, 2, NULL, 0);
  send_to_server(sockfd, message);
  bzero(response, strlen(response));
  response = receive_from_server(sockfd);
  printf("\n--- RESPONSE ---\n%s", response);

  // Ex 3: GET weather key from main server
  char **cookies = (char **)malloc(2 * sizeof(char *));
  cookies[0] = (char *)malloc(128);
  strcpy(cookies[0], "connect.sid=s%3ANylCmM_DpsRiV7ojh8CSmmCIqqbTKlkI."
                     "252zxpxw8Jbmc%2Bc9Uv%2FzXQmQXf2g1CyZX41XQZTSqxM");
  message =
      compute_get_request(ADDRESS, "/api/v1/weather/key", NULL, cookies, 1);
  send_to_server(sockfd, message);
  bzero(response, strlen(response));
  response = receive_from_server(sockfd);
  printf("\n--- RESPONSE ---\n%s", response);

  // Ex 4: GET weather data from OpenWeather API
  int newsockfd =
      open_connection("188.166.16.132", 80, AF_INET, SOCK_STREAM, 0);
  char *q = (char *)malloc(50);
  char *lat = (char *)malloc(30);
  strcpy(lat, "lat=45.137112&");
  char *lng = (char *)malloc(30);
  strcpy(lng, "lon=26.817112&");
  strcpy(q, "appid=b912dd495585fbf756dc6d8f415a7649");
  char *q_params = (char *)malloc(150);
  bzero(q_params, 150);
  strcat(q_params, lat);
  strcat(q_params, lng);
  strcat(q_params, q);
  message = compute_get_request("api.openweathermap.org", "/data/2.5/weather",
                                q_params, NULL, 0);
  send_to_server(newsockfd, message);
  bzero(response, strlen(response));
  response = receive_from_server(newsockfd);
  printf("\n--- RESPONSE ---\n%s", response);

  // Ex 5: POST weather data for verification to main server
  // Ex 6: Logout from main server

  message = compute_get_request(ADDRESS, "/api/v1/auth/logout", NULL, NULL, 0);
  send_to_server(sockfd, message);
  bzero(response, strlen(response));
  response = receive_from_server(sockfd);
  printf("\n--- RESPONSE ---\n%s", response);

  // BONUS: make the main server return "Already logged in!"

  // free the allocated data at the end!
  close_connection(sockfd);
  return 0;
}
