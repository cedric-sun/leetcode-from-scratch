static const int RN_VAL[] = {1,  4,   5,   9,   10,  40,  50,
                             90, 100, 400, 500, 900, 1000};

typedef enum { I, IV, V, IX, X, XL, L, XC, C, CD, D, CM, M } roman;

static roman next_token( char** s ) {
    char cur = **s, next = *( ( *s ) + 1 );
    switch ( cur ) {
        case 'I':
            if ( next == 'V' ) {
                *s += 2;
                return IV;
            }
            if ( next == 'X' ) {
                *s += 2;
                return IX;
            }
            ( *s )++;
            return I;
        case 'V':
            ( *s )++;
            return V;
        case 'X':
            if ( next == 'L' ) {
                *s += 2;
                return XL;
            }
            if ( next == 'C' ) {
                *s += 2;
                return XC;
            }
            ( *s )++;
            return X;
        case 'L':
            ( *s )++;
            return L;
        case 'C':
            if ( next == 'D' ) {
                *s += 2;
                return CD;
            }
            if ( next == 'M' ) {
                *s += 2;
                return CM;
            }
            ( *s )++;
            return C;
        case 'D':
            ( *s )++;
            return D;
        case 'M':
            ( *s )++;
            return M;
    }
    return 0xbada991e;
}

int romanToInt( char* s ) {
    int ans = 0;
    while ( *s != '\0' ) {
        ans += RN_VAL[next_token( &s )];
    }
    return ans;
}
