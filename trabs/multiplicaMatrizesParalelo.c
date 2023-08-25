#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int sizeOfColumnMatrix1, sizeOfLineMatrix1, sizeOfLineMatrix2, sizeOfColumnMatrix2;
    scanf("%d %d %d %d", &sizeOfLineMatrix1, &sizeOfColumnMatrix1, &sizeOfLineMatrix2, &sizeOfColumnMatrix2);
    if (sizeOfColumnMatrix1 != sizeOfLineMatrix2) {
        printf("Impossivel multiplicar as matrizes");
        return 0;
    }

    int i, j, k;
    int matriz1[sizeOfLineMatrix1][sizeOfColumnMatrix1];
    int matriz2[sizeOfLineMatrix2][sizeOfColumnMatrix2];
    for (i = 0; i < sizeOfLineMatrix1; i++) {
        for (j = 0; j < sizeOfColumnMatrix1; j++) {
            scanf("%d", &matriz1[i][j]);
        }
    }
    for (i = 0; i < sizeOfLineMatrix2; i++) {
        for (j = 0; j < sizeOfColumnMatrix2; j++) {
            scanf("%d", &matriz2[i][j]);
        }
    }

    int matrizResultado[sizeOfLineMatrix1][sizeOfColumnMatrix2];
    int sizeBlocagem = 32;

    #pragma omp parallel for private(i, j, k)
    for (i = 0; i < sizeOfLineMatrix1; i += sizeBlocagem) {
        for (j = 0; j < sizeOfColumnMatrix2; j += sizeBlocagem) {
            for (k = 0; k < sizeOfColumnMatrix1; k += sizeBlocagem) {
                #pragma omp task firstprivate(i, j, k) depend(out: matrizResultado[i:i+sizeBlocagem][j:j+sizeBlocagem])
                for (int ii = i; ii < i + sizeBlocagem && ii < sizeOfLineMatrix1; ii++) {
                    for (int jj = j; jj < j + sizeBlocagem && jj < sizeOfColumnMatrix2; jj++) {
                        matrizResultado[ii][jj] = 0;
                        for (int kk = k; kk < k + sizeBlocagem && kk < sizeOfColumnMatrix1; kk++) {
                            matrizResultado[ii][jj] += matriz1[ii][kk] * matriz2[kk][jj];
                        }
                    }
                }
            }
        }
    }

    #pragma omp taskwait

    printf("Matriz Resultado: \n");
    for (i = 0; i < sizeOfLineMatrix1; i++) {
        for (j = 0; j < sizeOfColumnMatrix2; j++) {
            printf("%d ", matrizResultado[i][j]);
        }
        printf("\n");
    }

    return 0;
}