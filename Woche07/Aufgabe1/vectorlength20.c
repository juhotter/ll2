#include <stdio.h>
#include <stdlib.h>
#include <omp.h>





int main (){



double startTime = omp_get_wtime();


    int repetitions = 1000000; //1e6 like given


    //exc 1a ; initialize vectors with constant values
    int size = 20;             
    float a[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    float b[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    float c[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    



        //given calculation
        for (int run = 0; run < repetitions; run++)
        {
            for (int i = 0; i < size; i++)
            {
                a[i] += b[i] * c[i];
            }
        }






//print the final array to check if the results are valid
for (int i = 0; i < size; i++)
{
    printf("The final Output Array Output is: %f - Eintrag %d \n", a[i], i);
}


double endTime = omp_get_wtime();
printf(" time: %2.4f seconds\n", endTime-startTime);
return 0;






}
