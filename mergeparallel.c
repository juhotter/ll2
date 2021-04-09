#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

long N = 0;
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int *array, int l, int m, int r, int *buff)
{
    int i = l;
    int j = m;

    for (int k = l; k < r; k++)
    {
        if (i < m && (j >= r || array[i] <= array[j]))
        {
            buff[k] = array[i];
            i = i + 1;
        }
        else
        {
            buff[k] = array[j];
            j = j + 1;
        }
    }
}

void mergeSort(int *array, int *buff)
{
    //split array into blocks
    for (int width = 1; width < N; width = 2 * width)
    {
#pragma omp parallel for
        //sort all blocks
        for (int i = 0; i < N; i = i + 2 * width)
        {
            merge(array, i,
                  (i + width) < N ? (i + width) : N,
                  (i + 2 * width) < N ? (i + 2 * width) : N,
                  buff);
        }
//write buffered array back
#pragma omp parallel for
        for (int i = 0; i < N; i++)
        {
            array[i] = buff[i];
        }
    }
}

/* Function to print an array */
void printArray(int *arr, int size)
{

    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
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
    N = atol(argv[1]);
    //sample array
    int *buff = (int *)malloc(sizeof(int) * N);
    int *arr = (int *)malloc(N * sizeof(int));
    //int32_t *arr;
    //random numbers generator from stdlib
    time_t t;
    srand((unsigned)time(&t));
#pragma omp for schedule(dynamic, 4)
    for (int i = 0; i < N; i++)
    {
        int a = rand() % 100;
        arr[i] = a;
    }

    //call function to print array

    printf("Given array is \n");
    //printArray(arr, n);

    //call function to sort Array

    mergeSort(arr, buff);

    //now call funcrtion to print sorted array again.
#pragma omp single
    {
        printf("\nSorted array is \n");
        //printArray(arr, n);
    }
    //simple "Test" to check if sorted array is sorted
#pragma omp barrier

#pragma omp master
    {
        if (testfunc(arr, N) == 0)
        {
            printf("test failed\n");
        }
        else
        {
            printf("test successfull\n");
        }
    }
    free(arr);

    double endTime = omp_get_wtime();
    printf("time: %2.4f seconds\n", endTime - startTime);
    return 0;
}