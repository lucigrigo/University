#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

#define INIT_VALUE -999999

int N;

void compareVectors(int * a, int * b) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		if(a[i]!=b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int * v) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");
}

int cmp(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A-B;
}

// Use 'mpirun -np 20 --oversubscribe ./pipeline_sort' to run the application with more processes
int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	if (rank == 0) { // This code is run by a single process
		int intialValue = -1;
		int sorted = 0;
		int aux;
		int *v = (int*)malloc(sizeof(int) * (nProcesses - 1));
		int *vQSort = (int*)malloc(sizeof(int) * (nProcesses - 1));
		int i, val;

		// generate the vector v with random values
		// DO NOT MODIFY
		srandom(42);
		for(i = 0; i < nProcesses - 1; i++)
			v[i] = random() % 200;
		N = nProcesses - 1;
		displayVector(v);

		// make copy to check it against qsort
		// DO NOT MODIFY
		for(i = 0; i < nProcesses - 1; i++)
			vQSort[i] = v[i];
		qsort(vQSort, nProcesses - 1, sizeof(int), cmp);

		// TODO sort the vector v
        for(int i = 0; i < nProcesses - 1; ++i) {
            MPI_Send(&v[i], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        }

        for(int i = 1; i < nProcesses; ++i) {
            int val;
            MPI_Recv(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD, NULL);
            v[i - 1] = val;
        }

		displayVector(v);
		compareVectors(v, vQSort);
	} else {
		// TODO sort the vector v
        int actual_value = INIT_VALUE;

		for(int i = rank; i <= nProcesses - 1; ++i) {
            int recv_value;
            MPI_Recv(&recv_value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, NULL);

            if(actual_value == INIT_VALUE) {
                actual_value = recv_value;
            } else if(actual_value <= recv_value) {
                MPI_Send(&recv_value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            } else {
                MPI_Send(&actual_value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                actual_value = recv_value;
            }
        }

        MPI_Send(&actual_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}