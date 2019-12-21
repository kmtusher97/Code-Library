/*  ~*BISMILLAHIR RAHMANIR RAHIM*~  */
#include <bits/stdc++.h>
using namespace std;
typedef long long intl;
#define MX_N 100005
int ff[MX_N];
struct point {
  intl x, y;
  point() { x = y = 0; }
  point( intl _x, intl _y ) : x(_x), y(_y) { }
  bool operator == ( point o ) const { return ( x == o.x && y == o.y ); }
  bool operator != ( point o ) const { return ( x != o.x || y != o.y ); }
  bool operator < ( point& o ) const { return ( x != o.x ) ? x < o.x : y < o.y ; }
};

point operator + ( const point& a, const point& b ) { return point( a.x + b.x, a.y + b.y ); }
point operator - ( const point& a, const point& b ) { return point( a.x - b.x, a.y - b.y ); }

intl dist_sq( point& a, point& b ) { return ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y ); }
intl crossp( point a, point b ) { return a.x * b.y - a.y * b.x; }
bool ccw( point& a, point& b, point& c ) { return crossp( b - a, c - a ) >= 0; }

vector<point> convexHull( vector<point> P ) {
  int n = P.size(), j = 0;
  if( n <= 1 ) return P;
  sort(P.begin(), P.end());
  vector<point> H(n * 2);

  for(int i = 0; i < n; H[j++] = P[i++])
    for(; j >= 2 && ccw( H[j - 2], H[j - 1], P[i] ); j--);

  for(int i = n - 2, k = j; i >= 0; H[j++] = P[i--])
    for(; j > k && ccw( H[j - 2], H[j - 1], P[i] ); j--);

  H.resize(j - 1 - (H[1] == H[0]));
  return H;
}

void kmpProcess( vector<point> v ) {
  int N = v.size();
  ff[0] = -1;
  for(int i = 0, j = -1; i < N; ) {
    while( j >= 0 && v[i] != v[j] ) j = ff[j];
    ff[++i] = ++j;
  }
}

bool kmpSearch( vector<point> T, vector<point> P ) {
  int n = T.size(), m = P.size();
  for(int i = 0, j = 0; i < 2 * n; ) {
    while( j >= 0 && T[i % n] != P[j] ) j = ff[j];
    i++, j++;
    if( j == n ) return true;
  }
  return false;
}

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<point> A(n), B(m);
  for(int i = 0; i < n; i++)
    scanf("%d %d", &A[i].x, &A[i].y);
  for(int i = 0; i < m; i++)
    scanf("%d %d", &B[i].x, &B[i].y);

  vector<point> H1 = convexHull( A );
  vector<point> H2 = convexHull( B );

  if( H1.size() != H2.size() ) {
    printf("NO\n");
    exit(0);
  }
  n = H1.size();
  vector<point> AA, BB;
  for(int i = 0; i < n; i++)
    AA.push_back({dist_sq( H1[i], H1[(i + 1) % n]), dist_sq( H1[i], H1[(i + 2) % n])});

  for(int i = 0; i < n; i++)
    BB.push_back({dist_sq( H2[i], H2[(i + 1) % n]), dist_sq( H2[i], H2[(i + 2) % n])});

  kmpProcess( AA );
  if( kmpSearch( AA, BB ) ) {
    printf("YES\n");
    exit(0);
  }

  kmpProcess( BB );
  if( kmpSearch( BB, AA ) ) {
    printf("YES\n");
    exit(0);
  }
  printf("NO\n");
  return 0;
}
