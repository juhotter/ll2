#include <stdio.h>
#include <stdlib.h>




int main(){


    //definitionen
    int n = 10;
    int a[n][n];
    int b[n][n];
    int c[n][n];


    //matrizen füllen
    for (int i = 0; i < n;i++){

        for (int j = 0; j < n;j++){
            a[i][j] = j;
            b[i][j] = j;
        }
    }




        //with locality
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                c[i][j] = a[i][j] * b[i][j];
            }
        }

/*

//without locality
for(size_t j = 0; j < n; ++j) {
    for(size_t i = 0; i < n; ++i) {
        c[i][j] = a[i][j] * b[i][j];
    }
}

*/

    return 0;
}

