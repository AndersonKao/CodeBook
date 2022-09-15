vector<vector<pii>> G;
vector<int> dis; // distance;
void dijkstra(){
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dis[0] = 0;
    pq.emplace(pii(0, 0));
    while(pq.size()){
        pii cur = pq.top();
        pq.pop();
        if(cur.first != dis[cur.second])
            continue;
        for(auto it: G[cur.second]){
            if(cur.first + it.first < dis[it.second]){
                dis[it.second] = cur.first + it.first;
                pq.emplace(dis[it.second], it.second);
            }
        }         
    }
}