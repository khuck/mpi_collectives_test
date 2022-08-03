#include "declarations.h"

void allgather (MPI_Comm comm, int rank, int size)
{
    REPORT
    int i,j;
    int table[MAX_PROCESSES][MAX_PROCESSES];
    int errors=0;
    int participants = size;

    /* Exactly MAX_PROCESSES processes can participate */
    if ( size >= MAX_PROCESSES ) {
        fprintf( stderr, "Number of processors must be less than %d\n", MAX_PROCESSES );
        fflush(stderr);
        MPI_Abort( comm, 1 );
    }
    if ( (rank < participants) ) {
        /* Determine what rows are my responsibility */
        int block_size = MAX_PROCESSES / participants;
        int begin_row = rank * block_size;
        int end_row = (rank+1) * block_size;
        int send_count = block_size * MAX_PROCESSES;
        int recv_count = send_count;
        /* Paint my rows my color */
        for (i=begin_row; i<end_row ;i++)
            for (j=0; j<MAX_PROCESSES; j++)
                table[i][j] = rank + 10;
        /* Everybody gets the gathered table */
        CHECK(MPI_Allgather(&table[begin_row][0], send_count, MPI_INT,
                           &table[0][0], recv_count, MPI_INT, comm));
        /* Everybody should have the same table now, */
        for (i=0; i<MAX_PROCESSES;i++) {
            if ( (table[i][0] - table[i][MAX_PROCESSES-1] !=0) )
                errors++;
        }
    }
    if (errors)
    {
        printf( "[%d] done with ERRORS(%d)!\n", rank, errors );fflush(stdout);
    }
}
