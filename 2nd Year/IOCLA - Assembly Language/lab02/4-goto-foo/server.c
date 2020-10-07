/* 
 * Description: Simple server implemntation C. Used to illustrate the
 * use of gotos.
 * IOCLA 2019
*/

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

int main(void) 
{ 
	
    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 

    /*
     *  HINT: use the error buffer for signaling errors;
     *        Do not forget to free it in the end
     *        EXIT_FAILURE and EXIT_SUCCESS are defined in the stdlib
     *        take a look at them and use them accordingaly
     */

    char *error_buffer = (char*)malloc(100);

    if (error_buffer == NULL)
    {
        /* Your code for socker creation error */
		printf("Malloc error.\n");
		goto malloc_error;
		

    } 
       
    /* Creating socket file descriptor */
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 

		    /* Your code for socker creation error */
		strcpy(error_buffer, "Socker creation error.\n");
		goto exit_error;
    } 
       
    /* Forcefully attaching socket to the port 8080 */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    {

		    /* Your code for socket set options error */
		strcpy(error_buffer, "Socket set options error.\n");
		goto exit_error;

    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    /* Forcefully attaching socket to the port 8080 */
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    {

		    /* Your code for invalid bind */
		strcpy(error_buffer, "Invalid bind.\n");
		goto exit_error;

    } 
    if (listen(server_fd, 3) < 0) 
    { 

		    /* Your code for invalid listen */
		strcpy(error_buffer, "Invalid listen. \n");
		goto exit_error;

    } 
	
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 

		    
		strcpy(error_buffer, "Invalid accept.\n");
		goto exit_error;

    } 
	
    read( new_socket , buffer, 1024); 
    printf("%s\n", buffer); 
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    //return 0; 

    /*
     * Label for the error message
     *
     */

exit_error:
	fprintf(stderr, "%s\n", error_buffer);
	free(error_buffer);
malloc_error:
	
	return EXIT_FAILURE;


} 
