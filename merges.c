#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void merge(int *arr, int n, int *buff)
{
    int i = 0;
    int j = n / 2;
    int ti = 0;

    while (i < n / 2 && j < n)
    {
        if (arr[i] < arr[j])
        {
            buff[ti] = arr[i];
            ti++;
            i++;
        }
        else
        {
            buff[ti] = arr[j];
            ti++;
            j++;
        }
    }
    while (i < n / 2)
    {
        buff[ti] = arr[i];
        ti++;
        i++;
    }
    while (j < n)
    {
        buff[ti] = arr[j];
        ti++;
        j++;
    }
    for (int a = 0; a < n; a++)
    {
        arr[a] = buff[a];
    }
}

void merge_sort(int *arr, int n, int *buff)
{
    //printf("hier %d\n ", count++);

    if (n < 2)
    {
        return;
    }
    // Divide and Conquer

    merge_sort(arr, n / 2, buff);
    merge_sort(arr + (n / 2), n - (n / 2), buff + n / 2);
    // Combine

    merge(arr, n, buff);

    return;
}

int testfunc(int32_t *arr, int n)
{
    //#pragma omp for schedule(dynamic, 4)
    for (long i = 0; i < n - 1; i++)
    {

        if (arr[i] > arr[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    double startTime = omp_get_wtime();
    int i;
    long n;
    srand(7);
    n = atol(argv[1]);
    int *arr = (int *)malloc(n * sizeof(int));
    int *buff = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        int a = rand() % 100;
        arr[i] = a;
    }

    /*printf("array:"); // print sorted array
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");*/

    merge_sort(arr, n, buff); // sort the array

    /*printf("\n\nSorted array:"); // print sorted array
    for (i = 0; i < n; i++)
        printf("%d ", buff[i]);
    */
    if (testfunc(arr, n) == 0)
    {
        printf("\ntest failed\n");
    }
    else
    {
        printf("\ntest successfull\n");
    }
    free(arr);
    free(buff);
    double endTime = omp_get_wtime();
    printf("time: %2.4f seconds\n", endTime - startTime);
    return 0;
}