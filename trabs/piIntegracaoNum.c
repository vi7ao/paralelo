#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double f(double x){
    return (4.0 / (x * x + 1)); // funcao generica
}

double regraDoTrapezio(double (*f)(double), double a, double b, int n){
    double h = (b-a)/n;
    double somaArea = 0.5 * (f(a) + f(b));
    for(int i = 1; i < n; i++){
        double x = a + i * h;
        somaArea += f(x);
    }
    return h * somaArea;
}

int main(){
    int n = 10000000;
    double a = 0; //limite inferior
    double b = 1; //limite superior
    double pi = regraDoTrapezio(f, a, b, n);
    printf("pi aproximado = %f\n", pi);
    return 0;
}

// gcc -fopenmp -o piIntegracaoNum piIntegracaoNum.c
// ./piIntegracaoNum