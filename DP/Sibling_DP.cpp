/**
 * LightOJ 1252 Maintaining Communities
 */
int cost[mxn];
int dwn[mxn], rgt[mxn];

void dfs( int u, int p ) {
	dwn[u] = 0;
	int last = 0;
	for(auto& v : G[u]) {
		if( v.first == p ) continue;
		cost[v.first] = v.second;
		dfs( v.first, u );

		if( !dwn[u] ) dwn[u] = v.first;
		rgt[last] = v.first;
		last = v.first;
	}
	rgt[last] = 0;
}

int dp[mxn][K];

int dfs1( int u, int have ) {
	if( !u ) return 0;
	int& ret = dp[u][have];
	if( ~ret ) return ret;

	/**disconnect the parent*/
	ret = 1 + dfs1( dwn[u], k ) + dfs1( rgt[u], have );
	/**connected with root*/
	int rest = have - cost[u];
	for(int i = 0; i <= rest; i++) {
		ret = min(ret, dfs1( dwn[u], i ) + dfs1( rgt[u], rest - i ));
	}
	return ret;
}

/**inside main*/
int res = dfs1( 1, k );


