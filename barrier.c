#include "declarations.h"

void barrier(MPI_Comm comm, int rank, int size) {
    REPORT
    CHECK(MPI_Barrier(comm));
    printf("Hello, world.  I am %d of %d\n", rank, size);
    fflush(stdout);
}

