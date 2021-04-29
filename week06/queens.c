#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int a[30], count = 0;
int place(int pos)
{
	int i;
	for (i = 1; i < pos; i++)
	{
		if ((a[i] == a[pos]) || ((abs(a[i] - a[pos]) == abs(i - pos))))
			return 0;
	}
	return 1;
}

void queen(int n)
{
	int k = 1;
	a[k] = 0;
	while (k != 0)
	{
		a[k] = a[k] + 1;
		while ((a[k] <= n) && !place(k))
			a[k]++;
		if (a[k] <= n)
		{
			if (k == n)
				count++;
			else
			{
				k++;
				a[k] = 0;
			}
		}
		else
			k--;
	}
}
void main()
{
	int i, n;

	printf("Enter the number of Queens: ");
	scanf("%d", &n);
	double start_time = omp_get_wtime();
	queen(n);
	double end_time = omp_get_wtime();
	printf("solutions=%d \n", count);
	printf("time:  %2.5f sec\n", end_time - start_time);
}