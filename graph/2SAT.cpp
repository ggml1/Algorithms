const int N = 12345;

vector<int> ra[N], a[N], order, comp, seen;
int n;

int NOT(int x) {
  return x ^ 1;
}

void addI(int x, int y) {
  a[x].push_back(y);
  ra[y].push_back(x);
}

void add(int x, int y) {
  addI(NOT(x), y);
  addI(NOT(y), x);
}

void dfs(int v) {
  if (seen[v]) return;
  seen[v] = 1;
  for (int u : a[v]) dfs(u);
  order.push_back(v);
}

void rdfs(int v, int c) {
  if (comp[v] != -1) return;
  comp[v] = c;
  for (int u : ra[v]) rdfs(u, c);
}

bool sat() {
  comp = vector<int>(2 * n, -1);
  seen = vector<int>(2 * n, 0);
  order.clear();
  for (int i = 0; i < 2 * n; ++i) dfs(i);
  reverse(order.begin(), order.end());
  int t = 0;
  for (int i = 0; i < 2 * n; ++i) {
    if (comp[order[i]] == -1) {
      rdfs(order[i], ++t);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (comp[i] == comp[i + n]) return 0;
  }
  return 1;
}