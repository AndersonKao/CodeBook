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

