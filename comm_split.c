#include "declarations.h"

#define BUFSIZE 2000

void comm_split(MPI_Comm comm, int rank, int size) {
    MPI_Status status;
    MPI_Comm icomm,scomm;
    int a[10], b[10];
    int buf[BUFSIZE], *bptr, bl, i, j, color, errs=0;

    color = rank % 2;
    CHECK(MPI_Comm_split( comm, color, rank, &scomm ));
    CHECK(MPI_Intercomm_create( scomm, 0, MPI_COMM_WORLD, 1-color, 52, &icomm));
    CHECK(MPI_Comm_rank( icomm, &rank ));
    CHECK(MPI_Comm_remote_size( icomm, &size ));
    CHECK(MPI_Buffer_attach( buf, BUFSIZE ));

    for (j=0; j<10; j++) {
        for (i=0; i<10; i++) {
            a[i] = (rank + 10 * j) * size + i;
        }
        CHECK(MPI_Bsend( a, 10, MPI_INT, 0, 27+j, icomm ));
    }
    if (rank == 0) {
        for (i=0; i<size; i++) {
            for (j=0; j<10; j++) {
                int k;
                status.MPI_TAG = -10;
                status.MPI_SOURCE = -20;
                CHECK(MPI_Recv( b, 10, MPI_INT, i, 27+j, icomm, &status ));

                if (status.MPI_TAG != 27+j) {
                    errs++;
                    printf( "Wrong tag = %d\n", status.MPI_TAG );fflush(stdout);
                }
                if (status.MPI_SOURCE != i) {
                    errs++;
                    printf( "Wrong source = %d\n", status.MPI_SOURCE );fflush(stdout);
                }
                for (k=0; k<10; k++) {
                    if (b[k] != (i + 10 * j) * size + k) {
                        errs++;
                        printf( "received b[%d] = %d from %d tag %d\n", k, b[k], i, 27+j );fflush(stdout);
                    }
                }
            }
        }
    }
    CHECK(MPI_Buffer_detach( &bptr, &bl ));
    CHECK(MPI_Comm_free(&scomm));
    CHECK(MPI_Comm_free(&icomm));
}

