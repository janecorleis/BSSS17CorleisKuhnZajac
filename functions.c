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
    if (current_length == 0) {
        printf("Es sind keine Daten gespeichert.\n");
        return -1;
    } else if(current_length != 0){
        for(a = 0; a < 128; a++) {
            //strcmp(v1, v2) vergleicht char v1 und char v2 -> wenn 0, sind sie gleich
            if(strcmp((const char *)daten_array.key[a], key) == 0) {
                printf("Key: %s \n Value: %s", daten_array.key[a], daten_array.value[a]);
                *res = (char) daten_array.value[a]; // & hinzugefuegt, weil in den Pointer ja die Adresse soll -> unten auch überall angepasst
                return 0; //Kann sein, dass das hier falsch ist, aber vielleicht ist es auch richtig
            }
        }
    } else {
      printf("Wert nicht gefunden!\n");
      return -1;
    }
}

/*****
* Die put() Funktion soll eine Wert (value) mit dem Schlüsselwert (key) hinterlegen.
* Wenn der Schlüssel bereits vorhanden ist, soll der Wert überschrieben werden,
* und der alte Wert zurückgegeben werden.
* IDEE: array_length-Variable anlegen, aufzählen beim Hinzufügen. Falls Array voll -> Error
*******/

int put(char *key, char *value, char *res) {
   for(a = 0; a < 128; a++) {
        //strcmp(v1, v2) vergleicht char v1 und char v2 -> wenn 0, sind sie gleich
        if(strcmp((const char *) daten_array.key[a], key) == 0) { //(const char *) eingefügt, weil es oben so war
            *res = (char) daten_array.value[a];
            daten_array.value[a] = value; //Kann sein, dass hier &value hin muss, da bin ich mir nicht sicher
            return 0;
        }
    }
    if (current_length == 128) {
        printf("Es kann nichts mehr hinzugefuegt werden\n");
        return -1;
    } else {
        current_length++;
        //strcpy(v1, v2) kopiert v2 in v1
        strcpy(daten_array.key[current_length], key);
        strcpy(daten_array.value[current_length], value);
        printf("Key: %s und Value: %s wurden hunzugefuegt.\n", daten_array.key[a], daten_array.value[a]);
        *res = (char)daten_array.value[current_length];
        return 0;
    }
}

/******
* Die del() Funktion soll einen Schlüsselwert suchen und zusammen
* mit dem Wert aus der Datenhaltung entfernen.
* Der letzte Wert soll dabei zurückgegeben werden
* IDEE: array_length-Variable anlegen, -1 beim Löschen
*******/

int del(char *key, char *res) {
    if (current_length == 0) {
        printf("Es sind keine Daten gespeichert.\n");
        return -1;
    } else {
        for(a = 0; a < 128; a++) {
            if(strcmp((const char *)daten_array.key[a], key) == 0) { //Hab hier man (const char *) eingefügt, weil es oben auch war
                res = &daten_array.value[a];
                printf("Key: %s und Value: %s wurden entfernt.\n", store_array.key[a], store_array.value[a]);
                strcpy(daten_array.key[a], NULL);
                strcpy(daten_array.value[a], NULL);
                for (int b = current_length; b > a; b--) { //Kann das so hinkommen? :S Hier sollen die darauffolgenden Einträge nach vorn gerückt werden, damit keine Lücken im Array sind
                    daten_array.key[b-1];
                    daten_array.value[b-1];
                }
                current_length--;
                return 0;
              } else {
                printf("Nichts gefunden\n");
                return -1;
              }
        }
    }
}

int strtoken(char *str, char *separator, char **token, int size) {
    int i=0;
    token[0] = strtok(str, separator);
    while(token[i++] && i < size)
        token[i] = strtok(NULL, separator);
    return (i);
}
