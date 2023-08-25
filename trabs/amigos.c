#include <stdio.h>
#include <omp.h>

typedef struct {
    int n;
    float abundancia;
} NumeroAbundancia;

float calculoAbundancia(int n){
    int somaFatores = 0;
    for (int i = 1; i <= n/2; i++){
        if(n % i == 0){
            somaFatores += i;
        }
    }
    float abundancia = somaFatores / (1.0 * n);
    return abundancia;
}

int main (){
    int max = 1000;
    NumeroAbundancia numeros[max];
    #pragma omp parallel for
    for (int n = 1; n < max; n++){
        numeros[n].n = n;
        numeros[n].abundancia = calculoAbundancia(n);
    }
    #pragma omp parallel for
    for (int n = 1; n < max; n++){
        for(int m = n + 1; m < max; m++){
            if(numeros[m].abundancia == numeros[n].abundancia && numeros[m].n != numeros[n].n){
                #pragma omp critical
                {
                    printf("%d (abnd: %.2f) e %d (abnd: %.2f) sao amigos\n", numeros[n].n, numeros[n].abundancia, numeros[m].n, numeros[m].abundancia);
                }
            }
        }
    }
    return 0;
}

// gcc -fopenmp -o amigos amigos.c
// ./amigos
