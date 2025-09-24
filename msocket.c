#include "msocket.h"
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int create_socket(char* port)
{
    int sfd;
    int cfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        perror("Failed to create socket\n");
        return SOCKET_ERROR;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = *port;
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (bind(sfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) < 0)
    {
        perror("Failed to bind\n");
        close(sfd);
        return SOCKET_ERROR;
    }

    printf("Socket successfully created and bound to 0.0.0.0:%s\n",port);

    if (listen(sfd, 1) < 0)
    {
        perror("Failed to listen to socket\n");
        return SOCKET_ERROR;
    }

    printf("Socket listening...\n");

    cfd = accept(sfd, (struct sockaddr *)&client_addr, &client_len);
    if (cfd < 0)
    {
        perror("Accept failed\n");
        return SOCKET_ERROR;
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
    printf("Client connected from %s:%d\n", client_ip, ntohs(client_addr.sin_port));

    return cfd;
}

int connect_socket(char* host, char* port)
{
    int sfd;
    struct sockaddr_in server_addr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        perror("Failed to create socket\n");
        return SOCKET_ERROR;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = *port;
    server_addr.sin_addr.s_addr = inet_addr(host);

    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0)
    {
        perror("Invalid address\n");
        return SOCKET_ERROR;
    }

    if (connect(sfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) < 0)
    {
        perror("Failed to connect\n");
        close(sfd);
        return SOCKET_ERROR;
    }

    printf("Socket successfully connected to %s:%s\n", host, port);

    return sfd;
}

int socket_write(int sfd, void* data, int size)
{
    int nwrite = 0;
    nwrite = send(sfd, data, size, 0);
    if(nwrite != size)
    {
        fprintf(stderr, "Failed to write data to socket\n");
        return -1;
    }
    return nwrite;
}

int socket_read(int sfd, void* data, int buf_size)
{
    char buf[buf_size];
    int nread = 0;
    nread = recv(sfd, buf, buf_size, 0);
    if (nread == -1 || nread > buf_size)
    {
        fprintf(stderr, "Failed to read data from socket\n");
        return -1;
    }
    memcpy(data, buf, nread);
    return nread;
}
