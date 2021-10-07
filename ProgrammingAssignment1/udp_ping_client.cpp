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
#include <chrono>

#define PORT	 12008

using namespace std;

int main() {
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr;
	struct timeval timeout;
	fd_set readfds;
	int msgCount = 10;

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
	len = sizeof(servaddr); // Address length

	// Set the timeout variables for use in select()
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	FD_ZERO(&readfds);
	FD_SET(sockfd, &readfds);

  for(int i = 0; i < msgCount; i++) {

		// Obtain current time and send a ping to the server
	  chrono::high_resolution_clock::time_point before = chrono::high_resolution_clock::now();
		if((sendto(sockfd, (const char *)buffer, strlen(buffer),
			MSG_CONFIRM, (const struct sockaddr *) &servaddr, len)) < 0){
			cout << "Send Error" << endl;
			exit(1);
		}

		// Equivalent to recvfrom, except it will detect timout after timeout.tv_sec seconds, which is set to 1
		n = select(32, &readfds, NULL, NULL, &timeout);
		if(n <= 0){

			cout << "Timeout: No message received within 1 second" << endl;

			// Reset the variables associated with detecting a timeout within select()
			timeout.tv_sec = 1;
			timeout.tv_usec = 0;
			FD_ZERO(&readfds);
			FD_SET(sockfd, &readfds);

		} else {

			// No timeout, receive message, get current time, and print difference between both obtained times
			n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
				MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
			buffer[n] = '\0';
			chrono::high_resolution_clock::time_point after = chrono::high_resolution_clock::now();
			chrono::duration<double, milli> duration = after - before;
			cout << "RTT: " << duration.count() << "ms" << endl;
		}
	}
	return 0;
}
