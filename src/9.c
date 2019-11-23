#include <limits.h>
static int reverse( int x ) {
    int ans = 0;
    while ( x ) {
        if ( ans > INT_MAX / 10 || ans < INT_MIN / 10 ) return 0;
        ans *= 10;
        if ( x > 0 && ans > INT_MAX - x % 10 ) return 0;
        if ( x < 0 && ans < INT_MIN - x % 10 ) return 0;
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

bool isPalindrome( int x ) {
    if ( x < 0 ) return 0;
    return x == reverse( x );
}
