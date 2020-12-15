#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROOT 3
#define TAG_EX4 15

int main(int argc, char *argv[])
{
    int numtasks, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(hostname, &len);

    int value;

    if (rank == ROOT)
    {

        // The ROOT process receives an element from any source.
        // Prints the element and the source. HINT: MPI_Status.
        for (int i = 0; i < numtasks - 1; ++i)
        {
            MPI_Status status;
            MPI_Recv(&value, 1, MPI_INT, MPI_ANY_SOURCE, TAG_EX4, MPI_COMM_WORLD, &status);
            printf("[ROOT - %d] Received from source %d value %d\n", ROOT, status.MPI_SOURCE, value);
        }
    }
    else
    {

        // Generate a random number.
        srand(time(NULL));
        value = rand() % (rank * 50 + 1);

        printf("Process [%d] send %d.\n", rank, value);

        // Sends the value to the ROOT process.
        MPI_Send(&value, 1, MPI_INT, ROOT, TAG_EX4, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
