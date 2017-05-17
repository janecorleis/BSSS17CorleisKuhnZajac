#ifndef HEADER_H
#define HEADER_H

struct Daten {
	char key[50];
	char value[50];
} daten;

extern int put(char* key, char* value, char* res);	//fügt hinzu
extern int get(char* key, char* res);			//holt etwas
extern int del(char* key, char* res);			//löscht etwas

#endif
