struct edge
{
    int u, v;
    bool is_bridge;
    edge(int u = 0, int v = 0) : u(u), v(v), is_bridge(0) {}
};

std::vector<edge> E;
std::vector<int> G[N]; // 1-base
int low[N], dfn[N], Time;
int bcc_id[N], bridge_cnt, bcc_cnt; // 1-base
int st[N], top;                     // BCC用

inline void add_edge(int u, int v)
{
    G[u].push_back(E.size());
    G[v].push_back(E.size());
    E.push_back(edge(u, v));
}

void dfs(int u, int pa)
{ // u當前點，re為u連接前一個點的邊
    int v;
    low[u] = dfn[u] = ++Time;
    st[top++] = u;
    for (size_t eid : G[u])
    {
        int v = E[eid].u ^ E[eid].v ^ u;
        if (!dfn[v])
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (dfn[u] < low[v])// 結 論 3 對於包含 r 在內的所有點 v 和 v 在 T 中的子節點 w，邊 e(v, w) 在圖 G 中為bridge 的充要條件為 dfn(v) < low(w)。
            {
                E[eid].is_bridge = 1;
                ++bridge_cnt;
            }
        }
        else if (dfn[v] < dfn[u] && v != pa)
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])   //處理BridgeCC
    {           
        do
            bcc_id[v = st[--top]] = bcc_cnt; //每個點所在的BCC
        while (v != u);
        ++bcc_cnt; // 1-base
    }
}
inline void bcc_init(int n)
{
    Time = bcc_cnt = bridge_cnt = top = 0;
    E.clear();
    for (int i = 1; i <= n; ++i)
    {
        G[i].clear();
        dfn[i] = 0;
        bcc_id[i] = 0;
    }
}