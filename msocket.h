#ifndef __msocket_h_
#define __msocket_h_

#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define IPV6 6
#define IPV4 4


/**
* @Brief initialize socket
* @Params buf buffer size
* @Params type Family type 
* @Params proto Protocol 
*/
void init_socket(int buf, int type, int proto);

/**
* @Brief Create the socket
* @Params port The port to create the socket 
* @Returnn sfd the file descriptor if create or 0 if error
*/
int create_socket(char* port);

/**
* @brief Write to the file descripor for socket 
* @Params sfd file descriptor 
* @Params *data pointer to the data to write 
* @Params size size of the data to write 
*/ 
void socket_write(int sfd, int* data, int size);

/**
* @Brief Read to the file descriptor for the socket 
* @Params sfd file descriptor 
* @Params *data pointer to the read data
* @Returns nread number of bytes read or -1 if error  
*/ 
int socket_read(int sfd, int* data);

/**
* @Brief Connect to a socket 
* @Params host The host address 
* @Params port The port to bind to
*/ 
int connect_socket(char* host, char* port);

#endif //__msocket_h_
