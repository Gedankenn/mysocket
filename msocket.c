#include "msocket.h"
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>


int BUF_SIZE = 0;
int FAMILY = AF_UNSPEC;
int PROTOCOL = 0;

void init_socket(int buf, int type, int proto)
{
    BUF_SIZE = buf;
    FAMILY = type;
    PROTOCOL = proto;
    if((proto == IPV4 && type == AF_INET6) || (proto == IPV6 && type == AF_INET))
    {
        fprintf(stderr, "Incompatible protocol and family");
        exit(EXIT_FAILURE);
    }
}

int m_getaddrinfo(char* name, char* service, const struct addrinfo* req, struct addrinfo* result)
{
    int s, sfd;
    struct addrinfo* rp;
    s = getaddrinfo(name, service, req,  &result);
    if (s != 0)
    {
        printf("getaddrinfo: %s\n",gai_strerror(s));
        return -1;
    }
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
        {
            continue;
        }
    }

    if (rp != NULL)
    {
        printf("could not create socket\n");
        return -1;
    }
    return sfd;

}

int create_socket(char* port)
{
    int                 sfd, s;
    struct addrinfo     hints;
    struct addrinfo     *result, *rp;

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
    return sfd;
}

int connect_socket(char* host, char* port)
{
    int                 sfd, s;
    struct addrinfo     hints;
    struct addrinfo     *result, *rp;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family     = AF_UNSPEC;    // Allow IPv4 or IPv6
    hints.ai_socktype   = SOCK_DGRAM;   // Datagram socket
    hints.ai_flags      = 0;
    hints.ai_protocol   = 0;            // Any Protocol

    s = getaddrinfo(host, port, &hints, &result);
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
        return -1;
    }
    return sfd;
}

void socket_write(int sfd, void* data, int size)
{
    if(write(sfd, (char*)data, size) != size)
    {
        fprintf(stderr, "failed to write data\n");
    }
}

int socket_read(int sfd, void* data)
{
    char buf[BUF_SIZE];
    int nread = 0;
    nread = read(sfd, buf, BUF_SIZE);
    if (nread == -1)
    {
        fprintf(stderr, "what is the fuck\n");
        return -1;
    }
    memcpy(data, buf, nread);
    return nread;
}
