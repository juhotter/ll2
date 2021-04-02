#include <omp.h>//include for open mp
#include <stdio.h>
#include <stdlib.h>

//given N
#define N 500000000

//random seed - same in all three programms
#define SEED 98765437

int main() {
     //start monte carlo with zero points
    long point_nr = 0;

#pragma omp parallel
    {
        double x, y;
        unsigned int seed = SEED + omp_get_thread_num();

// parallel for loop
#pragma omp for
        for (long i = 0; i < N; i++) {
            x = (double) rand_r(&seed) / RAND_MAX;
            y = (double) rand_r(&seed) / RAND_MAX;

           
            if (x * x + y * y <= 1) {
#pragma omp critical
                point_nr++;
            }
        }

    }
    //calculate the estimatet pi
    double pi;
    pi = 4 * ((double) point_nr / N);

    printf("Pi: %lf\n", pi);
    return EXIT_SUCCESS;
}