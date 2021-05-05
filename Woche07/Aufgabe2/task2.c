#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{

    double startTime = omp_get_wtime();

    int repetitions = 1000000; //1e6 like given

    int size = atoi(argv[1]);
    /*float a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float c[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};*/
    float a[size];
    float b[size];
    float c[size];

    for (int i = 0; i < size; i++)
    {
        a[i] = 0;
        b[i] = 1;
        c[i] = 1;
    }

    for (int run = 0; run < repetitions; run++)
    {
        for (int i = 0; i < size; i++)
        {
            a[i] += b[i] * c[i];
        }
    }
    int counter = 0;
    //print the final array to check if the results are valid
    for (int i = 0; i < size; i++)
    {
        printf("The final Output Array Output is: %f - Eintrag %d \n", a[i], i);
    }
    /*for (int i = 0; i < size; i++)
    {
        if (a[i] != 1000000.000)
        {
            counter++;
        }
    }
    printf("counter: %d\n", counter);*/
    double endTime = omp_get_wtime();
    printf(" time: %2.4f seconds\n", endTime - startTime);
    return 0;
}

//ohne simd: 0.0286
//mit 0.0085
