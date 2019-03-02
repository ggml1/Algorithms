#define all(x) x.begin(), x.end()

void build(int L = 0, int R = aptr - 1, int on = 0) {
  if (L == R) {
    tree[on].push_back(arr[L].first); // number 
    //tree[on].push_back(arr[L].second); kth smallest element
  } else {
    int mid = (L + R) >> 1;
    build(L, mid, on + on + 1);
    build(mid + 1, R, on + on + 2);
    merge(all(tree[on + on + 1]),
          all(tree[on + on + 2]),
          back_inserter(tree[on]));
  }
}

// how many elements are less than k
int queryS(int qs, int qe, ll v, int L = 0, int R = aptr - 1, int on = 0) {
  if (qs > R || qe < L || L > R) return 0;
  if (qs <= L && R <= qe) return lower_bound(all(tree[on]), v) - tree[on].begin() + 1;
  int mid = (L + R) >> 1;
  int q1 = queryS(qs, qe, v, L, mid, on + on + 1);
  int q2 = queryS(qs, qe, v, mid + 1, R, on + on + 2);
  return q1 + q2;
}

// kth smallest element
int queryS(int qs, int qe, int k, int L = 0, int R = n - 1, int on = 0) {
  if (L == R) return tree[on][0];
  int hi = upper_bound(all(tree[on + on + 1]), qe) - tree[on + on + 1].begin();
  int lo = lower_bound(all(tree[on + on + 1]), qs) - tree[on + on + 1].begin();
  int hm = hi - lo;
  int mid = (L + R) >> 1;
  if (hm >= k) {
    return queryS(qs, qe, k, L, mid, on + on + 1);
  }
  return queryS(qs, qe, k - hm, mid + 1, R, on + on + 2);
}