ll generator (ll p) {
    vector<ll> fact;
    ll phi = p-1,  n = phi;
    for (ll i=2; i*i<=n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (ll res=2; res<=p; ++res) {
        bool ok = true;
        for (size_t i=0; i<fact.size() && ok; ++i)
            ok &= binpow (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}
