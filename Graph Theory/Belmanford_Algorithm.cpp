/**
 * Belmanford Algorithm
 */

 /** input */
cin >> n >> m;
vector< pair< ll, pair<int, int> > > edge;
for(int i = 0, u, v, w; i < m; i++) {
    cin >> u >> v >> w;
    edge.push_back({w, {u, v}});
}

const ll inf = 1e15;
vector<ll> d(n, inf);
d[0] = 0;
bool negativeCycle = false;

for(int i = 1; i <= n + n; i++) {
    for(auto& e : edge) {
        int u = e.second.first;
        int v = e.second.second;
        ll w = e.first;
        if( d[v] > d[u] + w ) {
            d[v] = d[u] + w;
            if( i >= n and v == n - 1 ) {
                negativeCycle = true;
            }
        }
    }
}

