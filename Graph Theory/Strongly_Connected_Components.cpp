const int mxn = 20005;
int n, m;
vector<int> G[mxn];

static int clk;
int dfs_num[mxn], dfs_low[mxn], visited[mxn];
int grp_of[mxn], indegree[mxn], outdegree[mxn];
vector<int> S, R;

void sccTarjan( int u ) {
    dfs_low[u] = dfs_num[u] = ++clk;
    visited[u] = true;
    S.push_back(u);

    for(int i=0; i<G[u].size(); i++) {
        int v = G[u][i];
        if( !dfs_num[v] ) {
            sccTarjan( v );
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        if( visited[v] )
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
    if( dfs_low[u]==dfs_num[u] ) {
        R.push_back( u );
        while( true ) {
            int v = S.back();
            S.pop_back();
            grp_of[v] = u;
            visited[v] = 0;
            if( u==v )
                break;
        }
    }
}

// inside main()
S.clear(), R.clear(), clk = 0;
for(int i=1; i<=n; i++)
    if( !dfs_num[i] )
        sccTarjan( i );
