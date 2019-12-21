#define mxn 20050
#define inf 0x3f3f3f3f

struct Node {
    int len, link;
    int child[26];
    Node() { }
    void Reset() { memset(child, 0, sizeof child); }
};

struct Suffix_Automata {

    Node st[mxn];
    int sz, last, root;
    int match[mxn], LCS[mxn];

    void init() {
        sz = last = root = 0;
        st[root].len = 0;
        st[root].link = -1;
        st[root].Reset();
        memset(LCS, inf, sizeof LCS);
    }
    void add( int c ) {
        int cur = ++sz, p = last;
        st[cur].len = st[last].len + 1;
        st[cur].Reset();
        for(; ~p && !st[p].child[c]; p = st[p].link)
            st[p].child[c] = cur;

        if( !(p + 1) )
            st[cur].link = root;
        else {
            int q = st[p].child[c];
            if( st[q].len == st[p].len + 1 )
                st[cur].link = q;
            else {
                int clone = ++sz;
                st[clone].len = st[p].len + 1;
                st[clone].link = st[q].link;
                memcpy(st[clone].child, st[q].child, sizeof st[q].child);

                for(; ~p && st[p].child[c] == q; p = st[p].link)
                    st[p].child[c] = clone;

                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    void findMatch( char P[] ) {
        memset(match, 0, sizeof match);
        int p = root, L = 0;
        for(int i = 0; P[i]; i++) {
            int c = P[i] - 'a';
            while( p && !st[p].child[c] )
                p = st[p].link, L = st[p].len;

            if( st[p].child[c] )
                p = st[p].child[c], L++;

            match[p] = max(match[p], L);
        }
        for(int i = sz; i > 0; i--)
            match[i] = max(match[i], match[st[i].link]);
        for(int i = 0; i <= sz; i++)
            LCS[i] = min(LCS[i], match[i]);
    }
    int longestCommonSubstr() {
        int ret = 0;
        for(int i = 0; i <= sz; i++)
            ret = max(ret, LCS[i]);
        return ret;
    }
};

Suffix_Automata SA;
int n;
char s[mxn];

int main() {
    int cases;
    scanf("%d", &cases);
    while( cases-- ) {
        SA.init();
        scanf("%d %s", &n, s);
        for(int i = 0; s[i]; i++)
            SA.add( s[i] - 'a' );

        for(int i = 2; i <= n; i++) {
            scanf("%s", s);
            SA.findMatch( s );
        }
        int res = SA.longestCommonSubstr();
        printf("%d\n", res);
    }
    return 0;
}
