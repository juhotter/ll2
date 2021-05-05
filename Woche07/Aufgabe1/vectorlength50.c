#include <stdio.h>
#include <stdlib.h>
#include <omp.h>





int main (){



double startTime = omp_get_wtime();


    int repetitions = 1000000; //1e6 like given


    //exc 1a ; initialize vectors with constant values
    int size = 50;             
    float a[50] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
    float b[50] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
    float c[50] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50};
    



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
