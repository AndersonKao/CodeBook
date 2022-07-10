using i64 = long long;
#define maxn 300005
i64 fact[MAXN], tcaf[MAXN];

#define P 998244353
#define REP1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define REP(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
void init(int n){
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = i * fact[i - 1] % P;
    for (int i = n; i >= 0; --i)
        tcaf[i] = deg(fact[i], -1);
    
}
 
i64 deg(i64 x, i64 d) {
    if (d < 0) d += P - 1;
    i64 y = 1;
    while (d) {
        if (d & 1) (y *= x) %= P;
        d /= 2;
        (x *= x) %= P;
    }
    return y;
}
 
i64 cnk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * tcaf[k] % P * tcaf[n - k] % P;
}
 