// T for Text, P for Pattern
vec<int> KMP(const string& P) {
    vec<int> f(P.size(), -1);
    int len = f[0] = -1;
    for (int i = 1; i < P.size(); ++i) {
        while (len != -1 && P[len + 1] != P[i])
            len = f[len];
        if (P[len + 1] == P[i])
            ++len;
        f[i] = len;
    }
    return f;
}

// find S in T
vec<int> KMP_match(vec<int> fail, const string& S, const string& T) {
    vec<int> res; // start from these points
    int n = S.size();

    int i = -1;
    for (int j = 0; j < T.size(); ++j) {
        while (i != -1 && T[j] != S[i + 1]) 
            i = fail[i];

        if (T[j] == S[i + 1]) i++;
        if (i == n - 1) 
            res.eb(j - n + 1), i = fail[i];
    }
    
    return res;
}