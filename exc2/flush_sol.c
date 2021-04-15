#include <omp.h>
#include <stdio.h>

int main() {
   int data, flag = 0;
   #pragma omp parallel num_threads(2)
   {
      if (omp_get_thread_num()==0) {
         /* Write to the data buffer that will be read by thread */
         data = 42;
         /* Flush data to thread 1 and relative to the flag */
         #pragma omp flush(flag, data)
         /* Set flag to release thread 1 */
         flag = 1;
         /* Flush flag to be sure that thread 1 sees the change */
         #pragma omp flush(flag)
      }
      else if (omp_get_thread_num()==1) {
         /* Loop until the update to the flag */
         #pragma omp flush(flag, data)
         while (flag < 1) {
            #pragma omp flush(flag, data)
         }

         #pragma omp flush(flag, data)
         /* print flag and data*/
         printf("flag=%d data=%d\n", flag, data);
      }
   }
   return 0;
}
