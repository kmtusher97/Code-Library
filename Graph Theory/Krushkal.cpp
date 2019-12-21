typedef long long ll;

const int mxn = 1e4 + 5;
int id[mxn], nodes, edges;
pair <ll, pair<int, int> > p[mxn];

void initialize() {
    for(int i = 0; i < mxn; ++i)
        id[i] = i;
}

int root(int x) {
    while(id[x] != x) {
        id[x] = id[id[x]];
        x = id[x];
    }
    return x;
}

void union1(int x, int y) {
    int p = root(x);
    int q = root(y);
    id[p] = id[q];
}

ll kruskal(pair<ll, pair<int, int> > p[]) {
    int x, y;
    ll cost, minimumCost = 0;
    for(int i = 0; i < edges; ++i) {
        x = p[i].second.first;
        y = p[i].second.second;
        cost = p[i].first;
        if(root(x) != root(y)) {
            minimumCost += cost;
            union1(x, y);
        }
    }
    return minimumCost;
}

int main() {
    int x, y;
    ll weight, cost, minimumCost;
    initialize();
    cin >> nodes >> edges;
    for(int i = 0; i < edges; ++i) {
        cin >> x >> y >> weight;
        p[i] = make_pair(weight, make_pair(x, y));
    }
    // Sort the edges in the ascending order
    sort(p, p + edges);
    minimumCost = kruskal(p);
    cout << minimumCost << endl;
    return 0;
}
