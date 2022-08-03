#include "declarations.h"

/*
This program tests MPI_Alltoallv by having processor i send different
amounts of data to each processor.
The first test sends i items to processor i from all processors.
*/
void alltoallv( MPI_Comm comm, int rank, int size )
{
    REPORT
    int *sbuf, *rbuf;
    int *sendcounts, *recvcounts, *rdispls, *sdispls;
    int i, j, *p, err = 0;

    /* Create the buffer */
    sbuf = (int *)malloc( size * size * sizeof(int) );
    rbuf = (int *)malloc( size * size * sizeof(int) );
    if (!sbuf || !rbuf) {
        fprintf( stderr, "Could not allocated buffers!\n" );
        MPI_Abort( comm, 1 );
    }
    /* Load up the buffers */
    for (i=0; i<size*size; i++) {
        sbuf[i] = i + 100*rank;
        rbuf[i] = -i;
    }
    /* Create and load the arguments to alltoallv */
    sendcounts = (int *)malloc( size * sizeof(int) );
    recvcounts = (int *)malloc( size * sizeof(int) );
    rdispls = (int *)malloc( size * sizeof(int) );
    sdispls = (int *)malloc( size * sizeof(int) );
    if (!sendcounts || !recvcounts || !rdispls || !sdispls) {
        fprintf( stderr, "Could not allocate arg items!\n" );fflush(stderr);
        MPI_Abort( comm, 1 );
    }
    for (i=0; i<size; i++) {
        sendcounts[i] = i;
        recvcounts[i] = rank;
        rdispls[i] = i * rank;
        sdispls[i] = (i * (i+1))/2;
    }
    CHECK(MPI_Alltoallv( sbuf, sendcounts, sdispls, MPI_INT,
                   rbuf, recvcounts, rdispls, MPI_INT, comm ));
    /* Check rbuf */
    for (i=0; i<size; i++) {
        p = rbuf + rdispls[i];
        for (j=0; j<rank; j++) {
            if (p[j] != i * 100 + (rank*(rank+1))/2 + j) {
                fprintf( stderr, "[%d] got %d expected %d for %dth\n",
                                    rank, p[j],(i*(i+1))/2 + j, j );
                fflush(stderr);
                err++;
            }
        }
    }
    free( sdispls );
    free( rdispls );
    free( recvcounts );
    free( sendcounts );
    free( rbuf );
    free( sbuf );
}
