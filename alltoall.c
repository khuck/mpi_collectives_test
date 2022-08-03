#include "declarations.h"

void alltoall( MPI_Comm comm, int rank, int size ) {
    REPORT
    int chunk = 128;
    int i;
    int *sb;
    int *rb;
    int status, gstatus;

    sb = (int *)malloc(size*chunk*sizeof(int));
    if ( !sb ) {
        perror( "can't allocate send buffer" );fflush(stderr);
        MPI_Abort(comm,EXIT_FAILURE);
    }
    rb = (int *)malloc(size*chunk*sizeof(int));
    if ( !rb ) {
        perror( "can't allocate recv buffer");fflush(stderr);
        free(sb);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    for ( i=0 ; i < size*chunk ; ++i ) {
        sb[i] = rank + 1;
        rb[i] = 0;
    }
    status = MPI_Alltoall(sb, chunk, MPI_INT, rb, chunk, MPI_INT, comm);
    MPI_Allreduce( &status, &gstatus, 1, MPI_INT, MPI_SUM, comm );
    if (rank == 0) {
        if (gstatus != 0) {
            printf("all_to_all returned %d\n",gstatus);fflush(stdout);
        }
    }
    free(sb);
    free(rb);
}
