#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <stdbool.h>

int current_length = 0;
int a;

/*****
* Die get() Funktion soll einen Schlüsselwert (key) in der Datenhaltung suchen
* und den hinterlegten Wert (value) zurückgeben. Ist der Wert nicht vorhanden,
* wird durch einen Rückgabewert darauf aufmerksam gemacht.
* ****/

int get(char *key, char *res, struct daten *sm, char *array) {
    int e = 0;
    if (current_length == 0) {
        printf("Es sind keine Daten gespeichert.\n");
        return -1;
    } else {
        for(a = 0; a < LENGTH; a++) {
            if(strcmp(sm[a].key, key) == 0) {
                strcpy(res, sm[a].value);
                return 0;
            } else {
                if(wildCard(key, sm[a].key, 0, 0)){
                    array[e] = sm[a].value;
                    printf("%s\n", array[e]);
                    e++;
              }

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

int put(char *key, char *value, char *res, struct daten *sm) {
   for(a = 0; a < LENGTH; a++) {

       if(current_length == LENGTH) {
           strcpy(res, "Es koennen keine Daten hinzugefuegt werden!");
           printf("\nEs koennen keine Daten hinzugefuegt werden!\n");
           return -1;
        } else if(strcmp(sm[a].key, key) == 0) {
            strcpy(res, sm[a].value);
            strcpy(sm[a].value, value);
            printf("\nValue wurde ersetzt");
            return 0;
        } else if(strcmp(sm[a].key, NULL) == 0) {
            strcpy(sm[a].key, key);
            strcpy(sm[a].value, value);
            strcpy(res, value);
            current_length++;
            printf("Key: %s und Value: %s", sm[a].key, sm[a].value);
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

int del(char *key, char *res, struct daten *sm) {
    if(current_length == 0) {
        strcpy(res, "Es sind keine Daten vorhanden!");
        printf("Keine Daten vorhanden");
        return -1;
    } else {
        for(a = 0; a < LENGTH; a++) {
            if(strncmp(sm[a].key, key, 1) == 0) {
                strcpy(res, sm[a].value);
                strcpy(sm[a].key, NULL);
                strcpy(sm[a].value, NULL);
                return 0;
            }
        }
    }
    strcpy(res, "Keinen passenden Wert gefunden!");
    printf("Nichts gefunden");
    return -1;

}

bool wildCard(const char *pattern, const char *candidate, int p, int c) {
    if (pattern[p] == '\0') {
        //printf("1: %i %i\n", c, p);
        return candidate[c] == '\0';
    } else if (pattern[p] == '*') {
        //printf("2: %i %i\n", c, p);
        for (; candidate[c] != '\0'; c++) {
            //printf("hallo %i\n", c);
            if (wildCard(pattern, candidate, p+1, c)){
                printf("3: %i %i\n", c, p);
                return true;
        }
    }
    return wildCard(pattern, candidate, p+1, c);
    } else if (pattern[p] == '?') {
        return wildCard(pattern, candidate, p+1, c+1);
    } else if (pattern[p] != candidate[c]) {
        return false;
    } else {
        printf("4: %i %i\n", c, p);
        return wildCard(pattern, candidate, p+1, c+1);
  }
}

int strtoken(char *str, char *separator, char **token, int size) {
    int i=0;
    token[0] = strtok(str, separator);
    while(token[i++] && i < size)
        token[i] = strtok(NULL, separator);
    return (i);
}
