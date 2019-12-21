
const int mxn = 1e3 + 3;
struct Edge{
    int frm, to, flw, cap;
};

struct dinich_MaxFlow {
    int nodes, src, snk, dist[mxn], start[mxn];
    
    vector<Edge> E;
    vector<int> G[mxn];

    void initialize( int _n ) {
        nodes = _n, E.clear();
        for(int i=0; i<=nodes; i++)
            G[i].clear();
    }
    void Clear() {
        for(int i=0; i<(int)E.size(); i++)
            E[i].flw = 0;
    }
    void addEdge( int u, int v, int w ) {
        Edge p = { u, v, 0, w };
        Edge q = { v, u, 0, 0 };
        G[u].push_back( (int)E.size() );
        E.push_back(p);
        G[v].push_back( (int)E.size() );
        E.push_back(q);
    }

    bool bfs() {
        memset(dist, -1, sizeof dist);
        queue<int> Q;
        Q.push(src), dist[src] = 0;

        while( !Q.empty() ) {
            int u = Q.front();
            Q.pop();
            for(int j = 0; j < (int)G[u].size(); j++) {
                int id = G[u][j];
                int v = E[id].to;
                if( ~dist[v] || E[id].flw==E[id].cap )
                    continue;
                dist[v] = dist[u]+1;
                Q.push(v);
            }
        }
        return ~dist[snk];
    }
    int dfs( int u, int flow ) {
        if( !flow )
            return 0;
        if( u==snk )
            return flow;
        for(; start[u] < (int)G[u].size(); ++start[u]) {
            int id = G[u][start[u]];
            int v = E[id].to;
            if( dist[v]!=dist[u]+1 )
                continue;
            int df = dfs( v, min(flow, E[id].cap-E[id].flw) );
            if( df > 0 ) {
                E[id].flw += df;
                E[id ^ 1].flw -= df;
                return df;
            }
        }
        return 0;
    }
    int maxFlow( int _s, int _t ) {
        int ret = 0;
        Clear();
        src = _s, snk = _t;
        while( bfs() ) {
            memset(start, 0, sizeof start);
            while( int tmp = dfs( src, inf ) ) {
                ret += tmp;
            }
        }
        return ret;
    }
};
