// phi(n):= # of number in [1,n] s.t. co-prime to n.
/*
Theorems:
1. phi(p) = p-1 if p is a prime
2. phi(p^k) = p^k-p^{k-1} if p is a prime
3. phi(a*b) = phi(a)*phi(b) if gcd(a,b)=1.
*/
// O(sqrt(n))
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// by phi(n) = n*(1-1/p1)*(1-1/p2)*..
// O(nloglogn)
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

// Gauss phi's property: sum{phi(d) , for all d|n} = n.
// O(nlogn)
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i - 1;

    for (int i = 2; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
              phi[j] -= phi[i];
}
