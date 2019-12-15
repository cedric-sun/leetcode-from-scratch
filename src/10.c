#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t i, j;
} state;

state *bt_stack;
size_t sz, cap;

void init() {
    cap = 1024;
    bt_stack = malloc( cap * sizeof *bt_stack );
    sz = 0;
}

void push( size_t i, size_t j ) {
    if ( sz >= cap ) {
        cap <<= 1;
        bt_stack = realloc( bt_stack, cap * sizeof *bt_stack );
    }
    bt_stack[sz].i = i;
    bt_stack[sz].j = j;
    sz++;
}

// PRECOND: sz>0
state pop() { return bt_stack[--sz]; }

bool isMatch( char *s, char *p ) {
    init();
    size_t slen = strlen( s );
    size_t plen = strlen( p );
    size_t i = 0, j = 0;
    while ( i < slen || j < plen ) {
        if ( i >= slen ) {
            if ( !( plen - j & 1 ) ) {
                while ( j < plen ) {
                    if ( p[j + 1] != '*' ) goto BACK_TRACK;
                    j += 2;
                }
                break;
            }
        BACK_TRACK:
            if ( sz != 0 ) {
                state t = pop();
                i = t.i;
                j = t.j;
            } else {
                goto FAIL;
            }
        }
        if ( j >= plen ) {
            goto FAIL;
        }
        if ( j < plen - 1 && p[j + 1] == '*' ) {
            if ( p[j] == '.' ) {
                while ( i < slen ) {
                    push( i, j + 2 );
                    i++;
                }
                j += 2;
            } else {
                while ( s[i] == p[j] ) {
                    push( i, j + 2 );
                    i++;
                }
                j += 2;
            }
        } else if ( p[j] == '.' || s[i] == p[j] ) {
            i++;
            j++;
        } else {
            if ( sz == 0 ) goto FAIL;
            state t = pop();
            i = t.i;
            j = t.j;
        }
    }
    free( bt_stack );
    return true;
FAIL:
    free( bt_stack );
    return false;
}

#include <stdio.h>

int main() {
    char *s = "aabcbcbcaccbcaabc";
    char *p = ".*a*aa*.*b*.c*.*a*";
    bool ans = isMatch( s, p );
    printf( "%s\n", ans ? "true" : "false" );
}
