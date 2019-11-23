#include <ctype.h>
#include <limits.h>
#include <string.h>

#define SPACE ' '
#define PLUS '+'
#define MINUS '-'

int myAtoi( char* str ) {
    size_t len = strlen( str );
    size_t start = 0;
    while ( start < len && str[start] == SPACE ) start++;
    if ( start >= len ) return 0;
    int signum = 1;
    char* c = str + start;
    if ( *c == PLUS ) {
        c++;
    } else if ( *c == MINUS ) {
        signum = -1;
        c++;
    }
    int ans = 0, overflow = 0, intmax_plus1 = 0;
    while ( isdigit( *c ) ) {
        if ( ans > INT_MAX / 10 ) {
            overflow = 1;
            break;
        }
        int d = *c - '0';
        ans *= 10;
        if ( ans - INT_MAX >= 1 - d ) {
            // equal case is actually not overflow
            // but produce the same result
            overflow = 1;
            break;
        }
        ans += d;
        c++;
    }
    if ( overflow ) return signum > 0 ? INT_MAX : INT_MIN;
    return signum > 0 ? ans : -ans;
}
