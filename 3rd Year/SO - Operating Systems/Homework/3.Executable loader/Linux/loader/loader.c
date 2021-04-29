/*
	Grigore Lucian-Florin
	336CA
	Sisteme de Operare
	Tema 3 - Loader de executabile
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "exec_parser.h"

/* macro folosit pentru tratarea erorilor */
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(EXIT_FAILURE);				\
		}							\
	} while (0)

static so_exec_t *exec;

/* structura pentru tratarea SIGSEGV */
static struct sigaction sa;

/* handler default pentru SIGSEGV */
static struct sigaction prev;

/* fd pentru executabil */
static int fd;

/* structura retinuta in seg.data */
struct seg_data {
	int *pages;
	int no_pages;
	int page_size;
};

/* handler-ul pentru SIGSEGV */
static void handler(int signum, siginfo_t *info, void *ucontext)
{
	int i = 0, found = 0, rc = 0, page_addr = 0, no_pages = 0, page_size = 0;

	void *p;

	so_seg_t seg;

	struct seg_data *seg_data = NULL;

	/* daca este alt semnal, rulam handler-ul default */
	if (signum != SIGSEGV) {
		prev.sa_sigaction(signum, info, ucontext);
		return;
	}

	/* cautam segmentul de care apartine adresa */
	for (i = 0; i < exec->segments_no; ++i) {
		seg = exec->segments[i];
		if (info->si_addr >= (void *) seg.vaddr &&
			info->si_addr < (void *) seg.vaddr + seg.mem_size) {
			found = 1;
			seg_data = (struct seg_data *) seg.data;
			break;
		}
	}

	/* daca suntem in afara zonelor cunoscute */
	if (found == 0) {
		prev.sa_sigaction(signum, info, ucontext);
		return;
	}

	page_size = seg_data->page_size;
	page_addr = ((int) info->si_addr - seg.vaddr) / page_size;

	/* daca pagina curenta a fost mapata anterior */
	no_pages = seg_data->no_pages;
	for (i = 0; i < no_pages; ++i) {
		if (page_addr == seg_data->pages[i]) {
			prev.sa_sigaction(signum, info, ucontext);
			return;
		}
	}

	/* alocam memorie pentru memorarea paginilor mapate */
	if (seg_data->pages == NULL) {
		seg_data->pages =
			calloc((seg.mem_size / page_size + 1), sizeof(int));
		DIE(seg_data->pages == NULL, "malloc err");
	}

	/* mapam pagina curenta */
	p = mmap((void *) seg.vaddr + page_addr * page_size, page_size, PERM_W,
		MAP_ANONYMOUS | MAP_SHARED | MAP_FIXED, -1, 0);
	DIE(p == MAP_FAILED, "mmap err");

	/* doar daca sunt date de copiat din fisier */
	if (seg.file_size > page_addr * page_size) {
		/* ne mutam unde trebuie in fisier */
		rc = lseek(fd, seg.offset + page_addr * page_size, SEEK_SET);
		DIE(rc == -1, "lseek err");

		/* daca pagina curenta s-ar umple de date sau nu */
		if (seg.file_size < (page_addr + 1) * page_size) {
			rc = read(fd, p, seg.file_size - page_addr * page_size);
			DIE(rc < 0, "first read err");
		} else {
			rc = read(fd, p, page_size);
			DIE(rc < 0, "second read err");
		}
	}

	/* schimbam protectia paginii*/
	rc = mprotect(p, page_size, seg.perm);
	DIE(rc == -1, "mprotect err");

	/* memoram pagina curenta */
	seg_data->pages[seg_data->no_pages] = page_addr;
	seg_data->no_pages = seg_data->no_pages + 1;
}

/* initializarea handler-ului nou si memorarea celui vechi */
int so_init_loader(void)
{
	int rc = 0;

	memset(&sa, 0, sizeof(struct sigaction));
	memset(&prev, 0, sizeof(struct sigaction));

	sa.sa_flags = SA_SIGINFO;
	sa.sa_flags |= SA_NODEFER;

	rc = sigemptyset(&sa.sa_mask);
	DIE(rc < 0, "empty set err");

	rc = sigaddset(&sa.sa_mask, SIGSEGV);
	DIE(rc < 0, "add sigsegv to set err");

	sa.sa_sigaction = handler;

	rc = sigaction(SIGSEGV, &sa, &prev);
	DIE(rc < 0, "sigaction err");

	return 0;
}

int so_execute(char *path, char *argv[])
{
	int i, page_size = getpagesize();

	exec = so_parse_exec(path);
	if (!exec)
		return -1;

	/* deschidere fisier pentru citire */
	fd = open(path, O_RDONLY);
	DIE(fd < 0, "fd err");

	/* initializare seg.data */
	for (i = 0; i < exec->segments_no; ++i) {
		exec->segments[i].data = malloc(sizeof(struct seg_data));
		DIE(exec->segments[i].data == NULL, "malloc err");
		memset(exec->segments[i].data, 0, sizeof(struct seg_data));

		((struct seg_data *) exec->segments[i].data)->page_size = page_size;
		((struct seg_data *) exec->segments[i].data)->pages = NULL;
		((struct seg_data *) exec->segments[i].data)->no_pages = 0;
	}

	so_start_exec(exec, argv);

	return -1;
}
