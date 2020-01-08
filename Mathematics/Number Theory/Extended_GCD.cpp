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
 * Iterative Implementation
 */
void extendedEuclid( ll a, ll b) {
    ll x = 0, y = 1;
    ll lastx = 1, lasty = 0, temp;
    while( b != 0 ) {
        ll q = a / b;
        ll r = a % b;

        a = b;
        b = r;

        temp = x;
        x = lastx - q * x;
        lastx = temp;

        temp = y;
        y = lasty - q * y;
        lasty = temp;
    }
    cout << "GCD = " << a << "\n";
    cout << "Roots  x : " << lastx  << " y :" << lasty;
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


/**
X|+|Y|is the minimal.  If there areseveralXandYsatisfying the minimal criteria, 
output the pair for whichX≤Y. 
*/
ll extendedEuclid( ll a, ll b, ll& x, ll &y ) {
    if( b == 0 ) {
        x = 1, y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extendedEuclid( b, a % b, x1, y1 );

    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}
