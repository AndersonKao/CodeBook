#define MAXN 200005
int N = MAXN;
int pa[31][MAXN]; // pa(i, u), vertex u's 2^i ancestor.
void ComputeP()
{
    for (int i = 1; i < lgN; ++i)  // i = 0 is pre-built
    {
        for (int x = 0; x < N; ++x)
        {
            pa[i][x] = (pa[i - 1][x] == -1 ? -1 : pa[i - 1][pa[i - 1][x]]);
        }
    }
}
/* Binary Search Version */
int D[MAXN], L[MAXN];
vec<vec<int>> G;
int tstamp = 0;
// call this first
void DFS(int u, int pa){
    D[u] = tstamp++;
    for(int v: G[u]){
        if( v == pa ) continue;
        DFS(v, u);
    }
    L[u] = tstamp++;
}
bool isPa(int u, int v){
    return D[u] <= D[v] && L[u] >= D[v];
}

int LCA(int u, int v){
    if(isPa(u,v))
        return u;
    if(isPa(v,u))
        return v;
    for (int i = 30; i >= 0; i--){
        if(pa[i][u] != -1 && !isPa(pa[i][u], v))
            u = pa[i][u];
    }
    return pa[0][u];
}


/* jump up version */
int D[MAXN]; // depth
int LCA(int u, int v)
{
    if (D[u] > D[v])
        swap(u, v);
    int s = D[v] - D[u]; 
    for (int i = 0; i < 31; ++i) // adjust to same depth
        if (s & (1 << i))
            v = pa[i][v];

    if (u == v) 
        return v; 

    // because they are at same depth
    // jump up if they are different
    // think about that if P[u][i] == P[v][i]
    // then that point must be the ancestor of LCA or LCA itself
    // by this, we will stop at LCA's child
    for (int i = 31 - 1; i >= 0; --i)
        // 
        if (pa[i][u] != pa[i][v])
        {
            u = pa[i][u];
            v = pa[i][v];
        }
    return pa[0][u];
}


