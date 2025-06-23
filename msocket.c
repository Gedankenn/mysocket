#include "msocket.h"

#define BUF_SIZE 500

int create_socket(char* port)
{
    int                 sfd, s;
    char                buf[BUF_SIZE];
    size_t              size;
    ssize_t             nread;
    struct addrinfo     hints;
    struct addrinfo     *result, *rp;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addrlen = sizeof(peer_addr);
    (void)size;


    memset(&hints, 0, sizeof(hints));
    hints.ai_family =       AF_UNSPEC;  /* Allow IPv4 or IPv6 */
    hints.ai_socktype =     SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags =        AI_PASSIVE; /* For wildcard IP address */
    hints.ai_protocol =     0;          /* Any protocol */
    hints.ai_canonname =    NULL;
    hints.ai_addr =         NULL;
    hints.ai_next =         NULL;

    s = getaddrinfo(NULL, port, &hints, &result);
    if(s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(1);
    }

    /* getaddrinfo() returns a list of address structures.
    * Try each address until we successfully bind(2).
    * If socket(2) (or bind(2)) fails, we close the socket and try next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
        {
            continue;
        }

        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
        {
            break; // Success 
        }
        close(sfd);
    }


    freeaddrinfo(result);
}
