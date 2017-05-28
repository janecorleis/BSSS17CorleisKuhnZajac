#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define LENGTH 32

struct daten {
	char key[LENGTH];
	char value[LENGTH];
} ;
struct daten kv[LENGTH];
extern int put(char* key, char* value, char* res);	//fügt hinzu
extern int get(char* key, char* res);			//holt etwas
extern int del(char* key, char* res);			//löscht etwas
extern int strtoken(char *str, char *separator, char **token, int size);

#endif
