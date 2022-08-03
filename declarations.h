#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_PROCESSES 16

#define REPORT \
char * __rankstr = getenv("OMPI_COMM_WORLD_RANK"); \
int __rank = atoi(__rankstr); \
if (__rank == 0) printf("%s {%s +%d}\n", __func__, __FILE__, __LINE__);

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

void comm_split(MPI_Comm comm, int rank, int size);
void comm_dup(MPI_Comm comm, int rank, int size);
void intercomm(MPI_Comm comm, int rank, int size);

#define CHECK(x) do { \
int err = (x); \
if (err != MPI_SUCCESS) { \
    fprintf(stderr, "Runtime error: %s returned %d at %s:%d", #x, err, __FILE__, __LINE__); \
    MPI_Abort(comm, err); \
} } while (0);

#define UNUSED(expr) do { (void)(expr); } while (0)

