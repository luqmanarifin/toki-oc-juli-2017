#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int mod = 1e9 + 8;

const int BIL[] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 103};

char exact[N];
int mask[N];
int n;

int ada[N];
bool kos[N], zero[N];

long long pre[N], suf[N];

int main() {
  scanf("%d %s", &n, exact);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 7; j++) {
      int v;
      scanf("%d", &v);
      if (v) {
        mask[i] |= (1 << j);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (exact[i] == '1') {
      if (mask[i] == 0) {
        kos[i] = 1;
      } else {
        int cnt = 0;
        for (int j = 0; j < 10; j++) {
          if (mask[i] == BIL[j]) {
            //printf("digit %d possible %d\n", i, j);
            cnt++;
            ada[i]++;
            if (j == 0) {
              zero[i] = 1;
            }
          }
        }
        //printf("digit %d\n", i);
        //assert(cnt == 1);
      }
    } else {
      if (mask[i] == 0) {
        kos[i] = 1;
      }
      for (int j = 0; j < 10; j++) {
        if ((mask[i] & BIL[j]) == mask[i]) {
          ada[i]++;
          if (j == 0) {
            zero[i] = 1;
          }
        }
      }
    }
  }
  pre[0] = kos[0];
  for (int i = 1; i < n; i++) {
    pre[i] = pre[i - 1] * kos[i];
  }
  suf[n - 1] = ada[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    suf[i] = suf[i + 1] * ada[i] % mod;
  }
  long long ans = 0;
  for (int i = 0; i < n - 1; i++) {
    long long cur = 1;
    if (i > 0) {
      cur = cur * pre[i - 1] % mod;
    }
    if (i + 1 < n) {
      cur = cur * suf[i + 1] % mod;
    }
    cur = cur * (ada[i] - zero[i]) % mod;
    ans = (ans + cur) % mod;
  }
  long long cur = 1;
  if (n - 1 > 0) {
    cur = cur * pre[n - 2] % mod;
  }
  cur = cur * ada[n - 1] % mod;
  ans = (ans + cur) % mod;


  cout << ans << endl;
  return 0;
}