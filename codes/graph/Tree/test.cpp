#include <cmath>
#include <algorithm>
using namespace std;
#define MAXN 200005
#define MAXLOG 200
int N = MAXN;
int lgN = log(N) / log(2);
int D[MAXN];
int P[MAXLOG][MAXLOG];
int LCA(int u, int v)
{
    if (D[u] > D[v])
        swap(u, v);
    int s = D[v] - D[u]; // adjust D until D[v] = D[u]
    for (int i = 0; i <= lgN; ++i)
        if (s & (1 << i))
            v = P[v][i];
    if (u == v) 
        return v; 
    // because they are at same depth
    // jump up if they are different
    // think about that if P[u][i] == P[v][i]
    // then that point must be the ancestor of LCA or LCA itself
    // by this, we will stop at LCA's child
    for (int i = lgN; i >= 0; --i)
        // 
        if (P[u][i] != P[v][i])
        {
            u = P[u][i];
            v = P[v][i];
        }
    return P[u][0];
}

void ComputeP()
{
    int n = N;
    for (int i = 0; i < lgN; ++i) // to lgN enough
    {
        for (int x = 0; x < n; ++x)
        {
            if (P[x][i] == -1)
                P[x][i + 1] = -1;
            else
                P[x][i + 1] = P[P[x][i]][i]; // equal to move on the parent direction
                // And P[x][i] move 2 ^ n steps to a parent we call it y
                // P[y][i] means continue move 2 ^ n step from y to a parent we call z
                // so the total equal to move 2 ^ n * 2 ^ n steps from x to z
                // which is move 2 ^ (n + 1) steps to z
        }
    }
}