#include <stdio.h>
#include <omp.h>

#define n 100000

int main(int argc, char **argv)
{

    double x[n] = {[0 ...(n - 1)] = 2};
    double y[n] = {[0 ...(n - 1)] = 3};
    double z[n];

    double startTime = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < n - 1; i++)
    {
        z[i] = x[i];
    }
#pragma omp parallel for
    for (int i = 0; i < n - 1; i++)
    {
        x[i] = (y[i] + z[i + 1]) / 7;
    }

    double endTime = omp_get_wtime();

    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += x[i];
    }

    printf("sum: %f \n", sum);

    //print needed time for calculation
    //result must be 71429.857143
    printf("time: %2.4f seconds\n", endTime - startTime);
    return 0;
}
