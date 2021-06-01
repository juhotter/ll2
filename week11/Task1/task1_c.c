#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    double startTime = omp_get_wtime();

    unsigned c1 = 9999999;
    //**c)** `c1` is of type `unsigned`:
    //unsigned c2 = 96 * c1;
    //replace multiplication by 96 with shift left by 5 and
    //shift left by 1 and add c2
    unsigned c2 = (c1<<5);
    c2 = (c2<<1) + c2;

    double endTime = omp_get_wtime();
    double time = endTime - startTime;
    printf("result: %d\n", c2);
    printf("time * 10000000: %f seconds\n", time * 10000000);

    return 0;
}
