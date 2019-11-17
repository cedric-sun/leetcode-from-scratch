#include <limits.h>
int reverse( int x ) {
    int ans = 0;
    while ( x ) {
        if ( ans > INT_MAX / 10 || ans < INT_MIN / 10 ) return 0;
        int ttans = ans * 10;
        if ( x > 0 && ttans > INT_MAX - x % 10 ) return 0;
        if ( x < 0 && ttans < INT_MIN - x % 10 ) return 0;
        ans = ttans + x % 10;
        x /= 10;
    }
    return ans;
}
