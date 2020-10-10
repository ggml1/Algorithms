struct PalindromicTree {
  static const int ALPHABET_SIZE = 26;
  static const int NEG_ROOT = 0;
  static const int EMPTY_ROOT = 1;

  struct Node {
    int next[ALPHABET_SIZE];
    int len, suffixLink, occ;

    Node(int _len = 0, int _suffixLink = 0, int _occ = 0) :
      len(_len), suffixLink(_suffixLink), occ(_occ) {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
          next[i] = -1;
        }
      }
  };

  vector<Node> tree;
  int nodeCount, suff;

  PalindromicTree(int len) {
    tree = vector<Node>(len + 2);
    nodeCount = 2;
    suff = 1;
    tree[NEG_ROOT] = Node(-1, 0, 0);
    tree[EMPTY_ROOT] = Node(0, 0, 0);
  }

  int getSuffixLink(int cur, int pos, string& s) {
    int letter = s[pos] - 'a';
    while (true) {
      int curLen = tree[cur].len;
      if (pos - 1 - curLen >= 0 && s[pos - 1 - curLen] == s[pos]) {
        return cur;
      }
      cur = tree[cur].suffixLink;
    }
    assert(false);
    return -1;
  }

  void addNode(int cur, int pos, string& s) {
    int letter = s[pos] - 'a';

    int myLen = tree[cur].len + 2;
    tree[cur].next[letter] = nodeCount;
    suff = nodeCount;

    if (cur == NEG_ROOT) {
      tree[nodeCount] = Node(myLen, EMPTY_ROOT, 1);
      nodeCount += 1;
      return;
    }

    cur = getSuffixLink(tree[cur].suffixLink, pos, s);

    int mySuff = tree[cur].next[letter];
    int myOcc = tree[mySuff].occ + 1;

    tree[nodeCount] = Node(myLen, mySuff, myOcc);

    nodeCount += 1;
  }

  bool addLetter(int pos, string& s) {
    int cur = suff, curLen = 0;
    int letter = s[pos] - 'a';

    cur = getSuffixLink(cur, pos, s);

    if (tree[cur].next[letter] != -1) {
      suff = tree[cur].next[letter];
      return false;
    }

    addNode(cur, pos, s);

    return true;
  }
};
