/* Grigore Lucian-Florin - SO Tema 1 */
#ifndef _TEMA1_
#define _TEMA1_

#include "utils.h"

int process_define(char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMap * hashmap, FILE * in_fd);

int process_undefine(char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMap *hashmap);

int process_ifdef(TArgs *args, char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMap *hashmap, FILE *fd);

int process_ifndef(TArgs *args, char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMap *hashmap, FILE *fd);

int process_if(TArgs *args, char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMap *hashmap, FILE *fd);

int process_normal_line(TArgs *args, char line[IN_LINE_MAX_LEN],
	int len, THashMap *hashmap);

int process_include(TArgs *args, THashMap *hashmap,
	char in_line[IN_LINE_MAX_LEN], int index_first_space, int len);

int decide_action(char line[IN_LINE_MAX_LEN], TArgs *args,
	THashMap *hashmap, FILE *fd);

int preprocess(TArgs *args, THashMap *hashmap);

#endif
