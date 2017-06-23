#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define LENGTH 32
#define DIM 255
#include <stdbool.h>

struct daten {
	char key[LENGTH];
	char value[LENGTH];
};

typedef struct datenWrapper {
    struct daten entry[LENGTH];
    int current_length;

} DATENWRAPPER;

struct daten kv[LENGTH];

extern int put(char *key, char* value, char* res, struct datenWrapper *sm);
extern int get(char* key, char* res, struct datenWrapper *sm, char **array);
extern int del(char* key, char* res, struct datenWrapper *sm);
extern int strtoken(char *str, char *separator, char **token, int size);
extern bool wildCard(const char *pattern, const char *candidate, int p, int c);

#endif
