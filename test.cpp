#include <algorithm>
#include <cmath>
#include <utility>
#define MAXN 200005
using namespace std;
int n;
int lgN = log((double)n) / log(2);
int D[MAXN];
int P[MAXN][32 + 1];
int LCA(int u, int v) // query O(logN);
{
    if (D[u] > D[v])
        swap(u, v);
    int s = D[v] - D[u];
    for (int i = 0; i <= lgN; ++i)
        if (s & (1 << i)) // binary & to divide into binary sum ex. 8 + 0 + 2 + 1
            v = P[v][i];
    if (u == v)
        return v;
    for (int i = lgN; i >= 0; --i)
        if (P[u][i] != P[v][i])
        {
            u = P[u][i];
            v = P[v][i];
        }
    return P[u][0];
}

void ComputeP() // build O(NlogN)
{
    // P[x][0] is just pa[x];
    for (int i = 0; i < lgN; ++i)
    {
        for (int x = 0; x < n; ++x)
        {
            if (P[x][i] == -1)
                P[x][i + 1] = -1;
            else
                P[x][i + 1] = P[P[x][i]][i];
        }
    }
}
int oD[MAXN]; // subTSum;
int oP[MAXN]; // for parent
void oriLCA(int u, int v) // ordinary O(N)
{
    while(D[u] > D[v])
        u = oP[u];
    while(D[v] > D[u])
        v = oP[v];
    while(u != v){
        u = oP[u];
        v = oP[v];
    }
    return u;
}
