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
    int sockfd, connfd, n;
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
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("Server Accept Error");
        exit(1);
    }

    bzero(buff, MAX);

    // read the message from client and copy it in buffer
    read(connfd, buff, sizeof(buff));
    // print buffer which contains the client contents
    bzero(buff, MAX);
    n = 0;
    strcpy(buff, "X: Alice Received\n");

    // and send that buffer to client
    write(connfd, buff, sizeof(buff));

    printf("Sent acknowledgement to X\n");

    // After chatting close the socket
    close(sockfd);
}
