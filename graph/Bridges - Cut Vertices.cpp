const int MV = 1e5 + 5;

int low[MV];
int discovery[MV];
bool visited[MV];
bool cutVertex[MV];
int time;

void init() {
  time = 0;
  for (int i = 0; i < MV; ++i) {
    cutVertex[i] = visited[i] = false;
    low[i] = discovery[i] = -1;
  }
}

void dfs(int u, int p = -1) {
  low[u] = discovery[u] = ++time;
  visited[u] = 1;
  int children = 0;
  for (int v : adj[u]) {
    ++children;
    if (!visited[v]) {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (p != -1 && low[v] >= discovery[u]) { // the lowest reachable from this vertex is at least u, therefore, it is a subtree without a back edge to any ancestor of u
        cutVertex[u] = true;
      }
      //// BRIDGE - if we cant go back to u or ny ancestor of it, then removing this edge will make vertex v be on a disconnected component
      // if (p != -1 && low[v] > discovery[u]) {
      //   bridges.push_back(make_pair(u, v));
      // }
    } else {
      low[u] = min(low[u], discovery[v]);
    }
  }
  if (p == -1 && children > 1) cutVertex[u] = 1;
}

void go(int v) {
  init();
  for (int i = 0; i < v; ++i) {
    if (!visited[i]) {
      dfs(i);
    }
  }
  for (int i = 0; i < v; ++i) {
    if (cutVertex[i]) {
      cout << i << " is an articulation point." << endl;
    }
  }
}