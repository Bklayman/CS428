#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX 80
#define PORT 8081
#define SA struct sockaddr

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
		char buff[MAX];
		char sent1[MAX];

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Client1: Socket Creation Error\n");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // socket connect and verification
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("Client2: Connect Error\n");
        exit(1);
    }

    // Assign the client name to the buffer and send the buffer to the server
    bzero(buff, sizeof(buff));
    strcpy(buff, "Client Y: Bob");
    strcpy(sent1, buff);
    write(sockfd, buff, sizeof(buff));

    // receive the client connect order from the server, print the original sent message, and print the received message
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("Client Y: %s\n", sent1);
    printf("Client Y: %s\n", buff);

    // close the socket
    close(sockfd);
}
