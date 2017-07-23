#include <bits/stdc++.h>
using namespace std;

const int maxX = 1e7+10;

int primeDivisor[maxX + 10];

void computePrimeDivisor() {
  memset(primeDivisor, -1, sizeof primeDivisor);

  for(int i = 2; i * i < maxX; i++) {
    // if i is prime
    if (primeDivisor[i] == -1) {
      for(int j = i*i; j < maxX; j += i) {
        primeDivisor[j] = i;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  computePrimeDivisor();

  int n;
  cin >> n;

  unordered_map<int,int> fpb;

  for(int i = 0; i < n; i++) {
    unordered_map<int, int> kpk;

    int k;
    cin >> k;

    while(k--) {
      int x;
      cin >> x;

      while(x > 1) {
        if (primeDivisor[x] == -1) {
          kpk[x] = 1;
          x = 1;
        }
        else {
          int prime = primeDivisor[x], power = 0;

          while (x % prime == 0) {
            x /= prime;
            power++;
          }

          kpk[prime] = power;
        }
      }
    }

    if (i == 0 ) {
      fpb = kpk;
    }
    else {
      for (auto it = fpb.begin(); it != fpb.end(); it++) {
        it->second = min(it->second, kpk[it->first]);
      }
    }
  }

  vector<pair<int,int>> ans;

  for(auto it = fpb.begin(); it != fpb.end(); it++) {
    ans.push_back({it->first, it->second});
  }

  sort(ans.begin(), ans.end());

  cout << ans.size() << endl;

  for(auto jawab : ans) {
    cout << jawab.first << " " << jawab.second << endl;
  }
}
