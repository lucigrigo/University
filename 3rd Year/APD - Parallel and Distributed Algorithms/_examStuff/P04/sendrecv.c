#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])  {
    int numtasks, rank, dest, source, count, tag = 1;
    char inmsg, outmsg;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // procesul 0 trimite catre procesul 1 si apoi asteapta raspuns
        dest = 1;
        source = 1;

        outmsg = '0';
        MPI_Sendrecv(&outmsg, 1, MPI_CHAR, dest, tag,
                        &inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
    } else if (rank == 1) {
        // procesul 1 asteapta mesaj de la procesul 0, apoi trimite raspuns
        dest = 0;
        source = 0;

        outmsg = '1';
        MPI_Sendrecv(&outmsg, 1, MPI_CHAR, dest, tag,
                        &inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
    }

    // se foloseste variabila de status pentru a afla detalii despre schimbul de date
    MPI_Get_count(&status, MPI_CHAR, &count);
    printf("Process %d received %d char(s) from process %d with tag %d: %c\n",
            rank, count, status.MPI_SOURCE, status.MPI_TAG, inmsg);

    MPI_Finalize();
}
