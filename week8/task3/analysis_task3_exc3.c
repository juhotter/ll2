#include <stdio.h>
#include <omp.h>

#define N 10
#define M 20
#define L 30

int main(int argc, char **argv)
{
        double a[N][M][L] = {[0 ...(N - 1)] = 2};

        double startTime = omp_get_wtime();
        for (int i = 0; i < (N - 1); i++)
        {
                for (int j = 0; j < (M - 1); j++)
                {
                        for (int k = 0; k < (L - 1); k++)
                        {
                                a[i + 1 + 1][j + 1][k] = a[i + 1][j + 1][k + 1] + 5;
                        }
                }
        }

        double endTime = omp_get_wtime();

        int sum = 0;
        for (int i = 0; i < N; i++)
        {
                sum += a[i][i][i];
        }

        //print result, correct is: 182
        printf("%d \n", sum);
        //print needed time for calculation
        printf("time: %2.4f seconds\n", endTime - startTime);

        return 0;
}
