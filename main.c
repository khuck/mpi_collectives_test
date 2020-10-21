#include "declarations.h"

int main( int argc, char **argv )
{
    MPI_Comm comm;
    int rank, size;

    comm = MPI_COMM_WORLD;
    CHECK (MPI_Init( &argc, &argv ));
    MPI_Comm_size( comm, &size );
    MPI_Comm_rank( comm, &rank );
#if 0
    allgather(comm, rank, size);
    allgatherv(comm, rank, size);
    allreduce(comm, rank, size);
    alltoall(comm, rank, size);
    alltoallv(comm, rank, size);
    barrier(comm, rank, size);
    bcast(comm, rank, size);
    gather(comm, rank, size);
    gatherv(comm, rank, size);
    reduce(comm, rank, size);
#endif
    reduce_scatter(comm, rank, size);
#if 0
    scan(comm, rank, size);
    scatter(comm, rank, size);
    scatterv(comm, rank, size);
    file_write(comm, rank, size);
    comm_split(comm, rank, size);
    comm_dup(comm, rank, size);
    comm_dup(MPI_COMM_SELF, rank, size);
    intercomm(comm, rank, size);
#endif
    CHECK (MPI_Finalize());
    return 0;
}
