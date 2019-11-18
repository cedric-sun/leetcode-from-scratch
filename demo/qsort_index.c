static int *gdata;
/************************************
 *   Quick Sort - Hoare Partition
 ***********************************/
#include <stddef.h>

// array to be sorted
static int *arr;

// [lo, hi)
static void qsort_hoare( size_t lo, size_t hi ) {
    if ( lo < hi ) {
        int p = arr[( hi + lo ) >> 1];
        size_t i = lo - 1, j = hi + 1;
        while ( 1 ) {
            do ++i; while ( gdata[arr[i]] < gdata[p] );
            do --j; while ( gdata[arr[j]] > gdata[p] );
            if ( i >= j ) break;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
        qsort_hoare( lo, j );
        qsort_hoare( j + 1, hi );
    }
}

/*********************************
 *        index sort
 ********************************/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define TST_SZ 1000
int main() {
    srand( (unsigned int)time( 0 ) );
    {
        int data[TST_SZ];
        for ( size_t i = 0; i < TST_SZ; i++ ) data[i] = rand();
        gdata = data;

        int indice[TST_SZ];
        for ( size_t i = 0; i < TST_SZ; i++ ) indice[i] = (int)i;
        arr = indice;

        qsort_hoare( 0, TST_SZ - 1 );

        printf("%d\n", data[indice[0]]);
        for ( size_t i = 1; i < TST_SZ; i++ ){
            if (data[indice[i]]<data[indice[i-1]]){
                puts("PANIC");
                return -1;
            } else {
                printf("%d\n", data[indice[i]]);
            }
        }
    }
}
