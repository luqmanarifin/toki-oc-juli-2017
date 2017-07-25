#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

#define pb push_back

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	const int MAXN = 1e5;
	string cor;
	vector<vector<int> > ar;
	int result;
	void InputFormat(){
		LINE(N);
		RAW_LINE(cor);
		GRID(ar) % SIZE(N, 7);
	}

	void OutputFormat(){
		LINE(result);
	}

	void Constraints(){
		CONS(1 <= N && N <= MAXN);
		CONS((int)cor.size() == N);
		CONS((int)ar.size() == N);
		CONS(eachVectorLength(ar, 7));
		CONS(eachElementBetween(ar, 0, 1));
	}

	void Subtask1(){

	}

private:
	bool eachVectorLength(const vector<vector<int> > &ar, int len){
		for(vector<int> v : ar){
			if((int)v.size() != len) return false;
		}
		return true;
	}

	bool eachElementBetween(const vector<vector<int> > &ar, int lo, int hi){
		for(vector<int> v : ar){
			for(int x : v){
				if(x < lo || x > hi) return false;
			}
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

	void BeforeTestCase(){
		cor = "";
		ar.clear();
	}

	void SampleTestCase1(){
		Subtasks({1});
		Input({"2", "01", "0 0 0 0 0 0 0", "1 1 1 1 1 1 0"});
		Output({"10"});
	}

	void SampleTestCase2(){
		Subtasks({1});
		Input({"3", "110", "1 1 1 1 1 1 0", "1 1 1 1 1 1 0", "0 1 1 0 0 0 0"});
		Output({"0"});
	}

	void SampleTestCase3(){
		Subtasks({1});
		Input({"2", "01", "1 1 1 1 1 1 1", "0 0 0 0 0 0 0"});
		Output({"0"});
	}

	void SampleTestCase4(){
		Subtasks({1});
		Input({"2", "00", "1 1 1 1 1 1 0", "1 1 1 1 1 1 0"});
		Output({"2"});
	}

	void SampleTestCase5(){
		Subtasks({1});
		Input({"2", "00", "1 1 0 0 0 0 0", "0 0 0 0 0 0 0"});
		Output({"50"});
	}

	void SampleTestCase6(){
		Subtasks({1});
		Input({"7", "1001010", "0 0 0 0 0 0 0", 
			"0 0 0 0 0 0 0", "0 0 0 0 0 0 0", 
			"0 1 1 0 0 0 0", "1 1 1 1 1 1 0", 
			"1 1 1 1 1 1 1", "0 0 0 0 0 0 0"});
		Output({"2000"});
	}

	void TestGroup1(){
		Subtasks({1});

		CASE(N = 1; cor = "0"; ar.push_back(EmptySegment));
		CASE(N = 1; cor = "1"; ar.push_back(EmptySegment));
		/* Manual Test Case */
		ManualTestCases();
		
		CASE(N = 5; generateAllCorrect(); generateRandomArray());
		
		CASE(N = 1000; generateAllIncorrect(); generateRandomArray());
		CASE(N = 100; generateMixedCorrect(); generateRandomArray());
		CASE(N = 10; generateMixedCorrect(); generateRandomArray());
		CASE(N = 10; generateMixedCorrect(); generateRandomArray());
		
		CASE(N = rnd.nextInt(1, MAXN); generateAllIncorrect(); generateRandomArray());
		CASE(N = rnd.nextInt(1, MAXN); generateAllIncorrect(); generateRandomArray());
		CASE(N = rnd.nextInt(1, MAXN); generateAllIncorrect(); generateRandomArrayWithPrefix(rnd.nextInt(1, N)));
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomArrayWithPrefix(rnd.nextInt(max(0, N-10), N)));
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomArray());
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomArrayWithPrefix(rnd.nextInt(1, N)));
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomArray());
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomArrayWithPrefix(rnd.nextInt(1, N)));

		CASE(N = rnd.nextInt(1, MAXN); generateAllIncorrect(); generateRandomArrayWithPrefix(rnd.nextInt(1, N)); mutateAll(4));
		CASE(N = rnd.nextInt(1, MAXN); generateAllCorrect(); generateRandomArray(); mutateCorrect(10));
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomArrayWithPrefix(rnd.nextInt(1, N)); mutateCorrect(5));
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomArrayWithPrefix(rnd.nextInt(1, N)); mutateAll(100));

		CASE(N = MAXN; generateAllIncorrect(); generateRandomArray());
		CASE(N = MAXN; generateAllCorrect(); generateRandomArray());
		CASE(N = MAXN; generateMixedCorrect(); generateRandomArray());
		CASE(N = MAXN; generateMixedCorrect(); generateRandomArrayWithPrefix(rnd.nextInt(1, N)));
		CASE(N = MAXN; generateMixedCorrect(); generateRandomArrayWithPrefix(rnd.nextInt(1, N)));
		CASE(N = MAXN; generateMixedCorrect(); generateRandomArray());
		
	}

private:
	
	void ManualTestCases(){
		CASE(N = 3; cor = "101"; ar.pb(Segment[1]); ar.pb(EmptySegment); ar.pb(Segment[0]));
		CASE(N = 7; cor = "0001010";
			ar.pb(EmptySegment);ar.pb(EmptySegment);ar.pb(EmptySegment);
			ar.pb(Segment[1]);ar.pb(Segment[0]);ar.pb(Segment[8]);ar.pb(EmptySegment));
		CASE(N = 4; cor = "1111"; ar.pb(EmptySegment); ar.pb(EmptySegment);
			ar.pb(EmptySegment); ar.pb(EmptySegment));
		CASE(N = 10; cor = "1011101101"; ar.pb(Segment[7]); ar.pb(EmptySegment);
			ar.pb(Segment[0]);ar.pb(Segment[0]);ar.pb(Segment[0]);ar.pb(getSegmentFromBit((1 << 1) + (1 << 5)));
			ar.pb(Segment[1]);ar.pb(Segment[2]);ar.pb(getSegmentFromBit((1 << 1) + (1 << 5)));ar.pb(Segment[2]));
	}
	/** HELPERS **/	
		
	void generateAllIncorrect(){
		for(int i = 0;i < N; ++i){
			cor += '0';
		}
	}
	
	void generateAllCorrect(){
		for(int i = 0;i < N; ++i){
			cor += '1';
		}
	}
	
	void generateMixedCorrect(int rand = 2){
		for(int i = 0;i < N; ++i){
			int val = rnd.nextInt(rand) ? 0 : 1;
			cor += (val + '0');
		}
	}
	
	/* Generate Digits */
	char generateFirstDigit(){
		return rnd.nextInt(1, 9) + '0';
	}
	/*
	void generateRandomDigit(int size){
		S += generateFirstDigit();
		for(int i = 1; i < size; ++i){
			S += rnd.nextInt(10) + '0';
		}
	}
	
	void generateIncreasingDigit(int size){
		int MAX_NUM = 9;
		int num_now = 0;
		S += generateFirstDigit();
		for(int i = 1;i < size; ++i){
			if(rnd.nextInt(max(3, N / 5)) > 2){
				S += num_now + '0';
			}
			else{
				num_now = rnd.nextInt(num_now, min(num_now + 1, MAX_NUM));
				S += num_now + '0';
			}
		}
	}
	
	void generateDecreasingDigit(int size){
		int MIN_NUM = 0;
		int num_now = 9;
		S += generateFirstDigit();
		for(int i = 1;i < size; ++i){
			if(rnd.nextInt(max(3, N / 5)) > 2){
				S += num_now + '0';
			}
			else{
				num_now = rnd.nextInt(max(num_now - 1, MIN_NUM), num_now);
				S += num_now + '0';
			}
		}
	}*/
	
	void generatePrefixArray(int len){
		for(int i = 0;i < len; ++i){
			ar.push_back(EmptySegment);
		}
	}
	
	/* Generate Array */
	void generateRandomArray(){
		for(int i = 0;i < N; ++i){
			int cor_now = cor[i] - '0';
			if(cor_now == 1){
				ar.push_back(Segment[rnd.nextInt(10)]);
			}
			else{
				int rand_bitmask = rnd.nextInt(1 << 10);
				ar.push_back(getSegmentFromBit(rand_bitmask));
			}
		}
	}

	void generateRandomArrayWithPrefix(int len){
		generatePrefixArray(len);
		for(int i = len; i < N; ++i){
			int cor_now = cor[i] - '0';
			if(cor_now == 1){
				ar.push_back(Segment[rnd.nextInt(10)]);
			}
			else{
				int rand_bitmask = rnd.nextInt(1 << 10);
				ar.push_back(getSegmentFromBit(rand_bitmask));
			}
		}	
	}
	/*
	void generateRandomArray(){
		int len = (int) N - (int) S.length();
		generatePrefixArray(len);
		
		int mulaiS = max(0, -len);
		for(int i = mulaiS, j = max(len, 0);i < (int)S.length(); ++i, ++j){
			int cor_now = cor[j] - '0';
			if(cor_now == 1){
				ar.push_back(Segment[rnd.nextInt(10)]);
			}
			else{
				int rand_bitmask = rnd.nextInt(1 << 10);
				ar.push_back(getSegmentFromBit(rand_bitmask));
			}
		}
	}*/
	/*
	void generateSomeMaxArray(){
		int len = (int) N - (int) S.length();
		generatePrefixArray(len);
		
		int mulaiS = max(0, -len);
		for(int i = mulaiS, j = max(len, 0);i < (int)S.length(); ++i, ++j){
			int cor_now = cor[j] - '0';
			int val_now = S[i] - '0';
			if(cor_now == 1){
				ar.push_back(Segment[rnd.nextInt(10)]);
			}
			else{
				int rand_bitmask = rnd.nextInt(1 << 10);
				if(rnd.nextInt(3)){
					rand_bitmask = rnd.nextInt(1 << (val_now + 1));
				}
				ar.push_back(getSegmentFromBit(rand_bitmask));
			}
		}
	}*/
	/*
	void generateAllMaxArray(){
		int len = (int) N - (int) S.length();
		generatePrefixArray(len);
		
		int mulaiS = max(0, -len);
		for(int i = mulaiS, j = max(len, 0);i < (int)S.length(); ++i, ++j){
			int cor_now = cor[j] - '0';
			int val_now = S[i] - '0';
			if(cor_now == 1){
				ar.push_back(Segment[val_now]);
			}
			else{
				int rand_bitmask = rnd.nextInt(1 << (val_now + 1));
				ar.push_back(getSegmentFromBit(rand_bitmask));
			}
		}
	}*/
	void mutateArrayIdx(int idx, bool correct = false){
		if(correct && rnd.nextInt(5)){
			ar[idx] = Segment[rnd.nextInt(10)];
		}
		else{			
			for(int j = 0;j < 7; ++j){
				ar[idx][j] = rnd.nextInt(2);
			}
		}
	}
	
	void mutateAll(int amount){
		for(int i = 0;i < amount; ++i){
			int idx_mutate = rnd.nextInt(N);
			mutateArrayIdx(idx_mutate);
		}
	}
	
	void mutateCorrect(int amount){
		vector<int> idx_correct;
		for(int i = 0;i < N; ++i) if(cor[i] == '1') idx_correct.push_back(i);
		if(idx_correct.size() == 0) return;
		rnd.shuffle(idx_correct.begin(), idx_correct.end());
		for(int i = 0;i < min(amount, (int)idx_correct.size()); ++i){
			mutateArrayIdx(idx_correct[i], true);
		}
	}
	/*
	void mutateNoLeading(int amount){
		int start_n = max((int) N - (int) S.length(), 0);
		for(int i = 0;i < amount; ++i){
			int idx = rnd.nextInt(start_n, N);
			mutateArrayIdx(idx);
		}
	}*/

	vector<int> AND(const vector<int>& v1, const vector<int>& v2){
		vector<int> result;
		for(int i = 0;i < v1.size(); ++i){
			result.push_back(v1[i] & v2[i]);
		}
		return result;
	}
	
	vector<int> getSegmentFromBit(int bitmask){
		vector<int> result = {1, 1, 1, 1, 1, 1, 1};
		for(int i = 0; i < 10; ++i){
			if((1 << i) & bitmask){
				result = AND(result, Segment[i]);
			}
		}
		return result;
	}
	
	/* CONSTANTS */
	const vector<vector<int> > Segment = {
		{1, 1, 1, 1, 1, 1, 0},
		{0, 1, 1, 0, 0, 0, 0},
		{1, 1, 0, 1, 1, 0, 1},
		{1, 1, 1, 1, 0, 0, 1},
		{0, 1, 1, 0, 0, 1, 1},
		{1, 0, 1, 1, 0, 1, 1},
		{1, 0, 1, 1, 1, 1, 1},
		{1, 1, 1, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 0, 1, 1}
	};
	
	vector<int> EmptySegment = {0, 0, 0, 0, 0, 0, 0};
};

