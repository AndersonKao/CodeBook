// Tree_Centroid
vector<int> G[20000];
int N;
int centroid;
int centroid_subtree_sz;
int tree_centroid(int u, int pa)
{
    int sz = 1; // tree size of u.
    int maxsub = 0; // max subtree size of u

    for(int v:G[u])
    {
        if (v==pa)continue;
        int sub = tree_centroid(v, u);
        maxsub = max(maxsub, sub);
        sz += sub;
    }
    maxsub = max(maxsub, N-sz);

    if (maxsub <= N/2)
    {
        centroid = u;
        centroid_subtree_sz = maxsub;
    }
    return sz;
}
