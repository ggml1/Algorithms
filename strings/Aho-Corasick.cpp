const int N = 2e3 + 5, SIG = 70;
const int M = 1e5 + 5;
// edit
char s[N], txt[M];
int link[N];
vector<int> term[N];
bool fnd[N];
int t[N][SIG];
int sz = 1;

int val(char x) {
  if (x >= 'a' && x <= 'z') return x - 'a';
  if (x >= 'A' && x <= 'Z') return 27 + x - 'A';
  return 54 + x - '0';
}

void add(int w) {
	int nd = 0;
	for (int i = 0; s[i]; ++i) {
		int pos = val(s[i]);
		if (t[nd][pos] == -1) {
			t[nd][pos] = sz++;
		}
		nd = t[nd][pos];
	}
	term[nd].push_back(w);
}

void push_links() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int node = q.front(); q.pop();
		for (int c = 0; c < SIG; ++c) {
			int f = (node == 0 ? 0 : t[link[node]][c]);
			if (t[node][c] == -1) {
				t[node][c] = f;
			} else {
				link[t[node][c]] = f;
				q.push(t[node][c]);
			}
		}
	}
}

void search() {
	int nd = 0;
	for (int i = 0; txt[i]; ++i) {
		int pos = val(txt[i]);
		int where = t[nd][pos];
		for (int x : term[where]) {
			fnd[x] = 1;
		}
		nd = t[nd][pos];
	}
}

int main() {
  // SPOJ SUB_PROB
	memset(t, -1, sizeof t);
  scanf(" %s", txt);
  int n; scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf(" %s", s);
		add(i);
	}
	push_links();
	search();
	for (int i = 0; i < n; ++i) {
		if (fnd[i]) puts("Y");
		else puts("N");
	}
  return 0;
}
