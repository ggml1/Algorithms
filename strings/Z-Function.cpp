vector<int> zf(string pattern) {
  int n = s.length();
  vector<int> z(n, 0);
  int l, r = l = 0;
  for (int i = 1; i < n; ++i) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

// query
// string s = pattern + "@" + text;
// z = zf(s);
// for i in range(0, s.size())
if (z[i + len(pattern) + 1] == len(pattern)) {
  cout << "Found at " << i << endl;
}