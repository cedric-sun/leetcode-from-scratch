#include <stdlib.h>
#include <string.h>

/* counting_sort_letters but the total order is mapped */

#define LOA 26
char* customSortString( char* S, char* T ) {
    const size_t Slen = strlen( S );
    const size_t Tlen = strlen( T );

    int count[LOA];
    memset( count, 0, sizeof count );
    for ( size_t i = 0; i < Tlen; i++ ) count[T[i] - 'a']++;
    size_t sz = 0;
    char* const tmp = malloc( Tlen * sizeof *tmp );
    for ( size_t i = 0; i < Slen; i++ )
        while ( count[S[i] - 'a']-- ) tmp[sz++] = S[i];
    for ( size_t i = 0; i < Tlen; i++ )
        if ( count[T[i] - 'a'] > 0 ) tmp[sz++] = T[i];
    memcpy( T, tmp, Tlen * sizeof *tmp );
    free( tmp );
    return T;
}

#include <stdio.h>
int main() {
    char S[] = "abc";
    char T[] = "cbaxx";
    customSortString( S, T );
    printf( "%s\n", T );
}

