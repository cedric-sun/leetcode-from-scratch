int maxArea( int* height, int heightSize ) {
    int* a = height;
    int l = 0, r = heightSize - 1, max = 0;
    while ( l < r ) {
        int curProd;
        if ( a[l] < a[r] ) {
            curProd = a[l] * ( r - l );
            l++;
        } else {
            curProd = a[r] * ( r - l );
            r--;
        }
        if ( max < curProd ) max = curProd;
    }
    return max;
}
