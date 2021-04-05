/* Grigore Lucian-Florin - SO Tema 1 */
#include "strtok_saved.h"

/* la fel ca strtok(), doar ca salveaza in memorie */
/* ultimul token -> saveptr */
char *strtok_r(char *s, const char *delim, char **save_ptr)
{
	char *end;

	if (s == NULL)
		s = *save_ptr;

	if (*s == '\0') {
		*save_ptr = s;
		return NULL;
	}

	s += strspn(s, delim);
	if (*s == '\0') {
		*save_ptr = s;
		return NULL;
	}

	end = s + strcspn(s, delim);
	if (*end == '\0') {
		*save_ptr = end;
		return s;
	}

	*end = '\0';
	*save_ptr = end + 1;
	return s;
}
