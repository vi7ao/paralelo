#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>

bool sudoku (Tabuleiro t){
    if (solucao(t))return true;
    pos = proximo_preencher(t);
    for(i = 0; i < N*N; i++){
        #pragma omp task firstprivate(t, depth)
        if(valido (t[pos] = i)){
            sudoku(t, depth++);
        }
    }
    return false;
}