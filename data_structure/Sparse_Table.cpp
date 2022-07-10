#include <bits/stdc++.h>
using namespace std;
int n;
int v[1000009];
int sparse[22][1000009];
// O(nlogn) preprocess O(1)Query
// sp[x][y] is the answer from (v[x], v[x+2^y-1])
inline void init()
{
    for (int i = 0; i < n; ++i)
        sparse[0][i] = v[i];
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 0; i + (1 << j) <= n; ++i)
        sparse[j][i] = min(
        sparse[j - 1][i],
        sparse[j - 1][i + (1 << (j - 1)])
        );
}

inline int query(int l, int r)
{
    int k = __lg(r - l + 1);
    return min(sparse[k][l], sparse[k][r - (1 << k) + 1]);
}
