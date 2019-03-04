// LEGENDRE'S THEOREM
// -------------------
// Given a number N (1 <= N <= 1e18),
// it states that v_p(N!) = sum (k : 1 -> oo) [ceil(N / (p ^ k))],
// where v_x(N!) is the exact exponent of the prime x in the prime
// factorization of N!

// TRAILING ZEROES OF N! IN BASE B
// If N! has K trailing zeroes, then it is divisible by B^K.
// Therefore, the problem reduces to finding the greatest K
// such that N! % B^K == 0.
// Let p1, p2, .., px be the prime divisors of B.
// We have N! = p1^a1 * p2^a2 * p3^a3 ... * px^ax (found by Legendre's Theorem)
//         B  = p1^b1 * p2^b2 * p3^b3 ... * px^bx (normal factorization)
// Therefore, our answer is min(a1 / b1) for every prime divisor of B.
// -----------------------------------------------------------------------------

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
  ll n, b; cin >> n >> b;
  vector<ll> p, e;
  ll f = 2;
  while (f * f <= b) {
    ll q = 0;
    while (b % f == 0) {
      ++q;
      b /= f;
    }
    if (q) p.push_back(f), e.push_back(q);
    f += (f == 2 ? 1 : 2);
  }
  if (b > 1) p.push_back(b), e.push_back(1);
  ll ans = 1e18;
  for (int i = 0; i < p.size(); ++i) {
    ll fnd = 0, cur = 1;
    while (cur <= n / p[i]) {
      cur *= p[i];
      fnd += n / cur;
    }
    ans = min(ans, fnd / e[i]);
  }
  cout << ans << endl;
  return 0;
}