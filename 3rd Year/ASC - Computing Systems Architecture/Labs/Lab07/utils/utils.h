#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fill_array_int(int *a, int N) {
    for (int i = 0; i < N; ++i) {
        a[i] = i;
    }
}

void fill_array_float(float *a, int N) {
    for (int i = 0; i < N; ++i) {
        a[i] = (float) i;
    }
}

void fill_array_random(float *a, int N) {
    for (int i = 0; i < N; ++i) {
        a[i] = (float) rand() / RAND_MAX;
    }
}

/**
 * Helper function to check your results.
 *
 * @param task: the number of task you run
 * @param a: pointer to a dynamically allocated array
 */
void check_task_1(int task, int *a) {
    int ok = 1;
    int b[16];

    printf("\n[Checking todo %d]\n", task);
    
    for (int i = 0; i < 16; ++i) {
        switch (task) {
            case 3:
                b[i] = i % 2;
                break;
            case 4:
                b[i] = i / 4;
                break;
            case 5:
                b[i] = i % 4;
                break;
        }

        ok = ok && (a[i] == b[i]);
    }

    printf("\tYour results: ");
    for (int i = 0; i < 16; ++i) printf("%d ", a[i]);

    printf("\n\tExpected results: ");
    for (int i = 0; i < 16; ++i) printf("%d ", b[i]);

    if (ok)
        printf("\n\tCheck: OK!\n");
    else
        printf("\n\tCheck: WRONG!\n");
}

void check_task_2(float *a, float *b, float *c, int N) {
    float eps = 0.001;
    float serial;
    int ok = 1;

    for (int i = 0; i < N; ++i) {
        serial = a[i] + b[i];
        if (abs(serial - c[i]) > eps) {
            printf("WRONG value at index %d: [value: %d] [expected: %d]!\n",
                i, c[i], serial);
            ok = 0;
        }
    }

    printf("\na[i]\tb[i]\tc[i]\texpected\n");
    for (int i = 0; i < 10; ++i) {
        printf("%1.3f\t%1.3f\t%1.3f\t%1.3f\n", a[i], b[i], c[i], a[i] + b[i]);
    }

    if (ok)
        printf("\nCheck: OK!\n");
    else
        printf("\nCheck: WRONG!\n");
}

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(EXIT_FAILURE);				\
		}							\
	} while (0)
