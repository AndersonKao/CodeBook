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
