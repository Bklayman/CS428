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

using namespace std;

#define PORT	 12006

int main() {

	int sockfd, n;
	char buffer[1024];
  int numPings = 10;
	struct sockaddr_in servaddr;
	socklen_t len = sizeof(servaddr);

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

  time_t before;
  time_t after;
  double timeElapsed;

  //Send numPings pings to the server
  //numPings initially set to 10
  for(int i = 0; i < numPings; i++) {
    //Send a ping to the server and get current time
    time(&before);
    sendto(sockfd, (const char *)buffer, strlen(buffer),
			MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);

    cout << "Message Sent" << endl;

		//Receive the client packet along with the address it is coming from
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),
			MSG_WAITALL, ( struct sockaddr *) &servaddr, &len); //Stuck here
		buffer[n] = '\0';
		cout << "Message Received" << endl;
    time(&after);

    timeElapsed = difftime(before, after);
    printf("RTT = %.f", timeElapsed);

	}
	return 0;
}
