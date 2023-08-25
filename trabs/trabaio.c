#include <stdio.h>
#include <omp.h>

/* migos
float calculate_abundance(int num){
    int sum_factors = 0;
    for (int i = 1; i <= num/2; i++){
        if(num % i == 0){
            sum_factors += i;
        }
    }
    float abundance = sum_factors / (1.0 * num);
    return abundance;
}

int main (){
    int max = 1000;
    int numbers[max];
    float abundances[max];
    
    #pragma omp parallel for
    for (int num = 1; num < max; num++){
        numbers[num] = num;
        abundances[num] = calculate_abundance(num);
    }
    
    #pragma omp parallel for
    for (int num = 1; num < max; num++){
        for(int other_num = num + 1; other_num < max; other_num++){
            if(abundances[other_num] == abundances[num] && numbers[other_num] != numbers[num]){
                #pragma omp critical
                {
                    printf("%d and %d are friends\n", numbers[num], numbers[other_num]);
                }
            }
        }
    }
    return 0;
}

*/

/* monte carlo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000

int count_points_in_circle(int start, int end) {
    int points_inside = 0;
    for (int i = start; i < end; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1) {
            points_inside++;
        }
    }
    return points_inside;
}

int main() {
    srand(time(NULL));
    int points = 0;

    #pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int local_points = 0;
        int block_size = N / num_threads;
        int start = thread_id * block_size;
        int end = (thread_id == num_threads - 1) ? N : start + block_size;
        
        local_points = count_points_in_circle(start, end);

        #pragma omp critical
        {
            points += local_points;
        }
    }

    double pi = 4.0 * points / N;
    printf("Approximate value of pi = %f\n", pi);
    return 0;
}


*/

/* integracao numerica pela regra de 1/3 do simpson


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double f(double x){
    return (4.0 / (x * x + 1)); // generic function
}

double simpson_1_3_rule(double (*f)(double), double a, double b, int n){
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for(int i = 1; i < n; i++){
        double x = a + i * h;
        if (i % 2 == 0) {
            sum += 2 * f(x);
        } else {
            sum += 4 * f(x);
        }
    }

    return h * sum / 3.0;
}

int main(){
    int n = 10000000;
    double a = 0; // lower limit
    double b = 1; // upper limit
    double pi = simpson_1_3_rule(f, a, b, n);
    printf("Approximated pi = %f\n", pi);
    return 0;
}

*/