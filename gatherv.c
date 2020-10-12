#include "declarations.h"

void gatherv(MPI_Comm comm, int rank, int size) {
    int buffer[6];
    int i;
    int receive_counts[4] = { 0, 1, 2, 3 };
    int receive_displacements[4] = { 0, 0, 1, 3 };

    for (i=0; i<rank; i++)
    {
        buffer[i] = rank;
    }
    CHECK(MPI_Gatherv(buffer, rank, MPI_INT, buffer, receive_counts, receive_displacements, MPI_INT, 0, comm));
    if (rank == 0)
    {
        for (i=0; i<6; i++)
        {
            printf("[%d]", buffer[i]);
        }
        printf("\n");
        fflush(stdout);
    }
}

