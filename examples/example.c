#include "../msocket.h"
#include <stdlib.h>
#include <sys/socket.h>

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

    init_socket(BUF_SIZE, AF_UNSPEC, 0);

    if(strcmp(argv[1], "server") == 0)
    {
        server(argv[2]);
    }
    else if(strcmp(argv[2], "client") == 0)
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

    init_socket(BUF_SIZE, AF_INET6, IPV6);

    sfd = create_socket(port);

    while(1)
    {
        nread = socket_read(sfd,buf);
        memcpy(data,buf,nread);
        if(strcmp(data,"exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("server read: %s\n",data);
        }
    }
}

void client(char* port, char* ip)
{
    int nread = 0;
    int sfd = 0;
    char data[BUF_SIZE];
    memset(data,0,BUF_SIZE);

    sfd = bind_socket(ip, port);
    while(1)
    {
        printf("Escreve caraio: ");
        scanf("%s", data);
        socket_write(sfd, (int*)data,nread);
    }
}
