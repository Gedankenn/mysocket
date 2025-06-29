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



}

void client(char* port, char* ip)
{

}
