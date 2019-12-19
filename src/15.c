#include <stdint.h>
#include <stdlib.h>
/************************************
 *   Quick Sort - Hoare Partition
 ***********************************/
#include <stddef.h>

// array to be sorted
static int *arr;

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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **threeSum( int *nums, int numsSize, int *returnSize,
                int **returnColumnSizes ) {
    size_t anssz = 0, anscap = 20;
    int **ans = malloc( anscap * sizeof *ans );
    if ( numsSize < 3 ) goto DONE;

    arr = nums;
    qsort_hoare( 0, numsSize - 1 );
    for ( size_t i = 0; i < numsSize - 2; i++ ) {
        if ( i && nums[i] == nums[i - 1] ) continue;
        int a = nums[i];
        if ( a > 0 ) break;

        size_t start = i + 1, end = numsSize - 1;
        while ( start < end ) {
            int b = nums[start], c = nums[end];

            intmax_t res = a + b + c;
            if ( res == 0 ) {
                if ( anssz >= anscap ) {
                    anscap <<= 1;
                    ans = realloc( ans, anscap * sizeof *ans );
                }
                int *triplet = malloc( 3 * sizeof *triplet );
                triplet[0] = a;
                triplet[1] = b;
                triplet[2] = c;
                ans[anssz++] = triplet;
                while ( start < end && nums[start] == nums[start + 1] ) start++;
                while ( start < end && nums[end] == nums[end - 1] ) end--;

                start++;
                end--;
            } else if ( res > 0 ) {
                end--;
            } else {
                start++;
            }
        }
    }

DONE:;
    int *col_szs = malloc( anssz * sizeof *col_szs );
    for ( size_t i = 0; i < anssz; i++ ) col_szs[i] = 3;
    *returnColumnSizes = col_szs;
    *returnSize = anssz;
    return ans;
}

#include <stdio.h>

int main() {
    int data[] = {0};
    // -4 -1 -1 0 1 2
    int ret_sz;
    int *ret_col_szs;
    int **ans = threeSum( data, sizeof( data ) / sizeof( *data ), &ret_sz,
                          &ret_col_szs );

    for ( size_t i = 0; i < ret_sz; i++ )
        printf( "%d %d %d\n", ans[i][0], ans[i][1], ans[i][2] );

    free( ret_col_szs );
    for ( size_t i = 0; i < ret_sz; i++ ) free( ans[i] );
    free( ans );
}
