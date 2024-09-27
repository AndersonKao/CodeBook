// Bellman-Ford
vector<tuple<int, int, int>> edges;
vector<int> dis;
const int inf = 0x3f3f3f3f;
// return true if contain cycles
bool Bellman_Ford(int src)
{
    int V, E = edges.size();
    dis.resize(V, inf); dis[src] = 0;
    for (int i = 0; i < V - 1; i++)
    {
        for (int j = 0; j < E; j++){
            int u, v, w;
            tie(u, v, w) = edges[j];
            if(dis[u] != inf && dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
            }
        }
    }
    for (int j = 0; j < E; j++){
        int u, v, w;
        tie(u, v, w) = edges[j];
        if(dis[u] != inf && dis[u] + w < dis[v]){
            return true;
        }
    }
    return false;
}

// dijkstra
vec<vec<p<int>>> Graph; // (w, v)
vec<int> dis; // distance result
void dijkstra(int u) {
    priority_queue<p<int>, vec<p<int>>, greater<p<int>>> pq;
    dis[u] = 0;
    pq.emplace(0, u);
    while(pq.size()){
        auto cur = pq.top();
        pq.pop();
        if(cur.first != dis[cur.second])
            continue;
        for (auto it: Graph[cur.second]){
            if (cur.first + it.first < dis[it.second]){
                dis[it.second] = cur.first + it.first;
                pq.emplace(dis[it.second], it.second);
            }
        }         
    }
}