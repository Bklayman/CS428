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

// Driver function
int main()
{
    int sockfd, connfd1, connfd2, n;
    socklen_t len;
    struct sockaddr_in servaddr, cli;
		char buff[MAX];

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

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("Socket Bind Error");
        exit(1);
    }

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Server Listen Error");
        exit(1);
    }

    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd1 = accept(sockfd, (SA*)&cli, &len);
    if (connfd1 < 0) {
        printf("Server Accept Error");
        exit(1);
    }

    connfd2 = accept(sockfd, (SA*)&cli, &len);
    if (connfd2 < 0) {
        printf("Server Accept Error");
        exit(1);
    }

    bzero(buff, MAX);

    // read the message from client and copy it in buffer
    read(connfd1, buff, sizeof(buff));

    printf("%s", buff);

    char msg1[MAX];
    char msg2[MAX];

    strcpy(msg1, buff);

    // print buffer which contains the client contents
    bzero(buff, MAX);

    read(connfd2, buff, sizeof(buff));

    printf("%s", buff);

    strcpy(msg2, buff);

    const char* mid = " received before ";
    char final[MAX];
    strcpy(final, msg1);
    strcat(final, mid);
    strcat(final, msg2);

    // and send that buffer to client
    write(connfd1, final, sizeof(final));
    write(connfd2, final, sizeof(final));

    printf("Sent acknowledgement to both X and Y\n");

    // After chatting close the socket
    close(sockfd);
}
