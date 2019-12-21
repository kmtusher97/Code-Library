//(sieve Phi) Eular Totient Function

int phi[MX_N];
bitset<MX_N> vis;

void euler_totient()
{
  for(int i = 0; i < MX_N; phi[i] = i, i++);
  vis[1] = 1;

  for(int i = 2; i < MX_N; i += 2)
  {
    if( i != 2 ) vis[i] = 1;
    phi[i] = phi[i] / 2;
  }

  for(int i = 3; i < MX_N; i += 2)
  {
    if( !vis[i] )
    {
      phi[i] = phi[i] - 1;
      for(int j = i + i; j < MX_N; j += i)
        vis[j] = 1, phi[j] = phi[j] / i * (i - 1);
    }
  }
}

// phi( x ) 

ll phi( ll x ) 
{
  ll ret = x;

  for(ll p = 2; p * p <= x; p++)
  {
    if( x % p ) continue;
    for(; x % p == 0; x /= p);
    ret -= (ret / p);
  }
  if( x > 1 )
  {
    ret -= (ret / x);
  }
  return ret;
}
