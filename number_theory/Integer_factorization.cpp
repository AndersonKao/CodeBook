// need to build prime vector first.
vec<ll> primes;

vec<ll> trial_division4(ll n) {
    vec<ll> fac;

    for (ll d : primes) {
        if (d * d > n)
            break;
        while (n % d == 0) {
            fac.eb(d);
            n /= d;
        }
    }
    if (n > 1)
        fac.eb(n);

    return fac;
}

// MOON
vector<int> primes;
vector<int> LPFs(n + 1, 1);
for (int i = 2; i < n; ++i) {
  if (LPFs[i] == 1) {
    LPFs[i] = i;
    primes.emplace_back(i);
  }
  for (auto p : primes) {
    if (1LL * i * p > n) break;
    LPFs[i * p] = i;
    if (i % p == 0) break;
  }
}

void print_prime_factor(int x) {
  while (x != 1) {
    int factor = SPFs[x], cnt = 0;
    for (; x % factor == 0; ++cnt)
      x /= factor;
    cout << factor << ": " << cnt << endl;
  }
}
