const int MAX = 3000005;
const ll MOD = 998244353;

ll fact[MAX], tcaf[MAX]; // tcaf[a] = fact[a]^-1 mod n

ll binpow(ll x, ll d) {
    if (d < 0) d += MOD - 1;

    ll y = 1;
    do{
        if (d & 1) (y *= x) %= MOD;
        (x *= x) %= MOD;
    } while (d >>= 1);

    return y;
}

// Call this first.
void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = i * fact[i - 1] % MOD;
    for (int i = n; i >= 0; --i)
        tcaf[i] = binpow(fact[i], -1);
}

// Invoke nCr via this.
ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * tcaf[r] % MOD * tcaf[n - r] % MOD;
}
