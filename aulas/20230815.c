/*
    MPI - message passing interface
    biblioteca com centenas de funções
    troca de mensagem
    rede = hardware
    (assembly paralelo)
*/
/*
int main(int argc, char *argv[]){
    MPI_Init(&argc, &argv);
    MPI_Comm_size(
        MPI_COMM_WORLD,
        &numtasks
    );
    MPI_Comm_rank(
        MPI_COMM_WORLD,
        &id()
    );
    printf("Hello %d -> %d\n", id, numtasks);
    MPI_Finalize();
}
*/

#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[]){
    int clone = 0, n, id, procs, i, rc;
    double resparcial, res, h, sum, x;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    scanf("%d", &n);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    h = 1.0 / (double) n;
    sum = 0.0;
    for(i = id + 1; i <= n; i += procs){
        x = h * ((double)i - 0.5);
        sum += (4.0 / (1.0 + x*x));
    }
    resparcial = sum * h;
    MPI_Reduce(&resparcial, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("valor = %f", res);
    MPI_Finalize();
}
