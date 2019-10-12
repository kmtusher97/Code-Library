/**
 * Persistant Segment Tree for point update
 * range query
 */
struct Node {
	int sum, lft, rgt;
	Node() : sum(0), lft(0), rgt(0) { }
};

struct PersistantSegmentTree {
	int avail;
	vector<int> roots;
	vector<Node> tree;

	PersistantSegmentTree( int n ) {
		avail = 0;
		roots.resize(n + 10, 0);
		tree.resize(n * 30, Node());
	}
	int update( int last, int l, int r, int p, int vlu ) {
		int cur = ++avail;
		tree[cur] = tree[last];

		if( l == r ) {
			tree[cur].sum += vlu;
			return cur;
		}

		int mid = l + (r - l) / 2;
		if( p <= mid ) tree[cur].lft = update( tree[last].lft, l, mid, p );
		else           tree[cur].rgt = update( tree[last].rgt, mid + 1, r, p );

		tree[cur].sum = tree[tree[cur].lft].sum + tree[tree[cur].rgt].sum;
		return cur;
	}
	int query( int cur, int l, int r, int L, int R ) {
		if( l > R or r < L or L > R ) return 0;
		if( l >= L and r <= R ) return tree[cur].sum;

		int mid = l + (r - l) / 2;
		int pp = query( tree[cur].lft, l, mid, L, R );
		int qq = query( tree[cur].rgt, mid + 1, r, L, R );
		return pp + qq;
	}
};
