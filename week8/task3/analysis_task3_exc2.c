#include <stdio.h>
#include <omp.h>

#define N 1000000

int main(int argc, char **argv)
{
        double A[N] = {[0 ...(N - 1)] = 2};

        double startTime = omp_get_wtime();
        /*for (int i = 0; i <= (N - 4); i+=7)
        {
                A[(i + 4)] = 0;
        }*/
        for (int i = 0; i <= (N - 4)/7; i++)
        {
                A[(7*i + 4)] = 0;
        }
        double endTime = omp_get_wtime();

        int sum = 0;
        for (int i = 0; i < N; i++)
        {
                sum += A[i];
        }

        //print result, correct is: 1 714 286
        printf("%d \n", sum);
        //print needed time for calculation
        printf("time: %2.4f seconds\n", endTime - startTime);

        return 0;
}
