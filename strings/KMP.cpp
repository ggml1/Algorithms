const int M = 1e5 + 1;
const int ALPHABET = 27;

int aut[M][ALPHABET];

void automaton(string &p) {
	for (int i = 0; i < ALPHABET; ++i) {
		aut[0][i] = (i != p[0] - 'a');
	}
	int brd = 0;
	int m = p.size();
	for (int i = 1; i <= m; ++i) {
		for (int j = 0; j < ALPHABET; ++j) {
			aut[i][j] = aut[brd][j];
		}
		if (i < m) {
			aut[i][p[i] - 'a'] = i + 1;
			brd = a[brd][p[i] - 'a'];
		}
	}
}

vector<int> build(string &p){
	int n = p.size();
	vector<int> pi(n, 0);
	for (int i = 1; i < n; ++i) {
		int k = pi[i - 1];
		while (k && p[i] != p[k]) k = pi[k - 1];
		if (p[i] == p[k]) ++k;
		pi[i] = k;
	}
	return pi;
}

int calc(string &t, string &p) {
	vector<int> pi = build(p);
	int n = s.size(), m = p.size();
	int k = 0;
	for (int i = 0; i < n; ++i) {
		while (k && s[i] != p[k]) k = pi[k - 1];
		if (s[i] == p[k]) ++k;
		if (k == m) return i - m + 1;
	}
	return -1;
}