/* Grigore Lucian-Florin - SO Tema 1 */
#ifndef _UTILS_
#define _UTILS_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "hashmap.h"
#include "strtok_saved.h"

#define INPUT_DIRS 10
#define IN_LINE_MAX_LEN 256
#define DELIMS "\t []{}()<>=+-*/!@#$%^&\\:;|"
#define DEFINE_DELIMS "\t []{}()<>+-*/!@#$%^&\\:;|"

/* structura care inglobeaza argumentele programului */
typedef struct {
	int no_input_dirs;
	int max_input_dirs;
	char **input_dirs;
	FILE *in_fd;
	FILE *out_fd;
	char *output_filename;
	char *input_filename;
} TArgs;

int parse_input(int argc, char *argv[], THashMap *hashmap, TArgs **args);

void destroy_args(TArgs *args);

#endif
