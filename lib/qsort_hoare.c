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
            do ++i; while ( arr[i] < p );
            do --j; while ( arr[j] > p );
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
 *          UNIT TEST
 ********************************/

static int cmp_int( const void *p1, const void *p2 ) {
    int i1 = *(const int *)p1;
    int i2 = *(const int *)p2;
    if ( i1 > i2 )
        return 1;
    else if ( i1 < i2 )
        return -1;
    else
        return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TST_TIMES 15
#define TST_SZ 2000

int main() {
    srand( (unsigned int)time( 0 ) );
    for ( int tt = 0; tt < TST_TIMES; ++tt ) {
        int data[TST_SZ];
        for ( size_t i = 0; i < TST_SZ; i++ ) data[i] = rand();

        int stdlib_qsort_res[TST_SZ];
        int myqsort_res[TST_SZ];
        memcpy( stdlib_qsort_res, data, TST_SZ * sizeof( int ) );
        memcpy( myqsort_res, data, TST_SZ * sizeof( int ) );

        qsort( stdlib_qsort_res, TST_SZ, sizeof( int ), cmp_int );

        arr = myqsort_res;
        qsort_hoare( 0, TST_SZ - 1 );

        int flag =
            memcmp( myqsort_res, stdlib_qsort_res, TST_SZ * sizeof( int ) );
        if ( flag ) {
            puts( "FAILED!" );
        } else {
            puts( "pass" );
        }
    }
}

