/* Grigore Lucian-Florin - SO Tema 1 */
#ifndef _HASHMAP_
#define _HASHMAP_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "strtok_saved.h"

/* valori default folosite */
#define DELIMS "\t []{}()<>=+-*/!@#$%^&\\:;|"
#define PRIME 31
#define INITIAL_BUCKET_SIZE 20

/* o asociere <simbol, valoare> din hashmap */
typedef struct {
	char *symbol;
	char *mapping;
} THashMapEntry;

typedef THashMapEntry * THashMapEntryP;

typedef THashMapEntryP * THashMapEntryPP;

/* abstractizarea hashmapului */
typedef struct {
	THashMapEntryPP elems[PRIME];
	int sizes[PRIME];
	int capacities[PRIME];
	int prime;
} THashMap, *THashMapP;

int init_hashmap(THashMap **hashmap);

int insert_into_hashmap(THashMap *map, char *key, char *value);

int find_in_hashmap(THashMap *map, char *key);

int compute_symbol(THashMap *hashmap, char *key, char **returned_value);

int delete_from_hashmap(THashMap *hashmap, char *key);

char *get_value(THashMap *map, char *key);

int calc_hash(THashMap *map, char *key);

void destroy_hashmap(THashMap *map);

#endif
