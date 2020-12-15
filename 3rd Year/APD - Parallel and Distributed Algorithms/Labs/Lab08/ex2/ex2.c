#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define ROOT 0
#define TAG_EX2 65

int main(int argc, char *argv[])
{
    int numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int rand_num;
    // Root process generates a random number.
    if (rank == ROOT)
    {
        srand(42);
        rand_num = rand() % 20;
        printf("[ROOT] Generated num = %d\n", rand_num);
    }
    // Broadcasts to all processes.
    MPI_Bcast(&rand_num, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

    printf("Process [%d], after broadcast %d.\n", rank, rand_num);

    MPI_Finalize();
}
