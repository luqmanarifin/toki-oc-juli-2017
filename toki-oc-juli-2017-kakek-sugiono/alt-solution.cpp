#include <cstdio>

typedef long long LL;
const int N = 1e3, MOD = 1e9 + 7;

LL fact[N + 5];
LL modpowfact[N + 5];

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
inline void precompute(){
	fact[0] = 1;
	fact[1] = 1;
	modpowfact[0] = modpowfact[1] = 1;
	for(int i = 2;i <= N; ++i){
		fact[i] = fact[i - 1] * i;
		fact[i] %= MOD;
		modpowfact[i] = modpow(fact[i], MOD - 2, MOD);
	}
}

int main(){
	precompute();
	int n;
	scanf("%d", &n);
	LL total = 0;
	for(int i = 0;i <= n; i += 2){
		total += (((fact[n] * modpowfact[n - i]) % MOD) * sqr(modpowfact[i/2])) % MOD;
		total %= MOD;
	}
	printf("%lld\n", total);
	return 0;
}