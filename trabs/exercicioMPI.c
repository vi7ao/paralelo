#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  ARRAYSIZE    20000000
#define  MASTER       0

double  data[ARRAYSIZE];

int main (int argc, char *argv[])
{
    int   numtasks, taskid, rc, dest, offset, i, j, tag1,
          tag2, tag3, source, chunksize, leftover; 
    double mysum, sum;
    double update(int myoffset, int chunk, int myid);
    MPI_Status status;

    /***** Initializations *****/
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    printf("MPI task %d has started...  ", taskid);
    chunksize = (ARRAYSIZE / numtasks);
    leftover = (ARRAYSIZE % numtasks);
    tag2 = 1;
    tag1 = 2;
    tag3 = 3;

    /***** Master task only ******/
    if (taskid == MASTER) {

        /* Initialize the array */
        sum = 0;
        for (i = 0; i < ARRAYSIZE; i++) {
            data[i] = i * 1.0;
            sum = sum + data[i];
        }
        printf("Initialized array sum = %e\n", sum);
        printf("numtasks= %d  chunksize= %d  leftover= %d\n", numtasks, chunksize, leftover);

        /* Send each task its portion of the array - master keeps 1st part plus leftover elements */
        offset = chunksize + leftover;
        MPI_Bcast(&offset, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
        MPI_Bcast(&data[offset], chunksize, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

        /* Master does its part of the work */
        offset = 0;
        mysum = update(offset, chunksize + leftover, taskid);

        MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

        printf("Sample results: \n");
        offset = 0;
        for (i = 0; i < numtasks; i++) {
            for (j = 0; j < 5; j++)
                printf("  %e", data[offset + j]);
            printf("\n");
            offset = offset + chunksize;
        }
        printf("*** Final sum= %e ***\n", sum);
    }  /* end of master section */

    /***** Non-master tasks only *****/
    if (taskid > MASTER) {

        /* Receive my portion of array from the master task */
        MPI_Bcast(&offset, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
        MPI_Bcast(&data[offset], chunksize, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

        /* Do my part of the work */
        mysum = update(offset, chunksize, taskid);

        /* Send my results back to the master task */
        MPI_Reduce(&mysum, &sum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

    } /* end of non-master */

    MPI_Finalize();
}   /* end of main */

double update(int myoffset, int chunk, int myid) {
    int i; 
    double mysum;
    /* Perform addition to each of my array elements and keep my sum */
    mysum = 0;
    for (i = myoffset; i < myoffset + chunk; i++) {
        data[i] = data[i] + (i * 1.0);
        mysum = mysum + data[i];
    }
    printf("Task %d mysum = %e\n", myid, mysum);
    return(mysum);
}


// mpicc -o mpiex exercicioMPI.c 