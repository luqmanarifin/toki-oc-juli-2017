#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
  int LIMIT = 16;

  int N, M;
  vector<string> S;
  string ans;

  void InputFormat() {
    LINE(N, M);
    LINES(S) % SIZE(N);
  }

  void OutputFormat() {
    LINE(ans);
  }

  void GradingConfig(){
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(1 <= N && N <= 1000);
    CONS(1 <= M && M <= 1000);
    CONS(correctBoard());
    CONS(correctSize());
  }

  void Subtask1(){
    Points(100);
  }

private:

  bool digit(char c) {
    return '0' <= c && c <= '9';
  }

  bool correctSize() {
    if (S.size() != N) return 0;
    for (int i = 0; i < N; i++) {
      if (S[i].size() != M) return 0;
    }
    return 1;
  }

  // validasi character yang boleh *, 0-9, ?. Karakter ? maksimum 16
  bool correctBoard() {
    int ask = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (S[i][j] != '*' && !digit(S[i][j]) && S[i][j] != '?') {
          return false;
        }
        if (S[i][j] == '?') {
          ask++;
        }
      }
    }
    return ask <= LIMIT;
  }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({1});
    Input({"3 3", "2**", "*4?", "12*"});
    Output({"VALID"});
  }

  void SampleTestCase2() {
    Subtasks({1});
    Input({"3 3", "2**", "*5?", "12*"});
    Output({"INVALID"});
  }
  void SampleTestCase3() {
    Subtasks({1});
    Input({"4 5", "01121", "01*2*", "12232", "1*11*"});
    Output({"VALID"});
  }

  void TestGroup1() {
    Subtasks({1});
    // hand-maded case

    // logic-based
    CASE(N = 3, M = 4, S = {"*111", "2??*", "?1?*"});
    CASE(N = 4, M = 3, S = {"?2*", "1?1", "??1", "**1"});
    CASE(N = 3, M = 4, S = {"*?1?", "*??2", "111*"});
    CASE(N = 4, M = 3, S = {"1**", "1??", "1?1", "*2?"});
    CASE(N = 3, M = 4, S = {"*211", "2??*", "?1?*"});
    // there is no exact logic to start
    CASE(N = 3, M = 4, S = {"*??1", "2??*", "?1?*"});
    CASE(N = 3, M = 4, S = {"*??1", "2??*", "?1?2"});
    CASE(N = 4, M = 3, S = {"?2*", "1??", "???", "2*1"});
    CASE(N = 3, M = 4, S = {"2?1?", "*??2", "1??*"});
    CASE(N = 4, M = 3, S = {"1*2", "???", "??1", "*2?"});

    // corner case
    CASE(N = 1, M = 1, generate_small(0, 100, 0));
    CASE(N = 1, M = 1, generate_small(100, 0, 0));
    CASE(N = 1, M = 1, generate_small(0, 0, 0));
    CASE(N = 1, M = 2, S = {"?2"});
    CASE(N = 1, M = 2, S = {"*?"});

    // no ask
    CASE(N = 4, M = 4, generate_small(0, 0, 0));
    CASE(N = 4, M = 4, generate_small(25, 0, 0));
    CASE(N = 4, M = 4, generate_small(25, 0, 1));
    CASE(N = 4, M = 4, generate_small(50, 0, 0));
    CASE(N = 4, M = 4, generate_small(50, 0, 2));
    CASE(N = 4, M = 4, generate_small(50, 0, 4));
    CASE(N = 4, M = 4, generate_small(75, 0, 0));
    CASE(N = 4, M = 4, generate_small(75, 0, 1));
    CASE(N = 4, M = 4, generate_small(100, 0, 0));

    // all ask
    CASE(N = 4, M = 4, generate_small(100, 100, 0));

    // small map with rapid ask
    for (int bombPercentage = 25; bombPercentage <= 50; bombPercentage += 10) {
      for (int askPercentage = 25; askPercentage <= 75; askPercentage += 25) {
        CASE(N = nextInt(2, 3), M = nextInt(2, 3), generate_small(bombPercentage, askPercentage, 0));
        CASE(N = nextInt(2, 3), M = nextInt(2, 3), generate_small(bombPercentage, askPercentage, 1));
      }
    }

    // standard 16-sized map with normal distribution '?'
    for (int bombPercentage = 25; bombPercentage <= 75; bombPercentage += 25) {
      for (int askPercentage = 20; askPercentage <= 40; askPercentage += 20) {
        CASE(N = 4, M = 4, generate_small(bombPercentage, askPercentage, 0));
        CASE(N = 4, M = 4, generate_small(bombPercentage, askPercentage, 1));
      }
    }

    // huge map with sparse ask
    CASE(N = 100, M = 200, generate_big_sparse(10, 16, 0));
    CASE(N = 200, M = 200, generate_big_sparse(25, 16, 4));
    CASE(N = 950, M = 1000, generate_big_sparse(20, 15, 0));
    CASE(N = 1000, M = 1000, generate_big_sparse(3, 10, 1));
    CASE(N = 1000, M = 1000, generate_big_sparse(10, 16, 0));
    CASE(N = 1000, M = 1000, generate_big_sparse(10, 16, 10));

    // huge map with local ask
    for (int i = 0; i < 5; i++) {
      CASE(N = 1000, M = 1000, generate_big_local(nextInt(10, 40), nextInt(5, 10), 0));
      CASE(N = 1000, M = 1000, generate_big_local(nextInt(10, 40), nextInt(5, 10), 1));
    }
  }

private:
  mt19937 mersenne = mt19937(0xfafa);
  vector<vector<bool>> twist;

  void setup(int bombPercentage, int twisted) {
    S.clear();
    for (int i = 0; i < N; i++) {
      string buf = "";
      for (int j = 0; j < M; j++) {
        buf.push_back('.');
      }
      S.push_back(buf);
    }

    int notBomb = 0;

    // put the bombs
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        int num = nextInt(1, 100);
        if (num <= bombPercentage) {
          S[i][j] = '*';
        } else {
          S[i][j] = '-';
          notBomb++;
        }
      }
    }
    /*
    printf("need twist %d, N = %d, M = %d, bombPercentage = %d, notBomb %d\n",
      twisted, N, M, bombPercentage, notBomb);
    */
    assert(twisted <= notBomb);

    // fill with number
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (S[i][j] == '-') {
          S[i][j] = bomb_around(i, j) + '0';
        }
      }
    }

    twist.assign(N, vector<bool>(M, 0));

    // twist some number, make it wrong
    while (twisted--) {
      int at = nextInt(0, N * M - 1);
      while (S[at / M][at % M] == '*') {
        at = nextInt(0, N * M - 1);
      }
      twist[at / M][at % M] = 1;
      S[at / M][at % M] = nextInt(0, 9) + '0';
    }
  }

  bool valid(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
  }

  // get the number of bombs around this place
  int bomb_around(int i, int j) {
    int ret = 0;
    for (int k = -1; k <= 1; k++) {
      for (int l = -1; l <= 1; l++) {
        if (k == 0 && l == 0) continue;
        if (valid(i + k, j + l) && S[i][j] == '*') {
          ret++;
        }
      }
    }
    return ret;
  }

  // when generate small map, we use bomb percentage
  void generate_small(int bombPercentage, int askPercentage, int twisted) {
    // setup string of NxM char
    setup(bombPercentage, twisted);

    // fill with ask
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if  (twist[i][j]) continue;
        int num = nextInt(1, 100);
        if (num <= askPercentage) {
          S[i][j] = '?';
        }
      }
    }
  }

  // when generate big map, sparse bomb 
  void generate_big_sparse(int bombPercentage, int askNumber, int twisted) {
    // setup string of NxM char
    setup(bombPercentage, twisted);

    // put the ask chars
    while (askNumber--) {
      int num = nextInt(0, N * M - 1);
      S[num / M][num % M] = '?';
    }
  }

  // generate big map, with ? are concentrated on some local position
  void generate_big_local(int bombPercentage, int askNumber, int twisted) {
    // setup string of NxM char
    setup(bombPercentage, twisted);
    assert(N >= 4 && M >= 4);
    int sti = nextInt(0, N - 4);
    int stj = nextInt(0, M - 4);

    // put the ask chars
    while (askNumber--) {
      int i = nextInt(0, 3);
      int j = nextInt(0, 3);
      S[sti + i][stj + j] = '?';
    }
  }

  int nextInt(int L = 0, int R = 1e5) {
    return L + mersenne() % (R - L + 1);
  }
};
