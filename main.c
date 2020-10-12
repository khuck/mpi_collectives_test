#include "declarations.h"

int main( int argc, char **argv )
{
    MPI_Comm comm;
    int rank, size;

    CHECK (MPI_Init( &argc, &argv ));
    comm = MPI_COMM_WORLD;
    MPI_Comm_size( comm, &size );
    MPI_Comm_rank( comm, &rank );
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
    reduce_scatter(comm, rank, size);
    scan(comm, rank, size);
    scatter(comm, rank, size);
    scatterv(comm, rank, size);
    file_write(comm, rank, size);
    CHECK (MPI_Finalize());
    return 0;
}
