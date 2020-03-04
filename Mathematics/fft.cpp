const double pi=acos(-1.0);
 
void fft( vector< complex<double> >& a, bool inv ) {
  int n = a.size();
  for(int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for( ; bit & j; bit >>= 1) j ^= bit;
    j ^= bit;
    if( i < j ) swap(a[i], a[j]);
  }
  for(int len = 2; len <= n; len <<= 1) {
    double ang = 2 * pi / len * (inv ? -1 : 1);
    complex<double> wlen(cos(ang), sin(ang));
    for(int i = 0; i < n; i += len) {
      complex<double> w(1);
      for(int j = 0; j < len / 2; j++) {
        complex<double> u = a[i + j], v = a[i + j + len / 2] * w;
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }
  if( inv ) for(auto& x : a) x /= n;
}
 
vector<ll> multiply( vector<ll>& a, vector<ll>& b ) {
  int sz = a.size() + b.size();
  int n = 1;
  while( n < sz ) n <<= 1;
  vector< complex<double> > fa(a.begin(), a.end());
  vector< complex<double> > fb(b.begin(), b.end());
  fa.resize(n);
  fb.resize(n);
  fft( fa, false ); 
  fft( fb, false );
  for(int i = 0; i < n; i++) fa[i] *= fb[i];
  fft( fa, true ); 
  vector<ll> ret(n);
  for(int i = 0; i < n; i++)
    ret[i] = round(fa[i].real());
  return ret;
}
