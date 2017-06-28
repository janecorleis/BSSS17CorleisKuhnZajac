//Jane Corleis, Nathalie Kuhn, Simone Zajac

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

void bzero(void *to, size_t count){
  memset(to, 0, count);
}

int main(){
  int sock, n;
  struct sockaddr_in, server;
  char message[1000], server_reply[1000];

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0){
    printf("Could not create socket");
    exit(1);
  }

  puts("Socket created\n");

  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(1337);

  //stellt Verbindung mit dem Server her
  if(connect(sock, (struct sockaddr *) &server, sizeof(server))<0){
      perror("Connect failed. Error");
      exit(1);
  }

  puts("Connected\n");

  while(1){
    bzero(message, 1000);
    bzero(server_reply, 1000);
    printf("Please enter message: ");
    fgets(message, 1000, stdin);

    //schreibt Nachricht an den Server
    n = write(sock, message, strlen(message));

    if(n < 0){
      printf("Error writing to Server\n"); fllush(0);
      exit(1);
    }

    //Antwort vom Server lesen
    n = read(sock, server_reply, sizeof(server_reply));

    if(n < 0){
      printf("Error reading from Server\n"); fllush(0);
      exit(1);
    }
    printf("%s", server_reply);
  }
  close(sock);
  return 0;
}
