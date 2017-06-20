#include <stdio.h>

int main(int argc, char *argv[]) {
	struct sockaddr_in server;
	struct hostent *host_info;
	int sockfd, n;
	char buffer[256];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
      		perror("ERROR opening socket");
      		exit(1);
	}

	host_info = gethostbyname(argv[1]);

	/*if (server == NULL) {
    		fprintf(stderr,"ERROR, no such host\n");
      		exit(0);
   	}*/

	bzero((char *) &serv_addr, sizeof(serv_addr));
	//serv_addr.sin_family = AF_INET;
	memcpy(&server.sin_addr. host_info->h.addr. host_info->h_length);
	server.sin_port = htons(1337);

	/* Mit Server verbinden */
	if(connect(sockfd, (struct sockadrr*) &server, sizeof(server)) < 0) {
		perror("ERROR connecting");
		exit(1);
	}

	/* Nach Nachricht vom User fragen, diese wird vom Server gelesen */
	printf("Please enter message: ");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin)

	/* Nachricht an Server senden */
	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0) {
		perror("ERROR writing to socket");
		exit(1);
	}

	/* Antwort des Servers lesen */
	bzero(buffer, 256);
	n = read(sockfd, buffer, 255);
	if (n < 0) {
		perror("ERROR reading from socket");
		exit(1);
	}

	printf("%s\n", buffer);
	return 0;
}
