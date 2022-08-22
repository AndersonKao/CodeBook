// Cassini's identity : F_{n-1} F_{n+1} - F_n^2= (-1)^n
// The "addition" rule : F_{n+k} = F_k * F_{n+1} + F_{k-1} * F_n
// k = n, F_{2n} = F_n * (F_{n+1} + F_{n-1})
// F_{2k} = F_k * (2F_{k+1} - F_k)
// F_{2k+1} =  F_k^2 + F_{k+1}^2

// return fib(n), fib(n+1).
pair<int, int> fib (int n) {
    if (n == 0)
        return {0, 1};
    auto p = fib(n >> 1);
    int c = p.first * (2 * p.second - p.first);
    int d = p.first * p.first + p.second * p.second;
    if (n & 1)
        return {d, c + d};
    else
        return {c, d};
}
