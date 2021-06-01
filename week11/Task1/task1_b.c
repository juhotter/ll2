#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    double startTime = omp_get_wtime();

    unsigned c1 = 9999999;
    //**b)** `c1` is of type `unsigned`:
    //unsigned c2 = 15 * c1;
    //replace multiplication by 15 with shift left by 4 and subtract c1
    unsigned c2 = (c1<<4) - c1;

    double endTime = omp_get_wtime();
    double time = endTime - startTime;
    printf("result: %d\n", c2);
    printf("time * 10000000: %f seconds\n", time * 10000000);

    return 0;
}
