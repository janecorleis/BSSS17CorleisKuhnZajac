//Jane Corleis, Nathalie Kuhn, Simone Zajac

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

int pid, id, id2, id3;

void bzero(void *to, size_t count) {
    memset(to, 0, count);
}

void handler(int sig) {
    //Lösche Sempahore
    printf("Beende Server\n");
    if (id2 >= 0)
        semctl(id2, 1, IPC_RMID, 0);
    if (id3 >= 0)
        shmctl(id3, 1, IPC_RMID, 0);
    //Lösche Shared Memory
    if (id >= 0)
        shmctl(id, IPC_RMID, NULL);
    exit(0);
}

int main(){

    int sock, fileDescriptor;
    int var, i, read_size;
    struct sockaddr_in server;
    struct sockaddr_in client;
    struct datenWrapper *sm;
    struct sembuf up, down, upc, downc;
    unsigned long client_len;
    char in[2000], res[2000];
    char *seperator = " ";
	  char *token[256];
    char *array[LENGTH];

    client_len = sizeof(client);

    //Signale an Handler-Funktion binden
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    //Socket erstellen
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

    //Adresse an das Socket binden
    if(bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Error on Binding");
    };

    if(listen(sock, 5) < 0) {
        printf("Error on listening");
    };

    //Shared-Memory anlegen
    id = shmget(IPC_PRIVATE, sizeof(DATENWRAPPER), IPC_CREAT|0777);
    sm = (struct datenWrapper *) shmat (id, 0, 0);
    sm->current_length = 0;

    //Semaphor für Speicher anlegen
    id2 = semget(IPC_PRIVATE, 1, IPC_CREAT|0777);
    if(id2==1){
      printf("geht nicht");
      return -1;
    }
    sm->counter = 0;

    semctl(id2, 0, SETVAL, (int) 1);

    down.sem_num = 0;
    down.sem_op = -1;
    down.sem_flg = SEM_UNDO;

    up.sem_num = 0;
    up.sem_op = 1;
    up.sem_flg = SEM_UNDO;

    //zweiten Semaphor für Zähler anlegen
    id3 = semget(IPC_PRIVATE, 1, IPC_CREAT|0777);
    if(id3==1){
      printf("geht nicht");
      return -1;
    }

    semctl(id3, 0, SETVAL, (int) 1);

    downc.sem_num = 0;
    downc.sem_op = -1;
    downc.sem_flg = SEM_UNDO;

    upc.sem_num = 0;
    upc.sem_op = 1;
    upc.sem_flg = SEM_UNDO;

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
	             while (read_size = recv(fileDescriptor, in, 2000,0) > 0){
                    bzero(res, sizeof(res));
			              strtoken(in, seperator, token, 3);

                    if(strcmp(token[0], "PUT") == 0){
                      semop(id2, &down, 1);
                      var = put(token[1], token[2], res, sm);
                      write(fileDescriptor, res, strlen(res));
                      puts("PUT funktioniert\n");
                      semop(id2, &up, 1);

                    } else if (strcmp(token[0], "GET") == 0){
                      semop(id3, &downc, 1);
                      sm->counter += 1;
                      if(sm->counter == 1){
                        semop(id2, &down, 1);
                      }
                      semop(id3, &upc, 1);
                      var = get(token[1], res, sm, array);

                      //Ausgabe falls Array durch WildCards gefüllt ist
                      if(var > 0){
                        for(i = 0; i < var; i++){
                          write(fileDescriptor, array[i], strlen(array[i]));
                          array[i] = NULL;
                        }
                      }

                      //Ausgabe falls nur ein Value ausgegeben werden soll
                      if(var == 0) write(fileDescriptor, res, strlen(res));
                      semop(id3, &downc, 1);
                      sm->counter -= 1;
                      if(sm->counter == 0){
                        semop(id2, &up, 1);
                      }
                      puts("GET funktioniert\n");
                      semop(id3, &upc, 1);

                    } else if (strcmp (token[0], "DEL") == 0){
                      semop(id2, &down, 1);
                      var = del(token[1], res, sm);
                      char tmp[64];

                      //Ausgabe, wenn mehrere Einträge auf einmal gelöscht werden
                      if(var > 0){
                        sprintf(tmp, "%d", var);
                        write(fileDescriptor, tmp, strlen(tmp));
                        write(fileDescriptor, " Eintraege wurden geloescht!\n", 30);
                      }

                      //Ausgabe, wenn nur ein Eintrag gelöscht wird
                      write(fileDescriptor, res, strlen(res));
                      puts("DEL funktioniert\n");
                      semop(id2, &up, 1);

                    } else if (strcmp(token[0], "close") == 0){
                      close(fileDescriptor);

                    } else {
                      puts("Ungültige Eingabe vom Client\n");
                    }
                    bzero(in, sizeof(in));
              }
	        close(fileDescriptor);
        }
    }
	return 0;
}
