#include <limits.h>
#include <stdlib.h>
#include <string.h>

char *good_try_leetcode_making_fun_of_me() {
    char *empty = malloc( 1 );
    empty[0] = '\0';
    return empty;
}

char *longestCommonPrefix( char **strs, int strsSize ) {
    if ( strsSize == 0 ) {
        return good_try_leetcode_making_fun_of_me();
    }

    int *lens = malloc( strsSize * sizeof *lens );
    int minlen = INT_MAX;
    for ( int i = 0; i < strsSize; i++ ) {
        int len = strlen( strs[i] );
        if ( len < minlen ) minlen = len;
        lens[i] = len;
    }
    int cplen = 0;

    while ( cplen < minlen ) {
        char c = strs[0][cplen];
        for ( int i = 1; i < strsSize; i++ )
            if ( strs[i][cplen] != c ) goto DONE;
        cplen++;
    }

DONE:
    free( lens );
    char *ans = malloc( cplen + 1 );
    memcpy( ans, *strs, cplen );
    ans[cplen] = '\0';
    return ans;
}
