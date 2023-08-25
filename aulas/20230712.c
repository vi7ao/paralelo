#include <stdio.h>
#include <omp.h>
/*
int percorre(no_raiz){
    int n1, n2, n3;
    if (raiz == NULL)
        return 0;
    #pragma omp task shared (n1)
    n1 = processa(raiz);
    #pragma omp task shared(n2)
    n2 = percorre(raiz->filho_esq);
    #pragma omp task shared(n3)
    n3 = percorre(raiz->filho_dir);
}
*/
/*
visita(vertice, v){
    if(vertice == NULL)
        return NULL;
    if(vertice->visitado)
        return NULL;
    if(vertice == procurado){
        #pragma omp critical
        v = vertice;
        return vertice;
    }
    v = null
    vertice->visitado = true;
    
    for (;(!v) && (atual); atual = atual->proximo){
        #pragma omp task firstprivate(atual)
        v = visita(atual, v);
    }
    #pragma omp taskwait
    return v;
}
*/

#pragma omp taskgroup task_reduction(+:total)
{
    for(; (atual); atual->proximo){
        #pragma omp task firstprivate(atual) in_reduction(+:total)
        total += visita(atual);
    }
}