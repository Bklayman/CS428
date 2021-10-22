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
	char buffer[1024];
	struct sockaddr_in servaddr;
	int msgCount = 10;
	socklen_t len;

	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		cout << "Socket Creation Error" << endl;
		exit(1);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Fill server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	len = sizeof(servaddr); // Address length

	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0){
		cout << "Connect Error" << endl;
		exit(1);
	}

  	for(int i = 0; i < msgCount; i++) {
		// Obtain current time and send a ping to the server
		/*if((sendto(sockfd, (const char *)buffer, strlen(buffer),
			MSG_CONFIRM, (const struct sockaddr *) &servaddr, len)) < 0){
			cout << "Send Error" << endl;
			exit(1);
		}

		// No timeout, receive message, get current time, and print difference between both obtained times
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
			MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';
		cout << "Received" << endl;*/

		//write(sockfd, (char*)buffer, sizeof(buffer));
		sendto(sockfd, "Hi", strlen("Hi"), MSG_CONFIRM, (const struct sockaddr*) &servaddr, len);

		//memset(buffer, 0, sizeof(buffer));

		//n = read(sockfd, (char*)buffer, sizeof(buffer));

		//if(n > 0){
		//	cout << buffer << endl;
		//}
	}
	return 0;
}
