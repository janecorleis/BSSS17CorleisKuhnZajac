#include <stdio.h>
#include "functions.h"
#include <string.h>

int current_length = 0;
struct daten daten_array;
int a;

/*****
* Die get() Funktion soll einen Schlüsselwert (key) in der Datenhaltung suchen
* und den hinterlegten Wert (value) zurückgeben. Ist der Wert nicht vorhanden,
* wird durch einen Rückgabewert darauf aufmerksam gemacht.
* ****/

int get(char *key, char *res) {
    if (current_length = 0) {
        printf("Es befinden sich keine Daten im Array.\n");
        return -1;
    } else {
        for(a = 0; a < 128; a++)
        {
            //strcmp(v1, v2) vergleicht char v1 und char v2 -> wenn 0, sind sie gleich
            if(strcmp((const char *)daten_array.key[a], key) == 0) {
                printf("Key: %s \n Value: %s", daten_array.key[a], daten_array.value[a]);
                res = daten_array.value[a];
            } else {
              printf("\nWert nicht gefunden!");
            }
        }
    }
    return 0;
}

/*****
* Die put() Funktion soll eine Wert (value) mit dem Schlüsselwert (key) hinterlegen.
* Wenn der Schlüssel bereits vorhanden ist, soll der Wert überschrieben werden,
* und der alte Wert zurückgegeben werden.
* IDEE: array_length-Variable anlegen, aufzählen beim Hinzufügen. Falls Array voll -> Error
*******/

int put(char *key, char *value, char *res) {
  /**  if (current_length = MAX_LENGTH) {
        printf("Es koennen keine weiteren Daten hinzugefuegt werden.\n");
        return; **/
   if (){
      for(a = 0; a < 128; a++)
      {
          //strcmp(v1, v2) vergleicht char v1 und char v2 -> wenn 0, sind sie gleich
          if(strcmp(daten_array.key[a], key) == 0) {
            res = daten_array.value[a];
            daten_array.value[a] = value;
          }
        }
    } else {
        current_length++;
        //strcpy(v1, v2) kopiert v2 in v1
        strcpy(daten_array.key[current_length], key);
        strcpy(daten_array.value[current_length], value);
        printf("Key: %s und\nValue: %s\n wurden hunzugefuegt.", daten_array.key[a], daten_array.value[a]);
        res = daten_array.value[current_length];
    }

    return 0;
}

/******
* Die del() Funktion soll einen Schlüsselwert suchen und zusammen
* mit dem Wert aus der Datenhaltung entfernen.
* Der letzte Wert soll dabei zurückgegeben werden
* IDEE: array_length-Variable anlegen, -1 beim Löschen
*******/

int del(char *key, char *res) {
    if (current_length = 0) {
        printf("Es befinden sich keine Daten im Array.\n");
        return;
    } else {
        for(a = 0; a < 128; a++)
        {
            if(strcmp(daten_array.key[a], key) == 0) {
                res = daten_array.value[a];
                printf("Key: %s und\nValue: %s\n wurden entfernt.", store_array.key[a], store_array.value[a]);
                strcpy(daten_array.key[current_length], NULL);
                strcpy(daten_array.value[current_length], NULL);
                current_length--;
              } else {
                printf("\nNichts gefunden");
              }
        }
    }
    //Was machen, wenn Wert nicht gefunden wurde?
    return 0;
}

int strtoken(char *str, char *separator, char **token, int size) {
    int i=0;
    token[0] = strtok(str, separator);
    while(token[i++] && i < size)
        token[i] = strtok(NULL, separator);
    return (i);
}
