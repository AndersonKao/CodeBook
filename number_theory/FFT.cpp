using cd = complex<double>;
const double PI = acos(-1);

void fft(vec<cd>& a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

// if doing on real number polynomial, just change int to double. And check real() >= eps ? real() : 0 at line 62 (generating result)
vec<ll> multiply(vec<ll> const& a, vec<ll> const& b) {
    vec<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = fa[i] * fb[i]; // NTT: fa[i] * fb[i] % mod;
    fft(fa, true);

    vec<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real()); // NTT: result[i] = fa[i];

    //* if multiplying two number
    /*
    int carry = 0;
    for (int i = 0; i < n; i++) {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    */
        
    return result;
}

int main() {
    string sa,sb;
    cin >> sa >> sb;

    int na = sa.size(), nb = sb.size();
    vec<int> a(na, 0), b(nb, 0);  //* vector from LSB to MSB.
	
    for(int i = 0; i < na; i++) a[i] = sa[na - 1 - i] - '0';
    for(int i = 0; i < nb; i++) b[i] = sb[nb - 1 - i] - '0';
    
    vec<int> res = multiply(a, b);
    for(int i = res[na + nb - 1] ? na + nb - 1: na + nb - 2; i >= 0; i--)
       cout << res[i];
}

//! compute the coefficients modulo some prime number p.
/*
|   p = a * 2^b + 1   | a   | b   | prime factor |
|:-------------------:| --- | --- |:------------:|
|          3          | 1   | 1   |      2       |
|          5          | 1   | 2   |      2       |
|         17          | 1   | 4   |      3       |
|         97          | 3   | 5   |      5       |
|         193         | 3   | 6   |      5       |
|         257         | 1   | 8   |      3       |
|        7681         | 15  | 9   |      17      |
|        12289        | 3   | 12  |      11      |
|        40961        | 5   | 13  |      3       |
|        65537        | 1   | 16  |      3       |
|       786433        | 3   | 18  |      10      |
|       5767169       | 11  | 19  |      3       |
|       7340033       | 7   | 20  |      3       |
|      23068673       | 11  | 21  |      3       |
|      104857601      | 25  | 22  |      3       |
|      167772161      | 5   | 25  |      3       |
|      469762049      | 7   | 26  |      3       |
|      998244353      | 119 | 23  |      3       |
|     1004535809      | 479 | 21  |      3       |
|     2013265921      | 15  | 27  |      3       |
|     2281701377      | 17  | 27  |      3       |
|     3221225473      | 3   | 30  |      5       |
|     75161927681     | 35  | 31  |      3       |
|     77309411329     | 9   | 33  |      7       |
|    206158430209     | 3   | 36  |      22      |
|    2061584302081    | 15  | 37  |      7       |
|    2748779069441    | 5   | 39  |      3       |
|    6597069766657    | 3   | 41  |      5       |
|   39582418599937    | 9   | 42  |      5       |
|   79164837199873    | 9   | 43  |      5       |
|   263882790666241   | 15  | 44  |      7       |
|  1231453023109121   | 35  | 45  |      3       |
|  1337006139375617   | 19  | 46  |      3       |
|  3799912185593857   | 27  | 47  |      5       |
|  4222124650659841   | 15  | 48  |      19      |
|  7881299347898369   | 7   | 50  |      6       |
|  31525197391593473  | 7   | 52  |      3       |
| 180143985094819841  | 5   | 55  |      6       |
| 1945555039024054273 | 27  | 56  |      5       |
| 4179340454199820289 | 29  | 57  |      3       |

*/

ll inverse(ll a, ll m){ // returns a^-1 mod m, 0 if not found
    ll x, y;
    ll g = ext_gcd(a, m, x, y);

    if (g != 1) {
        return 0;
    }
    else {
        x = (x % m + m) % m;
        return x;
    }
}
// const_a, root_pw, prime_factor need to adjust by prime number
const ll mod = 7340033;
const ll const_a = 7;
const ll root_pw = 1 << 20;
const ll prime_factor = 3; // or call generator(mod).
const ll root = binpow(prime_factor, const_a);
const ll root_1 = inverse(root, mod);

void fft(vector<ll> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i+j], v = (1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        ll n_1 = inverse(n, mod);
        for (ll & x : a)
            x = (1LL * x * n_1 % mod);
    }
}
