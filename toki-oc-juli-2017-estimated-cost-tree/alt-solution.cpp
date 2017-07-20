#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

vector<pair<int, int>> edge[N];
int cnt[N][2], tot[2];
long long ans;
int n;

void pre(int now, int bef, int st) {
  cnt[now][st]++;
  for (auto it : edge[now]) {
    int near = it.first;
    int cost = it.second;
    if (near == bef) continue;
    pre(near, now, st ^ (cost % 2));
    cnt[now][0] += cnt[near][0];
    cnt[now][1] += cnt[near][1];
  }
}

void dfs(int now, int bef) {
  for (auto it : edge[now]) {
    int near = it.first;
    int cost = it.second;
    if (near == bef) continue;
    dfs(near, now);
    ans += 1LL * cost * cnt[near][0] * (tot[1] - cnt[near][1]);
    ans += 1LL * cost * cnt[near][1] * (tot[0] - cnt[near][0]); 
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
  pre(1, 0, 0);
  tot[0] = cnt[1][0];
  tot[1] = cnt[1][1];
  dfs(1, 0);
  printf("%lld\n", ans);
  return 0;
}