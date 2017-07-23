#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  int A;

  void InputFormat() {
    LINE(N);
  }

  void OutputFormat() {
    LINE(A);
  }

  void Constraints() {
    CONS(0 <= N && N <= 1000);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Input({"4"});
    Output({"19"});
  }

  void TestCases() {
    int nKasusKecil = 10;
    int nKasusRandom = 10;
    int nKasusBesar = 10;

    // Kasus Kecil
    for(int i = 0; i < nKasusKecil; i++) {
      CASE(N = i);
    }

    // Kasus Random
    for(int i = 0; i < nKasusRandom; i++) {
      CASE(N = rnd.nextInt(1, 1000));
    }

    // Kasus Besar
    for(int i = 0; i < nKasusBesar; i++) {
      CASE(N = 1000-i);
    }
  }
};
