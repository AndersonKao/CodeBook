vector<vector<pii>> G; // (w, v)
vector<int> dis;
const int inf = 0x3f3f3f3f;

void SPFA(int src){
    int V = G.size();
    dis.resize(V, inf);
    vector<bool> inq(V, false);
    vector<int> Q;
    dis[src] = 0, inq[src] = true, Q.push(src);
    while(q.size()){
        int u = Q.front();
        inq[u] = false, Q.pop();
        for(pii& e: G[u]){
            int w, v;
            tie(w, v) = e;
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                if(inq[v] == false)
                    Q.push(v);
                inq[v] = true;
            }
        }
    }
}
