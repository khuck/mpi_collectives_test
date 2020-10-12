#include "declarations.h"

void reduce_scatter(MPI_Comm comm, int rank, int size) {
    int err = 0;
    int *sendbuf, recvbuf, *recvcounts;
    int i, sumval;

    sendbuf = (int *) malloc( size * sizeof(int) );
    for (i=0; i<size; i++)
        sendbuf[i] = rank + i;
    recvcounts = (int *)malloc( size * sizeof(int) );
    for (i=0; i<size; i++)
        recvcounts[i] = 1;

    CHECK(MPI_Reduce_scatter( sendbuf, &recvbuf, recvcounts, MPI_INT, MPI_SUM, comm ));

    sumval = size * rank + ((size - 1) * size)/2;
    /* recvbuf should be size * (rank + i) */
    if (recvbuf != sumval) {
        err++;
        fprintf( stdout, "Did not get expected value for reduce scatter\n" );
        fprintf( stdout, "[%d] Got %d expected %d\n", rank, recvbuf, sumval );fflush(stdout);
    }
}

