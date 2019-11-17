#include <stdlib.h>
#include <string.h>

/*
  0     1010         20
  1    9  11       19
  2   8   12     18
  3  7    13   17
  4 6     14 16
  55      15

  rows = 6
  jump[0] = 10 0
      [1] = 8 2
      [2] = 6 4
      [3] = 4 6
      [4] = 2 8
      [5] = 0 10
 */

char *convert( char *s, int numRows ) {
    const size_t len = strlen( s );
    char *const ans = malloc( len + 1 );

    size_t ans_sz = 0;
    for ( size_t i = 0; i < (size_t)numRows; i++ ) {
        size_t j = i;
        ans[ans_sz++] = s[j];
        if ( ans_sz >= len ) break;

        size_t inc[2];
        inc[1] = i << 1;
        size_t normal = ( (size_t)numRows - 1 << 1 ) - inc[1];
        inc[0] = inc[1] ? normal : ( normal ? normal : 1 );
        for ( size_t toggle = 0; /* INF LOOP */; toggle++ ) {
            size_t tmpinc = inc[toggle & 1];
            if ( tmpinc == 0 ) continue;
            if ( ( j += tmpinc ) >= len ) break;
            ans[ans_sz++] = s[j];
        }
    }

    ans[len] = '\0';
    return ans;
}

#include <stdio.h>

int main() {
    char *ans = convert( "A", 1 );
    printf( "%s\n", ans );
    free( ans );
}
