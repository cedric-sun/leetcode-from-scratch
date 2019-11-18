#include <stdlib.h>
#include <string.h>

/*
  0      10         20
  1    9 11       19
  2   8  12     18
  3  7   13   17
  4 6    14 16
  5      15

  rows = 6
  jump[0] = 10
      [1] = 8 2
      [2] = 6 4
      [3] = 4 6
      [4] = 2 8
      [5] = 10
 */

char *convert( char *s, int numRows ) {
    const size_t len = strlen( s );
    char *const ans = malloc( len + 1 );

    size_t SZT_NROW = (size_t)numRows;
    size_t MAX_I = SZT_NROW - 1;

    size_t ans_sz = 0;
    for ( size_t i = 0; i < SZT_NROW; i++ ) {
        size_t j = i;
        ans[ans_sz++] = s[j];
        if ( ans_sz >= len ) break;

        size_t inc[2];
        if ( i == 0 || i == MAX_I ) {
            inc[0] = inc[1] = MAX_I ? MAX_I << 1 : 1;
        } else {
            inc[1] = i << 1;
            inc[0] = ( MAX_I << 1 ) - inc[1];
        }
        for ( size_t toggle = 0; ( j += inc[toggle & 1] ) < len; toggle++ ) {
            ans[ans_sz++] = s[j];
        }
    }

    ans[len] = '\0';
    return ans;
}

#include <stdio.h>

int main() {
    char *ans = convert( "ABC", 1 );
    printf( "%s\n", ans );
    free( ans );
}
