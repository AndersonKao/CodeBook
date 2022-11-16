struct CostFlow {
    static const int MAXN = 350;
    const ll INF = 1ll<<60;
    
    struct Edge {
        int to, r;
        ll rest, c;
        
        Edge() {}
        Edge(int to, int r, ll rest, ll c) : to(to), r(r), rest(rest), c(c) {}
    };

    int n, pre[MAXN], preL[MAXN];
    bool inq[MAXN];
    ll dis[MAXN], fl, cost;
    vec<Edge> G[MAXN];
    
    void init() {
        for (int i = 0; i < MAXN; i++) G[i].clear();
    }
    
    void add_edge(int u, int v, ll rest, ll c) {
        G[u].eb(v, G[v].size(), rest, c);
        G[v].eb(u, G[u].size()-1, 0, -c);
    }
    
    p<ll> flow(int s, int t) {
        fl = cost = 0;
        
        while (true) {
            fill(dis, dis+MAXN, INF);
            fill(inq, inq+MAXN, 0);
            dis[s] = 0;
            
            queue<int> que;
            que.emplace(s);
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                
                inq[u] = 0;
                for (int i = 0; i < G[u].size(); i++) {
                    int v = G[u][i].to;
                    ll w = G[u][i].c;
                    
                    if (G[u][i].rest > 0 and dis[v] > dis[u] + w) {
                        pre[v] = u;
                        preL[v] = i;
                        dis[v] = dis[u] + w;
                        if (!inq[v]) {
                            inq[v] = 1;
                            que.emplace(v);
                        }
                    }
                }
            }
            
            if (dis[t] == INF) break;
            ll tf = INF;
            for (int v = t, u, l; v != s; v = u) {
                u = pre[v]; l = preL[v];
                tf = min(tf, G[u][l].rest);
            }
            
            for (int v = t, u, l; v != s; v = u) {
                u = pre[v]; l = preL[v];
                G[u][l].rest -= tf;
                G[v][G[u][l].r].rest += tf;
            }
            
            cost += tf * dis[t];
            fl += tf;
        }
        
        return {fl, cost};
    }
};