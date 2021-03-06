//Jane Corleis, Nathalie Kuhn, Simone Zajac

#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <stdbool.h>

int i;

/*****
* Die get() Funktion soll einen Schlüsselwert (key) in der Datenhaltung suchen
* und den hinterlegten Wert (value) zurückgeben. Ist der Wert nicht vorhanden,
* wird durch einen Rückgabewert darauf aufmerksam gemacht.
* ****/

int get(char *key, char *res, struct datenWrapper *sm, char **array) {
    int e = 0;
    int check = 0;

    if (sm->current_length == 0) {
        printf("Es sind keine Daten gespeichert.\n");
        return -1;
    }

    //sucht Value im Shared-Memory
    for(i = 0; i < sm->current_length; i++) {
      if(strcmp(sm->entry[i].key, key) == 0) {
        strcpy(res, sm->entry[i].value);
        printf("%s", sm->entry[i].value);
        return 0;
      }
    }

    //sucht Value im Shared-Memory mit WildCards
    for(i = 0; i < sm->current_length; i++) {
      if(wildCard(key, sm->entry[i].key, 0, 0)){
        array[e] = sm->entry[i].value;
        printf("%s\n", array[e]);
        check += 1;
        e++;
      }
    }

    //Kein Wert wurde gefunden
    if(check == 0){
      strcpy(res, "Wert nicht gefunden!");
      printf("Wert nicht gefunden!\n");
      return -1;
    }
    return check;
}

/*****
* Die put() Funktion soll eine Wert (value) mit dem Schlüsselwert (key) hinterlegen.
* Wenn der Schlüssel bereits vorhanden ist, soll der Wert überschrieben werden,
* und der alte Wert zurückgegeben werden.
* IDEE: array_length-Variable anlegen, aufzählen beim Hinzufügen. Falls Array voll -> Error
*******/

int put(char *key, char *value, char *res, struct datenWrapper *sm) {
  //Falls Speicher voll ist
  if(sm->current_length == LENGTH) {
    strcpy(res, "Es koennen keine Daten hinzugefuegt werden!");
    printf("\nEs koennen keine Daten hinzugefuegt werden!\n");
    return -1;
  }

  //Ersetzt Value, falls Key bereits vorhanden
	for(i = 0; i < LENGTH; i++) {
		if(strcmp(sm->entry[i].key, key) == 0){
			  strcpy(res, sm->entry[i].value);
  		  strcpy(sm->entry[i].value, value);
        printf("\nValue wurde ersetzt\n");
        return 0;
		}
	}

  //Erstellt neuen Eintrag
	for(i = 0; i < LENGTH; i++) {
		if(strlen(sm->entry[i].key) == 0) {
      strcpy(sm->entry[i].key, key);
      strcpy(sm->entry[i].value, value);
      strcpy(res, value);
      sm->current_length++;
      printf("Key: %s und Value: %s", sm->entry[i].key, sm->entry[i].value); fflush(0);
      return 0;
    }
	}
  printf("%s \n", sm->entry[i].key);
}

/******
* Die del() Funktion soll einen Schlüsselwert suchen und zusammen
* mit dem Wert aus der Datenhaltung entfernen.
* Der letzte Wert soll dabei zurückgegeben werden
* IDEE: array_length-Variable anlegen, -1 beim Löschen
*******/

int del(char *key, char *res, struct datenWrapper *sm) {
    int var = 0;
    if(sm->current_length == 0) {
        strcpy(res, "Es sind keine Daten vorhanden!");
        printf("Keine Daten vorhanden");
        return -1;
    }

    //sucht nach Key im Shared-Memory und setzt beide Einträge auf NULL
    for(i = 0; i < LENGTH; i++) {
        if(strncmp(sm->entry[i].key, key, 1) == 0) {
            strcpy(res, sm->entry[i].value);
            strcpy(sm->entry[i].key, NULL);
            strcpy(sm->entry[i].value, NULL);
            return 0;
        }
    }

    //entfernt Werte mit WildCards
    for(i = 0; i < sm->current_length; i++) {
      if(wildCard(key, sm->entry[i].key, 0, 0)){
        strcmp(sm->entry[i].key, NULL);
        strcmp(sm->entry[i].value, NULL);
        var += 1;
      }
    }

    //Kein Wert zum Löschen gefunden
    if(var == 0){
      strcpy(res, "Keinen passenden Wert gefunden!");
      printf("Nichts gefunden");
      return -1;
    }
    return var;
}

//rekursive Funktion für WildCards
bool wildCard(const char *pattern, const char *candidate, int p, int c) {
    if (pattern[p] == '\0') {
        return candidate[c] == '\0';
    } else if (pattern[p] == '*') {
        for (; candidate[c] != '\0'; c++) {
            if (wildCard(pattern, candidate, p+1, c)){
                return true;
            }
        }
      return wildCard(pattern, candidate, p+1, c);
    } else if (pattern[p] == '?') {
        return wildCard(pattern, candidate, p+1, c+1);
    } else if (pattern[p] != candidate[c]) {
        return false;
    } else {
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
