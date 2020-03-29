const int mxnlg = 33 - __builtin_clz(n);
vector<int> h(n + 1, 0);
vector< vector<int> > par(n + 1, vector<int>(mxnlg, 0));
function<void(int, int)> dfs = [&](int u, int p) {
  par[u][0] = p;
  h[u] = h[p] + 1;
  for(int i = 1; i < mxnlg; i++) {
    par[u][i] = par[par[u][i - 1]][i - 1];
  }
  for(auto& v : G[u]) {
    if( v == p ) continue;
    dfs( v, u );
  }
};
auto lcaOf = [&](int u, int v) {
  if( h[u] < h[v] ) swap(u, v);
  for(int i = mxnlg - 1; i >= 0; i--) {
    if( h[par[u][i]] < h[v] ) continue;
    u = par[u][i];
  }
  if( u == v ) return u;
  for(int i = mxnlg - 1; i >= 0; i--) {
    if( par[u][i] == par[v][i] ) continue;
    u = par[u][i], v = par[v][i];
  }
  return par[u][0];
};
