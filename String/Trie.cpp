#define mxn 300005
struct Trie {
    int root, avail;
    int tree[mxn * 4][26], isWord[mxn * 4];

    void init() {
        root = avail = 0;
        isWord[root] = 0;
        for(int i = 0; i < 26; i++)
            tree[root][i] = -1;
    }
    void insertWord( string& s ) {
        int cur = root;
        for(int i = 0, ln = s.length(); i < ln; i++) {
            if( tree[cur][s[i] - 'a'] == -1 ) {
                tree[cur][s[i] - 'a'] = ++avail;
                isWord[avail] = 0;
                for(int j = 0; j < 26; j++)
                    tree[avail][j] = -1;
            }
            cur = tree[cur][s[i] - 'a'];
        }
        isWord[cur] = 1;
    }
};
