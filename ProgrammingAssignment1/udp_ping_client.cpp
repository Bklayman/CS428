// UDP Pinger

// Must have the server running before you can run this UDP Pinger Client code

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 12002

using namespace std;

int main() {
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr;

	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		cout << "Socket Creation Error" << endl;
		exit(1);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Fill server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number

	len = sizeof(servaddr);

  for(int i = 0; i < 10; i++) {
		//Otherwise, the server responds
		if((sendto(sockfd, (const char *)buffer, strlen(buffer),
			MSG_CONFIRM, (const struct sockaddr *) &servaddr, len)) < 0){
			cout << "Send Error" << endl;
			exit(1);
		}

		cout << "Message Sent" << endl;

		//Receive the client packet along with the address it is coming from
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
			MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';

		cout << "Message Received" << endl;
	}
	return 0;
}
