#include <vector>
#include <queue>
#include <utility>
using namespace std;
#define enp pair<int, int> // pair<edge_val, node>
int prim_pq(vector<vector<enp>> E){
    vector<bool> vis;
    vis.resize(E.size(), false);
    vis[0] = true;
    priority_queue<enp> pq;
    for(auto e: E[0]){
        pq.emplace(-e.first, e.second);
    }
    int ans = 0; // min value for MST
    while(pq.size()){
        int w, v; // edge-weight, vertex index
        tie(w, v) = pq.top();
        pq.pop();
        if(vis[v])
            continue;
        w = -w;
        vis[v] = true;
        ans += w;
        for(auto e: E[v]){
            pq.emplace(-e.first, e.second);
        }
    }
    return ans;
}
