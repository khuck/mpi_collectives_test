#include "declarations.h"

#define BUFSIZE 2000

/* Test intercomm merge, including the choice of the high value */

void GetIntercomm( MPI_Comm comm, int rank, int size, MPI_Comm *comm0, int *isLeftGroup )
{
    REPORT
    MPI_Comm mcomm;
    int rleader;

    /* Split comm world in half */
    if (size > 1) {
        CHECK(MPI_Comm_split( comm, (rank < size/2), rank, &mcomm ));
        if (rank == 0) {
            rleader = size/2;
        }
        else if (rank == size/2) {
            rleader = 0;
        }
        else {
            /* Remote leader is signficant only for the processes designated local leaders */
            rleader = -1;
        }
        *isLeftGroup = rank < size/2;
        CHECK(MPI_Intercomm_create( mcomm, 0, comm, rleader, 12345, comm0 ));
        CHECK(MPI_Comm_free( &mcomm ));
    } else {
        *comm0 = MPI_COMM_NULL;
	}
}

void intercomm(MPI_Comm comm, int rank, int size) {
    int errs = 0;
    int rsize;
    int nsize, nrank;
    int isLeft;
    MPI_Comm comm0, comm1, comm2, comm3, comm4;

    GetIntercomm( comm, rank, size, &comm0, &isLeft );
    /* Determine the sender and receiver */
    CHECK(MPI_Comm_rank( comm0, &rank ));
    CHECK(MPI_Comm_remote_size( comm0, &rsize ));
    CHECK(MPI_Comm_size( comm0, &size ));

    /* Try building intercomms */
    CHECK(MPI_Intercomm_merge( comm0, isLeft, &comm1 ));
    /* Check the size and ranks */
    CHECK(MPI_Comm_size( comm1, &nsize ));
    CHECK(MPI_Comm_rank( comm1, &nrank ));
    if (nsize != size + rsize) {
        errs++;
        printf( "(1) Comm size is %d but should be %d\n", nsize, size + rsize );fflush(stdout);
        if (isLeft) {
            /* The left processes should be high */
            if (nrank != rsize + rank) {
                errs++;
                printf( "(1) rank for high process is %d should be %d\n", nrank, rsize + rank );fflush(stdout);
            }
        }
        else {
            /* The right processes should be low */
            if (nrank != rank) {
                errs++;
                printf( "(1) rank for low process is %d should be %d\n", nrank, rank );fflush(stdout);
            }
        }
    }

    CHECK(MPI_Intercomm_merge( comm0, !isLeft, &comm2 ));
    /* Check the size and ranks */
    CHECK(MPI_Comm_size( comm1, &nsize ));
    CHECK(MPI_Comm_rank( comm1, &nrank ));
    if (nsize != size + rsize) {
        errs++;
        printf( "(2) Comm size is %d but should be %d\n", nsize, size + rsize );fflush(stdout);
        if (!isLeft) {
            /* The right processes should be high */
            if (nrank != rsize + rank) {
                errs++;
                printf( "(2) rank for high process is %d should be %d\n", nrank, rsize + rank );fflush(stdout);
            }
        }
        else {
            /* The left processes should be low */
            if (nrank != rank) {
                errs++;
                printf( "(2) rank for low process is %d should be %d\n", nrank, rank );fflush(stdout);
            }
        }
    }

    CHECK(MPI_Intercomm_merge( comm0, 0, &comm3 ));
    CHECK(MPI_Intercomm_merge( comm0, 1, &comm4 ));

    CHECK(MPI_Comm_free( &comm1 ));
    CHECK(MPI_Comm_free( &comm2 ));
    CHECK(MPI_Comm_free( &comm3 ));
    CHECK(MPI_Comm_free( &comm4 ));
}

