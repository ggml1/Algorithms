const int N = 1e6 + 5;
const int SIG = 28;

char s[N];
bool got[N];

struct Node {
  Node *next[SIG], *fail;
  vector<int> found;
  bool done;
  Node() {
      fail = NULL;
      done = false;
      found.clear();
      memset(next, 0, sizeof next);
  }
};

int val(char ch) {
  return ch - 'a';
}

void add(Node *root, int idx) {
  Node *p = root;
  for (int i = 0; s[i]; ++i) {
    int ch = val(s[i]);
    if (p->next[ch] == NULL) p->next[ch] = new Node();
    p = p->next[ch];
  }
  p->found.push_back(idx);
}

void get_links(Node *root) {
  Node *p;
  queue<Node*> q;
  q.push(root);
  root->fail = NULL;
  while (!q.empty()) {
    Node *cur = q.front(); q.pop();
    for (int i = 0; i < SIG; ++i) {
      if (cur->next[i] == NULL) continue;
      q.push(cur->next[i]);
      p = cur->fail;
      while (p != NULL && p->next[i] == NULL) p = p->fail;
      if (p == NULL) cur->next[i]->fail = root;
      else cur->next[i]->fail = p->next[i];
    }
  }
}

void search(Node *root) {
  Node *p, *q;
  p = root;
  for (int i = 0; s[i]; ++i) {
    int ch = val(s[i]);
    while (p != root && p->next[ch] == NULL) p = p->fail;
    p = p->next[ch];
    p = (p == NULL) ? root : p;
    q = p;
    while (q != root && q->done == false) {
      for (int x : q->found) {
        got[x] = 1;
      }
      q->done = true;
      q = q->fail;
    }
  }
}

void clear(Node *root) {
  queue<Node*> q;
  q.push(root);
  while (!q.empty()) {
    Node *cur = q.front(); q.pop();
    for (int i = 0; i < SIG; ++i) {
      if (cur->next[i] != NULL) {
        q.push(cur->next[i]);
      }
    }
    cur->found.clear();
    delete cur;
  }
}