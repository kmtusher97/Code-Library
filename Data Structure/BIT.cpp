/**
 * Fenwick Tree 
 */
struct BIT {
	int n;
	vector<ll> tt;
	BIT() {}
	BIT(int n) : n(n) {
		tt.resize(n + 10, 0);
	}
	void update( int id, ll vlu ) {
		if( id == 0 ) return;
		for(; id <= n; tt[id] += vlu, id += (id & -id));
	}
	ll query( int id ) {
		if( id < 1 ) return 0;
		ll ret = 0;
		for(; id > 0; ret += tt[id], id -= (id & -id));
		return ret;
	}
};

