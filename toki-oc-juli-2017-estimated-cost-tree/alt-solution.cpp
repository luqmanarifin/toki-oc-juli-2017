#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector<pair<int, int>> edge[N];
int cnt[N];
long long tot;
int n;

void dfs(int now, int bef) {
  cnt[now] = 1;
  for (auto it : edge[now]) {
    int near = it.first;
    int cost = it.second;
    if (near == bef) continue;
    dfs(near, now);
    cnt[now] += cnt[near];
    tot += 2LL * cnt[near] * (n - cnt[near]) * cost;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    edge[u].emplace_back(v, c);
    edge[v].emplace_back(u, c);
  }
  dfs(1, 0);
  printf("%.15f\n", (double) tot / (1LL * n * n));
  return 0;
}