void SieveErato(){
    int n; // becase of ll
    vec<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}

// O((R-L+1)loglog(R) + sqrt(R)loglog(sqrt(R)))
vec<char> segmentedSieve(ll L, ll R) {
    // generate all primes up to sqrt(R)
    ll lim = sqrt(R);
    vec<char> mark(lim + 1, false);
    vec<ll> primes;
    for (ll i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.eb(i);
            for (ll j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    vec<char> isPrime(R - L + 1, true);
    for (ll i : primes)
        for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1)
        isPrime[0] = false;
    return isPrime;
}

// O((R-L+1)log(R) + sqrt(R))
vec<char> segmentedSieveNoPreGen(ll L, ll R) {
    vec<char> isPrime(R - L + 1, true);
    ll lim = sqrt(R);
    for (ll i = 2; i <= lim; ++i)
        for (ll j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1)
        isPrime[0] = false;
    return isPrime;
}
