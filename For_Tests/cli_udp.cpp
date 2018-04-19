/**
 *  Компиляция:
 *      make udp
 *  или
 *      gcc -W -Wall cli_udp.c -o cli_udp
 *      gcc -W -Wall ser_udp.c -o ser_udp
 *
 *  Запуск:
 *      В отдельных консолях (терминалах) запускается один сервер
 *          ./ser_udp
 *      и несколько клиентов
 *          ./cli_udp
 *
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>


#define  SERVER_PORT    5556
#define  SERVER_NAME   "127.0.0.1"
#define  BUFLEN         512
#define  NCOPY          5


int main(void)
{
    int sock;
    int nbytes, i, err;
	unsigned int  size;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    struct hostent *hostinfo;
    char   buf[BUFLEN];

    
    hostinfo = gethostbyname(SERVER_NAME);
    if ( hostinfo==NULL ) {
        fprintf (stderr, "Unknown host %s.\n",SERVER_NAME);
        exit (EXIT_FAILURE);
    }

    server_addr.sin_family = hostinfo->h_addrtype;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(struct in_addr*) hostinfo->h_addr;

    sock = socket(AF_INET,SOCK_DGRAM,0);
    if ( sock<0 ) {
        perror ("Client: socket was not created");
        exit (EXIT_FAILURE);
    }

    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(0);
    err = bind(sock, (struct sockaddr*)&client_addr, sizeof(client_addr));
    if ( err<0 ) {
        perror ("Client: cannot bind socket");
        exit (EXIT_FAILURE);
    }

    fprintf(stdout,"Client: ready to send your message >");
    fgets(buf,BUFLEN,stdin);
    size = strlen(buf);
    for(i=0; i<NCOPY; i++) {
        sprintf(buf+size,"  (copy %d) ",i);
        fprintf(stdout,"sending %s\n",buf);
        nbytes = sendto(sock,buf, strlen(buf)+1, 0,
                    (struct sockaddr*)&server_addr,
                    sizeof(server_addr));
        if( nbytes<0 ) {
            fprintf(stderr,"Client: cannot send data copy %d\n",i);
            perror("Client");
            close(sock);
            exit (EXIT_FAILURE);
        }
    }

    fprintf(stdout,"getting server's replay\n");
    fcntl(sock,F_SETFL,O_NONBLOCK);
    for (i=0;i<NCOPY+2;i++) {
        sleep(1);
        size = sizeof(server_addr);
        nbytes = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&server_addr, &size);
        if( nbytes<0 ) {
            perror ("Client: read failure");
            continue;
        } else if ( nbytes==0 ) {
            fprintf(stdout,"The end\n");
            break;
        }
        fprintf(stdout,"%d bytes in replay: %s\n",nbytes,buf);
    }

    return 0;
}
