#include <stdio.h>
#include <omp.h>
#include <math.h>

#define n 100000

int main(int argc, char **argv)
{
    double x[n] = {[0 ...(n - 1)] = 2};
    double y[n] = {[0 ...(n - 1)] = 3};
    double z[n] = {[0 ...(n - 1)] = 4};

    double startTime = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        z[i] = (x[i] + y[i]) / (i + 1);
    }
    //f = sqrt(a + k) -> was never used

    double endTime = omp_get_wtime();

    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += z[i];
    }

    printf("sum: %f \n", sum);

    //print needed time for calculation
    //result must be 60.450731
    printf("time: %2.4f seconds\n", endTime - startTime);
    return 0;
}
