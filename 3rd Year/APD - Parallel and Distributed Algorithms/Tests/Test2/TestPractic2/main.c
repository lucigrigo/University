/*
    Grigore Lucian-Florin   -   336CA
    Algoritmi Paraleli si Distribuiti
            Test practic 2
*/
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define CONVERGENCE_COEF 100

/**
 * Run: mpirun -np 12 ./a.out
 */

static int num_neigh;
static int *neigh;

void read_neighbours(int rank)
{
    FILE *fp;
    char file_name[15];
    sprintf(file_name, "./files/%d.in", rank);

    fp = fopen(file_name, "r");
    fscanf(fp, "%d", &num_neigh);

    neigh = malloc(sizeof(int) * num_neigh);

    for (size_t i = 0; i < num_neigh; i++)
        fscanf(fp, "%d", &neigh[i]);
}

void compute_distances(int rank, int nProcesses)
{
    // initializez vectorul de distante
    int *dist = (int *)malloc(nProcesses * sizeof(int));
    memset(dist, -1, nProcesses * sizeof(int));

    // initializez vectorul in care voi primi distantele
    int *recv_dist = (int *)malloc(nProcesses * sizeof(int));
    memset(recv_dist, -1, nProcesses * sizeof(int));

    // actualizez distanta pana la mine si la vecinii mei
    dist[rank] = 0;
    for (int i = 0; i < num_neigh; ++i)
        dist[neigh[i]] = 1;

    /* Executam acest pas pana ajungem la convergenta */
    for (int k = 0; k < CONVERGENCE_COEF; k++)
    {
        for (int i = 0; i < num_neigh; ++i)
        {
            MPI_Status status;
            // trimit vectorul de distante propriu
            MPI_Send(dist, nProcesses, MPI_INT, neigh[i], 0, MPI_COMM_WORLD);

            // astept de la vecin vectorul lui de distante
            MPI_Recv(recv_dist, nProcesses, MPI_INT, neigh[i], 0, MPI_COMM_WORLD, &status);

            // verific ce am primit
            if (status.MPI_ERROR != 0)
            {
                printf("Error while receiving on worker %d\n", rank);
                exit(-1);
            }

            // actualizez vectorul meu de distante
            for (int j = 0; j < nProcesses; ++j)
            {
                if (recv_dist[j] > 0)
                {
                    if (dist[j] != -1)
                        dist[j] = min(dist[j], recv_dist[j] + dist[neigh[i]]);
                    else
                        dist[j] = recv_dist[j] + dist[neigh[i]];
                }
            }
        }
    }

    // astept sa termin de executat operatiile pe toti workerii
    MPI_Barrier(MPI_COMM_WORLD);

    // printez distantele de la fiecare nod
    for (int i = 0; i < nProcesses; ++i)
    {
        if (rank == i)
        {
            printf("De la nodul %d: ", rank);
            for (int j = 0; j < nProcesses; ++j)
            {
                printf("%d ", dist[j]);
            }
            printf("\n");
        }

        MPI_Barrier(MPI_COMM_WORLD);
    }
}

int main(int argc, char *argv[])
{
    int rank, nProcesses;

    // initializare MPI, aflarea rankului din topologie si a numarului de noduri
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    if (nProcesses != 12)
    {
        printf("please run with: mpirun --oversubscribe -np 12 %s\n", argv[0]);
        MPI_Finalize();
        exit(0);
    }

    // citire vecini
    read_neighbours(rank);

    // calcularea distantelor
    compute_distances(rank, nProcesses);

    MPI_Finalize();
    return 0;
}