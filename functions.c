#include <stdio.h>
#include "header.h"

const int MAX_LENGTH = 128;
int current_length = 0;
daten daten_array[MAX_LENGTH];
int a;

/*****
* Die get() Funktion soll einen Schlüsselwert (key) in der Datenhaltung suchen
* und den hinterlegten Wert (value) zurückgeben. Ist der Wert nicht vorhanden,
* wird durch einen Rückgabewert darauf aufmerksam gemacht.
* ****/

int get(char *key, char *res) {
    if (current_length = 0) {
        printf("Es befinden sich keine Daten im Array.\n");
        return;
    } else {
        for(a = 0; a < MAX_LENGTH; a++)
        {
            //strcmp(v1, v2) vergleicht char v1 und char v2 -> wenn 0, sind sie gleich
            if(strcmp(daten_array[a].key, &key) == 0) {
                printf("Key: %s \n Value: %s", daten_array[a].key, daten_array[a].value);
                res = &daten_array[a].value;
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
      for(a = 0; a < MAX_LENGTH; a++)
      {
          //strcmp(v1, v2) vergleicht char v1 und char v2 -> wenn 0, sind sie gleich
          if(strcmp(daten_array[a].key, &key) == 0) {
            res = &daten_array[a].value;
            daten_array[a].value = &value;
          }
        }
    } else {
        current_length++;
        //strcpy(v1, v2) kopiert v2 in v1
        strcpy(daten_array[current_length].key, &key);
        strcpy(daten_array[current_length].value, &value);
        printf("Key: %s und\nValue: %s\n wurden hunzugefuegt.", daten_array[a].key, daten_array[a].value);
        res = &daten_array[current_length].value;
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
        for(a = 0; a < MAX_LENGTH; a++)
        {
            if(strcmp(store_array[a].key, &key) == 0) {
                res = &store_array[a].value;
                printf("Key: %s und\nValue: %s\n wurden entfernt.", store_array[a].key, store_array[a].value);
                strcpy(store_array[current_length].key, null);
                strcpy(store_array[current_length].value, null);
                current_length--;
              } else {
                printf("\nNichts gefunden");
              }
        }
    }
    //Was machen, wenn Wert nicht gefunden wurde?
    return 0;
}
