#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 8

#define TOT_COUNT 500000000

float randNumGen(){
    int random_value = rand();
    float unit_random = random_value / (float) RAND_MAX; // number between 0 and 1
    return unit_random;
}

//allocate a thread
void *doCalcs(void *threadid)
{
    long longTid;
    longTid = (long)threadid;

    int tid = (int)longTid;//thread id

    //using malloc for the return variable in order make
    //sure that it is not destroyed once the thread call is finished
    float *in_count = (float *)malloc(sizeof(float));
    *in_count=0;

    //get the total number of iterations for a thread
    float tot_iterations= TOT_COUNT/NUM_THREADS;
    float x,y,result;

    int counter=0;

    //calculation
    for(counter=0; counter < tot_iterations; counter++){
        x = randNumGen();
        y = randNumGen();

        result = x*x + y*y;

        if(result < 1) {
            *in_count+=1;
        }
   }

    //get the remaining iterations calculated by thread 0
    if(tid == 0){
        float remainder = TOT_COUNT%NUM_THREADS;
        float x,y,result;

        for(counter=0;counter<remainder;counter++){
            x = randNumGen();
            y = randNumGen();

            result = x*x + y*y;

            if(result < 1) {
                *in_count+=1;
            }
        }
    }
   pthread_exit((void *)in_count);     //return the in count
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    void *status;
    float tot_in = 0;

    clock_t starting, ending;
    starting = clock();

    for(t=0;t<NUM_THREADS;t++){
        rc = pthread_create(&threads[t], NULL, doCalcs, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    //join the threads
    for(t=0;t<NUM_THREADS;t++){

        pthread_join(threads[t], &status);
        //printf("Return from thread %ld is : %f\n",t, *(float*)status);

        tot_in += *(float*)status;            //total in count
    }

    ending = clock();
    double clock_time = (double)(ending - starting)/CLOCKS_PER_SEC;

    printf("Approximate PI: %f \n", 4*(tot_in/TOT_COUNT));
    printf("execution time: %2.3f seconds\n", clock_time);

    //close all threads
    pthread_exit(NULL);
}
