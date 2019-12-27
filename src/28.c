#include <stdlib.h>
#include <string.h>

static int kmp_first_occur( const char *text, const char *pattern ) {
    const size_t plen = strlen( pattern );
    const size_t tlen = strlen( text );

    int *const kmp_next = malloc( plen * sizeof *kmp_next );
    kmp_next[0] = -1;
    // j has to allow negative here
    for ( int i = 1, j = 0; i < plen; i++, j++ ) {
        if ( pattern[i] == pattern[j] ) {
            kmp_next[i] = kmp_next[j];
        } else {
            kmp_next[i] = j;
            do
                j = kmp_next[j];
            while ( j >= 0 && pattern[i] != pattern[j] );
        }
    }

    int ans = -1;
    for ( int i = 0, j = 0; i < tlen; ) {
        if ( text[i] == pattern[j] ) {
            i++;
            j++;
            if ( j == plen ) {
                ans = i - j;
                break;
            }
        } else {
            j = kmp_next[j];
            if ( j < 0 ) {
                i++;
                j++;
            }
        }
    }
    free( kmp_next );
    return ans;
}

int strStr(char * haystack, char * needle){
    if (*needle == 0) return 0;
    return kmp_first_occur(haystack,needle);
}
