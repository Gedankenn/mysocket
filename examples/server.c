#include "../msocket.h"

#define BUFF_SIZE 500

int main(int argc, char* argv[])
{
    int                 sfd, s;
    char                buf[BUFF_SIZE];
    size_t              size;
    ssize_t             nread;
    struct addrinfo     hints;
    struct addrinfo     *result, *rp;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addrlen = sizeof(peer_addr);
    (void)size;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family =       AF_UNSPEC;  /* Allow IPv4 or IPv6 */
    hints.ai_socktype =     SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags =        AI_PASSIVE; /* For wildcard IP address */
    hints.ai_protocol =     0;          /* Any protocol */
    hints.ai_canonname =    NULL;
    hints.ai_addr =         NULL;
    hints.ai_next =         NULL;

    s = getaddrinfo(NULL, argv[1], &hints, &result);
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

    if(rp == NULL)
    {
        fprintf(stderr, "Could not bind\n");
        exit(1);
    }

    /* Main logic, reads datagrams and echo back to sender */

    for(;;)
    {
        char host[NI_MAXHOST], service[NI_MAXSERV];

        peer_addrlen = sizeof(peer_addr);
        nread = recvfrom(sfd, buf, BUFF_SIZE, 0, (struct sockaddr *)&peer_addr, &peer_addrlen);

        if(nread == -1)
        {
            continue;
        }

        s = getnameinfo((struct sockaddr *)&peer_addr, peer_addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);
        
        if(s == 0)
        {
            printf("Received %zd bytes from %s:%s | %s\n",nread, host, service, buf);
        }
        else
        {
            fprintf(stderr, "getnameinfo: %s\n",gai_strerror(s));
        }

        if(sendto(sfd, buf, nread, 0, (struct sockaddr *)&peer_addr, peer_addrlen) != nread)
        {
            fprintf(stderr, "Error sending response\n");
        }
    }

}
