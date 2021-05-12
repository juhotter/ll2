#include <stdio.h>
#include <omp.h>

#define SIZE 100000

int main(int argc, char **argv)
{

        void copy(double *x, double *y)
        {
#pragma omp for
                for (int i = 0; i < SIZE; i++)
                {
                        x[i] = y[i];
                }
        }

        double a[SIZE] = {[0 ...(SIZE - 1)] = 2};
        double b[SIZE] = {[0 ...(SIZE - 1)] = 3};

        printf("%f \n", a[SIZE - 1]);

        double startTime = omp_get_wtime();
#pragma omp parallel
        copy(a, b);
        double endTime = omp_get_wtime();

        printf("%f \n", a[SIZE-1]);

        //print needed time for calculation
        printf("time: %2.4f seconds\n", endTime - startTime);
        return 0;
}
