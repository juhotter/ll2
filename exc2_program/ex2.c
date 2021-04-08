#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//improve, allow nesting for parallel regions
#define OMP_NESTED = TRUE

#define SEED 150000;
//optimized for faster initialization
#define ARRINIT(m, x, y, size) m[size * x + y]

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
	do                     \
	{                      \
		PERROR;            \
		goto label;        \
	} while (0)

#define INIT_ARRAY(arr, label)                      \
	do                                              \
	{                                               \
		if (!(arr))                                 \
			PERROR_GOTO(label);                     \
		for (long i = 0; i < n; ++i)                \
		{                                           \
			(arr)[i] = malloc(sizeof(**(arr)) * n); \
			if (!(arr)[i])                          \
				PERROR_GOTO(label);                 \
		}                                           \
	} while (0)
/* optimized
void free_2d_array(int **arr, long len)
{
	if (!arr)
	{
		return;
	}
	for (long i = 0; i < len; ++i)
	{
		if (!arr[i])
		{
			break;
		}
		free(arr[i]);
	}
	free(arr);
}*/

int main(int argc, char **argv)
{
	// handle input
	if (argc != 2)
	{
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}
	errno = 0;
	char *str = argv[1];
	char *endptr;
	long n = strtol(str, &endptr, 0);
	if (errno != 0)
	{
		perror("strtol");
		return EXIT_FAILURE;
	}
	if (endptr == str)
	{
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if (n < 0)
	{
		fprintf(stderr, "Error: matrix size must not be negative!\n");
		return EXIT_FAILURE;
	}

	// allocate memory
	int status = EXIT_FAILURE;
	int *a = malloc(sizeof(a) * n * n);
	if (!a)
		PERROR_GOTO(error_a);
	int *b = malloc(sizeof(*b) * n * n);
	if (!b)
		PERROR_GOTO(error_b);
	int *c = malloc(sizeof(*c) * n * n);
	if (!c)
		PERROR_GOTO(error_c);
	status = EXIT_SUCCESS;

	/*
	// fill matrix
	srand(7);
	for (long i = 0; i < n; ++i)
	{
		for (long j = 0; j < n; ++j)
		{
			a[i][j] = rand();
			b[i][j] = rand();
		}
	}
	*/

#pragma omp parallel default(none) firstprivate(n) shared(a, b, c)
	{
		unsigned int seed = SEED + omp_get_thread_num();
		// fill matrix
#pragma omp for
		for (long i = 0; i < n; ++i)
		{
			for (long j = 0; j < n; ++j)
			{
				ARRINIT(a, i, j, n) = rand_r(&seed);
				ARRINIT(b, i, j, n) = rand_r(&seed);
				ARRINIT(c, i, j, n) = 0;
			}
		}
	}
	//optimized by starting time a bit later
	double start_time = omp_get_wtime();

	//optimized by transposing matrix b
	int *b_trans = malloc(sizeof(b_trans) * n * n);
#pragma omp parallel for
	for (long i = 0; i < n; ++i)
	{
		for (long j = 0; j < n; j++)
		{
			ARRINIT(b_trans, i, j, n) = ARRINIT(b, j, i, n);
		}
	}
//optimized, matrix multiplication with transposed matrix
#pragma omp parallel for default(none) firstprivate(n, a, b_trans) shared(c)
	for (long i = 0; i < n; ++i)
	{
		for (long j = 0; j < n; ++j)
		{
			for (long k = 0; k < n; ++k)
			{
				ARRINIT(c, i, j, n) += ARRINIT(a, i, k, n) * ARRINIT(b_trans, j, k, n);
			}
		}
	}

	//optimized sum of matrix c
	unsigned long result = 0;
#pragma omp parallel for default(none) firstprivate(c, n) reduction(+ \
																	: result)
	for (long i = 0; i < n; ++i)
	{
		for (long j = 0; j < n; ++j)
		{
			result += ARRINIT(c, i, j, n);
		}
	}
	double end_time = omp_get_wtime();
	printf("res: %lu, time: %2.2f seconds\n", result, end_time - start_time);

// cleanup
//optimized, to free directly not over function of 2 diomensional array
error_c:
	free(c);
error_b:
	free(b);
error_a:
	free(a);
	return status;
}