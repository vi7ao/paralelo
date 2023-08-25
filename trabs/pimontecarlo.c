#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000
int main(){
    srand(time(NULL));
    int pontos = 0;
    #pragma omp parallel
    {
        int nThreads = omp_get_num_threads();
        int idThread = omp_get_thread_num();
        int pontosLocais = 0;
        int tamanhoBloco = N / nThreads;
        int inicio = idThread * tamanhoBloco;
        int fim = (idThread == nThreads - 1) ? N : inicio + tamanhoBloco;        
        for (int i = inicio; i < fim; i++){
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;
            if (x*x + y*y <= 1){
                pontosLocais++;
            }
        }
        #pragma omp critical
        {
            pontos += pontosLocais;
        }
    }
    double pi = 4.0 * pontos / N;
    printf("pi aproximado = %f\n", pi);
    return 0;
}
// gcc -fopenmp -o pimontecarlo pimontecarlo.c
// ./pimontecarlo