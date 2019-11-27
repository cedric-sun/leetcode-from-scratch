#include <stdlib.h>
#include <string.h>

static const char *const RN_STR[] = {"I",  "IV", "V",  "IX", "X",  "XL", "L",
                                     "XC", "C",  "CD", "D",  "CM", "M"};
static const int RN_VAL[] = {1,  4,   5,   9,   10,  40,  50,
                             90, 100, 400, 500, 900, 1000};

typedef enum { I, IV, V, IX, X, XL, L, XC, C, CD, D, CM, M } roman;

static void handle( roman r, int *num, char *ans, size_t *len ) {
    while ( *num >= RN_VAL[r] ) {
        memcpy( ans + *len, RN_STR[r], 1 + ( r & 1 ) );
        *len += 1 + ( r & 1 );
        *num -= RN_VAL[r];
    }
}

char *intToRoman( int num ) {
    char *ans = malloc( 16 );
    size_t len = 0;
    for ( roman i = M; i >= I && num > 0; i-- ) handle( i, &num, ans, &len );
    ans[len] = '\0';
    return ans;
}

#include <stdio.h>
int main() {
    int max = 0;
    int maxnum;
    for ( int i = 1; i < 4000; i++ ) {
        char *ans = intToRoman( i );
        int len = strlen( ans );
        if ( max < len ) max = len, maxnum = i;
        free( ans );
    }
    printf( "%d at %d\n", max, maxnum );
}
