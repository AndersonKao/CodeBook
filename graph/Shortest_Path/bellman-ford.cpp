vector<tuple<int, int, int>> edges;
vector<int> dis;
const int inf = 0x3f3f3f3f;
// return true if contain cycles
bool Bellman_Ford()
{
    int V; // # of vertices
    int E = edges.size();
    dis.resize(V, inf);
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