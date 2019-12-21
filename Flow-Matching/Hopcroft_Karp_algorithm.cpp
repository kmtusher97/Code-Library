struct hopcroft {
    static const int MX1 = 50002;
    int N, M, match[2*MX1], dist[2*MX1];
    vector<int> G[MX1];

    hopcroft( int n, int m ) {
        N = n, M = m;
        memset(match, 0, sizeof match);
    }
    bool bfs() {
        queue<int> Q;
        for(int i=1; i<=N; i++) {
            if( match[i]==0 )
                dist[i] = 0, Q.push(i);
            else
                dist[i] = INT_MAX;
        }
        dist[0] = INT_MAX;
        
        while( !Q.empty() ) {
            int u = Q.front();
            Q.pop();
            if( u==0 ) continue;
            for(int i=0; i<G[u].size(); i++) {
                int v = G[u][i];
                if( dist[match[v]]!=INT_MAX ) continue;
                dist[match[v]] = dist[u] + 1;
                Q.push(match[v]);
            }
        }
        return (dist[0]!=INT_MAX);
    }
    bool dfs( int u ) {
        if( u!=0 ) {
            for(int i=0; i<G[u].size(); i++) {
                int v = G[u][i];
                if( dist[match[v]]==dist[u]+1 ) {
                    if( dfs( match[v] ) ) {
                        match[u] = v;
                        match[v] = u;
                        return true;
                    }
                }
            }
            dist[u] = INT_MAX;
            return false;
        }
        return true;
    }
    int maximum_bipartite_matching() {
        int matching = 0;
        while( bfs() ) {
            for(int i=1; i<=N; i++) {
                if( match[i]==0 && dfs( i ) )
                    matching++;
            }
        }
        return matching;
    }
};
