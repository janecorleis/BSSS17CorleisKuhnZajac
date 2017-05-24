#include <stdio.h>
#include "functions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

  int sock;
  struct sockaddr_in server;
  struct sockaddr_in client;
  int fileDescriptor;
  unsigned long client_len;
  client_len = sizeof(client);
  char in[2000];
  char out[2000];
	char seperator = " ";
	char *token[256];
	char *res;
  int var;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
	   perror("creating stream socket");
	    exit(2);
    }

    int option = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1337);

    if(bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0){
      printf("Error on Binding");
    };

    if(listen(sock, 5) < 0){
      printf("Error on listening");
    };

      while (1){
	       fileDescriptor = accept(sock, (struct sockaddr *) &client, &client_len);
				 //hier irgendwo fork?
				char greet[12] = "Hallo Client";
        write (fileDescriptor, greet, strlen(greet));

	       while (read(fileDescriptor, in, 2000) > 0){
					  strtoken(in, seperator, token, 3);

            int eingabe;

            if(strcmp(token[0], "PUT") == 0){
              eingabe = 1;
            } else if (strcmp(token[0], "GET") == 0){
              eingabe = 2;
            } else if (strcmp (token[0], "DEL") == 0){
              eingabe = 3;
            }

						switch (eingabe){
							case 1: var = put(token[1], token[2]); break;
							case 2: var = get(token[1], res); break;
							case 3: var = del(token[1], res); break;
							default: printf("\nUngültige Eingabe\n"); ;
						}
		       // write(fileDescriptor, in, strlen(in));
	        }
	        close(fileDescriptor);
      }


  /*
	int eingabe;
	char value;
	char key;
  char res;

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
	} while(eingabe != 4);*/
	return 0;
}
