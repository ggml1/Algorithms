struct range_t {
  int l, r;
  int v;

  range_t(int l = 0, int r = 0, int v = {}) : l(l), r(r), v(v) {}
  
  inline bool operator < (const range_t &other) const {
    return l < other.l;
  }
};

set<range_t> ranges;

vector<range_t> modify(int l, int r, int v) {
  vector<range_t> ret;
  if (l > r)
    return ret;
  auto it = ranges.lower_bound(l);
  if (it != ranges.begin()) {
    it--;
    if (it->r >= l) {
      auto er = *it;
      ranges.erase(it);
      ranges.emplace(er.l, l - 1, er.v);
      ranges.emplace(l, er.r, er.v);
    }
  }
  it = ranges.upper_bound(r);
  if (it != ranges.begin()) {
    it--;
    if (it->r > r) {
      auto er = *it;
      ranges.erase(it);
      ranges.emplace(er.l, r, er.v);
      ranges.emplace(r + 1, er.r, er.v);
    }
  }
  for (it = ranges.lower_bound(l); it != ranges.end() && it->l <= r; it++)
    ret.push_back(*it);
  ranges.erase(ranges.lower_bound(l), ranges.upper_bound(r));
  ranges.emplace(l, r, v);
  return ret;
}