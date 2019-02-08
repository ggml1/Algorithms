#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const ll mod = 1e9 + 7;
const int N = 3e4 + 1;

int bl;

struct Query {
	int l, r, id;

	void read(int i) {
		id = i;
		scanf("%d %d", &l, &r);
	}

	bool operator < (const Query& b) const {
		if (l / bl != b.l / bl) return l < b.l;
		return l / bl % 2 ? r > b.r : r < b.r;
	}
};

int t[N];
Query qry[N];
unordered_map<int, int> ft;
int ff[N];
set<int> ans;
int res[N];

int main() {
	int n, q; scanf("%d %d", &n, &q);

	bl = sqrt(n);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &t[i]);
	}

	for (int i = 0; i < q; ++i) {
		qry[i].read(i);
	}

	int L = 0, R = 0;

	ft[t[L]]++;
    ff[ft[t[L]]]++;
    ans.insert(ft[t[L]]);

	sort(qry, qry + q);

	for (int i = 0; i < q; ++i) {
		int l = qry[i].l - 1;
		int r = qry[i].r - 1;

		while (L > l) {
            int &cnt = ft[t[L - 1]];
			cnt++;
            ff[cnt]++;
            if (ff[cnt] == cnt) ans.insert(cnt);
			--L;
		}

		while (L < l) {
            int &cnt = ft[t[L]];
            if (ff[cnt] == cnt) ans.erase(cnt);
            ff[cnt]--;
			cnt--;
			++L;
		}

		while (R > r) {
            int &cnt = ft[t[R]];
            if (ff[cnt] == cnt) ans.erase(cnt);
            ff[cnt]--;
			cnt--;
			--R;
		}

		while (R < r) {
            int &cnt = ft[t[R + 1]];
			cnt++;
            ff[cnt]++;
            if (ff[cnt] == cnt) ans.insert(cnt);
			++R;
		}

		if (ans.size()) res[qry[i].id] = *ans.rbegin();
        else res[qry[i].id] = 1;
	}

	for (int i = 0; i < q; ++i) {
		printf("%d\n", res[i]);
	}

	return 0;
}