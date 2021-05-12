CC=gcc
CFLAGS=-Wall -Werror -O0
LIBDIRS=-L/usr/lib64/atlas
LIBS=-lsatlas

all: compare tema2_blas tema2_neopt tema2_opt_m 

tema2_blas: solver_blas.c main.c utils.h
	$(CC) $(CFLAGS) $^ $(LIBDIRS) $(LIBS) -o $@

tema2_neopt: solver_neopt.c main.c utils.h
	$(CC) $(CFLAGS) $^ -o $@

tema2_opt_m: solver_opt.c main.c utils.h
	$(CC) $(CFLAGS) $^ -o $@

compare: compare.c utils.h
	$(CC) $(OPT_CFLAGS) $^ -lm -o $@

clean:
	rm -rf compare tema2_blas tema2_neopt tema2_opt_m 
