#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int numtasks, rank, len; 
    char hostname[MPI_MAX_PROCESSOR_NAME];

    // se initializeaza MPI
    MPI_Init(&argc, &argv);

    // se citeste numarul de task-uri (procese)
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    // se citeste rangul procesului curent
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // se citeste numele masinii pe care ruleaza acest proces
    MPI_Get_processor_name(hostname, &len);

    printf("Hello world from task %d (out of %d) running on %s\n", rank, numtasks, hostname);

    // se finalizeza partea de MPI
    MPI_Finalize();
}
