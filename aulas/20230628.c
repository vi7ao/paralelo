#include <stdio.h>
#include <omp.h>

void main(void){
    int d = 2;
    #pragma omp parallel firstprivate(d)
    {
        int n = 10;
        int c[n], a[n], b[n];
        #pragma omp for
        for (int i = 0; i < n; i++){
            a[i] = i;
            b[i] = i;
        }
        #pragma omp for
        for (int i = 0; i < n; i++){
            c[i] = d*a[i] + b[i];
            printf("%d\n", c[i]);
        }
    }
}