// UDP Pinger

// Must have this server running before you can run the UDP Pinger Client code

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 12011

using namespace std;

int main() {
	int sockfd, n, connfd;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr, cliaddr;

	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		cout << "Socket Creation Error" << endl;
		exit(1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Fill server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number

	// Bind the socket with the server address
	if((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) < 0){
		cout << "Bind Error" << endl;
		exit(1);
	}

	if(listen(sockfd, 5) != 0){
		cout << "Listen Error" << endl;
		exit(1);
	}

	connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
	if(connfd < 0){
		cout << "Accept Error" << endl;
		exit(1);
	}

	len = sizeof(servaddr);
	n = 0;

        while (1) {

		//Receive the client packet along with the address it is coming from
		/*n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
			MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		buffer[n] = '\0';

		//Otherwise, the server responds
		sendto(sockfd, (const char *)buffer, strlen(buffer),
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);*/

		//n = read(sockfd, (char*)buffer, sizeof(buffer));
		n = recvfrom(connfd, (char*) buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr*) &cliaddr, &len);
		buffer[n] = '\0';
		if(n > 0){
			sendto(connfd, (const char*) buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr*) &cliaddr, len);

			cout << n << endl;
			cout << buffer << endl;
		}
		
	}
	return 0;
}