#include <omp.h>
/*
void main(){
    #pragma omp parallel
    {
        //#pragma omp critical //pode ser um bloco
        //#pragma omp atomic //só se aplica a próxima linha de código
        //#pragma omp flush //esvazia a cache
        int n = 0;
        #pragma omp for nowait //nowait pra processar os dois ao mesmo tempo, se tiver dependencia nao tirar
        for(int i = 0; i < n; i++){

        }
        for(int i = 0; i < n; i++){

        }
    }
}
*/
/*
void main(){
    #pragma omp parallel
    {
        #pragma omp sections //pra rodar as 3 seções ao mesmo tempo
        {
            #pragma omp section
            a();
            #pragma omp section
            b();
            #pragma omp section
            c();
        }
    }
}
*/
/*
void main(void){
    #pragma omp parallel
    {   
        #pragma omp single firstprivate(atual)
        for (atual = cabeca; atual != NULL; atual = atual->proximo){
            #pragma omp task
            processa(atual);
        }
    }
}
*/

void main(){
    #pragma omp parallel
    {
        int n = 10;
        #pragma omp single
        fibonacci(n);
    }
}

int fibonacci(n){
    if (n == 0)
        return 1;
    int i, j;
    #pragma omp task lastprivate(i)
    i = fibonacci(n-1);
    #pragma omp task lastprivate(j)
    j = fibonacci(n-2);
    #pragma omp taskwait
    return i + j;
}