/* Grigore Lucian-Florin 336CA - SO Tema 2 */
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include "so_stdio.h"

/* functie care creeaza un element de tipul SO_FILE* */
SO_FILE *so_fopen(const char *pathname, const char *mode)
{
	SO_FILE *stream = (SO_FILE *) malloc(sizeof(*stream));

	if (stream == NULL)
		return NULL;
	memset(stream->buffer, 0, BUFFER_SIZE);
	stream->buffer_size = 0;
	stream->curr_index = 0;
	stream->last_op_type = DEFAULT_LAST_OP;
	stream->cursor = 0;
	stream->eof = 0;
	stream->err = 0;
	stream->fd = INVALID_HANDLE_VALUE;
	stream->append = FALSE;

	/* setarea permisiunilor in functie de modul de deschidere */
	if (strcmp(mode, "r") == 0) {
		stream->fd = CreateFile(pathname, GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
		if (stream->fd == INVALID_HANDLE_VALUE) {
			free(stream);
			return NULL;
		}
	} else if (strcmp(mode, "r+") == 0) {
		stream->fd = CreateFile(pathname, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (stream->fd == INVALID_HANDLE_VALUE) {
			free(stream);
			return NULL;
		}
	} else if (strcmp(mode, "w") == 0) {
		stream->fd = CreateFile(pathname, GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
		if (stream->fd == INVALID_HANDLE_VALUE) {
			free(stream);
			return NULL;
		}
	} else if (strcmp(mode, "w+") == 0) {
		stream->fd = CreateFile(pathname, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
		if (stream->fd == INVALID_HANDLE_VALUE) {
			free(stream);
			return NULL;
		}
	} else if (strcmp(mode, "a") == 0) {
		stream->fd = CreateFile(pathname, GENERIC_READ | FILE_APPEND_DATA,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
		if (stream->fd == INVALID_HANDLE_VALUE) {
			free(stream);
			return NULL;
		}
		stream->append = TRUE;
	} else if (strcmp(mode, "a+") == 0) {
		stream->fd = CreateFile(pathname,
		GENERIC_READ | GENERIC_WRITE | FILE_APPEND_DATA,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
		if (stream->fd == INVALID_HANDLE_VALUE) {
			free(stream);
			return NULL;
		}
		stream->append = TRUE;
	} else {
		free(stream);
		stream = NULL;
		return NULL;
	}

	if (stream->fd == INVALID_HANDLE_VALUE) {
		free(stream);
		return NULL;
	}

	return stream;
}

/* functie care inchide un SO_FILE* */
int so_fclose(SO_FILE *stream)
{
	int ret = 0, curr_ret = 0;

	BOOL check = TRUE;

	/* la final se da si flush la buffer */
	curr_ret = so_fflush(stream);
	if (curr_ret == -1)
		ret = -1;

	/* se inchide file descriptorul */
	check = CloseHandle(stream->fd);
	if (check == FALSE)
		ret = -1;

	if (stream != NULL)
		free(stream);

	return ret;
}

/* intoarce fd-ul deschis de SO_FILE* */
HANDLE so_fileno(SO_FILE *stream)
{
	return stream->fd;
}

/* functie care da flush la buffer */
int so_fflush(SO_FILE *stream)
{
	int ret = 0, sz = 0;

	BOOL check;

	/* doar daca ultima operatie a fost de scriere in buffer */
	if (stream->last_op_type != WRITE_LAST_OP)
		return 0;

	if (stream->append == TRUE) {
		ret = so_fseek(stream, 0, SEEK_END);

		if (ret == -1)
			return -1;
	}

	/* se scrie pana cand se goleste buffer-ul */
	while (sz < stream->curr_index) {
		check = WriteFile(stream->fd, stream->buffer + sz,
		stream->curr_index - sz, &ret, NULL);
		if (check == FALSE)
			return SO_EOF;
		sz += ret;
	}

	/* golirea bufferului */
	stream->buffer_size = 0;
	stream->curr_index = 0;
	memset(stream->buffer, 0, BUFFER_SIZE);

	return 0;
}

/* seteaza cursorul din fisierul deschis de SO_FILE* */
int so_fseek(SO_FILE *stream, long offset, int whence)
{
	int ret;

	/* modifica bufferul in functie de ultima operatie */
	if (stream->last_op_type == READ_LAST_OP) {
		memset(stream->buffer, 0, BUFFER_SIZE);
		stream->buffer_size = 0;
		stream->curr_index = 0;
	} else if (stream->last_op_type == WRITE_LAST_OP) {
		so_fflush(stream);
	}

	ret = SetFilePointer(stream->fd, offset, NULL, whence);
	if (ret == INVALID_SET_FILE_POINTER) {
		stream->err = stream->err + 1;
		return -1;
	}

	/* memoreaza noul cursor */
	stream->cursor = ret;
	stream->last_op_type = DEFAULT_LAST_OP;
	return 0;
}

/* intoarce cursorul din SO_FILE* */
long so_ftell(SO_FILE *stream)
{
	return stream->cursor;
}

/* citeste intr-un pointer din stream */
size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	int ret = 0;

	size_t sz = 0, no_elems = 0;

	if (stream->last_op_type != READ_LAST_OP)
		ret = so_fflush(stream);

	/* se foloseste de so_fgetc */
	stream->last_op_type = READ_LAST_OP;
	while (no_elems < nmemb) {
		sz = 0;
		while (sz < size) {
			ret = so_fgetc(stream);
			if (ret < 0)
				return no_elems;
			memcpy(ptr, &ret, 1);
			((char *)ptr)++;
			sz++;
		}
		no_elems++;
	}

	return no_elems;
}

/* scrie in stream dintr-un pointer pasat ca argument */
size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	int ret = 0, chr = 0;

	size_t no_elems = 0, sz = 0;

	/* se foloseste de so_fputc */
	while (no_elems < nmemb) {
		sz = 0;
		while (sz < size) {
			memcpy(&chr, ptr, 1);
			ret = so_fputc(chr, stream);
			if (ret == SO_EOF)
				return 0;
			((char *)ptr)++;
			sz++;
		}
		no_elems++;
	}

	return no_elems;
}

/* citeste un caracter din stream si il intoarce */
int so_fgetc(SO_FILE *stream)
{
	int ret = 0, no_read = 0;

	BOOL check = TRUE;

	ret = so_fflush(stream);

	if (stream->buffer_size == 0
		|| stream->curr_index == stream->buffer_size) {

		check = ReadFile(stream->fd, stream->buffer,
		BUFFER_SIZE, &no_read, NULL);
		stream->buffer_size = no_read;
		if (check == FALSE || no_read == 0) {
			stream->eof = 1;
			stream->err = stream->err + 1;
			return SO_EOF;
		}
		stream->curr_index = 0;
	}

	ret = (int) stream->buffer[stream->curr_index];
	stream->curr_index = stream->curr_index + 1;
	stream->last_op_type = READ_LAST_OP;
	stream->cursor = stream->cursor + 1;

	return ret;
}

/* scrie un caracter pasat ca argument in stream */
int so_fputc(int c, SO_FILE *stream)
{
	int ret;

	if (stream->last_op_type != WRITE_LAST_OP) {
		memset(stream->buffer, 0, BUFFER_SIZE);
		stream->curr_index = 0;
		stream->buffer_size = BUFFER_SIZE;
	}

	stream->buffer[stream->curr_index] = (unsigned char) c;
	stream->curr_index = stream->curr_index + 1;
	stream->last_op_type = WRITE_LAST_OP;
	stream->cursor = stream->cursor + 1;

	/* da flush daca bufferul este plin */
	if (stream->curr_index == stream->buffer_size) {
		ret = so_fflush(stream);

		if (ret == SO_EOF) {
			stream->eof = 1;
			stream->err = stream->err + 1;
			return SO_EOF;
		}

		memset(stream->buffer, 0, BUFFER_SIZE);
		stream->curr_index = 0;
		stream->buffer_size = BUFFER_SIZE;
	}

	return c;
}

/* verifica daca s-a ajuns la finalul streamului */
int so_feof(SO_FILE *stream)
{
	return stream->eof;
}

/* verifica daca a avut loc vreo eroare in timpul executiei curente */
int so_ferror(SO_FILE *stream)
{
	return stream->err;
}

/* deschide un nou proces folosind pipe() si fork() */
SO_FILE *so_popen(const char *command, const char *type)
{
	return NULL;
}

/* inchide un proces */
int so_pclose(SO_FILE *stream)
{
	return 0;
}
