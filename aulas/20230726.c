// dependencias

void cholesky(int ts, int nt, double a[nt][nt]){
    for(int k = 0; k < nt; k ++){
        patrf(a[k][k], ts, ts);
        for (int i = k + 1; i < nt; i++){
            #pragma omp task 
            trsm(a[k][k], a[k][i], ts, ts);
            #pragma omp task depend (inout:a[k] depend (in:a[k][k]) i)
            for (int i = k+1; i < nt; i++){
                for(int j = k+1; j < i; j++){
                    #pragma omp task depend (inout:a[j][i])
                    dgemn(a[k][i], a[k][j], a[j][i], ts, ts);
                    #pragma omp task depend (inout:a[i][i])
                    syrk(a[k][i], a[i][i], ts, ts);
                }
            }
        }
    }
}

/*
    #pragma omp taskwait <- usar aqui fora pra nao ficar pra sempre
    if(condicao){

    }
*/

void gaussJordan(){ //pra algum dia aí com dependencia
    int i,j,k,n,c,soma,x;
    int A[n];
    for (j = 0; j < n; j++){
        for(i = 0; i< n; i++){
            if(i>j){
                c = A[i][j] / A[j][i];
                for(k = 0; k < n; k++){
                    A[i][k] = A[i][k] - c * A[j][k];
                }
            }
        }
    }
    x[n-1] = A[n-1][n] / A[n-1][n-1];

    for (i = n-2; i >= 0; i--){
        soma = 0;
        for(j = i + 1; j < n; j++){
            soma += A[i][j]**[j];
        }
        x[i] = (A[i][n] - soma) / A[i][i];
    }
}

