typedef vector<int> vi;

const int MX = 12;
int n, m, indegree[MX];
bool mark[MX];
vi g[MX];

vi tropologiacl_sort() {
    priority_queue< int, vector<int>, greater<int> > pq;
    for(int i=1; i<=n; i++) {
        if( indegree[i]==0 ) {
            pq.push(i), mark[i] = true;
        }
    }
    vi T;
    while( !pq.empty() ) {
        int u = pq.top();
        pq.pop();
        T.push_back(u);
        for(int i=0, sz=g[u].size(); i<sz; i++) {
            int v = g[u][i];
            if( !mark[v] ) {
                indegree[v]--;
                if( indegree[v]==0 ) {
                    pq.push(v), mark[v] = true;
                }
            }
        }
    }

    return T;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    cin>>n>>m;
    for(int i=0, a, b; i<m; i++) {
        cin>>a>>b;
        g[a].push_back( b );
        indegree[b]++;
    }

    vi T = tropologiacl_sort();
    for(int i=0, sz=T.size(); i<sz; i++) {
        cout<<T[i]<<" ";
    }
    cout<<endl;

    return 0;
}
