const int mxn = 1000007;
int n, m, prfx[mxn];
char t[mxn], p[mxn];

void kmpProcess() {
    prfx[0] = -1;
    for(int i=0, j=-1; i<m; ) {
        while( j>=0 && p[i]!=p[j] )
            j = prfx[j];
        prfx[++i] = ++j;
    }
}

int kmpSearch() {
    int cnt = 0;
    for(int i=0, j=0; i<n; ) {
        while( j>=0 && t[i]!=p[j] )
            j = prfx[j];
        i++, j++;
        if( j==m )
            cnt++;
    }
    return cnt;
}
