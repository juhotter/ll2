#include <stdio.h>
#include <omp.h>
#include <math.h>

#define n 100000

int main(int argc, char **argv)
{
    double x[n] = {[0 ...(n - 1)] = 2};
    double y[n] = {[0 ...(n - 1)] = 3};
    double a = 1;
    double b = 1;

    double startTime = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        x[i] = y[i] * 2 + b * i;
    }
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        y[i] = x[i] + a / (i + 1);
    }
    double endTime = omp_get_wtime();

    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += y[i];
    }

    printf("sum: %f \n", sum);

    //print needed time for calculation
    //result must be 5000550012.090864
    printf("time: %2.4f seconds\n", endTime - startTime);
    return 0;
}
