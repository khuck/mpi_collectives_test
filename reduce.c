#include "declarations.h"

void reduce(MPI_Comm comm, int rank, int size) {
    REPORT
    int errs = 0;
    int root;
    int *sendbuf, *recvbuf, i;
    int count;

    for (count = 1; count < 130000; count = count * 2) {
        sendbuf = (int *)malloc( count * sizeof(int) );
        recvbuf = (int *)malloc( count * sizeof(int) );
        for (root = 0; root < size; root ++) {
            for (i=0; i<count; i++) sendbuf[i] = i;
            for (i=0; i<count; i++) recvbuf[i] = -1;
            CHECK(MPI_Reduce( sendbuf, recvbuf, count, MPI_INT, MPI_SUM, root, comm ));
            if (rank == root) {
                for (i=0; i<count; i++) {
                    if (recvbuf[i] != i * size) {
                        errs++;
                    }
                }
            }
        }
        free( sendbuf );
        free( recvbuf );
    }

}

