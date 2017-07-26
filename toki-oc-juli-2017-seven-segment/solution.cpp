#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>

using namespace std;

const int SEVEN = 7;
const int N = 1e5;
const int MOD = 1e9 + 8;
const int MAX_DIG = 10;

enum {
	SEG_ZERO,
	SEG_ONE,
	SEG_TWO,
	SEG_THREE,
	SEG_FOUR,
	SEG_FIVE,
	SEG_SIX,
	SEG_SEVEN,
	SEG_EIGHT,
	SEG_NINE,
	TOTAL_SEGMENT
};

class Segment{
private:
	bool segment[SEVEN];

public:
	Segment(){
		segment[0] = segment[1] = segment[2] = segment[3] = segment[4] = segment[5] = segment[6] = false;
	}

	Segment(bool _A, bool _B, bool _C, bool _D, bool _E, bool _F, bool _G){
		segment[0] = _A;
		segment[1] = _B;
		segment[2] = _C;
		segment[3] = _D;
		segment[4] = _E;
		segment[5] = _F;
		segment[6] = _G;
	}

	bool get_segment(){
		return segment;
	}
	bool get_segment_idx(int idx){
		return segment[idx];
	}
	void set_segment_idx(int idx, bool val){
		segment[idx] = val;
	}

	bool operator==(const Segment &S){
		for(int i = 0;i < SEVEN; ++i){
			if(segment[i] != S.segment[i]) return false;
		}
		return true;
	}
	bool compatible(const Segment &S){
		for(int i = 0;i < SEVEN; ++i){
			if(segment[i] > S.segment[i]) return false;
		}
		return true;
	}
};

Segment SEG[TOTAL_SEGMENT] = {Segment(1, 1, 1, 1, 1, 1, 0),
			 	 Segment(0, 1, 1, 0, 0, 0, 0),
			 	 Segment(1, 1, 0, 1, 1, 0, 1),
			 	 Segment(1, 1, 1, 1, 0, 0, 1),
			 	 Segment(0, 1, 1, 0, 0, 1, 1),
			 	 Segment(1, 0, 1, 1, 0, 1, 1),
			 	 Segment(1, 0, 1, 1, 1, 1, 1),
			 	 Segment(1, 1, 1, 0, 0, 0, 0),
			 	 Segment(1, 1, 1, 1, 1, 1, 1),
			 	 Segment(1, 1, 1, 0, 0, 1, 1)
			 	};
			 	
Segment EmptySegment = Segment();

int n;
bool maks_from_awal = true;

char num[N + 5];
int max_num[N + 5];

char correct[N + 5];
int dp[N][2][2]; // dp[pos][still_max][still_zero]
int val[N + 5];
Segment ar[N + 5];

int start_num;
int start_n;

void setup(){
	char _arr[N + 5];

	scanf("%d", &n);
	scanf("%s", correct);
	memset(_arr, 0, sizeof _arr);
	for(int i = 0;i <= N; ++i) _arr[i] = '9';
	strcpy(num, _arr);

	int lenArr = strlen(_arr);
	if(lenArr > n) {
		maks_from_awal = false;
		for(int i = 0;i < n; ++i){
			max_num[i] = _arr[i] - '0';
		}
	}
	else{
		int len_zero_digit = n - lenArr;
		for(int i = 0;i < len_zero_digit; ++i){
			max_num[i] = 0;
		}
		for(int i = len_zero_digit; i < n; ++i){
			max_num[i] = _arr[i - len_zero_digit] - '0';
		}
	}
	for(int i = 0;i < n; ++i){
		for(int j = 0;j < SEVEN; ++j){
			int x;
			scanf("%d", &x);
			ar[i].set_segment_idx(j, x);	
		}
	}
	memset(dp, -1, sizeof dp);
	memset(val, -1, sizeof val);
}

int rek(int pos, bool still_max, bool already_start){
	if(pos == n) return 1;
	if(dp[pos][still_max][already_start] == -1){
		int &ret = dp[pos][still_max][already_start] = 0;
		if(!already_start){
			int max_num_pos = still_max ? max_num[pos] : TOTAL_SEGMENT - 1;
			if(val[pos] == -2){
				if(pos == n - 1) ret = 0;
				else ret = rek(pos + 1, false, false);
			}
			else if(val[pos] != -1){
				if(val[pos] > max_num_pos || (val[pos] == 0 && pos != n-1)) ret = 0;
				else{
					ret = rek(pos + 1, still_max && (val[pos] == max_num_pos), true);
				}
			}
			else{
				// special case where 0 exist!
				if(pos == n - 1){
					if(ar[pos].compatible(SEG[0])){
						ret = rek(pos + 1, still_max && (0 == max_num_pos), true);
					}
				}
				
				// it still can be empty segment!!!
				else if(ar[pos].compatible(EmptySegment)){
					ret = rek(pos + 1, false, false);
				}
				
				for(int i = 1;i <= max_num_pos; ++i){
					if(ar[pos].compatible(SEG[i])){
						ret += rek(pos + 1, still_max && (i == max_num_pos), true);
						if(ret >= MOD) ret -= MOD;
					}
				}
			}
		}
		else{
			
			if(val[pos] == -2){
				return 0;
			}
			
			int max_num_pos = still_max ? max_num[pos] : TOTAL_SEGMENT - 1;
			if(val[pos] != -1){
				if(val[pos] > max_num_pos) ret = 0;
				else{
					ret = rek(pos + 1, still_max && (val[pos] == max_num_pos), already_start);
				}
			} 
			else{
				for(int i = 0;i <= max_num_pos; ++i){
					if(ar[pos].compatible(SEG[i])){
						ret += rek(pos + 1, still_max && (i == max_num_pos), already_start);
						if(ret >= MOD) ret -= MOD;
					}
				}	
			}
		}
	}

	return dp[pos][still_max][already_start];
}

void precheck(){
	
	int lenNum = strlen(num);
	int lenN = n;
	
	start_n = max(0, lenN - lenNum);
	start_num = max(0, lenNum - lenN);
	
	for(int i = start_n; i < n; ++i){
		if(correct[i] - '0'){
			bool ketemu = false;
			for(int j = 0;j < TOTAL_SEGMENT && !ketemu; ++j){
				if(ar[i] == SEG[j]) {
					ketemu = true;
					val[i] = j;
				}
			}
			
			if(ar[i] == EmptySegment){
				ketemu = true;
				val[i] = -2;
			}
			
			if (!ketemu){
				puts("0");
				exit(0);
			}
		}
	}
	
	/* checking for pre-correct string*/
	for(int i = 0; i < start_n; ++i){
		if(ar[i] == EmptySegment) continue;
		puts("0");
		exit(0);
	}
	
	if(start_num > 0){
		maks_from_awal = false;
	}
}

int main(){
	setup();
	precheck();
	printf("%d\n", rek(start_n, maks_from_awal, false));
	return 0;
}
