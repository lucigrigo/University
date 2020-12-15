#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ROOT 0
#define CHUCK_SIZE 5 // numarul de elemente per proces

int main (int argc, char **argv) {
    int rank, proc, a;

    int* arr;
    int* process_arr;
    int* result_arr;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc);

    if (rank == ROOT) {
        arr = malloc (CHUCK_SIZE * proc * sizeof(int));
        for (int i = 0; i < proc * CHUCK_SIZE; ++i) {
            arr[i] = 0;
        }
    }

    process_arr = malloc (CHUCK_SIZE * sizeof(int));
    MPI_Scatter(arr, CHUCK_SIZE, MPI_INT, process_arr, CHUCK_SIZE, MPI_INT, ROOT, MPI_COMM_WORLD);

    for (int i = 0; i < CHUCK_SIZE; i++) {
        printf("Before: rank [%d] - value = %d\n", rank, process_arr[i]);
        process_arr[i] = i;
        printf("After: rank [%d] - value = %d\n", rank, process_arr[i]);
    }

    if (rank == ROOT) {
        result_arr = malloc (CHUCK_SIZE * proc * sizeof(int));
    }

    MPI_Gather(process_arr, CHUCK_SIZE, MPI_INT, result_arr, CHUCK_SIZE, MPI_INT, ROOT, MPI_COMM_WORLD);

    if (rank == ROOT) {
        for (int i = 0; i < CHUCK_SIZE * proc; i++) {
            printf("%d ", result_arr[i]);
        }
        printf("\n");
    }

    if (rank == ROOT) {
        free(arr);
        free(result_arr);
    }

    free(process_arr);

    MPI_Finalize();
    return 0;
}

