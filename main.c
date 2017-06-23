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
#include <sys/sem.h>
#include <memory.h>
#include "signal.h"

int pid, i, id, y, id2;

void bzero(void *to, size_t count) {
    memset(to, 0, count);
}

void handler(int sig) {
    //Delete Sempahore.
    printf("Beende Server\n");
    if (id2 >= 0)
        semctl(id2, 1, IPC_RMID, 0);
    //Delete Shared Memory
    if (id >= 0)
        shmctl(id, IPC_RMID, NULL);
    exit(0);
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
    char *seperator = " ";
	char *token[256];
	char res[2000];
    int var;
    int read_size;
    struct datenWrapper *sm;
    char *array[LENGTH];
    struct sembuf up, down;

    //Here we bind the signals to our handler function
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

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

    id = shmget(IPC_PRIVATE, sizeof(DATENWRAPPER), IPC_CREAT|0777);
    sm = (struct datenWrapper *) shmat (id, 0, 0);
    sm->current_length = 0;

    id2 = semget(IPC_PRIVATE, 1, IPC_CREAT|0777);
    if(id2==1){
      printf("geht nicht");
      return -1;
    }

    semctl(id2, 0, SETVAL, (int) 1);

    down.sem_num = 0;
    down.sem_op = -1;
    down.sem_flg = SEM_UNDO;

    up.sem_num = 0;
    up.sem_op = 1;
    up.sem_flg = SEM_UNDO;

    while (1){
	       fileDescriptor = accept(sock, (struct sockaddr *) &client, &client_len);
        printf("Connection accepeted\n"); fflush(0);
           pid = fork();
           if(pid < 0){
               printf("Fehler!\n");
               exit(1);
            } else if(pid > 0){
                //Vaterprozess
                close(fileDescriptor);
            } else if(pid == 0){
                //Kindprozess
               close(sock);
			    char greet[14] = "Hallo Client\n";
                write (fileDescriptor, greet, strlen(greet));

               //bzero(in, sizeof(in));
	            while (recv(fileDescriptor, in, 2000,0) > 0){
                    bzero(res, sizeof(res));
			    strtoken(in, seperator, token, 3);
                if(strcmp(token[0], "PUT") == 0){
                    semop(id2, &down, 1);
                    var = put(token[1], token[2], res, sm);
                    puts("PUT funktioniert\n");
                    //sleep(5);
                    semop(id2, &up, 1);
                } else if (strcmp(token[0], "GET") == 0){
                    semop(id2, &down, 1);
                    var = get(token[1], res, sm, array);
                    puts("GET funktioniert\n");
                    semop(id2, &up, 1);
                } else if (strcmp (token[0], "DEL") == 0){
                    semop(id2, &down, 1);
                    var = del(token[1], res, sm);
                    puts("DEL funktioniert\n");
                    semop(id2, &up, 1);
                }else if(strcmp(token[0], "close") == 0){
                    shutdown(fileDescriptor, 2);
                } else {
                    puts("Ungültige Eingabe vom Client\n");
                }

            bzero(in, sizeof(in));
		        write(fileDescriptor, res, strlen(res));
	        }

	        close(fileDescriptor);
        }
    }
	return 0;
}
