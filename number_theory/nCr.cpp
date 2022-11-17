const int MAX = 3000005;
const ll mod = 998244353;

ll fact[MAX], tcaf[MAX]; // tcaf[a] = fact[a]^-1 mod n

ll binpow(ll x, ll d, ll m = mod) {
    if (d < 0) d += mod - 1;

    ll y = 1;
    do{
        if (d & 1) (y *= x) %= mod;
        (x *= x) %= mod;
    } while (d >>= 1);

    return y;
}

// Call this first.
void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = i * fact[i - 1] % mod;
    for (int i = n; i >= 0; --i)
        tcaf[i] = binpow(fact[i], -1);
}

// Invoke nCr via this.
ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * tcaf[r] % mod * tcaf[n - r] % mod;
}
