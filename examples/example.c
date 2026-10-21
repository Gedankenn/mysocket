#include "../msocket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 500

void server(char* port);
void client(char* port, char* ip);

//Usage: ./example [server/client] [port] [ip if client]
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: ./example [server/client] [port] [ip]\n");
        exit(EXIT_FAILURE);
    }

    if(strcmp(argv[1], "server") == 0)
    {
        server(argv[2]);
    }
    else if(strcmp(argv[1], "client") == 0)
    {
        client(argv[2], argv[3]);
    }
    else 
    {
        fprintf(stderr, "DAFUQ you wrote\n");
    }
    return EXIT_SUCCESS;
}

void server(char* port)
{
    int buf[BUF_SIZE];
    int nread = 0;
    int sfd = 0;
    char data[BUF_SIZE];
    memset(data,0,BUF_SIZE);

    sfd = create_socket(port);

    while(1)
    {
        nread = socket_read(sfd, buf, BUF_SIZE - 1);
        if (nread <= 0)
        {
            exit(EXIT_SUCCESS);
        }
        memcpy(data,buf,nread);
        if(strcmp(data,"exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("server read %d bytes: %s\n",nread,data);
        }
        memset(data, 0, nread);
    }
}

void client(char* port, char* ip)
{
    int sfd = 0;
    char data[BUF_SIZE];
    memset(data,0,BUF_SIZE);

    sfd = connect_socket(ip, port);
    while(1)
    {
        printf("Escreve caraio: ");
        if (fgets(data, BUF_SIZE, stdin) == NULL)
        {
            break;
        }
        data[strcspn(data, "\n")] = '\0';
        socket_write(sfd, (void*)data, strlen(data));
        if (strcmp(data, "exit") == 0)
        {
            break;
        }
    }
    close(sfd);
    exit(EXIT_SUCCESS);
}
