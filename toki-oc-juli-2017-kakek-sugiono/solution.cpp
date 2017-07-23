#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll mod = 1e9 + 7;
ll maxn = 1000;
ll comb[maxn+10][maxn+10];

void computeCombination() {
  memset(comb, 0, sizeof comb);
  comb[0][0] = 1;

  for(int i = 1; i <= maxn; i++) {
    for(int j = 0; j <= i; j++) {
      comb[i][j] = comb[i-1][j];
      if (j > 0) comb[i][j] += comb[i-1][j-1];
      comb[i][j] %= mod;
    }
  }
}

int main() {
  computeCombination();

  ll n;
  cin >> n;

  ll ans = 0;
  for(int i = 0; i <= n; i+= 2) {
    ans += (comb[n][i] * comb[i][i/2]) % mod;
    ans %= mod;
  }

  cout << ans << endl;
}
