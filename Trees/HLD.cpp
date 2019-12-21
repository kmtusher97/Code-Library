int dpth, sz[mxn], lvl[mxn];
int head[mxn], prnt[mxn], st[mxn], ed[mxn];

void dfs( int u = 1, int p = 0 ) {
    lvl[u] = lvl[p] + 1, prnt[u] = p, sz[u] = 1;

    for(auto& v : adj[u]) {
        if( v == p ) continue;
        dfs( v, u ), sz[u] += sz[v];
        if( sz[v] >= sz[adj[u][0]] ) swap(v, adj[u][0]);
    }
}

void decompose( int u = 1, int p = 0 ) {
    st[u] = ++dpth;

    for(auto& v : adj[u]) {
        if( v == p ) continue;
        head[v] = (v == adj[u][0]) ? head[u] : v;
        decompose( v, u );
    }

    ed[u] = dpth;
}

int lca_of( int u, int v ) {
    while( head[u] != head[v] ) {
        if( lvl[head[u]] > lvl[head[v]] ) u = prnt[head[u]];
        else                              v = prnt[head[v]];
    }
    return (lvl[u] < lvl[v]) ? u : v;
}int dpth, sz[mxn], lvl[mxn];
int head[mxn], prnt[mxn], st[mxn], ed[mxn];

void dfs( int u = 1, int p = 0 ) {
    lvl[u] = lvl[p] + 1, prnt[u] = p, sz[u] = 1;

    for(auto& v : adj[u]) {
        if( v == p ) continue;
        dfs( v, u ), sz[u] += sz[v];
        if( sz[v] >= sz[adj[u][0]] ) swap(v, adj[u][0]);
    }
}

void decompose( int u = 1, int p = 0 ) {
    st[u] = ++dpth;

    for(auto& v : adj[u]) {
        if( v == p ) continue;
        head[v] = (v == adj[u][0]) ? head[u] : v;
        decompose( v, u );
    }

    ed[u] = dpth;
}

int lca_of( int u, int v ) {
    while( head[u] != head[v] ) {
        if( lvl[head[u]] > lvl[head[v]] ) u = prnt[head[u]];
        else                              v = prnt[head[v]];
    }
    return (lvl[u] < lvl[v]) ? u : v;
}
