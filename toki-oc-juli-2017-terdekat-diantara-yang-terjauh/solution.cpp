#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, k, col[N];
vector< int > g[N];
int ans[N];
int depth[N], sz[N], toBig[N];
bool live[N];

void getSize(int v, int par = -1) {
  sz[v] = 1;
  toBig[v] = -1;
  for (int u : g[v]) if (live[u] && u != par) {
    getSize(u, v);
    sz[v] += sz[u];
    if (toBig[v] == -1 || sz[toBig[v]] < sz[u])
      toBig[v] = u;
  }
}

void reset(int v, int par = -1) {
  depth[col[v]] = -1;
  for (int u : g[v]) if (live[u] && u != par)
    reset(u, v);
}

void update(int v, int par = -1, int level = 0) {
  depth[col[v]] = max(depth[col[v]], level);
  for (int u : g[v]) if (u != par && live[u])
    update(u, v, level + 1);
}

void get(int v, int par = -1, int level = 0) {
  int c = col[v];
  if (depth[c] != -1)
    ans[c] = max(ans[c], depth[c] + level);
  for (int u : g[v]) if (u != par && live[u])
    get(u, v, level + 1);
}

void centroidDecompose(int v) {
  getSize(v);
  int total = sz[v];
  while (toBig[v] != -1 && sz[toBig[v]] * 2 >= total) v = toBig[v];
  reset(v);
  depth[col[v]] = 0;
  for (int u : g[v]) if (live[u]) {
    get(u, v, 1);
    update(u, v, 1);
  }
  live[v] = 0;
  for (int u : g[v]) if (live[u]) {
    centroidDecompose(u);
  }
}

void solve() {
  memset(ans, 0, sizeof ans);
  memset(depth, -1, sizeof depth);
  memset(live, true, sizeof live);
  centroidDecompose(1);
  for (int i = 1; i <= k; i++)
    ans[i] = (ans[i] + 1)/2;
}

void read() {
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; i++)
    scanf("%d", col+i);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
}

void output() {
  for (int i = 1; i <= k; i++)
    printf("%d%c", ans[i], (i == k) ? '\n' : ' ');
}

int main() {
  read();
  solve();
  output();
  return 0;
}