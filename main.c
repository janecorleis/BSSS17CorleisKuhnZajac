#include <stdio.h>
#include "functions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

void bzero(void *to, size_t count) {
    memset(to, 0, count);
}
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
    int read_size;
    int pid, i, id, y, id2;
    struct daten *sm;
    struct sembuf up, down;


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("creating stream socket");
	    exit(1);
    }

    int option = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));


    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1337);

    if(bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Error on Binding");
    };

    if(listen(sock, 5) < 0) {
        printf("Error on listening");
    };

    id = shmget(IPC_PRIVATE, sizeof(struct daten), IPC_CREAT|0777);
    sm = (struct daten *) shmat (id, 0, 0);


    id2 = semget(IPC_PRIVATE, 1, IPC_CREAT | 0777);
    if(id2 == -1){
      printf("Semaphorengruppe konnte nicht erzeugt werden\n");
      return -1;
    }


    semctl(id2, 0, SETALL, (int) 1);

    down.sem_num = 0;
    down.sem_op = -1;
    down.sem_flg = SEM_UNDO;

    up.sem_num = 0;
    up.sem_op = 1;
    up.sem_flg = SEM_UNDO;

    while (1){
	       fileDescriptor = accept(sock, (struct sockaddr *) &client, &client_len);
           pid = fork();
           if(pid < 0){
               printf("Fehler!\n");
               exit(1);
            } else if(pid > 0){
                //Vaterprozess
                close(fildeDescriptor);
            } else if(pid == 0){
                //Kindprozess
                close(sock);


			    char greet[12] = "Hallo Client";
                write (fileDescriptor, greet, strlen(greet));

	            while (read_size = recv(fileDescriptor, in, 2000,0) > 0){
			    strtoken(in, seperator, token, 3);

                if(strcmp(token[0], "PUT") == 0){
                    semop(id2, &down, 1);
                    var = put(token[1], token[2], res, sm);
                    puts("PUT funktioniert\n");
                    //sleep(5);
                    semop(id2, &up, 1);
                } else if (strcmp(token[0], "GET") == 0){
                    semop(id2, &down, 1);
                    var = get(token[1], res, sm);
                    puts("GET funktioniert\n");
                    semop(id2, &down, 1);
                } else if (strcmp (token[0], "DEL") == 0){
                    semop(id2, &down, 1);
                    var = del(token[1], res, sm);
                    puts("DEL funktioniert\n");
                    semop(id2, &up, 1);
                } else {
                    puts("Ungültige Eingabe vom Client\n");
                }

                bzero(in, sizeof(in));
                bzero((char *) &res, sizeof((char *) &res));
		        write(fileDescriptor, out, strlen(out));
	        }

	        close(fileDescriptor);
        }
    }
	return 0;
}
