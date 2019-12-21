const int mxn = 2e5 + 5;
int n, Q, seg, a[mxn], frq[mxn * 5];
 
struct Query {
    int l, r, id;
    bool operator < (Query q) const {
        int a = l / seg, b = q.l / seg;
        return a == b ? r < q.r : a < b;
    }
} qq[mxn];
 
ll ans = 0, res[mxn];
void addition( int i ) {
    ll f = frq[a[i]];
    ans -= (f * f * a[i]);
    frq[a[i]]++, f = frq[a[i]];
    ans += (f * f * a[i]);
}
void subtract( int i ) {
    ll f = frq[a[i]];
    ans -= (f * f * a[i]);
    frq[a[i]]--, f = frq[a[i]];
    ans += (f * f * a[i]);
}
void MO() {
    seg = sqrt(n) + 1;
    sort(qq, qq + Q);
    ans = 0;
    int l = 0, r = -1;
    for(int i = 0; i < Q; i++) {
        for(; l > qq[i].l; addition( --l ));
        for(; r < qq[i].r; addition( ++r ));
        for(; l < qq[i].l; subtract( l++ ));
        for(; r > qq[i].r; subtract( r-- ));
        res[qq[i].id] = ans;
    }
}
