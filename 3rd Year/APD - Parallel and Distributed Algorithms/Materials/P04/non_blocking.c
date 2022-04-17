#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 10

int main(int argc, char *argv[])  {
    int numtasks, rank, dest, source, count, flag, tag = 1;
    char inmsg[MAX_LEN], outmsg[] = "Hello";
    MPI_Status status;
    MPI_Request request;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // procesul 0 trimite catre procesul 1
        dest = 1;
        source = 1;

        sleep(3);

        MPI_Isend(outmsg, strlen(outmsg) + 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD, &request);
        // MPI_Issend(outmsg, strlen(outmsg) + 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD, &request);
        MPI_Test(&request, &flag, &status);

        if (flag) {
            printf("[P0] The send operation is over\n");
        } else {
            printf("[P0] The send operation is not over yet\n");
            MPI_Wait(&request, &status);
        }

        printf("[P0] The send operation is definitely over\n");
    } else if (rank == 1) {
        // procesul 1 asteapta mesaj de la procesul 0
        dest = 0;
        source = 0;

        sleep(1);

        MPI_Irecv(inmsg, MAX_LEN, MPI_CHAR, source, tag, MPI_COMM_WORLD, &request);
        MPI_Test(&request, &flag, &status);

        if (flag) {
            printf("[P1] The receive operation is over\n");
        } else {
            printf("[P1] The receive operation is not over yet\n");
            MPI_Wait(&request, &status);
        }
        
        MPI_Get_count(&status, MPI_CHAR, &count);
        printf("[P1] Received %d char(s) from process %d with tag %d: %s\n",
                count, status.MPI_SOURCE, status.MPI_TAG, inmsg);
    }

    MPI_Finalize();
}
