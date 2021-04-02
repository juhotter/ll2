#include <omp.h> //include for open mp
#include <stdio.h>
#include <stdlib.h>

//given N
#define N 500000000

//random seed - same in all three programms
#define SEED 98765437

int main() {
     //start monte carlo with zero points
    long point_nr = 0;


        //start open mp measure time
    	double startTime = omp_get_wtime();

// parallel for loop
#pragma omp parallel
    {
        double x, y;
       //each thread own a seed
        unsigned int seed = SEED + omp_get_thread_num();

        
#pragma omp for reduction(+:point_nr)
        for (long i = 0; i < N; i++) {
            x = (double) rand_r(&seed) / RAND_MAX;
            y = (double) rand_r(&seed) / RAND_MAX;


            if (x * x + y * y <= 1)
                point_nr++;
        }

    }
     //calculate the estimatet pi
    double pi;
    pi = 4 * ((double) point_nr / N);



//get end time from open mp
double endTime = omp_get_wtime();

    printf("Pi: %lf\n", pi);
     printf(" time: %2.4f seconds\n", endTime-startTime);
    return EXIT_SUCCESS;
}
