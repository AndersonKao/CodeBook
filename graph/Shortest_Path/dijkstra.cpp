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