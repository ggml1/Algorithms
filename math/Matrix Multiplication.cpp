const ll MOD = 1e9 + 7;
const ll MOD2 = MOD * MOD;

template <typename T>
struct Matrix {
  int r, c;
  vector<vector<T>> m;

  Matrix () {}
  Matrix (int _r, int _c) : r(_r), c(_c) {
    m.resize(r);
    for (int i = 0; i < r; ++i) {
      m[i].resize(c);
    }
  }
  Matrix operator * (const Matrix& b) {
    // Ax,y*By,k = Cx,k
    Matrix a = *this;
    Matrix c(a.r, b.c);
    for (int i = 0; i < a.r; ++i) {
      for (int k = 0; k < b.r; ++k) {
        for (int j = 0; j < b.c; ++j) {
          T p = (a.m[i][k] * b.m[k][j]);
          c.m[i][j] += p;
          if (c.m[i][j] >= MOD2) c.m[i][j] -= MOD2;
        }
      }
    }
    for (int i = 0; i < a.r; ++i) {
      for (int j = 0; j < b.c; ++j) {
        c.m[i][j] %= MOD;
      }
    }
    return c;
  }
  void id() {
    assert(r == c);
    for (int i = 0; i < r; ++i) {
      for (int j = 0; j < r; ++j) {
        m[i][j] = (i == j);
      }
    }
  }
};

Matrix<ll> fexp(Matrix<ll> b, ll e) {
  Matrix<ll> r(b.r, b.r); r.id();
  while (e) {
    if (e & 1) r = r * b;
    b = b * b;
    e >>= 1;
  }
  return r;
}