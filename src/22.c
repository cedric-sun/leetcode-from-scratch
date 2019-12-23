#include <stdlib.h>
#include <string.h>

static size_t g_n;
static size_t unclosed_lp_cnt, lp_cnt;

static char* buffer;
static size_t buf_sz;

static char** ans;
static size_t ans_sz, ans_cap;

static void dfs( size_t i ) {
    if ( i == buf_sz - 1 ) {
        if ( ans_sz == ans_cap ) {
            ans_cap <<= 1;
            ans = realloc( ans, ans_cap * sizeof *ans );
        }
        ans[ans_sz++] =
            memcpy( malloc( buf_sz * sizeof **ans ), buffer, buf_sz );
        return;
    }
    if ( unclosed_lp_cnt ) {
        buffer[i] = ')';
        unclosed_lp_cnt--;
        dfs( i + 1 );
        unclosed_lp_cnt++;
    }
    if ( lp_cnt < g_n ) {
        buffer[i] = '(';
        lp_cnt++;
        unclosed_lp_cnt++;
        dfs( i + 1 );
        lp_cnt--;
        unclosed_lp_cnt--;
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** generateParenthesis( int n, int* returnSize ) {
    g_n = n;
    ans_cap = 100;
    ans = malloc( ans_cap * sizeof *ans );
    buf_sz = ( n << 1 ) + 1;
    buffer = malloc( buf_sz * sizeof *buffer );
    buffer[buf_sz - 1] = 0;  // null termination
    lp_cnt = unclosed_lp_cnt = 0;
    ans_sz = 0;

    dfs( 0 );

    free( buffer );
    *returnSize = ans_sz;
    return ans;
}

#include <stdio.h>
int main() {
    int ret_sz;
    char** ans = generateParenthesis( 6, &ret_sz );
    for ( size_t i = 0; i < ret_sz; i++ ) {
        printf( "%s\n", ans[i] );
        free( ans[i] );
    }
    free( ans );
}
