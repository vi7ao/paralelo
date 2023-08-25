#include "mpi.h"
#include <stdio.h>

MPI_Barrier(comm);
MPI_Bcast(&buffer, count, type, root, comm);
MPI_Scatter(&sendbuf, sendcnt, sendtype, &recvbuf, recvcnt, recvtype, root, comm);
MPI_Gather(&sendbuf, sendcnt, sendtype, &recvbuf, recvcnt, recvtype, root, comm);
MPI_Allgather(&sendbuf, sendcnt, sendtype, &recvbuf, recvcnt, recvtype, comm);
MPI_Reduce(&sendbuf, &recvbuf, count, type, op, root, comm);

/*
op = MPI_MAX
     MPI_MIN
     MPI_SUM
     MPI_PROD
     MPI_LAND BAND
     MPI_LOR BOR
     MPI_LXOR BXOR
     MPI_MAXLOC
     MPI_MINLOC
     custom
*/

MPI_Allreduce(&sendbuf, &recvbuf, count, type, op, comm);

MPI_Scan(&sendbuf, &recvbuf, count, type, op, comm);

MPI_Alltoall(&sendbuf, sendcnt, sendtype, &recvbuf, recvcnt, recvtype, comm); //faz uma transposta basicamente