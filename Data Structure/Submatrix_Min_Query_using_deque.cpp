
/**
 * Alternative solution for submatrix min query
 * using deque instead of Sparse Table, precal
 */
const int mxn = 3e3 + 3;
int n, m, a, b, g0, x, y, z;
int h[mxn][mxn];

int tmp[mxn][mxn], mn[mxn][mxn];

void precal() {
	for(int i = 0; i < n; i++) {
		deque<int> DQ;
		for(int j = 0; j < m; j++) {
			for(; !DQ.empty() and j - DQ.front() + 1 > b; DQ.pop_front());
			for(; !DQ.empty() and h[i][j] <= h[i][DQ.back()]; DQ.pop_back());
			DQ.push_back(j);
			tmp[i][j] = h[i][DQ.front()];
		}
	}

	for(int j = 0; j < m; j++) {
		deque<int> DQ;
		for(int i = 0; i < n; i++) {
			for(; !DQ.empty() and i - DQ.front() + 1 > a; DQ.pop_front());
			for(; !DQ.empty() and tmp[i][j] <= tmp[DQ.back()][j]; DQ.pop_back());
			DQ.push_back(i);
			mn[i][j] = tmp[DQ.front()][j];
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> a >> b >> g0 >> x >> y >> z;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			h[i][j] = g0;
			g0 = ((ll)g0 * x + y) % z;
		}
	}
	precal();
	ll res = 0LL;
	for(int i = a - 1; i < n; i++) {
		for(int j = b - 1; j < m; j++) {
			res += mn[i][j];
		}
	}
	cout << res << "\n";
	return 0;
}

