
#include <bits/stdc++.h>

using namespace std;

const int N = 1010;

int n, m;
char s[N][N];
int b[N][N];

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", s[i]);
  }
  memset(b, 0, sizeof b);
  vector< pair<int, int > > unknown;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (s[i][j] == '?') {
        unknown.emplace_back(i, j);
      }
      else if (s[i][j] == '*') {
        // remove bomb
        for (int dx = -1; dx <= 1; dx++) {
          for (int dy = -1; dy <= 1; dy++) {
            int x = i + dx, y = j + dy;
            if (x < 0 || x >= n || y < 0 || y >= m) continue;
            if (s[x][y] < '0' || s[x][y] > '9') continue;
            b[x][y]--;
          }
        }
      }
      else {
        // add initial bomb count
        b[i][j] += s[i][j] - '0';
      }
    }
  }
  // count non zero bomb count
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if ('0' <= s[i][j] && s[i][j] <= '9') {
        cnt += b[i][j] != 0;
      }
    }
  }
  int tot_mask = 1 << unknown.size();
  for (int mask = 0; mask < tot_mask; mask++) {
    // remove bomb from '?'
    for (int i = 0; i < unknown.size(); i++) if (mask & (1 << i)) {
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          int x = unknown[i].first + dx, y = unknown[i].second + dy;
          if (x < 0 || x >= n || y < 0 || y >= m) continue;
          if (s[x][y] < '0' || s[x][y] > '9') continue;
          b[x][y]--;
          if (b[x][y] == 0)
            cnt--;
          else if (b[x][y] == -1)
            cnt++;
        }
      }
    }
    if (cnt == 0) {
      puts("VALID");
      return 0;
    }
    // revert bomb
    for (int i = 0; i < unknown.size(); i++) if (mask & (1 << i)) {
      for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          int x = unknown[i].first + dx, y = unknown[i].second + dy;
          if (x < 0 || x >= n || y < 0 || y >= m) continue;
          if (s[x][y] < '0' || s[x][y] > '9') continue;
          b[x][y]++;
          if (b[x][y] == 0)
            cnt--;
          else if (b[x][y] == 1)
            cnt++;
        }
      }
    }
  }
  puts("INVALID");
  return 0;
}