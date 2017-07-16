#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

#define pb push_back

class ProblemSpec : public BaseProblemSpec {
protected:
	int N;
	const int MAXN = 1e5;
	string cor, S;
	vector<vector<int> > ar;
	int result;
	void InputFormat(){
		LINE(N);
		RAW_LINE(cor);
		RAW_LINE(S);
		GRID(ar) % SIZE(N, 7);
	}

	void OutputFormat(){
		LINE(result);
	}

	void Constraints(){
		CONS(1 <= N && N <= MAXN);
		CONS((int)cor.size() == N);
		CONS((1 <= (int) S.size()) && ((int)S.size() <= MAXN));
		CONS((int)ar.size() == N);
		CONS(eachVectorLength(ar, 7));
		CONS(eachElementBetween(ar, 0, 1));
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
		S = "";
		ar.clear();
	}

	void SampleTestCase1(){
		Input({"3", "101", "156789000", "0 1 1 0 0 0 0", "0 0 0 0 0 0 0", "1 1 1 1 1 1 0"});
		Output({"10"});
	}
	void TestCases(){
		CASE(N = 1; cor = "0"; S = "0"; ar.push_back(EmptySegment));
		CASE(N = 1; cor = "1"; S = "0"; ar.push_back(EmptySegment));
		/* Manual Test Case */
		ManualTestCases();
		
		CASE(N = 5; generateAllCorrect(); generateRandomDigit(N); generateSomeMaxArray());
		
		CASE(N = 1000; generateAllIncorrect(); generateRandomDigit(N); generateSomeMaxArray());
		CASE(N = 100; generateMixedCorrect(); generateRandomDigit(N); generateRandomArray());
		CASE(N = 10; generateMixedCorrect(); generateIncreasingDigit(N); generateRandomArray());
		CASE(N = 10; generateMixedCorrect(); generateRandomDigit(5); generateRandomArray());
		
		CASE(N = rnd.nextInt(1, MAXN); generateAllIncorrect(); generateRandomDigit(rnd.nextInt(1, MAXN)); generateSomeMaxArray());
		CASE(N = rnd.nextInt(1, MAXN); generateAllIncorrect(); generateRandomDigit(rnd.nextInt(1, MAXN)); generateRandomArray());
		CASE(N = rnd.nextInt(1, MAXN); generateAllIncorrect(); generateRandomDigit(rnd.nextInt(1, MAXN)); generateAllMaxArray());
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomDigit(rnd.nextInt(1, MAXN)); generateSomeMaxArray());
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomDigit(rnd.nextInt(1, MAXN)); generateRandomArray());
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateRandomDigit(rnd.nextInt(1, MAXN)); generateAllMaxArray());
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateIncreasingDigit(rnd.nextInt(1, MAXN)); generateRandomArray());
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateDecreasingDigit(rnd.nextInt(1, MAXN)); generateSomeMaxArray());

		CASE(N = rnd.nextInt(1, MAXN); generateAllIncorrect(); generateRandomDigit(rnd.nextInt(1, MAXN)); generateSomeMaxArray(); mutateAll(4));
		CASE(N = rnd.nextInt(1, MAXN); generateAllCorrect(); generateRandomDigit(rnd.nextInt(1, MAXN)); generateRandomArray(); mutateCorrect(10));
		CASE(N = rnd.nextInt(1, MAXN); generateAllCorrect(); generateRandomDigit(rnd.nextInt(1, MAXN)); generateRandomArray(); mutateNoLeading(10));
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateDecreasingDigit(rnd.nextInt(1, MAXN)); generateSomeMaxArray(); mutateCorrect(5));
		CASE(N = rnd.nextInt(1, MAXN); generateMixedCorrect(); generateDecreasingDigit(rnd.nextInt(1, MAXN)); generateSomeMaxArray(); mutateAll(100));

		CASE(N = MAXN; generateAllIncorrect(); generateRandomDigit(N); generateRandomArray());
		CASE(N = MAXN; generateAllCorrect(); generateRandomDigit(N); generateRandomArray());
		CASE(N = MAXN; generateMixedCorrect(); generateRandomDigit(N); generateRandomArray());
		CASE(N = MAXN; generateMixedCorrect(); generateRandomDigit(N); generateSomeMaxArray());
		CASE(N = MAXN; generateMixedCorrect(); generateRandomDigit(N); generateAllMaxArray());
		CASE(N = MAXN; generateMixedCorrect(); generateDecreasingDigit(N); generateRandomArray());
		
	}

private:
	
	void ManualTestCases(){
		CASE(N = 7; cor = "0001010"; S = "100000000000000000000000000000000000000";
			ar.pb(EmptySegment);ar.pb(EmptySegment);ar.pb(EmptySegment);
			ar.pb(Segment[1]);ar.pb(Segment[0]);ar.pb(Segment[8]);ar.pb(EmptySegment));
		CASE(N = 7; cor = "0001010"; S = "19999";
			ar.pb(EmptySegment);ar.pb(EmptySegment);ar.pb(EmptySegment);
			ar.pb(Segment[1]);ar.pb(Segment[0]);ar.pb(Segment[8]);ar.pb(EmptySegment));
		CASE(N = 7; cor = "1001010"; S = "100000000000000000000000000000000000000";
			ar.pb(EmptySegment);ar.pb(EmptySegment);ar.pb(EmptySegment);
			ar.pb(Segment[1]);ar.pb(Segment[0]);ar.pb(Segment[8]);ar.pb(EmptySegment));
		CASE(N = 7; cor = "1001010"; S = "991888";
			ar.pb(EmptySegment);ar.pb(EmptySegment);ar.pb(EmptySegment);
			ar.pb(Segment[1]);ar.pb(Segment[0]);ar.pb(Segment[8]);ar.pb(EmptySegment));
		CASE(N = 7; cor = "1001010"; S = "991788";
			ar.pb(EmptySegment);ar.pb(EmptySegment);ar.pb(EmptySegment);
			ar.pb(Segment[1]);ar.pb(Segment[0]);ar.pb(Segment[8]);ar.pb(EmptySegment));
		CASE(N = 4; cor = "1111"; S = "100000"; ar.pb(EmptySegment); ar.pb(EmptySegment);
			ar.pb(EmptySegment); ar.pb(EmptySegment));
		CASE(N = 10; cor = "1011101101"; S = "7000011222"; ar.pb(Segment[7]); ar.pb(EmptySegment);
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
	}
	
	void generatePrefixArray(int len){
		for(int i = 0;i < len; ++i){
			ar.push_back(EmptySegment);
		}
	}
	
	/* Generate Array */
	void generateRandomArray(){
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
				ar.push_back(getSegmentFromBit(rand_bitmask));
			}
		}
	}
	
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
	}
	
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
	}
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
	
	void mutateNoLeading(int amount){
		int start_n = max((int) N - (int) S.length(), 0);
		for(int i = 0;i < amount; ++i){
			int idx = rnd.nextInt(start_n, N);
			mutateArrayIdx(idx);
		}
	}
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

