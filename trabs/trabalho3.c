#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double f(double x){
    return (4.0 / (x * x + 1)); // funcao generica
}

double regraDoTrapezio(double (*f)(double), double a, double b, int n){
    double h = (b-a)/n;
    double somaArea = 0.5 * (f(a) + f(b));
    #pragma omp target enter data map(tofrom: a, b, n, h, somaArea)
    #pragma omp teams distribute parallel for reduction(+:somaArea)
    for(int i = 1; i < n; i++){
        double x = a + i * h;
        somaArea += f(x);
    }
    #pragma omp target exit data map(from: somaArea)
    return h * somaArea;
}

int main(){
    int n = 10000000;
    double a = 0; //limite inferior
    double b = 1; //limite superior
    #pragma omp target enter data map(to: a, b, n)
    double pi = regraDoTrapezio(f, a, b, n);
    #pragma omp target exit data map(from: pi)
    printf("pi aproximado = %f\n", pi);
    return 0;
}

// gcc -fopenmp -o trabalho3 trabalho3.c
// ./trabalho3