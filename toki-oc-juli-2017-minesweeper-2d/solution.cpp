#include <bits/stdc++.h>

using namespace std;

const int N = 1005;

char s[N][N];
int n, m;

bool valid(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < m;
}

bool digit(char c) {
  return '0' <= c && c <= '9';
}


// i and j should be number
int get_bomb(int i, int j) {
  int bom = 0;
  for (int k = -1; k <= 1; k++) {
    for (int l = -1; l <= 1; l++) {
      int ti = i + k;
      int tj = j + l;
      if (valid(ti, tj) && s[ti][tj] == '*') {
        bom++;
      }
    }
  }
  return bom;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", s[i]);
  }
  // set of concern point
  set<pair<int, int>> con;
  
  // list for undecidables number
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (s[i][j] == '?') {
        for (int k = -1; k <= 1; k++) {
          for (int l = -1; l <= 1; l++) {
            if (k == 0 && l == 0) continue;
            int ti = i + k;
            int tj = j + l;
            if (!valid(ti, tj) || !digit(s[ti][tj])) continue;
            con.insert({ti, tj});
          }
        }
      }
    }
  }

  vector<pair<int, int>> ask;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      // check for decidable number
      if (!con.count({i, j}) && digit(s[i][j])) {
        int c = s[i][j] - '0';
        int bom = get_bomb(i, j);
        if (bom != c) {
          puts("INVALID");
          return 0;
        }
      }

      // list all '?' question tag
      if (s[i][j] == '?') {
        ask.emplace_back(i, j);
      }
    }
  }

  for (int mask = 0; mask < (1 << ask.size()); mask++) {
    for (int i = 0; i < ask.size(); i++) {
      int pi = ask[i].first;
      int pj = ask[i].second;
      if (mask & (1 << i)) {
        s[pi][pj] = '*';
      } else {
        s[pi][pj] = '0';
      }
    }
    bool all_correct = 1;
    for (auto it : con) {
      int pi = it.first;
      int pj = it.second;
      if (s[pi][pj] - '0' != get_bomb(pi, pj)) {
        all_correct = 0;
      }
    }
    if (all_correct) {
      puts("VALID");
      return 0;
    }
  }
  puts("INVALID");
  return 0;
}