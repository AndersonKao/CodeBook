struct edge
{
    int u, v;
    bool is_bridge;
    edge(int u = 0, int v = 0) : u(u), v(v), is_bridge(0) {}
};

vector<int> G[maxn]; // 1-base
vector<edge> E;
vector<int> nG[maxn], bcc[maxn];
int low[maxn], dfn[maxn], Time;
int bcc_id[maxn], bcc_cnt; // 1-base
bool is_cut[maxn];         // whether is av
bool cir[maxn];
int st[maxn], top;

void bcc_init(int n)
{
    Time = bcc_cnt = top = 0;
    for (int i = 1; i <= n; ++i)
        G[i].clear(), dfn[i] = bcc_id[i] = is_cut[i] = 0;
}

inline void add_edge(int u, int v)
{
    G[u].push_back(E.size());
    G[v].push_back(E.size());
    E.push_back(edge(u, v));
}

void dfs(int u, int pa = -1)// call dfs(u) for all unvisited node
{ 
    int child = 0;
    low[u] = dfn[u] = ++Time;
    st[top++] = u;
    for (int eid : G[u])
    {
        int v = E[eid].u ^ E[eid].v ^ u;
        if (!dfn[v])
        {
            dfs(v, u), ++child;
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v])
            {
                is_cut[u] = true; // 結 論 2 對於除了 root 點以外的所有點 v，v 點在 G 上為 AP 的充要條件為其在 T 中至少有一個子節點 w 滿足 dfn(v) ≤ low(w)
                // getting bcc
                bcc[++bcc_cnt].clear();
                int t;
                do
                {
                    bcc_id[t = st[--top]] = bcc_cnt;
                    bcc[bcc_cnt].push_back(t);
                } while (t != v);
                bcc_id[u] = bcc_cnt;
                bcc[bcc_cnt].eb(u);
            }
        }
        else if (dfn[v] < dfn[u] && v != pa) // !=pa vary important
            low[u] = min(low[u], dfn[v]);
    }
    if (pa == -1 && child < 2)
        is_cut[u] = false;
}

void bcc_solve(int n)
{
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            dfs(i);
    // block-cut tree
    for (int i = 1; i <= n; ++i)
        if (is_cut[i])
            bcc_id[i] = ++bcc_cnt, cir[bcc_cnt] = 1;
    for (int i = 1; i <= bcc_cnt && !cir[i]; ++i)
        for (int j : bcc[i])
            if (is_cut[j])
                nG[i].pb(bcc_id[j]), nG[bcc_id[j]].pb(i);
}