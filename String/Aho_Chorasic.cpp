const int mxn = 312345;

struct AhoChorasick {
    struct Node {
        int next[27];
        Node() {
            memset(next, -1, sizeof next);
        }
    };
    int sz, len, root;
    Node tree[mxn];
    int suffix[mxn], path[mxn];
    int ff[mxn], ed[mxn];

    void init() {
        root = sz = len = 0;
        tree[root] = Node();
        for(int i = 0; i < mxn; i++)
            suffix[i] = ff[i] = 0;
    }
    void Insert( char *s, int id ) {
        int cur = root;
        for(int i = 0; s[i]; i++) {
            int ltr = s[i] - 'a';
            if( tree[cur].next[ltr] == -1 ) {
                tree[cur].next[ltr] = ++sz;
                tree[sz] = Node();
            }
            cur = tree[cur].next[ltr];
        }
        ed[id] = cur;
    }
    void reverseLink() {
        queue<int> Q;
        for(int i = 0; i < 26; i++) {
            if( ~tree[root].next[i] )
                Q.push(tree[root].next[i]);
            else
                tree[root].next[i] = root;
        }

        while( !Q.empty() ) {
            int u = Q.front();
            Q.pop();
            for(int i = 0; i < 26; i++) {
                int v = tree[u].next[i];
                if( v == -1 ) {
                    tree[u].next[i] = tree[suffix[u]].next[i];
                    continue;
                }
                suffix[v] = tree[suffix[u]].next[i];
                Q.push(v), path[len++] = v;
            }
        }
    }
    void Search( char *s ) {
        int cur = root;
        for(int i = 0; s[i]; i++) {
            int ltr = s[i] - 'a';
            cur = tree[cur].next[ltr];
            ff[cur]++;
        }
        for(int i = len - 1; i >= 0; i--)
            ff[suffix[path[i]]] += ff[path[i]];
    }
};

int Q;
char T[1000005], P[505];
AhoChorasick aho;

int main() {
    int cases, caseno = 0;
    scanf("%d", &cases);
    while( cases-- ) {
        aho.init();
        scanf("%d %s", &Q, T);

        for(int i = 1; i <= Q; i++) {
            scanf("%s", P);
            aho.Insert( P, i );
        }

        aho.reverseLink();
        aho.Search( T );

        printf("Case %d:\n", ++caseno);
        for(int i = 1; i <= Q; i++) {
            printf("%d\n", aho.ff[aho.ed[i]]);
        }
    }
    return 0;
}
