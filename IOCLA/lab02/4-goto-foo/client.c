/* 
 * Description: Simple client implemntation C. Used to illustrate the
 * use of gotos.
 * IOCLA 2019
*/

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdlib.h> 
#define PORT 8080 
   
int main(void) 
{ 
    int sock = 0; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 

    /*
     *  HINT: use the error buffer for signaling errors;
     *        Do not forget to free it in the end
     */

	  char *error_buffer = malloc(100);

    if (error_buffer == NULL)
    {

        /* Your code for malloc error */
			printf("Malloc error.\n");
			goto malloc_error;

    } 

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 

		    /* Your code for socket creation error */
			strcpy(error_buffer, "Socket creation error occured.\n");
			goto exit_error;
        
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 

		    /* Your code for invalid address error */
			strcpy(error_buffer, "Invalid address error occured.\n");
			goto exit_error;
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 

		  /* Your code for connection fail */
			strcpy(error_buffer, "Conncetion fail.\n");
			goto exit_error;
    } 

    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    return 0; 

    /*
    * Label for the error message
    *
    */

exit_error:
		fprintf(stderr, "%s", error_buffer);
		free(error_buffer);
malloc_error:
		
		return EXIT_FAILURE;
} 
