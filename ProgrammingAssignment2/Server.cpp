#include <cstring>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 80
#define PORT 8081
#define SA struct sockaddr

int main()
{
    //Initialize all needed variables for the server
    int sockfd, connfd1, connfd2;
    socklen_t len;
    struct sockaddr_in servaddr, cli;
		char buff[MAX];
    char final[MAX];
    char msg1[MAX];
    char msg2[MAX];
    const char* mid = " received before ";

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket Creation Error");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // socket binding and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket Bind Error");
        exit(1);
    }

    // socket listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Server Listen Error");
        exit(1);
    }

    len = sizeof(cli);

    // accept the first client and verification
    connfd1 = accept(sockfd, (SA*)&cli, &len);
    if (connfd1 < 0) {
        printf("Server Accept Error");
        exit(1);
    }

    // accept the second client and verification
    connfd2 = accept(sockfd, (SA*)&cli, &len);
    if (connfd2 < 0) {
        printf("Server Accept Error");
        exit(1);
    }

    bzero(buff, MAX);

    // read the first client's message, save the message to msg1, and empty the buffer
    read(connfd1, buff, sizeof(buff));
    printf("Server: %s\n", buff);
    strcpy(msg1, buff);
    bzero(buff, MAX);

    // read the second client's message, save the message to msg1, and empty the buffer
    read(connfd2, buff, sizeof(buff));
    printf("Server: %s\n", buff);
    strcpy(msg2, buff);

    // create the string to send back to the clients detailing the order the clients were received in
    const char* mid = " received before ";
    char final[MAX];
    strcpy(final, msg1);
    strcat(final, mid);
    strcat(final, msg2);

    // send the string of the received order to both clients
    write(connfd1, final, sizeof(final));
    write(connfd2, final, sizeof(final));

    printf("Server: Sent acknowledgement to both X and Y\n");

    close(sockfd);
}
