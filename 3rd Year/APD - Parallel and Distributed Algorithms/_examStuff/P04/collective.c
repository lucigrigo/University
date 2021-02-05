#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 10
#define COUNT 12

int main(int argc, char *argv[])  {
    int numtasks, rank, dest, source, count, tag = 1, i;
    int bcast_value = 0, chunk;
    int *v_recv;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    chunk = COUNT / numtasks;
    v_recv = (int*)malloc(sizeof(int) * chunk);

    if (rank == 0) {
        int v[COUNT];
        bcast_value = 42;

        MPI_Bcast(&bcast_value, 1, MPI_INT, 0, MPI_COMM_WORLD);

        for (i = 0; i < COUNT; i++) {
            v[i] = i;
        }

        MPI_Scatter(v, chunk, MPI_INT, v_recv, chunk, MPI_INT, 0, MPI_COMM_WORLD);

        for (i = 0; i < chunk; i++) {
            printf("[P%d] Scatter %d\n", rank, v_recv[i]);
            v_recv[i] *= 2;
        }

        MPI_Gather(v_recv, chunk, MPI_INT, v, chunk, MPI_INT, 0, MPI_COMM_WORLD);

        printf("\n");
        for (i = 0; i < COUNT; i++) {
            printf("[P%d] Gather %d\n", rank, v[i]);
        }
    } else {
        MPI_Bcast(&bcast_value, 1, MPI_INT, 0, MPI_COMM_WORLD);

        printf("[P%d] Received broadcast value %d\n", rank, bcast_value);

        MPI_Scatter(NULL, chunk, MPI_INT, v_recv, chunk, MPI_INT, 0, MPI_COMM_WORLD);

        for (i = 0; i < chunk; i++) {
            printf("[P%d] Scatter %d\n", rank, v_recv[i]);
            v_recv[i] *= 2;
        }

        MPI_Gather(v_recv, chunk, MPI_INT, NULL, chunk, MPI_INT, 0, MPI_COMM_WORLD);
    }

    free(v_recv);

    MPI_Finalize();
}
