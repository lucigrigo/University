/* Grigore Lucian-Florin 336 CA - SO Tema 3*/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define DLL_EXPORTS
#include "loader.h"
#include "exec_parser.h"

static PVOID p_handler;

static so_exec_t *exec;

static HANDLE fd;

static LONG WINAPI seg_fault_handler(
	struct _EXCEPTION_POINTERS *ExceptionInfo
) {
	int i = 0, no_pages = 0, page_size = 0, rc = 0, bytes_read = 0;

	BOOL found = FALSE, ret = TRUE;

	so_seg_t seg;

	DWORD err_code =
		ExceptionInfo->ExceptionRecord->ExceptionCode,
		old_perm = 0, new_perm = 0;

	ULONG_PTR addr =
		ExceptionInfo->ExceptionRecord->ExceptionInformation[1],
		page_addr = 0x0;

	LPVOID p = NULL, t = NULL;

	HANDLE q = NULL;

	/* daca este alt tip de exceptie */
	if (err_code !=
		EXCEPTION_ACCESS_VIOLATION &&
		err_code !=
		EXCEPTION_IN_PAGE_ERROR)
		return EXCEPTION_CONTINUE_SEARCH;

	/* caut adresa printre segmente */
	for (i = 0; i < exec->segments_no; ++i) {
		seg = exec->segments[i];

		if (addr >= seg.vaddr &&
			addr <= seg.vaddr + seg.mem_size) {
			found = TRUE;
			break;
		}
	}

	/* daca adresa nu este in vreun segment */
	if (found == FALSE)
		exit(139);

	page_size = 0x10000;
	page_addr = (addr - seg.vaddr) / page_size;

	/* aloc memoria virtuala */
	p = VirtualAlloc(
		(LPVOID) (seg.vaddr + page_addr * page_size),
		page_size,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE);
	if (p == NULL) {
		rc = GetLastError();

		/* daca adresa a mai fost alocata */
		if (rc == ERROR_INVALID_ADDRESS)
			exit(139);
		else
			exit(-1);
	}

	/* citesc datele din HANDLE la adresa alocata */
	if (seg.file_size > page_addr * page_size) {
		rc = SetFilePointer(
			fd,
			seg.offset + page_addr * page_size,
			NULL,
			FILE_BEGIN);
		if (rc == INVALID_SET_FILE_POINTER)
			exit(-1);

		if (seg.file_size < (page_addr + 1) * page_size) {
			ret = ReadFile(
				fd,
				p,
				seg.file_size - page_addr * page_size,
				&bytes_read,
				NULL);
			if (ret == FALSE || bytes_read < 0)
				exit(-1);
		} else {
			ret = ReadFile(
				fd,
				p,
				page_size,
				&bytes_read,
				NULL);
			if (ret == FALSE || bytes_read < 0)
				exit(-1);
		}
	}

	/* setez permisiunile pentru adresa */
	if ((seg.perm & PERM_R) == PERM_R &&
		(seg.perm & PERM_X) == PERM_X &&
		(seg.perm & PERM_W) == PERM_W)
		new_perm = PAGE_EXECUTE_READWRITE;
	else if ((seg.perm & PERM_R) == PERM_R &&
		(seg.perm & PERM_X) == PERM_X)
		new_perm = PAGE_EXECUTE_READ;
	else if ((seg.perm & PERM_R) == PERM_R &&
		(seg.perm & PERM_W) == PERM_W)
		new_perm = PAGE_READWRITE;
	else if ((seg.perm & PERM_X) == PERM_X)
		new_perm = PAGE_EXECUTE;
	else if ((seg.perm & PERM_R) == PERM_R)
		new_perm = PAGE_READONLY;

		/* fixez permisiunile corect pentru adresa */
	ret = VirtualProtect(
			p,
			page_size,
			new_perm,
			&old_perm);
	if (ret == FALSE)
		exit(-1);

	return EXCEPTION_CONTINUE_EXECUTION;
}

int so_init_loader(void)
{
	/* adaugarea handler-ului pentru prinderea seg fault */
	p_handler = AddVectoredExceptionHandler(
		1,
		seg_fault_handler);

	if (p_handler == NULL)
		exit(-1);

	return -1;
}

int so_execute(char *path, char *argv[])
{
	exec = so_parse_exec(path);
	if (!exec)
		return -1;

		/* deschiderea fisierului din care copiez datele */
	fd = CreateFile(
		path,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (fd == INVALID_HANDLE_VALUE)
		exit(-1);

	so_start_exec(exec, argv);

	RemoveVectoredExceptionHandler(p_handler);

	return -1;
}
