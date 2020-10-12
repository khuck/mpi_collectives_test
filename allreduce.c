#include "declarations.h"

void allreduce(MPI_Comm comm, int rank, int size) {
    int count = 1000;
    int *in, *out, *sol;
    int i, fnderr=0;

    in = (int *)malloc( count * sizeof(int) );
    out = (int *)malloc( count * sizeof(int) );
    sol = (int *)malloc( count * sizeof(int) );
    for (i=0; i<count; i++)
    {
        *(in + i) = i;
        *(sol + i) = i*size;
        *(out + i) = 0;
    }
    CHECK(MPI_Allreduce( in, out, count, MPI_INT, MPI_SUM, comm ));
    for (i=0; i<count; i++)
    {
        if (*(out + i) != *(sol + i))
        {
            fnderr++;
        }
    }
    if (fnderr)
    {
        fprintf( stderr, "(%d) Error for type MPI_INT and op MPI_SUM\n", rank );
        fflush(stderr);
    }
    free( in );
    free( out );
    free( sol );
}