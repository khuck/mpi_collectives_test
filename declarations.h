#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_PROCESSES 16

void allgather(MPI_Comm comm, int rank, int size);
void allgatherv(MPI_Comm comm, int rank, int size);
void allreduce(MPI_Comm comm, int rank, int size);
void alltoall(MPI_Comm comm, int rank, int size);
void alltoallv(MPI_Comm comm, int rank, int size);
void barrier(MPI_Comm comm, int rank, int size);
void bcast(MPI_Comm comm, int rank, int size);
void gather(MPI_Comm comm, int rank, int size);
void gatherv(MPI_Comm comm, int rank, int size);
void reduce(MPI_Comm comm, int rank, int size);
void reduce_scatter(MPI_Comm comm, int rank, int size);
void scan(MPI_Comm comm, int rank, int size);
void scatter(MPI_Comm comm, int rank, int size);
void scatterv(MPI_Comm comm, int rank, int size);
void file_write(MPI_Comm comm, int rank, int size);

#define CHECK(x) do { \
int err = (x); \
if (err != MPI_SUCCESS) { \
    fprintf(stderr, "Runtime error: %s returned %d at %s:%d", #x, err, __FILE__, __LINE__); \
    MPI_Abort(comm, err); \
} } while (0);

