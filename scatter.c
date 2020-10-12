#include "declarations.h"

void scatter(MPI_Comm comm, int rank, int size) {
    int i,j;
    int table[MAX_PROCESSES][MAX_PROCESSES];
    int row[MAX_PROCESSES];
    int errors=0;
    int participants;

    /* A maximum of MAX_PROCESSES processes can participate */
    if ( size > MAX_PROCESSES ) participants = MAX_PROCESSES;
    else participants = size;
    if ( (rank < participants) ) {
        int send_count = MAX_PROCESSES;
        int recv_count = MAX_PROCESSES;

        /* If I'm the root (process 0), then fill out the big table */
        if (rank == 0)
            for ( i=0; i<participants; i++)
                for ( j=0; j<MAX_PROCESSES; j++ )
                    table[i][j] = i+j;

        /* Scatter the big table to everybody's little table */
        CHECK(MPI_Scatter(&table[0][0], send_count, MPI_INT,
                         &row[0] , recv_count, MPI_INT, 0, comm));

        /* Now see if our row looks right */
        for (i=0; i<MAX_PROCESSES; i++)
            if ( row[i] != i+rank ) errors++;
    }
}

