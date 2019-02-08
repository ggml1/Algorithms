int discoveryT[MV];
int low[MV];
bool onStack[MV];
stack<int> st;
int tempo;
vector<vector<int>> components;

void init() {
  memset(low, -1, sizeof low);
  memset(discovery, -1, sizeof discovery);
  memset(onStack, false, sizeof onStack);
  st = stack<int>();
  tempo = 0;
}

void dfs(int u, int p = -1) {
  discovery[u] = low[u] = ++tempo;
  st.push(u); onStack[u] = true;
  for (int v : adj[u]) {
    if (discovery[v] == -1) {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
    } else if (onStack[v]) {
      low[u] = min(low[u], discovery[v]);
    }
  }
  vector<int> component;
  if (low[u] == discovery[u]) {
    while (st.top() != u) {
      int w = st.top(); st.pop();
      component.push_back(w);
      onStack[w] = 0;
    }
    w = st.top(); st.pop();
    onStack[w] = 0;
    components.push_back(component);
  }
}

void scc(int v) {
  init();
  for (int i = 0; i < v; ++i) {
    if (discovery[v] == -1) {
      dfs(i);
    }
  }
}