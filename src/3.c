#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ord( x ) ( (size_t)x )
static int lengthOfLongestSubstring( char* s ) {
    size_t len = strlen( s );
    if ( len == 0 ) return 0;
    // Length of Longest Substring Without Repeating Characters _ That End
    // Exactly At
    size_t* llswrc_teea = malloc( len * sizeof *llswrc_teea );
    size_t latest_occur[CHAR_MAX];
    memset( latest_occur, -1, sizeof( latest_occur ) );

    latest_occur[ord( s[0] )] = 0;
    llswrc_teea[0] = 1;

    for ( size_t i = 1; i < len; i++ ) {
        size_t cur_ord = ord( s[i] );
        // previous ls range: [ i-ll[i-1] , i-1  ]
        llswrc_teea[i] = latest_occur[cur_ord] >= ( i - llswrc_teea[i - 1] ) &&
                                 latest_occur[cur_ord] <= i - 1
                             ? i - latest_occur[cur_ord]
                             : llswrc_teea[i - 1] + 1;
        latest_occur[cur_ord] = i;
    }

    size_t res = 0;
    for ( size_t i = 0; i < len; i++ ) {
        if ( res < llswrc_teea[i] ) res = llswrc_teea[i];
    }
    free( llswrc_teea );
    return (int)res;
}
