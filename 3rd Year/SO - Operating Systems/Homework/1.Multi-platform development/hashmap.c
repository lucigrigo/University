/* Grigore Lucian-Florin - SO Tema 1 */
#include "hashmap.h"

/* initializeaza si aloca hashmapul */
int init_hashmap(THashMap **hashmap)
{
	int i, j;

	(*hashmap) = (THashMap *) malloc(sizeof(THashMap));
	if ((*hashmap) == NULL)
		return 12;
	if (hashmap == NULL)
		return 12;
	(*hashmap)->prime = PRIME;

	for (i = 0; i < PRIME; ++i) {
		(*hashmap)->elems[i] = (THashMapEntry **)
			malloc(INITIAL_BUCKET_SIZE * sizeof(THashMapEntry *));
		if ((*hashmap)->elems[i] == NULL)
			return 12;

		for (j = 0; j < INITIAL_BUCKET_SIZE; ++j)
			(*hashmap)->elems[i][j] = NULL;
		(*hashmap)->sizes[i] = 0;
		(*hashmap)->capacities[i] = INITIAL_BUCKET_SIZE;
	}

	return 0;
}

/* insereaza/suprascrie in hashmap o cheie */
int insert_into_hashmap(THashMap *hashmap, char *key, char *value)
{
	int hash = calc_hash(hashmap, key), i;

	unsigned int len, key_len, mapping_len;

	char *prev = NULL;

	THashMapEntry *entry = NULL;

	/* cauta cheia prin cele existente deja */
	for (i = 0; i < hashmap->sizes[hash]; ++i) {
		len = strlen(hashmap->elems[hash][i]->symbol);
		key_len = strlen(key);
		if (len != key_len)
			continue;
		if (strcmp(key, hashmap->elems[hash][i]->symbol) == 0) {
			/* daca a gasit-o, o suprascrie */
			prev = hashmap->elems[hash][i]->mapping;

			hashmap->elems[hash][i]->mapping = value;
			free(prev);
			free(key);
			return 0;
		}
	}

	/* e nevoie sa fie alocata mai multa memorie */
	if (hashmap->sizes[hash] == hashmap->capacities[hash]) {
		hashmap->capacities[hash] = hashmap->capacities[hash] * 2;
		hashmap->elems[hash] = (THashMapEntry **)
		realloc(hashmap->elems[hash], hashmap->capacities[hash]);
		if (hashmap->elems[hash] == NULL)
			return 12;
	}

	/* creeaza noua intrare din hashmap */
	entry = (THashMapEntry *) malloc(sizeof(THashMapEntry));

	if (entry == NULL)
		return 12;
	key_len = strlen(key);
	mapping_len = strlen(value);

	entry->symbol = (char *) malloc(key_len + 1);
	if (entry->symbol == NULL)
		return 12;
	memset(entry->symbol, 0, key_len + 1);
	strncpy(entry->symbol, key, key_len);
	entry->mapping = (char *) malloc(mapping_len + 1);
	if (entry->mapping == NULL)
		return 12;
	memset(entry->mapping, 0, mapping_len + 1);
	strncpy(entry->mapping, value, mapping_len);

	if (key != NULL)
		free(key);

	if (value != NULL)
		free(value);

	/* adauga noua intrare in hashmap */
	hashmap->elems[hash][hashmap->sizes[hash]] = entry;
	hashmap->sizes[hash] = hashmap->sizes[hash] + 1;

	return 0;
}

/* cauta o cheie in hashmap */
int find_in_hashmap(THashMap *map, char *key)
{
	int hash = calc_hash(map, key), i;

	unsigned int len, key_len;

	for (i = 0; i < map->sizes[hash]; ++i) {
		len = strlen(map->elems[hash][i]->symbol);
		key_len = strlen(key);
		if (len != key_len)
			continue;
		if (strcmp(map->elems[hash][i]->symbol, key) == 0)
			return 0;
	}

	return 1;
}

/* intoarce maparea pentru un simbol, in mod recursiv */
int compute_symbol(THashMap *map, char *key, char **returned_repr)
{
	int hash = calc_hash(map, key), i, sz = 0, index = 0, ret = 0,
		count = 0;

	char *mapping = NULL, *dummy = NULL, *copy = NULL, *repr = NULL,
		*saveptr = NULL, *tok = NULL, *append = NULL, *new_repr = NULL;

	unsigned int len, key_len, len_mapping;

	/* cauta intrarea in hashmap */
	for (i = 0; i < map->sizes[hash]; ++i) {
		len = strlen(map->elems[hash][i]->symbol);
		key_len = strlen(key);
		if (len != key_len)
			continue;
		if (strcmp(map->elems[hash][i]->symbol, key) == 0) {
			mapping = map->elems[hash][i]->mapping;
			break;
		}
	}

	/* daca maparea este "" */
	if (mapping == NULL) {
		dummy = (char *) malloc(strlen("") + 1);

		if (dummy == NULL)
			return 12;
		memset(dummy, 0, strlen("") + 1);
		strcpy(dummy, "");
		(*returned_repr) = dummy;
		return 0;
	}

	len_mapping = strlen(mapping);

	copy = (char *) malloc((len_mapping + 1) * sizeof(char));

	if (copy == NULL)
		return 12;
	memset(copy, 0, len_mapping + 1);
	strncpy(copy, mapping, len_mapping);
	sz = 256;
	repr = (char *) malloc(sz);
	if (repr == NULL)
		return 12;
	memset(repr, 0, sz);
	saveptr = NULL;
	tok = strtok_r(copy, DELIMS, &saveptr);

	/* imparte maparea dupa delimitatoare */
	while (tok != NULL) {
		ret = find_in_hashmap(map, tok);

		append = (char *) malloc(strlen(tok) + 1);
		if (append == NULL)
			return 12;
		memset(append, 0, strlen(tok) + 1);
		strncpy(append, tok, strlen(tok));

		if (ret == 0) {
			if (append != NULL)
				free(append);
			/* se apeleaza recursiv, daca e necesar */
			ret = compute_symbol(map, tok, &append);
			if (ret != 0)
				return ret;
		}

		count = tok - copy - index;

		/* adauga delimitatoarele */
		repr = strncat(repr, mapping + index, count);
		/* adauga tokenul sau reprezentarea lui */
		repr = strcat(repr, append);
		index += count;
		index += strlen(tok);
		if (append != NULL)
			free(append);
		tok = strtok_r(NULL, DELIMS, &saveptr);
	}
	count = tok - copy - index;

	repr = strncat(repr, mapping + index, count);

	if (copy != NULL)
		free(copy);

	/* intoarce reprezentarea finala */
	new_repr = (char *) malloc(sizeof(char) * (strlen(repr) + 1));

	if (new_repr == NULL)
		return 12;
	memset(new_repr, 0, strlen(repr) + 1);
	strcpy(new_repr, repr);
	free(repr);

	(*returned_repr) = new_repr;
	return 0;
}

/* sterge o intrare din hashmap */
int delete_from_hashmap(THashMap *hashmap, char *key)
{
	int hash = calc_hash(hashmap, key), i;

	unsigned int len, key_len;

	/* cauta intrarea in hashmap */
	for (i = 0; i < hashmap->sizes[hash]; ++i) {
		len = strlen(hashmap->elems[hash][i]->symbol);
		key_len = strlen(key);
		if (len != key_len)
			continue;
		if (strcmp(key, hashmap->elems[hash][i]->symbol) == 0) {
			THashMapEntry *entry = hashmap->elems[hash][i];

			hashmap->sizes[hash] = hashmap->sizes[hash] - 1;

			if (hashmap->sizes[hash] > 0) {
				/* daca era singura din lista hashului */
				hashmap->elems[hash][i] =
				hashmap->elems[hash][hashmap->sizes[hash]];
				hashmap->elems[hash][hashmap->sizes[hash]]
				= NULL;
			}
			/* elibereaza memoria alocata intrarii */
			if (entry->symbol != NULL)
				free(entry->symbol);

			if (entry->mapping != NULL)
				free(entry->mapping);

			if (entry != NULL)
				free(entry);

			return 0;
		}
	}

	return -1;
}

/* intoarce valoarea unei chei din hashmap */
char *get_value(THashMap *hashmap, char *key)
{
	int hash = calc_hash(hashmap, key), i;

	unsigned int len, key_len;

	for (i = 0; i < hashmap->sizes[hash]; ++i) {
		len = strlen(hashmap->elems[hash][i]->symbol);
		key_len = strlen(key);
		if (len != key_len)
			continue;
		if (strcmp(hashmap->elems[hash][i]->symbol, key) == 0)
			return hashmap->elems[hash][i]->mapping;
	}

	return NULL;
}

/* calculeaza valoarea hash pentru o cheie */
int calc_hash(THashMap *hashmap, char *key)
{
	return (((int) (*key)) % hashmap->prime);
}

/* dezaloca complet memoria ocupata de hashmap */
void destroy_hashmap(THashMap *hashmap)
{
	int i, j;

	for (i = 0; i < hashmap->prime; ++i) {
		if (hashmap->elems[i] != NULL) {
			for (j = 0; j < hashmap->sizes[i]; ++j) {
				if (hashmap->elems[i][j]->symbol != NULL)
					free(hashmap->elems[i][j]->symbol);

				if (hashmap->elems[i][j]->mapping != NULL)
					free(hashmap->elems[i][j]->mapping);

				free(hashmap->elems[i][j]);
			}

			free(hashmap->elems[i]);
		}
	}

	free(hashmap);
}
