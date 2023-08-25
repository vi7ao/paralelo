/*
Comunicação ponto-a-ponto

Síncrono:


*/

/*
#include "mpi.h"

MPI_Send(&buffer, count, type, dest, tag, comm);
MPI_Recv(&buffer, count, type, src, tag, comm, &status);
*/
/* 
status pode ser MPI_STATUSES_IGNORE
src pode ser MPI_ANY_SOURCE nao recomendado
tag pode ser MPI_ANY_TAG nao recomendado
WILD CARD

MPI_INT
   _FLOAT
   _BYTE
   _CHAR
   _DOUBLE
*/
/*

MPI_Sendrecv(&sendbuf, sendcount, sendtype, dest, sendtag, &recvbuf, recvcount, recvtype, src, recvtag, comm, &status);
*/

/*
Assíncrono:
*/

/*
MPI_Isend(&buffer, count, type, dest, tag, comm, &request);
MPI_Irecv(&buffer, count, type, src, tag, comm, &request);

MPI_Wait(&request, &status);
MPI_Test(&request, &flag, &status);
MPI_Waitany(count, &vetor_requisicoes, request, &indice, &status);
MPI_Testany(count, &vetor_requisicoes, &indice, &flag, &status);
MPI_Waitall(count, &vetor_requisicoes, &status);
MPI_Testall(count, &vetor_requisicoes, &flag, &vetor_status);

MPI_Waitsome(count, &vetor_requisicoes, &outcount, &vetor_offsets, &vetor_status);
MPI_Testsome(incount, &vetor_requisicoes, &outcount, &vetor_offsets, &vetor_status); */

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[]){
    int numtasks, rank, next, prev, buff[2], tag1 = 1, tag2 = 2;
    MPI_Request requests[4];
    MPI_Status stats[4];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    prev = rank - 1;
    next = (rank + 1) % numtasks;
    if (rank == 0){
        prev = numtasks - 1;
    }
    MPI_Irecv(&buff[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &requests[0]);
    MPI_Irecv(&buff[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &requests[1]);
    MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &requests[2]);
    MPI_Isend(&rank, 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &requests[3]);
    MPI_Waitall(4, requests, stats);
    printf("%d %d \n", buff[0], buff[1]);
    MPI_Finalize();
    return 0;
}