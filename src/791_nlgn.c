static int *gdata;
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
            while ( gdata[arr[i]] < gdata[p] );
            do
                --j;
            while ( gdata[arr[j]] > gdata[p] );
            if ( i >= j ) break;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
        qsort_hoare( lo, j );
        qsort_hoare( j + 1, hi );
    }
}

#include <stdlib.h>
#include <string.h>
#define LOA 26
char *customSortString( char *S, char *T ) {
    const size_t Slen = strlen( S );
    const size_t Tlen = strlen( T );

    gdata = malloc( LOA * sizeof *gdata );
    arr = malloc( Tlen * sizeof *arr );

    for ( size_t i = 0; i < Slen; i++ ) gdata[S[i] - 'a'] = i;
    // note that gdata[] for letters that never appear in
    // S[] is uninitialized, but this doesn't matter since arbitrary order is
    // acceptable for those.
    for ( size_t i = 0; i < Tlen; i++ ) arr[i] = T[i] - 'a';
    qsort_hoare( 0, Tlen - 1 );
    for ( size_t i = 0; i < Tlen; i++ ) T[i] = (char)( arr[i] + 'a' );

    free( arr );
    free( gdata );
    return T;
}

#include <stdio.h>
int main() {
    char S[] = "abc";
    char T[] = "cbaxxyxyxyxyxyxyxyxxyxyxy";
    char *ans = customSortString( S, T );
    printf( "%s\n", ans );
}
