#include "declarations.h"
#include "memory.h"

#define ROOT 0
#define NUM_REPS 5
#define NUM_SIZES 3

void bcast(MPI_Comm comm, int rank, int size) {
    REPORT
    int *buf;
    int i, reps, n;
    int bVerify = 1;
    int sizes[NUM_SIZES] = { 100, 64*1024, 128*1024 };
    int num_errors=0, tot_errors;
    UNUSED(size);

    buf = (int *) malloc(sizes[NUM_SIZES-1]*sizeof(int));
    memset(buf, 0, sizes[NUM_SIZES-1]*sizeof(int));
    for (n=0; n<NUM_SIZES; n++)
    {
        if (rank == ROOT)
        {
            printf("bcasting %d MPI_INTs %d times\n", sizes[n], NUM_REPS);
            fflush(stdout);
        }
        for (reps=0; reps < NUM_REPS; reps++)
        {
            if (bVerify)
            {
                if (rank == ROOT)
                {
                    for (i=0; i<sizes[n]; i++)
                    {
                        buf[i] = 1000000 * (n * NUM_REPS + reps) + i;
                    }
                }
                else
                {
                    for (i=0; i<sizes[n]; i++)
                    {
                        buf[i] = -1 - (n * NUM_REPS + reps);
                    }
                }
            }
            CHECK(MPI_Bcast(buf, sizes[n], MPI_INT, ROOT, comm));
            if (bVerify)
            {
                num_errors = 0;
                for (i=0; i<sizes[n]; i++)
                {
                    if (buf[i] != 1000000 * (n * NUM_REPS + reps) + i)
                    {
                        num_errors++;
                        if (num_errors < 10)
                        {
                            printf("Error: Rank=%d, n=%d, reps=%d, i=%d, buf[i]=%d expected=%d\n", rank, n, reps, i, buf[i],
                                    1000000 * (n * NUM_REPS + reps) +i);
                            fflush(stdout);
                        }
                    }
                }
                if (num_errors >= 10)
                {
                    printf("Error: Rank=%d, num_errors = %d\n", rank, num_errors);
                    fflush(stdout);
                }
            }
        }
    }

    CHECK(MPI_Reduce( &num_errors, &tot_errors, 1, MPI_INT, MPI_SUM, 0, comm ));
    if (rank == 0 && tot_errors == 0)
        printf(" No Errors\n");
    fflush(stdout);
    free(buf);
}

