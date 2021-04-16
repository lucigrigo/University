/* Grigore Lucian-Florin 336CA - SO Tema 2 */
#ifndef SO_STDIO_H
#define SO_STDIO_H

#if defined(__linux__)
#define FUNC_DECL_PREFIX
#elif defined(_WIN32)
#include <Windows.h>

#ifdef DLL_EXPORTS
#define FUNC_DECL_PREFIX __declspec(dllexport)
#else
#define FUNC_DECL_PREFIX __declspec(dllimport)
#endif

#else
#error "Unknown platform"
#endif

#include <stdlib.h>

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

#define SO_EOF (-1)
#define BUFFER_SIZE 4096

#define DEFAULT_LAST_OP 0
#define READ_LAST_OP 1
#define WRITE_LAST_OP 2

#define min(a, b) ((a) < (b) ? (a) : (b))

struct _so_file {
	int fd;
	unsigned char buffer[BUFFER_SIZE];
	int buffer_size;
	int curr_index;
	int last_op_type;
	long cursor;
	int eof;
	int err;
	pid_t child_pid;
};

typedef struct _so_file SO_FILE;

FUNC_DECL_PREFIX SO_FILE *so_fopen(const char *pathname, const char *mode);
FUNC_DECL_PREFIX int so_fclose(SO_FILE *stream);

#if defined(__linux__)
FUNC_DECL_PREFIX int so_fileno(SO_FILE *stream);
#elif defined(_WIN32)
FUNC_DECL_PREFIX HANDLE so_fileno(SO_FILE *stream);
#else
#error "Unknown platform"
#endif


FUNC_DECL_PREFIX int so_fflush(SO_FILE *stream);

FUNC_DECL_PREFIX int so_fseek(SO_FILE *stream, long offset, int whence);
FUNC_DECL_PREFIX long so_ftell(SO_FILE *stream);

FUNC_DECL_PREFIX
size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream);

FUNC_DECL_PREFIX
size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream);

FUNC_DECL_PREFIX int so_fgetc(SO_FILE *stream);
FUNC_DECL_PREFIX int so_fputc(int c, SO_FILE *stream);

FUNC_DECL_PREFIX int so_feof(SO_FILE *stream);
FUNC_DECL_PREFIX int so_ferror(SO_FILE *stream);

FUNC_DECL_PREFIX SO_FILE *so_popen(const char *command, const char *type);
FUNC_DECL_PREFIX int so_pclose(SO_FILE *stream);

#endif /* SO_STDIO_H */
