#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define LENGTH 32

struct daten {
	char key[LENGTH];
	char value[LENGTH];
};
struct daten kv[LENGTH];

extern int put(char *key, char* value, char* res, struct daten *sm);
extern int get(char* key, char* res, struct daten *sm);
extern int del(char* key, char* res, struct daten *sm);
extern int strtoken(char *str, char *separator, char **token, int size);

#endif
