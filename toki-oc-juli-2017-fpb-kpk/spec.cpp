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
    CONS(correctSize());
    CONS(countAllBetween(X, 1, int(1e5)));
    CONS(distinctElementForEachGroup(X));
  }

  void Subtask1(){
    Points(100);
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
  bool correctSize() {
    if (X.size() != N || K.size() != N)
      return false;
    for (int i = 0; i < N; i++) {
      if (X[i].size() != K[i])
        return false;
    }
    return true;
  }
  bool distinctElementForEachGroup(const vector<vector<int>> &v) {
    for (int i = 0; i < v.size(); i++) {
      set<int> st;
      for (int x : v[i]) {
        if (st.count(x))
          return false;
        st.insert(x);
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
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

  void SampleTestCase2() {
    Subtasks({1});
    Input({
      "3",
      "1 4",
      "2 2 5",
      "3 1 3 6"
    });
    Output({
      "1",
      "2 1"
    });
  }

  void BeforeTestCase() {
      K.clear();
      X.clear();
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(N = 1, K = {8}, X = {{1, 2, 4, 8, 16, 32, 64, 128}});
    CASE(N = 2, K = {1, 4}, X = {{2 * 3 * 5 * 7}, {2, 3, 5, 7}});
    CASE(N = 5, K = {4, 3, 2, 1, 5}, X = {{1, 4, 5, 11}, {3, 22, 26}, {99, 165}, {121}, {1, 20, 33, 70, 91}}); 
    CASE(N = 5, K = {5, 5, 5, 5, 5}, X = {{4, 5, 7, 11, 13}, {3, 5, 7, 11, 13}, {3, 4, 5, 11, 13}, {3, 4, 5, 7, 13}, {3, 4, 5, 7, 11}});

    CASE(N = 1, randomSize(100000, 100000), numberWithMostPrime(1e7));
    CASE(N = 10, randomSize(10000, 100000), numberWithMostPrime(1e7));
    CASE(N = 10, randomSize(1000, 100000), numberWithMostPrime(1e7));
    CASE(N = 100, randomSize(1000, 100000), numberWithMostPrime(1e7));
    CASE(N = 100, randomSize(100, 100000), numberWithMostPrime(1e7));

    CASE(N = 1, randomSize(100000, 100000), consecutiveNumber(1));
    CASE(N = 10, randomSize(10000, int(1e5)), consecutiveNumber(1e7 - 2e5 + rnd.nextInt(1, int(1e3))));
    CASE(N = 10, randomSize(1000, int(1e5)), consecutiveNumber(rnd.nextInt(1, int(5e6))));
    CASE(N = 100, randomSize(100, int(1e5)), consecutiveNumber(rnd.nextInt(1, int(5e6))));

    CASE(N = 1, randomSize(1, 1e5), randomNumber(int(1e7), {}));
    CASE(N = 2, randomSize(2, 1e2), randomNumber(int(1e3), {3, 4}));
    CASE(N = 2, randomSize(2, 1e4), randomNumber(int(1e4), {97, 101}));
    CASE(N = 10, randomSize(10, 1e3), randomNumber(int(1e5), {}));
    CASE(N = 10, randomSize(100, 1e5), randomNumber(int(1e7), {32}));
    CASE(N = 100, randomSize(100, 1e4), randomNumber(int(1e6), randomCoprimeList(10, 1e6)));
    CASE(N = 100, randomSize(100, 1e5), randomNumber(int(1e7), {}));
    CASE(N = 100, randomSize(100, 1e5), randomNumber(int(1e7), randomCoprimeList(10, 1e7)));
    CASE(N = 100, randomSize(1000, 1e5), randomNumber(int(1e7), randomCoprimeList(100, 1e7)));
    CASE(N = 1000, randomSize(1, 1e5), randomNumber(int(1e7), {}));
    CASE(N = 1000, randomSize(5, 1e5), randomNumber(int(1e7), randomCoprimeList(5, 1e7)));
    CASE(N = 1000, randomSize(25, 1e5), randomNumber(int(1e7), randomCoprimeList(13, 1e7)));
    CASE(N = 1000, randomSize(100, 1e5), randomNumber(int(1e7), randomCoprimeList(20, 1e7)));
    CASE(N = 10000, randomSize(2, 1e5), randomNumber(int(1e7), {41, 4099}));
    CASE(N = 20000, randomSize(1, 1e5), randomNumber(int(1e7), {}));
    CASE(N = 100000, randomSize(1, 1e5), randomNumber(int(1e7), {3}));
  }

private:
  void randomSize(int low, int tot) {
    K.resize(N);
    for (int i = 0; i < N; i++) {
      K[i] = low;
    }
    tot -= low * N;
    assert(tot >= 0);
    for (int i = 0; i < tot; i++) {
      int add = rnd.nextInt(0, N-1);
      K[add]++;
    }
  }
  int gcd(int a, int b) {
    return a ? gcd(b % a, a) : b;
  }

  vector<int> randomCoprimeList(int n, int hi) {
    set<int> st;
    while (st.size() < n) {
      int now = rnd.nextInt(2, hi);
      for (int x : st) {
        int d = gcd(x, now);
        while (d > 1) {
          now /= d;
          d = gcd(x, now);
        }
      }
      if (now > 1)
        st.insert(now);
    }
    vector<int> ret;
    for (int x : st)
      ret.push_back(x);
    return ret;
  }

  void randomNumber(int hi, vector<int> includedAns) {
    X.resize(N);
    for (int i = 0; i < N; i++) {
      X[i].resize(K[i]);
      for (int j = 0; j < K[i]; j++)
        X[i][j] = 1;
      for (int val : includedAns) {
        int id = rnd.nextInt(0, K[i]-1);
        while (hi < 1LL * X[i][id] * val) id = rnd.nextInt(0, K[i]-1);
        X[i][id] *= val;
      }
      set<int> numbers;
      for (int j = 0; j < K[i]; j++)
        numbers.insert(X[i][j] * rnd.nextInt(1, hi/X[i][j]));
      while (numbers.size() < K[i])
        numbers.insert(rnd.nextInt(1, hi));
      auto it = numbers.begin();
      for (int j = 0; j < K[i]; j++, it++)
        X[i][j] = *it;
    }
  }

  void consecutiveNumber(int start) {
    X.resize(N);
    for (int i = 0; i < N; i++) {
      X[i].resize(K[i]);
      for (int j = 0; j < K[i]; j++)
        X[i][j] = start + j;
    }
  }

  void numberWithMostPrime(int hi) {
    vector<int> prime;
    vector<bool> isprim(hi+1, true);
    for (int i = 2; i <= hi; i++) if (isprim[i]) {
      prime.push_back(i);
      for (int j = i + i; j <= hi; j += i)
        isprim[j] = false;
    }
    rnd.shuffle(prime.begin(), prime.end());
    X.resize(N);
    for (int i = 0; i < N; i++) {
      X[i].resize(K[i]);
      int nprime = min(K[i], (int)prime.size());
      set<int> numbers;
      for (int j = 0; j < nprime; j++) {
        int p = prime[j], power = 0, cur = hi/p;
        while (cur) {
          power++;
          cur /= p;
        }
        power = rnd.nextInt(1, power);
        cur = 1;
        while (power--) {
          cur *= p;
        }
        numbers.insert(cur);
      }
      while (numbers.size() < K[i]) {
        numbers.insert(rnd.nextInt(1, hi));
      }
      auto it = numbers.begin();
      for (int j = 0; j < K[i]; j++, it++)
        X[i][j] = *it;
    }
  }
};