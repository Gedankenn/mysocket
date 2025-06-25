#include "../msocket.h"
#include <netdb.h>
#include <sys/socket.h>

#define BUF_SIZE 500

int main(int argc, char* argv[])
{
    int              sfd, s;
    char             buf[BUF_SIZE];
    size_t           size;
    ssize_t          nread;
    struct addrinfo  hints;
    struct addrinfo  *result, *rp;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;    // Allow IPv4 or IPv6
    hints.ai_socktype   = SOCK_DGRAM;   // Datagram socket
    hints.ai_flags      = 0;
    hints.ai_protocol   = 0;            // Any Protocol

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n",gai_strerror(s));
        exit(1);
    }

    /* getaddinfo() returns a list of address structures.
    * Try each address until we successfully connect(2). */

    for(rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
        {
            continue;
        }
        if(connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
        {
            break; //Success
        }

        close(sfd);
    }

    freeaddrinfo(result);

    if (rp == NULL)
    {
        fprintf(stderr, "Could not connect\n");
        exit(1);
    }

    for(size_t j = 3; j < argc; j++)
    {
        size = strlen(argv[j]) + 1;

        if (size > BUF_SIZE)
        {
            fprintf(stderr, "ignore long message in argument %zu\n",j);
            continue;
        }
        if(write(sfd, argv[j], size) != size)
        {
            fprintf(stderr, "partial/failed write\n");
            exit(1);
        }

        nread = read(sfd, buf, BUF_SIZE);
        if(nread == -1)
        {
            perror("read");
            exit(1);
        }

        printf("Received %zu bytes: %s\n",nread,buf);
    }
    exit(0);
}


