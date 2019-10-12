/**
 * Suffix Array O(n log n)
 * LCP
 */
struct SuffixArray {
	char* T;
	int n;
	vector<int> RA, tempRA;
	vector<int> SA, tempSA;

	vector<int> phi, pLCP, LCP;

	SuffixArray( string& t ) {
		n = t.length();
		T = new char[n + n];
		for(int i = 0; i < n; T[i] = t[i], i++);
		T[n++] = '#', T[n] = '\0';
		RA.resize(n), tempRA.resize(n);
		SA.resize(n), tempSA.resize(n);
	}
	void countingSort( int k ) {
		vector<int> c(max(300, n), 0);
		for(int i = 0; i < n; i++) c[i + k < n ? RA[i + k] : 0]++;
		for(int i = 0, sum = 0, lim = max(300, n); i < lim; i++) {
			int t = c[i]; c[i] = sum, sum += t;
		}
		for(int i = 0; i < n; i++) tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
		for(int i = 0; i < n; i++) SA[i] = tempSA[i];
	}
	void buildSA() {
		for(int i = 0; i < n; SA[i] = i, i++);
		for(int i = 0; i < n; RA[i] = T[i], i++);
		for(int k = 1, r; k < n; k <<= 1) {
			countingSort( k );
			countingSort( 0 );
			tempRA[SA[0]] = r = 0;
			for(int i = 1; i < n; i++) {
				tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] and RA[SA[i] + k] == RA[SA[i - 1] + k] ? r : ++r);
			}
			for(int i = 0; i < n; RA[i] = tempRA[i], i++);
			if( RA[SA[n - 1]] == n - 1 ) break;
		}
	}
	void computeLCP() {
		phi.resize(n), pLCP.resize(n), LCP.resize(n);
		phi[SA[0]] = -1;
		for(int i = 1; i < n; phi[SA[i]] = SA[i - 1], i++);
		for(int i = 0, L = 0; i < n; i++) {
			if( phi[i] == -1 ) {
				pLCP[i] = 0;
				continue;
			}
			for(; T[i + L] == T[phi[i] + L]; L++);
			pLCP[i] = L;
			L = max(0, L - 1);
		}
		for(int i = 0; i < n; LCP[i] = pLCP[SA[i]], i++);
	}
	void print() {
		for(int i = 0; i + 1 < n; i++) {
			printf("%2d\t%2d\t%s\n", SA[i], LCP[i], T + SA[i]);
		}
	}
};
