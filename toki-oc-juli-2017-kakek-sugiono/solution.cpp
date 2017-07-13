#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll mod = 1e9 + 7;

ll pangkat(ll n) {
  if (n == 0) return 1;
  else if (n % 2) return (pangkat(n-1) * 2) % mod;
  else {
    ll tmp = pangkat(n / 2);
    return (tmp*tmp) % mod;
  }
}

int main() {
  ll n;
  cin >> n;
  cout << pangkat(n-1) << endl;
}
