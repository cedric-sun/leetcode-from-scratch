#include <stddef.h>
#include <stdlib.h>
#include <string.h>


char* longestPalindrome( char* s ) {

    char* ans = malloc( maxlen + 1 );
    strncpy( ans, s + start_at, maxlen );
    ans[maxlen] = '\0';
    return ans;
}
