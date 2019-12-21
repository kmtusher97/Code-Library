struct matrix {
    intl mm[4][4] = {
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { 9, 0, 9, 1 },
        { 0, 0, 0, 1 }
    };

    void init() {
        memset(mm, 0, sizeof mm);
    }

    matrix operator * ( matrix o ) const {
        matrix t;
        t.init();
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                for(int k=0; k<4; k++)
                    t.mm[i][j] = (t.mm[i][j] + (mm[i][k]*o.mm[k][j])%MOD) % MOD;

        return t;
    }
};

void expo() {
    matrix B, I;
    I.init();
    B.mm[2][0] = b, B.mm[2][2] = a;
    for(int i=0; i<4; i++)
        I.mm[i][i] = 1;

    for(int p=n; p>0; p>>=1) {
        if( p&1 )
            I = I * B;
        B = B * B;
    }

    intl res = (I.mm[0][3]*c)%MOD;
    printf("%lld\n", res);
}

