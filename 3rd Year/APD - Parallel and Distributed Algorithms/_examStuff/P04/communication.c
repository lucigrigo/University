#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 10

int main(int argc, char *argv[])  {
    int numtasks, rank, dest, source, count, tag = 1;
    char inmsg, outmsg;
    // char inmsg[MAX_LEN], outmsg[] = "Hello";
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // procesul 0 trimite catre procesul 1 si apoi asteapta raspuns
        dest = 1;
        source = 1;

        outmsg = '0';
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        // MPI_Send(outmsg, strlen(outmsg) + 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // procesul 1 asteapta mesaj de la procesul 0, apoi trimite raspuns
        dest = 0;
        source = 0;

        outmsg = '1';
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        // MPI_Recv(inmsg, MAX_LEN, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
        // MPI_Get_count(&status, MPI_CHAR, &count);
        // printf("Process %d received %d char(s) from process %d with tag %d: %s\n",
        //     rank, count, status.MPI_SOURCE, status.MPI_TAG, inmsg);
    }

    // se foloseste variabila de status pentru a afla detalii despre schimbul de date
    MPI_Get_count(&status, MPI_CHAR, &count);
    printf("Process %d received %d char(s) from process %d with tag %d: %c\n",
            rank, count, status.MPI_SOURCE, status.MPI_TAG, inmsg);

    MPI_Finalize();
}
