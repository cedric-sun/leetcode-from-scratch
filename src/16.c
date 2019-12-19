/************************************
 *   Quick Sort - Hoare Partition
 ***********************************/
#include <stddef.h>

// array to be sorted
static int* arr;

// [lo, hi]
static void qsort_hoare( size_t lo, size_t hi ) {
    if ( lo < hi ) {
        int p = arr[( hi + lo ) >> 1];
        size_t i = lo - 1, j = hi + 1;
        while ( 1 ) {
            do
                ++i;
            while ( arr[i] < p );
            do
                --j;
            while ( arr[j] > p );
            if ( i >= j ) break;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
        qsort_hoare( lo, j );
        qsort_hoare( j + 1, hi );
    }
}

#include <stdint.h>
int threeSumClosest( int* nums, int numsSize, int target ) {
    if ( numsSize < 3 ) return 0xbada991e;

    arr = nums;
    qsort_hoare( 0, numsSize - 1 );

    int ans = 0xbada991e;
    uintmax_t min_diff = UINTMAX_MAX;

    for ( int *a = nums, *end = nums + numsSize - 1; a != end; a++ ) {
        //testing duplication never brings benefit
        if ( a != nums && *a == *( a - 1 ) ) continue;
        for ( int *b = a + 1, *c = end; b < c; ) {
            intmax_t sum = ( intmax_t )( *a ) + *b + *c;
            intmax_t diff = sum - target;
            if ( !diff ) return target;
            if (diff<0) {
                while (b<c && *b == *(b+1)) b++;
                b++;
                diff=-diff;
            } else {
                while (b<c && *c==*(c-1)) c--;
                c--;
            }

            if ( (uintmax_t)diff < min_diff ) {
                min_diff = (uintmax_t)diff;
                ans = (int)sum;
            }
        }
    }
    return ans;
}

#include <stdio.h>
int main() {
    int data[] = {0, 0, 0};
    int ans = threeSumClosest( data, sizeof( data ) / sizeof *data, 1 );
    printf( "%d\n", ans );
}
