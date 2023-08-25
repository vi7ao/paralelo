#include <omp.h>
#include <stdio.h>

int main(){
    #pragma omp paralell
    {
        int n = 10;
        int a[] = {1,2,3,4,5,6,7,8,9,10};
        int b[] = {1,2,3,4,5,6,7,8,9,10};
        int c[n];
        for (int i = 0; i < n; i++){
            c[i] = a[i] + b[i];
            printf("%d\n", c[i]);
            }
    }
}

// gcc -fopenmp -o somaVetores1 somaVetores1.c
// ./somaVetores1