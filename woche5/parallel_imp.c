#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int dealnnoy_serial(int n, int m)
{
    
  
        // Base case
        if (m == 0 || n == 0)
            return 1;
  
        // Recursive step.
        return dealnnoy_serial(m - 1, n) + 
               dealnnoy_serial(m - 1, n - 1) + 
                     dealnnoy_serial(m, n - 1);
    }



int dealnnoy(int n, int m)
{


int d1;
int d2;
int d3;
    

    // Base case
    if (m == 0 || n == 0)
    {
        return 1;}
           
if (m < 8 || m < 8)
    {
        return dealnnoy_serial(n,m);}
       


 #pragma omp parallel 
{
#pragma omp single 
{
    
#pragma omp task shared(d1)
d1 = dealnnoy(m - 1, n);

#pragma omp task  shared(d2)
d2 = dealnnoy(m - 1, n - 1);

#pragma omp task  shared(d3)
d3 = dealnnoy(m, n - 1);

#pragma omp taskwait 


}}
return d1 + d2 + d3;
}






//programm end klammer
            


    // driver function
 int main(int argc, char* argv[])
    {



int n = atoi(argv[1]);
        double startTime = omp_get_wtime();

       


     
        printf("%d\n", (dealnnoy(n, n)));


    double endTime = omp_get_wtime();
	printf("time: %2.4f seconds\n" , endTime-startTime);

    return 0;
    }