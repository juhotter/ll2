#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int *prefix_sum(int a[], int n)
{
    int *b = malloc(sizeof(int) * n);
    b[0] = 0;
    for (int i = 1; i < n; i++)
    {
        b[i] = b[i - 1] + a[i - 1];
    }
    return b;
}

int main(int argc, char **argv)
{
    double startTime = omp_get_wtime();
    int n = atoi(argv[1]);
    int *arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = 1;
    }
    int *b = malloc(sizeof(int) * n);
    b = prefix_sum(arr, n);
    /*for (int i = 0; i < n; i++)
    {
        printf("%d ", b[i]);
    }*/

    printf("\n");
    free(arr);
    free(b);
    double endTime = omp_get_wtime();
    printf("time: %2.4f seconds\n", endTime - startTime);
    return EXIT_SUCCESS;
}