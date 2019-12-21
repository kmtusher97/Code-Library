struct State {
    int len, link;
    map<char, int> next;
};

struct Suffix_Automata {
    State st[mxn];
    int sz, last;

    void init() {
        sz = last = 0;
        st[0].len = 0;
        st[0].link = -1;
        st[0].next.clear();
        memset(distinct, 0, sizeof distinct);
    }
    void add_State( char c ) {
        int now = ++sz, p;
        st[now].len = st[last].len + 1;
        st[now].next.clear();

        for(p = last; ~p && !st[p].next.count(c); p = st[p].link)
            st[p].next[c] = now;

        if( !(p + 1) )
            st[now].link = 0;
        else {
            int q = st[p].next[c];
            if( st[q].len == st[p].len + 1 )
                st[now].link = q;
            else {
                int clone = ++sz;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                for(; ~p && st[p].next[c] == q; p = st[p].link)
                    st[p].next[c] = clone;
                st[q].link = st[now].link = clone;
            }
        }
        last = now;
    }
};

/**Number of distinct substring*/
//inside structure

ll distinct[mxn];

ll dfs_distict( int u ) {
    ll& ret = distinct[u];
    if( ret )
        return ret;

    ret = 1;
    for(auto it = st[u].next.begin(); it != st[u].next.end(); it++)
        ret += dfs_distict( it -> S );

    return distinct[u] = ret;
}

