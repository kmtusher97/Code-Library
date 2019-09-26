int extended_gcd( int a, int b, int& x, int &y )
{
  if( a == 0 )
  {
    x = 0, y = 1;
    return b;
  }
  int x1, y1;
  int gcd = extended_gcd( b % a, a, x1, y1 );

  x = y1 - (b / a) * x1;
  y = x1;
  return gcd;
}

int mod_inverse( int a, int m ) //ax + my = 1
{
  int x, y;
  int gcd = extended_gcd( a, m, x, y );
  if( gcd != 1 )
  {
    return -1;    // modular inverse doesn't exits
  }
  return (x % m + m) % m;
}
