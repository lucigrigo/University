/* Grigore Lucian-Florin - SO Tema 1 */
#include "tema1.h"

typedef FILE * FFILE;

/* se ocupa de directiva '#define' */
int process_define(char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMapP hashmap, FFILE in_fd)
{
	int i = index_first_space + 1, ret, dif, var = 1;

	char *symbol = NULL, *empty = NULL, *mapping = NULL, *where = NULL;

	char buffer[IN_LINE_MAX_LEN];

	/* cauta primul element de pe linie (simbolul) */
	while (i < len && line[i] != ' ')
		++i;

	if (i == len)
		--i;

	symbol = (char *) malloc(sizeof(char) * (i - index_first_space));

	if (symbol == NULL)
		return 12;
	memset(symbol, 0, i - index_first_space);
	strncpy(symbol, line + index_first_space + 1,
		i - index_first_space - 1);

	/* daca se mapeaza la <""> */
	if (i == len - 1) {
		empty = (char *) malloc(sizeof(char) *
			(strlen("") + 1));

		if (empty == NULL)
			return 12;
		memset(empty, 0, strlen("") + 1);
		strcpy(empty, "");
		ret = insert_into_hashmap(hashmap, symbol, empty);
		return ret;
	}

	/* se cauta maparea simbolului curent */
	len = strchr(line, '\n') - line - 1;

	if (line[len] == '\\') {
		/* trateaza un define pe mai multe randuri */
		mapping = (char *) malloc(sizeof(char) *
			IN_LINE_MAX_LEN);

		if (mapping == NULL)
			return 12;
		memset(mapping, 0, IN_LINE_MAX_LEN);
		where = strrchr(line, '\\');

		dif = len - i;

		mapping = strncat(mapping, line + i, dif);

		while (var) {
			if (fgets(buffer, IN_LINE_MAX_LEN, in_fd) == NULL)
				break;

			where = strchr(buffer, '\\');
			if (where == NULL) {
				dif = strchr(buffer, '\n') - buffer;
				mapping = strncat(mapping, buffer, dif);
				break;
			}

			dif = where - buffer;
			mapping = strncat(mapping, buffer, dif);
		}

		ret = insert_into_hashmap(hashmap, symbol, mapping);

		if (ret != 0)
			return ret;
	} else {
		/* trateaza maparea la un singur cuvant */
		mapping = (char *) malloc(sizeof(char) * (len - i + 1));

		if (mapping == NULL)
			return 12;
		memset(mapping, 0, len - i + 1);
		strncpy(mapping, line + i + 1, len - i);

		ret = insert_into_hashmap(hashmap, symbol, mapping);

		if (ret != 0)
			return ret;
	}

	return 0;
}

/* trateaza directiva '#undef'*/
int process_undefine(char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMap *hashmap)
{
	int i = index_first_space + 1;

	char *symbol = NULL;

	/* cauta simbolul pe linia curenta*/
	while (i < len && line[i] != '\n' &&
		line[i] != '\0' && line[i] != '\t')
		++i;

	symbol = (char *) malloc(sizeof(char) *
		(i - index_first_space));

	if (symbol == NULL)
		return 12;
	memset(symbol, 0, i - index_first_space);
	strncpy(symbol, line + index_first_space + 1,
		i - index_first_space - 1);

	/* verifica daca exista in hashmap */
	if (find_in_hashmap(hashmap, symbol) != 0)
		return -1;

	/* daca exista, il sterge din hashmap */
	if (delete_from_hashmap(hashmap, symbol) != 0)
		return -1;

	if (symbol != NULL)
		free(symbol);

	return 0;
}

/* functie care decide ce functie de tratare trebuie apelata */
int decide_action(char line[IN_LINE_MAX_LEN],
	TArgs *args, THashMap *hashmap, FILE *fd)
{
	int index_first_space = 0, len = strlen(line), ret = 0, found = 0;

	char *command = NULL;

	/* cauta directiva pe linia curenta */
	while (index_first_space < len) {
		if (line[index_first_space] == ' ')
			break;
		++index_first_space;
	}

	command = (char *) malloc(sizeof(char) *
		(index_first_space + 1));

	if (command == NULL)
		return 12;
	memset(command, 0, index_first_space + 1);
	strncpy(command, line, index_first_space);

	/* vede ce tip de directiva este */
	if (strcmp(command, "#include") == 0) {
		ret = process_include(args, hashmap,
			line, index_first_space, len);
		found = 1;
	} else if (strcmp(command, "#define") == 0) {
		ret = process_define(line,
			index_first_space, len, hashmap, fd);
		found = 1;
	} else if (strcmp(command, "#undef") == 0) {
		ret = process_undefine(line,
			index_first_space, len, hashmap);
		found = 1;
	} else if (strcmp(command, "#ifdef") == 0) {
		ret = process_ifdef(args, line,
			index_first_space, len, hashmap, fd);
		found = 1;
	} else if (strcmp(command, "#ifndef") == 0) {
		ret = process_ifndef(args, line,
			index_first_space, len, hashmap, fd);
		found = 1;
	} else if (strcmp(command, "#if") == 0) {
		ret = process_if(args, line,
			index_first_space, len, hashmap, fd);
		found = 1;
	}

	/* linia este una fara nicio directiva */
	if (found == 0)
		ret = process_normal_line(args, line, len, hashmap);

	if (command != NULL)
		free(command);

	return ret;
}

/* trateaza directiva '#ifdef' */
int process_ifdef(TArgs *args, char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMap *hashmap, FILE *fd)
{
	int i = index_first_space + 1, ret = 0;

	char *symbol = NULL;

	char buffer[IN_LINE_MAX_LEN];

	/* cauta simbolul care trebuie cautat */
	while (i < len && line[i] != '\n' &&
		line[i] != '\0' && line[i] != '\t')
		++i;

	symbol = (char *) malloc(sizeof(char) *
		(i - index_first_space));

	if (symbol == NULL)
		return 12;
	memset(symbol, 0, i - index_first_space);
	strncpy(symbol, line + index_first_space + 1,
		i - index_first_space - 1);

	ret = find_in_hashmap(hashmap, symbol);

	if (symbol != NULL)
		free(symbol);

	/* daca simbolul a fost gasit in hashmap */
	if (ret == 0) {
		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				return 0;

			ret = decide_action(buffer, args, hashmap, fd);

			if (ret != 0)
				return ret;

			if (strncmp(buffer, "#else", strlen("#else")) == 0)
				break;
		}

		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL)
			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				break;
	} else {
		/* daca simbolul nu a fost gasit in hashmap */
		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#else", strlen("#else")) == 0)
				break;

			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				return 0;
		}

		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				break;

			ret = decide_action(buffer, args, hashmap, fd);

			if (ret != 0)
				return ret;
		}
	}

	return 0;
}

/* trateaza directiva '#ifndef' */
int process_ifndef(TArgs *args, char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMap *hashmap, FILE *fd)
{
	int i = index_first_space + 1, ret = 0;

	char *symbol = NULL;

	char buffer[IN_LINE_MAX_LEN];

	/* cauta simbolul care trebuie cautat */
	while (i < len && line[i] != '\n' &&
		line[i] != '\0' && line[i] != '\t')
		++i;
	symbol = (char *) malloc(sizeof(char)
		* (i - index_first_space));
	if (symbol == NULL)
		return 12;
	memset(symbol, 0, i - index_first_space);
	strncpy(symbol, line + index_first_space + 1,
		i - index_first_space - 1);

	ret = find_in_hashmap(hashmap, symbol);

	if (symbol != NULL)
		free(symbol);

	/* daca simbolul nu a fost gasit in hashmap */
	if (ret == 1) {
		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				return 0;

			if (strncmp(buffer, "#else", strlen("#else")) == 0)
				break;

			ret = decide_action(buffer, args, hashmap, fd);

			if (ret != 0)
				return ret;
		}

		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL)
			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				break;
	} else {
		/* daca simbolul a fost gasit in hashmap */
		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#else", strlen("#else")) == 0)
				break;

			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				return 0;
		}

		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				break;

			ret = decide_action(buffer, args, hashmap, fd);

			if (ret != 0)
				return ret;
		}
	}

	return 0;
}

/* trateaza directiva '#if' */
int process_if(TArgs *args, char line[IN_LINE_MAX_LEN],
	int index_first_space, int len, THashMap *hashmap, FILE *fd)
{
	int i = index_first_space + 1, ret;

	char *symbol = NULL;

	char buffer[IN_LINE_MAX_LEN];

	/* cauta simbolul/intregul */
	while (i < len && line[i] != '\n' &&
		line[i] != '\0' && line[i] != '\t')
		++i;

	if (i == len)
		--i;

	symbol = (char *) malloc(sizeof(char) *
		(i - index_first_space));
	if (symbol == NULL)
		return 12;
	memset(symbol, 0, i - index_first_space);
	strncpy(symbol, line + index_first_space + 1,
		i - index_first_space - 1);

	/* verifica daca e intreg */
	ret = atoi(symbol);
	if (ret == 0) {
		/* daca nu, il cauta in hashmap */
		ret = find_in_hashmap(hashmap, symbol);
		if (ret == 0)
			ret = atoi(get_value(hashmap, symbol));
		else
			ret = 1 - ret;
	}

	/* daca se executa codul din if */
	if (ret != 0) {
		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#endif", strlen("#endif")) == 0) {
				if (symbol != NULL)
					free(symbol);

				return 0;
			}

			ret = decide_action(buffer, args, hashmap, fd);

			if (ret != 0)
				return ret;

			if (strncmp(buffer, "#else", strlen("#else")) == 0 ||
				strncmp(buffer, "#elif", strlen("#elif")) == 0)
				break;
		}

		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				break;

		}
	} else {
		/* daca nu se executa codul din if */
		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#else", strlen("#else")) == 0)
				break;

			if (strncmp(buffer, "#elif", strlen("#elif")) == 0) {
				ret = process_if(args,
					buffer, strchr(buffer, ' ') - buffer,
					strlen(buffer), hashmap, fd);

				if (ret != 0)
					return ret;

				break;
			}

			if (strncmp(buffer, "#endif", strlen("#endif")) == 0) {
				if (symbol != NULL)
					free(symbol);

				return 0;
			}
		}

		while (fgets(buffer, IN_LINE_MAX_LEN, fd) != NULL) {
			if (strncmp(buffer, "#endif", strlen("#endif")) == 0)
				break;

			if (strncmp(buffer, "#elif", strlen("#elif")) == 0)
				ret = process_if(args,
					buffer, strchr(buffer, ' ') - buffer,
					strlen(buffer), hashmap, fd);
			else
				ret = decide_action(buffer, args, hashmap, fd);

			if (ret != 0)
				return ret;
		}
	}

	if (symbol != NULL)
		free(symbol);

	return 0;
}

/* se ocupa de procesarea unei linii fara directive */
int process_normal_line(TArgs *args, char line[IN_LINE_MAX_LEN],
	int len, THashMap *hashmap)
{
	int in_literal = 0, ret = 0;

	long long count = 0, index = 0;

	char *out_line = NULL, *copy = NULL, *tok = NULL, *saveptr = NULL,
		*tok_copy = NULL, *append = NULL, *so_far = NULL;

	/* salveaza o copie a liniei */
	if ((line[0] == '\n' || line[0] == '\0' || line[0] == '#' || len == 0))
		return 0;
	out_line = (char *) malloc(IN_LINE_MAX_LEN + 1);
	if (out_line == NULL)
		return 12;
	copy = (char *) malloc(strlen(line) + 1);
	if (copy == NULL)
		return 12;
	memset(copy, 0, strlen(line) + 1);
	memset(out_line, 0, IN_LINE_MAX_LEN + 1);
	strcpy(copy, line);

	tok = strtok_r(copy, DELIMS, &saveptr);

	/* parcurge linia dupa delimitatori */
	while (tok != NULL) {
		/* salveaza tokenul intr-o copie */
		tok_copy = (char *) malloc(strlen(tok) + 1);
		if (tok_copy == NULL)
			return 12;
		memset(tok_copy, 0, strlen(tok) + 1);
		strncpy(tok_copy, tok, strlen(tok));
		ret = find_in_hashmap(hashmap, tok_copy);
		/* se pregateste sa appenduiasca tokenul */
		append = (char *) malloc(strlen(tok) + 1);
		if (append == NULL)
			return 12;
		memset(append, 0, strlen(tok) + 1);
		strncpy(append, tok, strlen(tok));
		count = tok - copy - index;
		so_far = (char *) malloc((size_t) count + 1);
		if (so_far == NULL)
			return 12;
		memset(so_far, 0, (size_t) count + 1);
		strncpy(so_far, line + index, (size_t) count);

		/* verifica daca tokenul este intr-un literal */
		if (strchr(so_far, '\"') != NULL ||
			strchr(so_far, '\'') != NULL)
			in_literal = 1 - in_literal;

		if (ret == 0 && in_literal == 0) {
			if (append != NULL)
				free(append);
			/* inlocuieste recursiv tokenul */
			ret = compute_symbol(hashmap, tok_copy, &append);
			if (ret != 0)
				return ret;
		}

		if (so_far != NULL)
			free(so_far);

		/* adauga la linia preprocesata delimitatoarele */
		out_line = strncat(out_line, line + index, (size_t) count);
		/* si tokenul, procesat sau nu */
		out_line = strcat(out_line, append);

		index += count;
		index += strlen(tok);

		tok = strtok_r(NULL, DELIMS, &saveptr);

		if (append != NULL)
			free(append);

		if (tok_copy != NULL)
			free(tok_copy);
	}
	count = tok - copy - index;

	/* adauga ultimele delimitatoare */
	out_line = strncat(out_line, line + index, (size_t) count);

	fputs(out_line, args->out_fd);
	fflush(args->out_fd);

	if (copy != NULL)
		free(copy);

	if (out_line != NULL)
		free(out_line);

	return 0;
}

/* trateaza directiva '#include' */
int process_include(TArgs *args, THashMap *hashmap,
	char in_line[IN_LINE_MAX_LEN], int index_first_space, int len)
{
	int i = index_first_space + 1, ret = 0, j = 0, found;

	char *lib_name = NULL, *last_occur = NULL,
		*path_name = NULL, *full_name = NULL, *command = NULL;

	char buffer[IN_LINE_MAX_LEN];

	FILE *lib = NULL;

	/* cauta numele headerului */
	while (i != len && in_line[i] == ' ')
		++i;
	if (i == len)
		return -1;

	/* daca nu este header local */
	if (in_line[i] == '<') {
		fputs(in_line, args->out_fd);
	} else if (in_line[i] == '\"') {
		j = i + 1;

		/* parseaza numele headerului */
		while (j != len && in_line[j] != '\"')
			++j;
		if (j == len)
			return -1;

		lib_name = (char *) malloc(sizeof(char) * (j - i));

		if (lib_name == NULL)
			return 12;
		memset(lib_name, 0, j - i);
		strncpy(lib_name, in_line + index_first_space + 2, j - i - 1);

		/* cauta headerul */
		if (args->in_fd == stdin)
			/* in folderul curent */
			lib = fopen(lib_name, "r");
		else {
			/* in folderul fisierului sursa */
			last_occur = strrchr(args->input_filename, '/');

			if (last_occur == NULL)
				last_occur =
			strrchr(args->input_filename, '\\');
			if (last_occur == NULL)
				lib = fopen(lib_name, "r");
			else {
				path_name = (char *) malloc(last_occur -
					args->input_filename +
					2 + strlen(lib_name));

				if (path_name == NULL)
					return 12;
				memset(path_name, 0, last_occur
					- args->input_filename +
					2 + strlen(lib_name));
				strncat(path_name, args->input_filename,
					last_occur -
					args->input_filename + 1);
				strcat(path_name, lib_name);

				lib = fopen(path_name, "r");

				if (path_name != NULL)
					free(path_name);
			}
		}
		if (lib == NULL) {
			/* cauta headerul in folderele date */
			for (i = 0; i < args->no_input_dirs; ++i) {
				full_name = (char *) malloc(sizeof(char) *
					(strlen(args->input_dirs[i]) +
						3 + strlen(lib_name)));

				if (full_name == NULL)
					return 12;
				memset(full_name, 0,
					strlen(args->input_dirs[i]) +
					3 + strlen(lib_name));
				full_name = strcat(full_name,
					args->input_dirs[i]);
				full_name = strcat(full_name, "/");
				full_name = strcat(full_name, lib_name);
				lib = fopen(full_name, "r");

				if (full_name != NULL)
					free(full_name);

				if (lib != NULL)
					break;
			}
		}

		if (lib == NULL)
			return -1;

		/* preproceseaza si headerul gasit */
		while (fgets(buffer, IN_LINE_MAX_LEN, lib) != NULL) {
			ret = 0;
			index_first_space = 0;
			len = strlen(buffer);

			while (index_first_space < len) {
				if (buffer[index_first_space] == ' ')
					break;
				++index_first_space;
			}

			command = (char *) malloc(sizeof(char) *
				index_first_space + 1);

			if (command == NULL)
				return 12;
			memset(command, 0, index_first_space + 1);
			strncpy(command, buffer, index_first_space);
			found = 0;

			/* decide ce tip de comanda este */
			if (strcmp(command, "#include") == 0) {
				ret = process_include(args, hashmap, buffer,
					index_first_space, len);
				found = 1;
			} else if (strcmp(command, "#define") == 0) {
				ret = process_define(buffer,
					index_first_space,
					len, hashmap, lib);
				found = 1;
			} else if (strcmp(command, "#undef") == 0) {
				ret = process_undefine(buffer,
					index_first_space,
					len, hashmap);
				found = 1;
			} else if (strcmp(command, "#ifdef") == 0) {
				ret = process_ifdef(args,
					buffer, index_first_space,
					len, hashmap, lib);
				found = 1;
			} else if (strcmp(command, "#ifndef") == 0) {
				ret = process_ifndef(args,
				buffer, index_first_space,
					len, hashmap, lib);
				found = 1;
			} else if (strcmp(command, "#if") == 0) {
				ret = process_if(args,
					buffer, index_first_space, len,
					hashmap, lib);
				found = 1;
			}

			if (found == 0)
				ret = process_normal_line(args,
					buffer, len, hashmap);

			if (command != NULL)
				free(command);

			if (ret != 0)
				return ret;
		}

		if (lib_name != NULL)
			free(lib_name);

		if (lib != NULL)
			fclose(lib);
	}

	return 0;
}

/* executa preprocesarea liniilor */
int preprocess(TArgs *args, THashMap *hashmap)
{
	char in_line[IN_LINE_MAX_LEN];

	int ret = 0, index_first_space = 0, found = 0;

	unsigned int len = 0;

	char *command = NULL;

	/* parcurge tot fisierul de intrare */
	while (fgets(in_line, IN_LINE_MAX_LEN, args->in_fd) != NULL) {
		index_first_space = 0;

		len = strlen(in_line);

		ret = 0;

		while ((unsigned int) index_first_space < len) {
			if (in_line[index_first_space] == ' ')
				break;
			++index_first_space;
		}

		command = (char *) malloc(sizeof(char) *
			(index_first_space + 1));

		if (command == NULL)
			return 12;
		memset(command, 0, index_first_space + 1);
		strncpy(command, in_line, index_first_space);
		found = 0;

		/* decide ce tip de linie este */
		if (strcmp(command, "#include") == 0) {
			ret = process_include(args, hashmap, in_line,
				index_first_space, len);
			found = 1;
		} else if (strcmp(command, "#define") == 0) {
			ret = process_define(in_line, index_first_space,
				len, hashmap, args->in_fd);
			found = 1;
		} else if (strcmp(command, "#undef") == 0) {
			ret = process_undefine(in_line, index_first_space,
				len, hashmap);
			found = 1;
		} else if (strcmp(command, "#ifdef") == 0) {
			ret = process_ifdef(args, in_line, index_first_space,
				len, hashmap, args->in_fd);
			found = 1;
		} else if (strcmp(command, "#ifndef") == 0) {
			ret = process_ifndef(args, in_line, index_first_space,
				len, hashmap, args->in_fd);
			found = 1;
		} else if (strcmp(command, "#if") == 0) {
			ret = process_if(args, in_line, index_first_space,
				len, hashmap, args->in_fd);
			found = 1;
		}

		if (found == 0)
			ret = process_normal_line(args, in_line, len, hashmap);

		if (command != NULL)
			free(command);

		if (ret != 0)
			return ret;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int ret = 0;

	TArgs *args = NULL;

	THashMap *hashmap = NULL;

	ret = init_hashmap(&hashmap);
	if (ret != 0)
		return ret;

	/* citeste argumentele programului */
	ret = parse_input(argc, argv, hashmap, &args);
	if (ret != 0)
		return ret;

	/* citeste si preproceseaza liniile din input */
	ret = preprocess(args, hashmap);
	if (ret != 0)
		return ret;

	/* elibereaza memoria folosita */
	destroy_args(args);
	destroy_hashmap(hashmap);

	return 0;
}
