#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//large number that at least it needs 2 seconds
#define N 9 * 100 * 1000 * 100000000000


int main(){

    int valuetoIncrement = 0;
    
   
double startTime = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < N; i++){


#pragma omp atomic
valuetoIncrement++;

    }

double endTime = omp_get_wtime();
printf("sum: %d, time: %2.2f seconds\n", sum, endTime-startTime);




        return EXIT_SUCCESS;
}
