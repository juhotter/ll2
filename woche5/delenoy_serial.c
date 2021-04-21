
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int dealnnoy(int n, int m)
{
    
  
        // Base case
        if (m == 0 || n == 0)
            return 1;
  
        // Recursive step.
        return dealnnoy(m - 1, n) + 
               dealnnoy(m - 1, n - 1) + 
                     dealnnoy(m, n - 1);
    }


  
    // driver function
 int main(int argc, char* argv[])
    {

        double startTime = omp_get_wtime();

        int n = atoi(argv[1]);
        printf("%d\n", (dealnnoy(n, n)));


    double endTime = omp_get_wtime();
	printf("time: %2.4f seconds\n" , endTime-startTime);

    }
