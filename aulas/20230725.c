#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100


int main(){
    int i = 0;
    #pragma omp taskloop
    for (i = 0; i < N; i++){
        
    }   
}

void gauss_seidel(int tsteps, int sizem, int (*p)[size]){
    for (int t = 0; t < tsteps; t++){
        for (int i = 0; i < sizem-1; i++){
            for(int j = 0; j < sizem-1; i++){
                p[i][j] = 0.25 * (p[i+1][j] + p[i-1][j] + p[i][j+1] + p[i][j-1]);
            }
        }
    }
}

void gauss_seidel2(int tsteps, int sizem, int (*p)[size]){
    int NB = size/TS;
    #pragma omp parallel
    #pragma omp single
    for(int t = 0; t < tsteps; t++){
        for(int ii = 0; ii < sizem-1; ii++){
            for(int jj = 0; jj < sizem-1; jj++){
                #pragma omp depend(inout: p[ii:TS], p[jj:TS]) depend (in: p[ii-TS:TS], p[jj+1:TS])
            }
        }
    }
}