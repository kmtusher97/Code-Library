typedef long long ll;
#define mxn 90005

struct State {..};
struct SuffixAutomata {
    int sz, last;
    State st[mxn * 2];

    ll ff[mxn * 2];
    ll K;
    string kthsubstr;

    void init() {..}
    void Insert( int c ) {..}
    ll dfs( int u ) {..}
    /* Lexicographically k th sub string */
    void dfs_kth( int u ) {
        for(int i = 0; i < 26; i++) {
            if( !K || !st[u].next[i] )
                continue;
            ll have = ff[st[u].next[i]];
            if( have < K )
                K -= have;
            else {
                kthsubstr += (char)(i + 'a');
                K--;
                dfs_kth( st[u].next[i] );
                break;
            }
        }
    }
    void lexicographicallykthSubstr( int k ) {
        K = k;
        kthsubstr = "";
        dfs_kth( 0 );
        for(int i = 0; kthsubstr[i]; i++)
            printf("%c", kthsubstr[i]);
        printf("\n");
    }
};

char T[mxn];
SuffixAutomata SA;

int main() {
    int Q, k;
    scanf("%s", T);
    SA.init();
    for(int i = 0; T[i]; i++)
        SA.Insert( T[i] - 'a' );

    SA.dfs( 0 );
    scanf("%d", &Q);
    while( Q-- ) {
        scanf("%d", &k);
        SA.lexicographicallykthSubstr( k );
    }
}
