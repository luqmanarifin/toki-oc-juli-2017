#include <tcframe/spec.hpp>
#include <bits/stdc++.h>

using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector< int > K;
  vector<vector<int>> X;
  int M;
  vector<int> P, Q;

  void InputFormat() {
    LINE(N);
    LINES(K, X) % SIZE(N);
  }

  void OutputFormat() {
    LINE(M);
    LINES(P, Q) % SIZE(M);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(1 <= N && N <= int(1e5));
    CONS(eachElementBetween(X, 1, int(1e7)));
    CONS(eachElementBetween(K, 1, int(1e5)));
    CONS(countAllBetween(X, 1, int(1e5)));
  }
private:
  bool eachElementBetween(const vector<int>& v, int lo, int hi) {
    for (int x : v) {
      if (x < lo || x > hi) {
        return false;
      }
    }
    return true;
  }
  bool eachElementBetween(const vector<vector<int>>& vv, int lo, int hi) {
    for (const vector<int>& v : vv) {
      for (int x : v) {
        if (x < lo || x > hi) {
          return false;
        }
      } 
    }
    return true;
  }
  bool countAllBetween(const vector<vector<int>>& vv, int lo, int hi) {
    int cnt = 0;
    for (const vector<int>& v : vv) {
      cnt += v.size();
    }
    return lo <= cnt && cnt <= hi;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "2",
      "2 2 27",
      "2 4 9"
    });
    Output({
      "2",
      "2 1",
      "3 2"
    });
  }
  void BeforeTestCase() {
      K.clear();
      X.clear();
  }

  void TestCases() {
    CASE(N = 1, randomSize(1, int(1e5)), randomNumber(1, int(1e7)));
    CASE(N = 10, randomSize(1, int(1e5)), randomNumber(1, int(1e7)));
    CASE(N = 100, randomSize(1, int(1e5)), randomNumber(1, int(1e7)));
    CASE(N = 1000, randomSize(1, int(1e5)), randomNumber(1, int(1e7)));
    CASE(N = 10000, randomSize(1, int(1e5)), randomNumber(1, int(1e7)));
    CASE(N = 100000, randomSize(1, int(1e5)), randomNumber(1, int(1e7)));
  }

private:
  void randomSize(int lo, int tot) {
    K.resize(N);
    for (int i = 0; i < N; i++) {
      K[i] = lo;
    }
    tot -= lo * N;
    assert(tot >= 0);
    for (int i = 0; i < tot; i++) {
      int add = rnd.nextInt(0, N-1);
      K[add]++;
    }
  }

  void randomNumber(int lo, int hi) {
    X.resize(N);
    for (int i = 0; i < N; i++) {
      X[i].resize(K[i]);
      for (int j = 0; j < K[i]; j++)
        X[i][j] = rnd.nextInt(lo, hi);
    }
  }
};