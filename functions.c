#include <stdio.h>
#include "functions.h"
#include <string.h>

int current_length = 0;
int a;

/*****
* Die get() Funktion soll einen Schlüsselwert (key) in der Datenhaltung suchen
* und den hinterlegten Wert (value) zurückgeben. Ist der Wert nicht vorhanden,
* wird durch einen Rückgabewert darauf aufmerksam gemacht.
* ****/

int get(char *key, char *res) {
    if (current_length == 0) {
        printf("Es sind keine Daten gespeichert.\n");
        return -1;
    } else {
        for(a = 0; a < LENGTH; a++) {
          if(strcmp(kv[a].key, key) == 0){
            strcpy(res, kv[a].value);
            return 0;
          }
        }
    }
      strcpy(res, "Wert nicht gefunden!");
      printf("Wert nicht gefunden!\n");
      return -1;

}

/*****
* Die put() Funktion soll eine Wert (value) mit dem Schlüsselwert (key) hinterlegen.
* Wenn der Schlüssel bereits vorhanden ist, soll der Wert überschrieben werden,
* und der alte Wert zurückgegeben werden.
* IDEE: array_length-Variable anlegen, aufzählen beim Hinzufügen. Falls Array voll -> Error
*******/

int put(char *key, char *value, char *res) {
   for(a = 0; a < LENGTH; a++) {
     if(current_length == LENGTH){
        strcpy(res, "Es koennen keine Daten hinzugefuegt werden!");
        printf("\nEs koennen keine Daten hinzugefuegt werden!\n");
        return -1;
     } else if(strcmp(kv[a].key, key)== 0){
        strcpy(res, kv[a].value);
        strcpy(kv[a].value, value);
        printf("\nValue wurde ersetzt");
        return 0;
     }else if(strcmp(kv[a].key, NULL) == 0){
        strcpy(kv[a].key, key);
        strcpy(kv[a].value, value);
        strcpy(res, value);
        current_length++;
        printf("Key: %s und Value: %s", kv[a].key, kv[a].    value);
        return 0;
     }
    }

}

/******
* Die del() Funktion soll einen Schlüsselwert suchen und zusammen
* mit dem Wert aus der Datenhaltung entfernen.
* Der letzte Wert soll dabei zurückgegeben werden
* IDEE: array_length-Variable anlegen, -1 beim Löschen
*******/

int del(char *key, char *res) {
  if(current_length == 0){
                 strcpy(res, "Es sind keine Daten vorhanden!");
                 printf("Keine Daten vorhanden");
                 return -1;
         } else {
                 for(a = 0; a < LENGTH; a++){
                  if(strncmp(kv[a].key, key, 1)==0){
                         strcpy(res, kv[a].value);
                         strcpy(kv[a].key, NULL);
                         strcpy(kv[a].value, NULL);
                         return 0;
                  }
                 }
         }
         strcpy(res, "Keinen passenden Wert gefunden!");
         printf("Nichts gefunden");
         return -1;

}

int strtoken(char *str, char *separator, char **token, int size) {
    int i=0;
    token[0] = strtok(str, separator);
    while(token[i++] && i < size)
        token[i] = strtok(NULL, separator);
    return (i);
}
