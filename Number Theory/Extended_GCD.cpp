/**
 * Extended Euclidean Algorithm
 * a⋅x + b⋅y = gcd(a, b)
 */
int extended_gcd( int a, int b, int& x, int &y ) {
    if( a == 0 ) {
        x = 0, y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extended_gcd( b % a, a, x1, y1 );

    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

/**
 * Modular Inverse using Extended Euclidean algorithm
 * a⋅x + m⋅y = 1
 * a⋅x ≡ 1 (mod m)
 */
int mod_inverse( int a, int m ) {
    int x, y;
    int gcd = extended_gcd( a, m, x, y );
    if( gcd != 1 ) {
        /**modular inverse doesn't exits*/
        return -1;
    }
    return (x % m + m) % m;
}
