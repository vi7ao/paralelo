#include <stdio.h>
#include <omp.h>

int main(void){
    #pragma omp parallel
    /*
    #pragma omp parallel num_threads(4)
    {   
        int num_threads = omp_get_num_threads();
        int id = omp_get_thread_num();
        printf("Hello World!\n %d de %d\n", id, num_threads);
    }
    */
   {
    int num_threads = omp_get_num_threads();
    int id = omp_get_thread_num();
    int i, n;
    int c[10], a[10], b[10];
    for (i = id; i < n; i+=num_threads){
            c[i] = a[i] + b[i];  
            printf("%d", c[i]);
    }
    /*
    int tamanho = n/num_threads;
    for (i = id * tamanho; i < (id + 1) * tamanho; i++){
        c[i] = a[i] + b[i];
    }
    */
   }
}