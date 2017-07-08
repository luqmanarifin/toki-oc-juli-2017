#include <bits/stdc++.h>

using namespace std;

const int M = 1e7 + 7;

int n;
int prime_fact[M];
vector< vector< int > > num;


void precompute() {
  for (int i = 2; i < M; i++) if (prime_fact[i] == 0) {
    for (long long j = i; j < M; j += i) if (prime_fact[j] == 0)
      prime_fact[j] = i;
  }
}

void read() {
  scanf("%d", &n);
  num.resize(n);
  for (int i = 0; i < n; i++) {
    int k;
    scanf("%d", &k);
    num[i].resize(k);
    for (int j = 0; j < k; j++) {
      scanf("%d", &num[i][j]);
    }
  }
}

map<int, int> kpk(vector<int> & v) {
  map<int, int> res;
  for (int x : v) {
    while (x > 1) {
      int p = prime_fact[x], power = 0;
      while ((x % p) == 0) {
        power++;
        x /= p;
      }
      res[p] = max(res[p], power);
    }
  }
  return res;
}

void solve() {
  map<int, int> ans;
  for (int i = 0; i < n; i++) {
    map<int, int> res = kpk(num[i]);
    if (i == 0)
      ans = res;
    else {
      for (map<int, int>::iterator it = ans.begin(); it != ans.end(); ) {
        it->second = min(it->second, res[it->first]);
        if (it->second)
          it++;
        else {
          map<int, int>::iterator del = it;
          it++;
          ans.erase(del);
        }
      }
    }
  }
  printf("%d\n", ans.size());
  for (auto it : ans) {
    printf("%d %d\n", it.first, it.second);
  }
}

int main() {
  precompute();
  read();
  solve();
  return 0;
}