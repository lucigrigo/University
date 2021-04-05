/* Grigore Lucian-Florin - SO Tema 1 */
#include "utils.h"

typedef TArgs * TArgsP;

typedef TArgsP * TArgsPP;

/* functie care se ocupa de parsarea inputului */
int parse_input(int argc, char *argv[],
	THashMapP hashmap,
	TArgsPP args)
{
	unsigned int len;

	int i, ret;

	char *curr = NULL, *arg = NULL, *symbol = NULL,
	*mapping = NULL, *tok = NULL, *fname = NULL;

	FILE *in_fd = NULL, *out_fd = NULL;

	/* initializeaza argumentele */
	(*args) = (TArgs *) malloc(sizeof(TArgs));
	if ((*args) == NULL)
		return 12;
	if (args == NULL)
		return 12;
	(*args)->input_filename = NULL;
	(*args)->output_filename = NULL;
	(*args)->no_input_dirs = 0;
	(*args)->max_input_dirs = 0;
	(*args)->input_dirs = NULL;
	(*args)->in_fd = NULL;
	(*args)->out_fd = NULL;

	/* parcurge argumentele */
	for (i = 1; i < argc; ++i) {
		curr = argv[i];
		len = strlen(curr);
		arg = NULL;

		if (curr[0] == '-') {
			switch (curr[1]) {
			case 'D':
				/* adauga un simbol in hashmap */
				if (len == 2) {
					arg = (char *) malloc(sizeof(char)
						*
						strlen(argv[i + 1]) + 1);
					if (arg == NULL)
						return 12;
					memset(arg, 0,
						strlen(argv[i + 1]) + 1);
					memcpy(arg, argv[i + 1],
						strlen(argv[i + 1]));
					++i;
				} else {
					arg = (char *) malloc(sizeof(char)
						* (len - 1));
					if (arg == NULL)
						return 12;
					memset(arg, 0, len - 1);
					memcpy(arg, (curr + 2), (len - 2));
				}

				if (arg == NULL)
					return 12;
				tok = strtok(arg, "=");
				if (tok == NULL)
					return 12;
				symbol = (char *) malloc(sizeof(char)
					* strlen(tok) + 1);
				if (symbol == NULL)
					return 12;
				memset(symbol, 0, strlen(tok) + 1);
				strncpy(symbol, tok, strlen(tok));

				tok = strtok(NULL, "=");
				if (tok == NULL) {
					mapping = (char *) malloc(sizeof(char)
						* strlen("") + 1);
					if (mapping == NULL)
						return 12;
					memset(mapping, 0, strlen("") + 1);
					memcpy(mapping, "", strlen(""));
				} else {
					mapping = (char *) malloc(sizeof(char)
						* strlen(tok) + 1);
					if (mapping == NULL)
						return 12;
					memset(mapping, 0, strlen(tok) + 1);
					memcpy(mapping, tok, strlen(tok));
				}

				ret = insert_into_hashmap(hashmap, symbol,
					mapping);
				if (ret != 0)
					return ret;

				if (arg != NULL)
					free(arg);

				break;
			case 'I':
				/* adauga un director in lista */
				if (len == 2) {
					arg = (char *) malloc(sizeof(char) *
						strlen(argv[i + 1]) + 1);
					if (arg == NULL)
						return 12;
					memset(arg, 0,
						strlen(argv[i + 1]) + 1);
					strcpy(arg, argv[i + 1]);
					++i;
				} else {
					arg = (char *) malloc(sizeof(char) *
						(len - 1));
					if (arg == NULL)
						return 12;
					memset(arg, 0, len - 1);
					strncpy(arg, (curr + 2), (len - 2));
				}

				if ((*args)->max_input_dirs ==
					(*args)->no_input_dirs) {
					if ((*args)->input_dirs == NULL) {
						(*args)->input_dirs = (char **)
						malloc(INPUT_DIRS *
							sizeof(char *));

					if ((*args)->input_dirs == NULL)
						return 12;

					(*args)->max_input_dirs = INPUT_DIRS;
					} else {
						(*args)->input_dirs = (char **)
						realloc((*args)->input_dirs,
							(*args)->max_input_dirs
							* 2 * sizeof(char *));
					if ((*args)->input_dirs == NULL)
						return 12;
					(*args)->max_input_dirs =
					(*args)->max_input_dirs * 2;
					}
				}

				(*args)->input_dirs[(*args)->no_input_dirs] =
				arg;
				(*args)->no_input_dirs =
				(*args)->no_input_dirs + 1;

				break;
			case 'o':
				/* adauga un fisier de output */
				if ((*args)->output_filename != NULL)
					return -1;

				if (len == 2) {
					arg = (char *) malloc(sizeof(char) *
						strlen(argv[i + 1]) + 1);
					if (arg == NULL)
						return 12;
					memset(arg, 0,
						strlen(argv[i + 1]) + 1);
					memcpy(arg, argv[i + 1],
						strlen(argv[i + 1]));
					++i;
				} else {
					arg = (char *)
					malloc(sizeof(char) * (len - 1));
					if (arg == NULL)
						return 12;
					memset(arg, 0, len - 1);
					memcpy(arg, (curr + 2), (len - 2));
				}

				(*args)->output_filename = arg;

				break;
			default:
				return -1;
			}
		} else {
			/* deschide fisier de input*/
			if ((*args)->input_filename == NULL) {
				in_fd = fopen(curr, "r");

				(*args)->input_filename = curr;

				if (in_fd == NULL)
					return -1;
			} else if ((*args)->output_filename == NULL) {
				/* deschide fisier de output */
				char *copy = (char *) malloc(strlen(curr) + 1);

				if (copy == NULL)
					return 12;
				memset(copy, 0, strlen(curr) + 1);
				memcpy(copy, curr, strlen(curr));
				(*args)->output_filename = copy;
			} else {
				return -1;
			}
		}
	}

	if ((*args)->output_filename == NULL)
		out_fd = stdout;
	else {
		/* deschide fisier de output pasat cu '-o' */
		fname = (char *)
			malloc(strlen((*args)->output_filename) + 1);

		if (fname == NULL)
			return 12;
		memset(fname, 0, strlen((*args)->output_filename) + 1);
		len = strlen((*args)->output_filename);

		strncpy(fname, (*args)->output_filename, len);
		out_fd = fopen(fname, "w");
		if (fname != NULL)
			free(fname);
	}

	if (out_fd == NULL)
		return -1;

	if (in_fd == NULL)
		in_fd = stdin;

	(*args)->out_fd = out_fd;
	(*args)->in_fd = in_fd;

	return 0;
}

/* elibereaza memoria alocata pentru argumente */
void destroy_args(TArgs *args)
{
	int i;

	if (args == NULL)
		return;
	if (args->input_dirs != NULL) {
		for (i = 0; i < args->no_input_dirs; ++i) {
			if (args->input_dirs[i] != NULL)
				free(args->input_dirs[i]);
		}
		free(args->input_dirs);
	}

	if (args->output_filename != NULL)
		free(args->output_filename);

	if (args->out_fd != NULL)
		fclose(args->out_fd);

	if (args->in_fd != NULL)
		fclose(args->in_fd);

	free(args);
}
