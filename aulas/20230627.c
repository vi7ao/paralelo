#include <stdio.h>
#include <omp.h>

void main(void)
{
    #pragma omp parallel num_threads(16)
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        int acc[16];
        acc[id] = 0;
        int i;
        int a[100];
        for (i = 0; i < 100; i++){
            a[i] = i;
        }
        for(i = 0; i < 100; i++){
            acc[id] += a[i];
            printf("%d\n", acc[id]);
        }
    }
    /*
    for (i = 0; i < num_threads; i++){
        acc_global += acc[i];
        printf("%d\n", acc_global);
    }
    */
}