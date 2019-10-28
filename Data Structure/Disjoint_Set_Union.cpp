/**
 * Disjoint Set Union
 * Union Find
 */

struct DSU {
    vector<int> P;

    DSU(int n) {
        P.resize(n + 1);
        for(int i = 0; i <= n; P[i] = i, i++);
    }
    void join( int u, int v ) {
        P[findRoot( u )] = P[findRoot( v )];
    }
    int findRoot( int u ) {
        while( P[u] != u ) {
            P[u] = P[P[u]];
            u = P[u];
        }
        return P[u];
    }
};

