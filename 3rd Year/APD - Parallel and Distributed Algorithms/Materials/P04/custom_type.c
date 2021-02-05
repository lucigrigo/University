#include <mpi.h>
#include <stdio.h>

// structura aflata la baza tipului custom
typedef struct {
    float f1, f2;
    char c;
    int i[2];
} custom_type;

int main(int argc, char *argv[])  {
    int numtasks, rank, source = 0, dest = 1, tag = 1;

    custom_type t;
    MPI_Datatype customtype, oldtypes[3];
    int blockcounts[3];
    MPI_Aint offsets[3];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    // campurile de tip float
    offsets[0] = 0;
    oldtypes[0] = MPI_FLOAT;
    blockcounts[0] = 2;

    // campul de tip char, cu offset la doua valori float
    offsets[1] = 2 * sizeof(float);
    oldtypes[1] = MPI_CHAR;
    blockcounts[1] = 1;

    // campul de tip int array, cu offset la doua valori float si un char
    offsets[2] = offsets[1] + sizeof(char);
    oldtypes[2] = MPI_INT;
    blockcounts[2] = 2;

    // se defineste tipul nou si se comite
    MPI_Type_create_struct(3, blockcounts, offsets, oldtypes, &customtype);
    MPI_Type_commit(&customtype);

    if (rank == 0) {
        t.f1 = 0.5;
        t.f2 = -1.2;
        t.c = 'a';
        t.i[0] = 0;
        t.i[1] = 1;
        MPI_Send(&t, 1, customtype, dest, tag, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(&t, 1, customtype, source, tag, MPI_COMM_WORLD, &status);
        printf("Received custom type with f1=%.1f, f2=%.1f, c=%c, i[0]=%d, i[1]=%d\n", t.f1, t.f2, t.c, t.i[0], t.i[1]);
    }

    // se elibereaza tipul nou cand nu se mai foloseste
    MPI_Type_free(&customtype);

    MPI_Finalize();
}
