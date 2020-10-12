#include "declarations.h"

void gather(MPI_Comm comm, int rank, int size) {
    MPI_Datatype vec;
    double *vecin, *vecout;
    int minsize = 2, count;
    int root, i, n, stride, errs = 0;

    for (root=0; root<size; root++) {
        for (count = 1; count < 65000; count = count * 2) {
            n = 12;
            stride = 10;
            vecin = (double *)malloc( n * stride * size * sizeof(double) );
            vecout = (double *)malloc( size * n * sizeof(double) );

            CHECK(MPI_Type_vector( n, 1, stride, MPI_DOUBLE, &vec ));
            CHECK(MPI_Type_commit( &vec ));

            for (i=0; i<n*stride; i++) vecin[i] =-2;
            for (i=0; i<n; i++) vecin[i*stride] = rank * n + i;

            CHECK(MPI_Gather( vecin, 1, vec, vecout, n, MPI_DOUBLE, root, comm ));

            if (rank == root) {
                for (i=0; i<n*size; i++) {
                    if (vecout[i] != i) {
                        errs++;
                        if (errs < 10) {
                            fprintf( stderr, "vecout[%d]=%d\n", i, (int)vecout[i] );fflush(stderr);
                        }
                    }
                }
            }
            CHECK(MPI_Type_free( &vec ));
            free( vecin );
            free( vecout );
        }
    }

    /* do a zero length gather */
    CHECK(MPI_Gather( NULL, 0, MPI_BYTE, NULL, 0, MPI_BYTE, 0, comm ));
}

