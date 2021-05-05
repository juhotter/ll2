#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <xmmintrin.h>

#define SIZE 2048

int main()
{
    int repetitions = 1000000; //10e6

    //initialize vectors with constant values
    __attribute__((aligned(16))) float a[SIZE] = {[0 ... 2047] = 2};
    __attribute__((aligned(16))) float b[SIZE] = {[0 ... 2047] = 3};
    __attribute__((aligned(16))) float c[SIZE] = {[0 ... 2047] = 4};

    __m128 w, x, y, z, result;

    double startTime = omp_get_wtime();

    for (int run = 0; run < repetitions; run++)
    {
        for (int i = 0; i < SIZE; i+=4)
        {
            x = _mm_load_ps(&a[i]);
            y = _mm_load_ps(&b[i]);
            z = _mm_load_ps(&c[i]);
            w = _mm_mul_ps(y, z);
            result = _mm_add_ps(x, w);
            _mm_store_ps(&a[i], result);
        }
    }

    double endTime = omp_get_wtime();

    //print the result of the last array entry
    printf("The final sum of the last entry is: %10.f\n", a[SIZE-1]);
    //print needed time for calculation
    printf("time: %2.4f seconds\n", endTime - startTime);
    return 0;
}