#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const char pad[][5] = {"abc", "def",  "ghi", "jkl",
                              "mno", "pqrs", "tuv", "wxyz"};

static const char *g_digits;
static char *buffer;
static char **ans;
static size_t len, anssz;

static inline uintmax_t simple_pow( uintmax_t base, uintmax_t exp ) {
    uintmax_t ans = 1;
    while ( exp-- ) ans *= base;
    return ans;
}

static inline void append_new_ans() {
    char *tmp = malloc( len + 1 );
    memcpy( tmp, buffer, len + 1 );
    ans[anssz++] = tmp;
}

static void dfs( size_t i ) {
    if ( i == len ) {
        append_new_ans();
        return;
    }
    int c;
    for ( size_t j = 0; c = pad[g_digits[i] - '2'][j]; j++ ) {
        buffer[i] = c;
        dfs( i + 1 );
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCombinations( char *digits, int *returnSize ) {
    g_digits = digits;
    len = strlen( digits );
    anssz = 0;
    ans = malloc( simple_pow( 4, len ) * sizeof *ans );
    buffer = malloc( len + 1 );
    buffer[len] = 0;  // null termination

    dfs( 0 );

    free( buffer );
    *returnSize = len ? anssz : 0;
    return ans;
}

#include <stdio.h>

int main() {
    char data[] = "";
    int retsz;
    char **ans = letterCombinations( data, &retsz );

    for ( size_t i = 0; i < retsz; i++ ) printf( "%s\n", ans[i] );
    printf( "Return size = %d\n", retsz );

    for ( size_t i = 0; i < retsz; i++ ) free( ans[i] );
    free( ans );
}
