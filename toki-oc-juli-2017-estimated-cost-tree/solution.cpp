#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector< pair<int, int> > g[N];
int par[N], cost[N], cnt[N][2];
int col[N];

void dfs(int v) {
  cnt[v][0] = cnt[v][1] = 0;
  cnt[v][col[v]]++;
  for (auto it : g[v]) {
    int u = it.first;
    if (u == par[v]) continue;
    par[u] = v;
    cost[u] = it.second;
    col[u] = 1 - col[v];
    dfs(u);
    cnt[v][0] += cnt[u][0];
    cnt[v][1] += cnt[u][1];
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }
  col[1] = 0;
  dfs(1);
  long long sum = 0;
  for (int i = 2; i <= n; i++) {
    sum += 2LL * cost[i] * (1LL * cnt[i][0] * (cnt[1][1] - cnt[i][1]) + 1LL * cnt[i][1] * (cnt[1][0] - cnt[i][0]));
  }
  printf("%lld\n", sum);
  return 0;
}