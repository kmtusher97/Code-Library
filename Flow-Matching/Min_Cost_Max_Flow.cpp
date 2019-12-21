const int mxn = 7210;
const int mxm = 100010;
const int inf = 100000008;
struct Edge {
	int u, v, cap;
	double cost;
	int next;
	Edge() { }
	Edge(int u, int v, int cap, double cost, int next) : u(u), v(v), cap(cap), cost(cost), next(next) { }  
} edge[mxm * 3];
int NE;
int head[mxn], pp[mxn];
double dist[mxn];
bool vis[mxn];
void init( int n ) {
	NE = 0;
	fill(head, head + n + 1, -1);
}
void addEdge( int u, int v, int cap, double cost ) {
	edge[NE] = Edge( u, v, cap, cost, head[u] );
	head[u] = NE++;
	edge[NE] = Edge( v, u, 0, -cost, head[v] );
	head[v] = NE++;
}
int Q[mxm * 3];
bool SPFA( int s, int t, int n ) {
	int i, u, v;
	double tmp;
	int he = 0, ta = 0;
	fill(pp, pp + n + 1, -1);
	fill(vis, vis + n + 1, false);
	fill(dist, dist + n + 1, inf);
	vis[s] = true, dist[s] = 0;
	Q[++ta] = s;
	while( he != ta ) {
		u = Q[++he]; vis[u] = false;
		if( he >= 250000 ) he = 0;
		for(i = head[u]; ~i; i = edge[i].next) {
			v = edge[i].v;
			tmp = dist[u] + edge[i].cost;
			if( edge[i].cap and dist[v] > tmp ) {
				dist[v] = tmp;
				pp[v] = i;
				if( vis[v] ) continue;
				Q[++ta] = v;
				if( ta >= 250000 ) ta = 0;
				vis[v] = true;
			}
		}
	}
	if( dist[t] == inf ) return false;
	return true;
}
pair<int, double> minCostMaxFlow( int s, int t, int n ) {
	int flow = 0;
	int i, minFlow;
	double minCost = 0;
	for(; SPFA( s, t, n ); ) {
		minFlow = inf + 1;
		for(i = pp[t]; ~i; i = pp[edge[i].u]) {
			minFlow = min(minFlow, edge[i].cap);
		}
		flow += minFlow;
		for(i = pp[t]; ~i; i = pp[edge[i].u]) {
			edge[i].cap -= minFlow;
			edge[i^1].cap += minFlow;
		}
		minCost += dist[t] * minFlow;
	}
	return {flow, minCost};
}
