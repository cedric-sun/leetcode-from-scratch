/********* MANACHER **********/
#include <stdlib.h>

#define DELI '|'
static void manacher( char *s ) {
    size_t slen = strlen( s );
    size_t tlen = ( slen << 1 ) + 1;
    char *t = malloc( tlen );
    for ( size_t i = 0; i < slen; i++ ) {
        t[i << 1] = DELI;
        t[( i << 1 ) + 1] = s[i];
    }
    t[tlen - 1] = DELI;
    size_t *radius = malloc( tlen );
    radius[0] = 1;
    size_t r = 0, c = 0;
    for ( size_t i = 1; i < tlen; i++ ) {
        if ( i <= r ) {
            size_t j = ( c << 1 ) - i;
            if ( radius[j] < lprb - i ) {
                radius[i] = radius[j];
            } else {
                size_t nr = r + 1;
                while ( true ) {
                    size_t tmp_l = ( i << 1 ) - nr;
                    if ( t[tmp_l] == t[nr] )
                        nr++;
                    else
                        break;
                }
                r = nr - 1;
                c = i;
                radius[i] = nr - i;
            }
        } else {
        }
    }
}
