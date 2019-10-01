/**
 * Submatrix Min query
 * O(1) Query
 */
#define MX_N 1005
#define MX_LG 11
int n, m, a[MX_N][MX_N], sp[MX_LG][MX_N][MX_LG][MX_N];

void build_Sparce_Table() {
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++)
      sp[0][i][0][j] = a[i][j];

    for(int y = 1; (1 << y) <= m; y++)
      for(int j = 1; j + (1 << y) - 1 <= m; j++)
        sp[0][i][y][j] = max( sp[0][i][y - 1][j], sp[0][i][y - 1][j + (1 << (y - 1))] );
  }

  for(int x = 1; (1 << x) <= n; x++)
    for(int i = 1; i + (1 << x) - 1 <= n; i++)
      for(int y = 0; (1 << y) <= m; y++)
        for(int j = 1; j + (1 << y) - 1 <= m; j++)
          sp[x][i][y][j] = max( sp[x - 1][i][y][j], sp[x - 1][i + (1 << (x - 1))][y][j] );
}

int Range_Query( int x1, int y1, int x2, int y2 ) {
  int kx = log2(x2 - x1 + 1);
  int ky = log2(y2 - y1 + 1);
  int tmp1 = max( sp[kx][x1][ky][y1], sp[kx][x1][ky][y2 - (1 << ky) + 1] );
  int tmp2 = max( sp[kx][x2 - (1 << kx) + 1][ky][y1], sp[kx][x2 - (1 << kx) + 1][ky][y2 - (1 << ky) + 1] );
  return max( tmp1, tmp2 );
}
