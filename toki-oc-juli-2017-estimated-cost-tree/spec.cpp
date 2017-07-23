#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N;
  vector<int> U, V, C;
  long long A;

  void InputFormat() {
    LINE(N);
    LINES(U, V, C) % SIZE(N-1);
  }

  void OutputFormat() {
    LINE(A);
  }

  void GradingConfig() {
    // Berapa nih?

    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(1 <= N && N <= 1e5);
    CONS(ElementsBetween(U, 1, N));
    CONS(ElementsBetween(V, 1, N));
    CONS(ElementsBetween(C, 1, (int) 1e7));
    CONS(U.size() == N-1 && V.size() == N-1 && C.size() == N-1);
    CONS(DifferentElements(U, V));
    CONS(UniquePairs(U, V));
  }

private:
  template<class T>
  bool ElementsBetween(vector<T> elements, T lowerBound, T upperBound) {
    for(T element: elements) {
      if ((element < lowerBound) || (element > upperBound)) {
        return false;
      }
    }

    return true;
  }

  template<class T>
  bool DifferentElements(vector<T> elementsA, vector<T> elementsB) {
    for(int i = 0; i < elementsA.size(); i++) {
      if (elementsA[i] == elementsB[i]) return false;
    }

    return true;
  }

  template<class T>
  bool UniquePairs(vector<T> elementsA, vector<T> elementsB) {
    set<pair<T,T> > visitedElements;

    for(int i = 0; i < elementsA.size(); i++) {
      pair<T,T> currentPair = {min(elementsA[i], elementsB[i]), max(elementsA[i], elementsB[i])};
      if (visitedElements.count(currentPair) > 0) return false;
      visitedElements.insert(currentPair);
    }

    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({
      "3",
      "1 2 2",
      "2 3 1"
    });
    Output({
      "8"
    });
  }

  void BeforeTestCase() {
    U.clear(); V.clear(); C.clear();
  }

  void TestCases() {
    int nLittleCase = 10;
    int nBigCase = 10;
    int nMaxCase = 5;

    // Sama aja linear star atau random juga
    CASE(N = 1, LinearTree(1, 1));
    CASE(N = 2, LinearTree(1, 1e7));

    // Random Kecil
    CASE(N = rnd.nextInt(100, 1000), LinearTree(1, 1e7));
    CASE(N = rnd.nextInt(100, 1000), StarGraph(1, 1e7));
    for(int i = 0; i < nLittleCase; i++) {
      CASE(N = rnd.nextInt(100, 1000), RandomTree(1, 1e7));
    }

    // Random Besar
    CASE(N = rnd.nextInt(50000, 100000), LinearTree(1, 1e7));
    CASE(N = rnd.nextInt(50000, 100000), StarGraph(1, 1e7));
    for(int i = 0; i < nBigCase; i++) {
      CASE(N = rnd.nextInt(50000, 100000), RandomTree(1, 1e7));
    }

    // Max Case
    CASE(N = 100000, LinearTree(1e7, 1e7));
    CASE(N = 100000, StarGraph(1e7, 1e7));
    for(int i = 0; i < nMaxCase; i++) {
      CASE(N = 100000, RandomTree(1e7, 1e7));
    }
  }

private:
  void GenerateRandomMapping(int n, vector<int>& mapping) {
    mapping.clear();
    for(int i = 1; i <= n; i++) mapping.push_back(i);
    rnd.shuffle(mapping.begin(), mapping.end());
  }

  void LinearTree(int minC, int maxC) {
    vector<int> mapping;
    GenerateRandomMapping(N, mapping);

    for(int i = 1; i < N; i++) {
      if (rnd.nextInt(2) == 0) {
        U.push_back(mapping[i]);
        V.push_back(mapping[i-1]);
        C.push_back(rnd.nextInt(minC, maxC));
      }
      else {
        U.push_back(mapping[i-1]);
        V.push_back(mapping[i]);
        C.push_back(rnd.nextInt(minC, maxC));
      }
    }
  }

  void StarGraph(int minC, int maxC) {
    vector<int> mapping;
    GenerateRandomMapping(N, mapping);

    for(int i = 1; i < N; i++) {
      if (rnd.nextInt(2) == 0) {
        U.push_back(mapping[i]);
        V.push_back(mapping[0]);
        C.push_back(rnd.nextInt(minC, maxC));
      }
      else {
        U.push_back(mapping[0]);
        V.push_back(mapping[i]);
        C.push_back(rnd.nextInt(minC, maxC));
      }
    }
  }

  void RandomTree(int minC, int maxC) {
    vector<int> mapping;
    GenerateRandomMapping(N, mapping);

    for(int i = 1; i < N; i++) {
      if (rnd.nextInt(2) == 0) {
        U.push_back(mapping[i]);
        V.push_back(mapping[rnd.nextInt(i)]);
        C.push_back(rnd.nextInt(minC, maxC));
      }
      else {
        U.push_back(mapping[rnd.nextInt(i)]);
        V.push_back(mapping[i]);
        C.push_back(rnd.nextInt(minC, maxC));
      }
    }
  }
};
