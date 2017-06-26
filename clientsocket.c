#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 1337

int main(int argc, char *argv[]) {
	struct sockaddr_in server;
	struct hostent *host_info;
	int sockfd, n;
	char buffer[256];

	if(argc != 2) {
		fprinf(stderr, "usage: client <hostname>\n");
		exit(2);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}

	server.sin_family = AF_INET;

	host_info = gethostbyname(argv[1]);

	if (host_info == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
  }

	bzero((char *) &serv_addr, sizeof(serv_addr));

	memcpy(&server.sin_addr. host_info->h.addr. host_info->h_length);
	/* copies internet address to server address */
	//bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
	server.sin_port = htons(PORT);

	/* Mit Server verbinden */
	if(connect(sockfd, (struct sockadrr*) &server, sizeof(server)) < 0) {
		perror("ERROR connecting");
		exit(1);
	}

	/* Nach Nachricht vom User fragen, diese wird vom Server gelesen */
	printf("Please enter message: ");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);

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
	/* read input from stdin */
	/*while(run=read(0,buf,BUF_SIZE)) {
		if(run<0) {
			perror(“error reading from stdin”);
			exit(1);
		}*/
 	/* write buffer to stream socket */
 		/*if(write(sock,buf,run) < 0) {
			perror(“writing on stream socket”);
			exit(1);
		}
	}*/
	/*close(sock);*/
