// UDP Pinger Client

// Must have the server running before you can run the UDP Pinger Client code

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


#define PORT	 12000


int main() {
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
  int numPings = 10;
	struct sockaddr_in servaddr, cliaddr;

	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Fill client information
	cliaddr.sin_family = AF_INET; // IPv4
	cliaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	cliaddr.sin_port = htons(PORT); // port number

	// Bind the socket with the client address
	bind(sockfd, (const struct sockaddr *)&cliaddr, sizeof(cliaddr));

  time_t before;
  time_t after;
  double timeElapsed;

  //Send numPings pings to the server
  //numPings initially set to 10
  for(int i = 0; i < numPings; i++) {
    //Send a ping to the server and get current time
    time(&before);
    sendto(sockfd, (const char *)buffer, strlen(buffer),
			0, (const struct sockaddr *) &servaddr, len);

		//Receive the client packet along with the address it is coming from
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
			MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
		buffer[n] = '\0';
    time(&after);

    timeElapsed = difftime(before, after);
    printf("RTT = %.f", timeElapsed);

	}
	return 0;
}
