#include <limits.h>

static inline int max( int a, int b ) { return a > b ? a : b; }

int maxSubArray( int* nums, size_t numsSize ) {
    int* dp = malloc( numsSize * sizeof *dp );
    dp[0] = nums[0];
    for ( size_t i = 1; i < numsSize; i++ ) {
        dp[i] = max( dp[i - 1] + nums[i], nums[i] );
    }
    int ans = INT_MIN;
    for ( size_t i = 0; i < numsSize; i++ )
        if ( ans < dp[i] ) ans = dp[i];
    return ans;
}
