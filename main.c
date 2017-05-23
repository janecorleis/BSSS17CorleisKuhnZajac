#include <stdio.h>
#include "header.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>

int main(){

	int eingabe;
	char value;
	char key;
  char res;

  int sock;
  struct sockaddr_in server;
  struct sockaddr_in client;
  int fileDescriptor, client_len;
  client_len = sizeof(client);
  char in[2000];
  char out[2000];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
	   perror("creating stream socket");
	    exit(2);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(4711);

    if(bind(sock, (struct sockaddr *) &server, sizeof(server)) <0){
			perror("bind socket to server_addr");
			exit(2);
		}

    if(listen(sock, 128) < 0){
			perror("listening for connections");
		}

    //fileDescriptor = accept(sock, &client, &client_len);

    /*if(fileDescriptor < 0){
	     perror("accept");
	      exit(2);
      }*/

      while (TRUE){
	       fileDescriptor = accept(sock, &client, &client_len);
	        while (read(fileDescriptor, in, 2000) > 0){
		          write(fileDescriptor, out, 2000);
	        }
	        close(fileDescriptor);
      }


  printf("\n1: Put\n2: Get\n3: Delete\n4: Abbrechen");

	do{
		scan("%d", &eingabe);
		if(eingabe > 4){
			printf("Falsche Eingabe!");
		}

		switch(eingabe){
			case 1: printf("\nPUT ");
				scanf("%d", &key);
				printf(" ");
				scanf("%d", &value);
        put();
				break;
			case 2: printf("\nGET ");
				scanf("%d", &key);
				printf("\n%d", value);
        get();
				break;
			case 3: printf("\nDEL");
				scanf("%d", &key);
        del();
				break;
			case 4: break;
	} while(eingabe != 4);
	return 0;
}
