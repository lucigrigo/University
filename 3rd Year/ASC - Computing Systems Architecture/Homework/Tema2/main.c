/*
 * Tema 2 ASC
 * 2021 Spring
 * !!! Do not modify this file !!!
 */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define MAX_BONUS 10.0

//used to generate random numbers between [-limit, limit]
#define RANGE 1

#define SAFE_ASSERT(condition, message) while(condition) {	\
	perror(message);		\
	goto failure;			\
}

/*
 * Function which reads an input file in a specific format and fills
 * a vector of 'struct test's.
 */
int read_input_file(char *input_file, int *num_tests, struct test **tests)
{
	FILE *file = NULL;
	struct test *aux = NULL;
	int ret = 0, i = 0;

	file = fopen(input_file, "r");
	SAFE_ASSERT(file == 0, "Failed opening file");

	ret = fscanf(file, "%d\n", num_tests);
	SAFE_ASSERT(ret < 1, "Failed reading from file");

	*tests = (struct test*) malloc(*num_tests * sizeof **tests);
	SAFE_ASSERT(*tests == 0, "Failed malloc");

	aux = *tests;

	for (i = 0; i < *num_tests; i++) {
		struct test t;

		ret = fscanf(file, "%d %d %s\n", &t.N, &t.seed, t.output_save_file);
		SAFE_ASSERT(ret == 0, "Failed reading from file");

		*aux++ = t;
	}

	fclose(file);
	return 0;

failure:
	if (aux) {
		free(aux);
	}
	if (file) {
		fclose(file);
	}
	return -1;
}

/*
 * Write a NxN complex number matrix to a binary file 
 */
int write_cmat_file(char *filepath, int N, double *data) {

	int ret, fd;
	size_t size;
	double *map = NULL;

	fd = open(filepath, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0777);
	SAFE_ASSERT(fd < 0, "Error opening file for writing");

	size = N * N * sizeof(double);

	ret = lseek(fd, size - 1, SEEK_SET);
	SAFE_ASSERT(ret < 0, "Error calling lseek() to stretch file");

	ret = write(fd, "", 1);
	SAFE_ASSERT(ret < 0, "Error writing in file");

	map = (double *)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	SAFE_ASSERT(map == MAP_FAILED, "Error mapping the file");

	memcpy(map, data, size);

	ret = msync(map, size, MS_SYNC);
	SAFE_ASSERT(ret < 0, "Could not sync the file to disk"); 

	ret = munmap(map, size);
	SAFE_ASSERT(ret < 0, "Error unmapping the file");

	close(fd);
	return 0;

failure:
	if (fd > 0) {
		close(fd);
	}
	return -1;
}

/*
 * Generate the test data, based on the number of elements and
 * the seed in the struct test. Allocates the arrays and fills
 * them with random numbers in [-RANGE, RANGE] (see RANGE define
 * above).
 */
int generate_data(struct test t, double **A, int triangular)
{
	int N = t.N, i, j;
	double *aux;

	*A = (double*) calloc(N * N, sizeof(double));
	SAFE_ASSERT(*A == 0, "Failed calloc");

	aux = *A;

	srand(t.seed);

	for (i = 0; i < N; ++i) {
		for ( j = (triangular ? i : 0); j < N; ++j) {
			aux[i * N + j] = get_rand_double(RANGE);
		}
	}

	return 0;

failure:
	return -1;
}

/*
 * Generates data and runs the solver on the data.
 */
int run_test(struct test t, Solver solve, float *elapsed)
{
	double *A, *B, *res;
	int ret;
	struct timeval start, end;

	ret = generate_data(t, &A, 1);
	if (ret < 0)
		return ret;

	ret = generate_data(t, &B, 0);
	if (ret < 0)
		return ret;

	gettimeofday(&start, NULL);
	res = solve(t.N, A, B);
	gettimeofday(&end, NULL);

	if (res) {
		write_cmat_file(t.output_save_file, t.N, res);
	}

	*elapsed = ((end.tv_sec - start.tv_sec) * 1000000.0f + end.tv_usec - start.tv_usec) / 1000000.0f;

	if (A) {
		free(A);
	}
	if (B) {
		free(B);
	}
	if (res) {
		free(res);
	}

	return 0;
}

int main(int argc, char **argv) {
	int num_tests, ret, i;
	struct test *tests;
	float start_bonus_time = 8.00;
	float stop_bonus_time = 4.00;
	float bonus = 0;

	if (argc < 2) {
		printf("Please provide an input file: %s input_file\n", argv[0]);
		return -1;
	}

	ret = read_input_file(argv[1], &num_tests, &tests);
	if(ret < 0)
		return ret;
	
	for (i = 0; i < num_tests; i++) {
		float current_elapsed = 0.0f;

		ret = run_test(tests[i], my_solver, &current_elapsed);
		if (ret < 0){
			free(tests);
			return -1;
		}
		printf("Run=%s: N=%d: Time=%.6f\n", 	argv[0], tests[i].N, current_elapsed);
		if (!strcmp(argv[0], "./tema2_opt_m")) {
			if (tests[i].N == 1200) {
				float current_bonus;

				current_bonus = (start_bonus_time - current_elapsed) / stop_bonus_time * MAX_BONUS;
				if (current_bonus <= 0) {
					current_bonus = 0;
				} else if (current_bonus >= MAX_BONUS) {
					current_bonus = MAX_BONUS; 
				}

				if (current_bonus > bonus)
					bonus = current_bonus;
			}
		}
	}
	
	if (!strcmp(argv[0], "./tema2_opt_m")) {
		printf("<<< Bonus=%dp >>>\n", (int)(bonus + 0.5));
	}

	free(tests);
	return 0;
}
