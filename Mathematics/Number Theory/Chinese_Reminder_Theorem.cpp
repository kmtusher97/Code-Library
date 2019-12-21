/**
 * Chinese Remainder Theorem
 * if
 * x % M1 = A1
 * x % M2 = A2
 * ...........
 * x % Mk = Ak
 * then,
 * x ≅ A1 (mod M1)
 * x ≅ A2 (mod M2)
 * ...............
 * x ≅ Ak (mod Mk)
 * solve() function will return {x, m} pair,
 * where x is the unique solution modulo m.
 */

/**
 * Weak form of CRT (all mi ∈ M are pairwise coprime)
 *
 */
class ChineseReminderTheorm {
public:
    vector<int> A, M;

    void clear() {
        A.clear(), M.clear();
    }

    ll extendedEuclid( ll a, ll b, ll& x, ll& y ) {
        if( a == 0 ) {
            x = 0, y = 1;
            return b;
        }
        ll x1, y1;
        ll gcd = extendedEuclid( b % a, a, x1, y1 );

        x = y1 - (b / a) * x1;
        y = x1;
        return gcd;
    }

    pair<ll, ll> solve() {
        if( A.empty() or A.size() != M.size() ) return {-1, -1}; // invalid input

        ll a1 = A[0];
        ll m1 = M[0];
        for(int i = 1; i < A.size(); i++) {
            ll a2 = A[i];
            ll m2 = M[i];

            ll p, q;
            extendedEuclid( m1, m2, p, q );
            ll x = (a1 * m2 * q + a2 * m1 * p) % (m1 * m2);
            a1 = x;
            m1 = m1 * m2;
        }
        if( a1 < 0 ) a1 += m1;
        return {a1, m1};
    }
};

/**
 * Chinese Remainder Theorem for non Coprime Moduli
 */
class ChineseReminderTheorm {
public:
    vector<ll> A, M;

    void clear() {
        A.clear(), M.clear();
    }

    ll extendedEuclid( ll a, ll b, ll& x, ll& y ) {
        ... ... ...
    }

    pair<ll, ll> solve() {
        if( A.empty() or A.size() != M.size() ) return {-1, -1}; // invalid input

        ll a1 = A[0];
        ll m1 = M[0];
        a1 %= m1;

        for(int i = 1; i < A.size(); i++) {
            ll a2 = A[i];
            ll m2 = M[i];

            ll gcd = __gcd(m1, m2);
            if( a1 % gcd != a2 % gcd ) return {-1, -1}; // conflict in equation

            ll p, q;
            extendedEuclid( m1 / gcd, m2 / gcd, p, q );

            ll mod = (m1 / gcd) * m2;
            /**careful about overflow**/
            ll tmp = ((__int128)a1 * (m2 / gcd) * q + (__int128)a2 * (m1 / gcd) * p) % mod;
            a1 = tmp;
            if( a1 < 0 ) a1 += mod;
            m1 = mod;
        }
        return {a1, m1};
    }
};
