// O(sqrt(n))
bool isPrime(int x) {
    for (int d = 2; d * d <= x; d++) {
        if (x % d == 0)
            return false;
    }
    return true;
}

// rely on Fermat's little theorem
// : a^(p-1) = 1(mod p) if p is a prime and gcd(a,p) = 1.
/*
Carmichael Number : if a^(n-1)=1(mod n) for every a prime to n. 
There exist only 646 Carmichael Number <= 10^9.
*/
bool probablyPrimeFermat(int n, int iter=5) {
    if (n < 4)
        return n == 2 || n == 3;

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (binpower(a, n - 1, n) != 1)
            return false;
    }
    return true;
}
//Miller Rabin for long long range
ull mul(ull a, ull b, ull m) {
	ull ans = 0;
	while(b>0) {
		if(b&1) {
			ans+=a;
			if(ans>=m) ans-=m; 
		}
		a<<=1, b>>=1;
		if(a>=m) a-=m;
	}
	return ans;
}

ull fpow(ull a, ull n, ull m) {
	if(n == 0) return 1;
	if(n%2 == 0) return fpow(mul(a, a, m), n/2, m);
	return mul(a, fpow(mul(a, a, m), n/2, m), m);
}

bool MillerRabin(ll n) {
	if(n == 2) return true;
	if(n<2 || n%2 == 0) return false;
	
	ll u = n-1, t = 0;
	while(u%2 == 0) u>>=1, t++;
	
	for(ll a : {2,3,5,7,11,13,17,19,23,29,31,37}) {
		if(n == a) return true;
		ll x = fpow(a, u, n);
		if(x == 1 || x == n-1) continue;
		
		for(int i=0;i<t;i++) {
			x = mul(x, x, n);
			if(x == 1) return false;
			if(x == n-1) break;
		}
		if(x == n-1) continue;
		return false;
	}
	return true;
}

//* --------- copy from cp-algorithm.

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}