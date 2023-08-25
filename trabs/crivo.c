#include <omp.h>
#include <stdio.h>

int main(){
    int maxNumeros = 10000;
    int primos[maxNumeros + 1];
    #pragma omp parallel for
    for(int i = 0; i <= maxNumeros; i++){
        primos[i] = 1;
    }
    #pragma omp parallel
    {
        for (int i = 2; i*i <= maxNumeros; i++){
            if (primos[i] == 1){
                #pragma omp for
                for(int j = i*i; j <= maxNumeros; j+=i){
                    primos[j] = 0;
                }
            }
        }
    }
    for(int i = 2; i <= maxNumeros; i++){
        if (primos[i] == 1){
            printf("%d\n", i);
        }
    }
    return 0;
}

// gcc -fopenmp -o crivo crivo.c
// ./crivo