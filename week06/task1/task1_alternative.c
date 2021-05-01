#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void prefix_sum(int *a, int *b, int n, int startValue)
{
    b[0] = startValue;

    for (int i = 1; i < n; i++)
    {
        b[i] = b[i - 1] + a[i - 1];
    }
}

int sum(int *a, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    return sum;
}

int main(int argc, char **argv)
{
    double startTime = omp_get_wtime();
    int n = atoi(argv[1]) + 1;
    int *arr = malloc(sizeof(int) * n);

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        arr[i] = 1;
    }

    int *b = malloc(sizeof(int) * n);

#pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int current_thread_num = omp_get_thread_num();
        int iterations_per_thread = n / num_threads;

        int array_start_index = current_thread_num * iterations_per_thread;
        int previous_array_start_index = (current_thread_num - 1) * iterations_per_thread;

        int previous_sum = sum(arr, array_start_index - 1);

        prefix_sum(arr + array_start_index, b + array_start_index, iterations_per_thread, previous_sum);
    }

    /*for (int i = n - 20; i < n; i++)
    {
        printf("%d ", b[i]);
    }*/

    free(arr);
    free(b);
    double endTime = omp_get_wtime();
    printf("time: %2.4f seconds\n", endTime - startTime);
    return EXIT_SUCCESS;
}