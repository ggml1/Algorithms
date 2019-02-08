vector<int> build(string &p){
	vector<int> b(p.size() + 5);
	int sz = p.size();
	int i = 0, j = -1;
	b[i] = j;
	while (i < sz) {
		while (j >= 0 && p[j] != p[i]) j = b[j];
		j++, i++;
		b[i] = j;
	}
	return b;
}

int calc(string &t, string &p) {
	vector<int> b = build(p);
	int sz = t.size(), m = p.size();
	int i = 0, j = 0;
	while (i < sz) {
		while (j >= 0 && t[i] != p[j]) j = b[j];
		i++, j++;
		if (j == m) return i - j;
	}
	return -1;
}