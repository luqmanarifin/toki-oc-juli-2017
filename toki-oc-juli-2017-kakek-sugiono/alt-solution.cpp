#include <cstdio>

typedef long long LL;
const int N = 1e9, MOD = 1e9 + 7;

LL sqr(LL x, int mod = MOD){
	return (x * x) % MOD;
}

LL modpow(int x, int y, int mod){
	if(y == 0) return 1;
	if(y == 1) return (x % mod);
	LL tmp = sqr(modpow(x, y >> 1, mod));
	if (y & 1) tmp = (tmp * x) % mod;
	return tmp;
}

int main(){

	int n;
	scanf("%d", &n);
	if(n == 0){
		puts("1");
	}
	else{
		printf("%lld\n", modpow(2, n-1, MOD));
	}
	return 0;
}