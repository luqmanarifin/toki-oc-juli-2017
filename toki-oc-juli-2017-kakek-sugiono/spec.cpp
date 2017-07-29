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

  void GradingConfig(){
    TimeLimit(1);
    MemoryLimit(64);
  }

  void Constraints() {
    CONS(0 <= N && N <= 10);
  }

  void Subtask1(){
      Points(100);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({"4"});
    Output({"19"});
  }

  void TestGroup1() {
    Subtasks({1});
    for(int i = 0;i <= 10; ++i) {
      if (i == 4) continue;
      CASE(N = i);
    }
  }
};
