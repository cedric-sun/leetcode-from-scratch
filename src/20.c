#include <stdbool.h>

#include <stdlib.h>
#include <string.h>

static inline bool is_match( char open, char close ) {
    if ( open == '[' ) return close == ']';
    if ( open == '(' ) return close == ')';
    if ( open == '{' ) return close == '}';
    return false;
}

static bool isValid( char *s ) {
    size_t len = strlen( s );
    if ( len & 1 ) return false;
    char *stack = malloc( len );
    size_t sz = 0;
    for ( size_t i = 0; i < len; i++ ) {
        if ( len - i < sz ) return false;
        if ( sz == 0 || !is_match( stack[sz - 1], s[i] ) )
            stack[sz++] = s[i];
        else
            sz--;
    }
    free( stack );
    return sz == 0;
}

#include <stdio.h>
int main() { printf( "%b\n", isValid( "()[]" ) ); }
