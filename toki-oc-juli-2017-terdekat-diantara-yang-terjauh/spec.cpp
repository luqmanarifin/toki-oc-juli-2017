#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, K;
  vector< int > U, V, C;
  vector< int > A;

  void InputFormat() {
    LINE(N, K);
    LINE(C % SIZE(N));
    LINES(U, V) % SIZE(N-1);
  }

  void OutputFormat() {
    LINE(A % SIZE(K));
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(1 <= N && N <= int(1e5));
    CONS(1 <= K && K <= N);
    CONS(eachElementBetween(U, 1, N));
    CONS(eachElementBetween(V, 1, N));
    CONS(eachElementBetween(C, 1, K));
    CONS(C.size() == N);
    CONS(isTree(N, U, V));
  }

  void Subtask1(){
  	Points(100);
  }

private:
  bool eachElementBetween(const vector<int>&v, int lo, int hi) {
    for (int x : v) {
      if (x < lo || x > hi) {
        return false;
      }
    }
    return true;
  }
  vector<bool> vis;
  vector< vector<int> > adj;
  bool isTree(int n, const vector<int>& u, const vector<int>& v) {
    if (u.size() != n-1 || v.size() != n-1)
      return false;
    vis.assign(n+1, false);
    adj.assign(n+1, vector<int>());
    for (int i = 0; i < n-1; i++) {
      adj[u[i]].push_back(v[i]);
      adj[v[i]].push_back(u[i]);
    }
    int cnt = 0;
    queue<int> que;
    que.push(1);
    while (!que.empty()) {
      int now = que.front(); que.pop();
      cnt++;
      vis[now] = true;
      for (int next : adj[now]) if (!vis[next])
        que.push(next);
    }
    return cnt == n;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
  	Subtasks({1});
    Input({
      "3 2",
      "1 2 1",
      "1 2",
      "1 3"
    });
    Output({
      "1 0"
    });
  }

  void BeforeTestCase() {
    U.clear();
    V.clear();
    C.clear();
    A.clear();
  }

  void TestGroup1() {
  	Subtasks({1});
    // manual cases
    CASE(N = 1, K = 1, C = {1}, U = {}, V = {});
    CASE(N = 2, K = 1, C = {1, 1}, U = {1}, V = {2});
    CASE(N = 4, K = 2, C = {1, 1, 2, 2}, U = {1, 2, 2}, V = {2, 3, 4});
    CASE(N = 5, K = 2, C = {2, 2, 1, 2, 1}, U = {1, 2, 3, 2}, V = {2, 3, 4, 5});

    // linear
    CASE(N = 100, K = N/3, randomColor(N, C, 1, K), randomLinear(N, U, V));
    CASE(N = 5000, K = N/5, randomColor(N, C, 1, K), randomLinear(N, U, V));
    CASE(N = 100000, K = 1, randomColor(N, C, 1, K), randomLinear(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(10, 50), randomColor(N, C, 1, K), randomLinear(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(100, 500), randomColor(N, C, 1, K), randomLinear(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(1000, 5000), randomColor(N, C, 1, K), randomLinear(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(10000, 50000), randomColor(N, C, 1, K), randomLinear(N, U, V));
    CASE(N = 100000, K = N, randomColor(N, C, 1, K), randomLinear(N, U, V));

    // balanced binary tree
    CASE(N = 100000, K = rnd.nextInt(10, 50), randomColor(N, C, 1, K), balancedBinaryTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(100, 500), randomColor(N, C, 1, K), balancedBinaryTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(1000, 5000), randomColor(N, C, 1, K), balancedBinaryTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(10000, 50000), randomColor(N, C, 1, K), balancedBinaryTree(N, U, V));

    // k-star tree
    CASE(N = 100000, K = 1, randomColor(N, C, 1, K), kStarTree(N, N-1, U, V));
    CASE(N = 100000, K = rnd.nextInt(10, 50), randomColor(N, C, 1, K), kStarTree(N, rnd.nextInt(3, 10), U, V));
    CASE(N = 100000, K = rnd.nextInt(10, 50), randomColor(N, C, 1, K), kStarTree(N, rnd.nextInt(50000, N-2), U, V));
    CASE(N = 100000, K = rnd.nextInt(100, 500), randomColor(N, C, 1, K), kStarTree(N, rnd.nextInt(3, 10), U, V));
    CASE(N = 100000, K = rnd.nextInt(100, 500), randomColor(N, C, 1, K), kStarTree(N, rnd.nextInt(50000, N-1), U, V));
    CASE(N = 100000, K = rnd.nextInt(1000, 10000), randomColor(N, C, 1, K), kStarTree(N, rnd.nextInt(3, 10), U, V));
    CASE(N = 100000, K = rnd.nextInt(1000, 10000), randomColor(N, C, 1, K), kStarTree(N, rnd.nextInt(50000, N-1), U, V));
    CASE(N = 100000, K = rnd.nextInt(50000, 100000), randomColor(N, C, 1, K), kStarTree(N, rnd.nextInt(3, 10), U, V));
    CASE(N = 100000, K = rnd.nextInt(50000, 100000), randomColor(N, C, 1, K), kStarTree(N, N-1, U, V));

    // random tree
    CASE(N = 100, K = N/3, randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 5000, K = N/5, randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 10000, K = N/100, randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 50000, K = N/25, randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 50000, K = N, randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 100000, K = 1, randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(2, 10), randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(10, 50), randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(50, 100), randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(100, 500), randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(1000, 5000), randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(10000, 50000), randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 100000, K = rnd.nextInt(50000, 100000), randomColor(N, C, 1, K), randomTree(N, U, V));
    CASE(N = 100000, K = N, randomColor(N, C, 1, K), randomTree(N, U, V));
  }
private:
  vector<int> permutation;
  void randomColor(int n, vector<int>& c, int minC = 1, int maxC = 100000) {
    for (int i = 0; i < n; i++) {
      c.push_back(rnd.nextInt(minC, maxC));
    }
  }

  void renumber(int n, vector<int>& u, vector<int>& v) {
    permutation.clear();
    for (int i = 1; i <= n; i++) {
      permutation.push_back(i);
    }
    rnd.shuffle(permutation.begin(), permutation.end());
    for (int i = 0; i < u.size(); i++) {
      u[i] = permutation[u[i]-1];
      v[i] = permutation[v[i]-1];
    }
  }

  void balancedBinaryTree(int n, vector<int> &u, vector<int> &v) {
    for (int i = 2; i <= n; i++) {
      u.push_back(i);
      v.push_back(i/2);
    }
    renumber(n, u, v);
  }

  void kStarTree(int n, int k, vector<int> &u, vector<int> &v) {
    vector< int > child;
    for (int i = 0; i < k; i++) {
      u.push_back(1);
      v.push_back(2 + i);
      child.push_back(2 + i);
    }
    for (int i = k+2; i <= n; i++) {
      int select = rnd.nextInt(0, k-1);
      u.push_back(child[select]);
      v.push_back(i);
      child[select] = i;
    }
    renumber(n, u, v);
  }

  void randomTree(int n, vector<int>& u, vector<int>& v) {
    for (int i = 2; i <= n; i++) {
      u.push_back(i);
      v.push_back(rnd.nextInt(1, i - 1));
    }
    renumber(n, u, v);
  }

  void randomLinear(int n, vector<int>& u, vector<int>& v) {
    for (int i = 2; i <= n; i++) {
      u.push_back(i);
      v.push_back(i-1);
    }
    renumber(n, u, v);
  }
};