#include <stddef.h>
#include <stdint.h>

static double solve( int* A, size_t m, int* B, size_t n ) {
    size_t k = ( ( m + n ) >> 1 ) + 1;
    size_t r = ( m > k ? k : m ) + 1;
    size_t l = ( int_fast64_t )( k - n ) > 0 ? k - n : 0;  // TODO
    size_t p, q;
    while ( l < r ) {
        p = ( l + r ) >> 1;
        q = k - p;
        if ( q == 0 || ( p > 0 && A[p - 1] > B[q - 1] ) ) {
            if ( q != n && A[p - 1] > B[q] )
                r = p;  // A offer too much
            else
                break;  // found unique solution
        } else {
            if ( p != m && B[q - 1] > A[p] )
                l = p + 1;  // A offered too less
            else
                break;  // found unique solution
        }
    }
    int_fast64_t m0 = ( p == 0 ? INT_FAST64_MIN : A[p - 1] ) >
                              ( q == 0 ? INT_FAST64_MIN : B[q - 1] )
                          ? ( A[p-- - 1] )
                          : ( B[q-- - 1] );
    int_fast64_t m1 = ( p == 0 && q == 0 )
                          ? 0x114514deadbeef
                          : ( ( p == 0 ? INT_FAST64_MIN : A[p - 1] ) >
                                      ( q == 0 ? INT_FAST64_MIN : B[q - 1] )
                                  ? ( A[p - 1] )
                                  : ( B[q - 1] ) );
    return ( m + n ) & 1 ? m0 : ( m0 + m1 ) / 2.0;
}

double findMedianSortedArrays( int* nums1, int nums1Size, int* nums2,
                               int nums2Size ) {
    return solve( nums1, (size_t)nums1Size, nums2, (size_t)nums2Size );
}
