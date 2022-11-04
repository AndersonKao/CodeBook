// 樹上依賴背包問題
// 上下界優化 Time complexity = O(NM)
// 另有Postorder 的順序做DP也能做到O(NM)
void dfs(int u)
{
    siz[u]=1;
    f[u][1]=a[u];
    int i,j,k,v;
    for (i=head[u];i;i=nxt[i])
    {
        v=to[i];
        dfs(v);
        for (j=min(m+1,siz[u]+siz[v]);j>=1;--j)
        {
            for (k=max(1,j-siz[u]);k<=siz[v]&&k<j;++k)
            {
                f[u][j]=max(f[u][j],f[u][j-k]+f[v][k]);
            }
        }
        siz[u]+=siz[v];
    }
}
