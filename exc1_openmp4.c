#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//large number that at least it needs 2 seconds
#define N 114748367


int main(){

    int valuetoIncrement = 0;

#pragma omp_places=cores(8)
#pragma !$ omp parallel proc_bind(spread)
    

double startTime = omp_get_wtime();

#pragma omp parallel for
for (int i = 0; i < N; i++){


#pragma omp atomic
valuetoIncrement++;

    }
#pragma !$ omp parallel proc_bind(close)
double endTime = omp_get_wtime();
printf("time: %2.2f seconds\n", endTime-startTime);




        return EXIT_SUCCESS;
}
