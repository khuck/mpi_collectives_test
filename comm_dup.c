#include "declarations.h"

#define BUFSIZE 2000

void comm_dup(MPI_Comm comm, int rank, int size) {
    MPI_Comm dcomm;
    CHECK(MPI_Comm_dup( comm, &dcomm ));
    CHECK(MPI_Comm_free(&dcomm));
}

