#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

#define con pair<int, int> // first for distance, second for index


vector<vector<con>> Graph; //
vector<int> dis; // distance;
int main(){
    int N;
    cin >> N;
    int T;
    cin >> T;
    Graph.resize(N);
    dis.resize(N, 1000000);
    while(T--){
        int u, v, w;
        cin >> u >> v >> w;
        Graph[u].emplace_back(w, v);
        // Graph[v].emplace_back(u, w);
    }
    for (int i = 0; i < N; i++){
        cout << i << ": \n";
        for(auto it : Graph[i]){
            cout << it.second << " " << it.first << endl;
           
        }
    }
        priority_queue<con> pq;
    pq.emplace(con(dis[0] = 0, 0));

    while(pq.size()){
        con cur = pq.top();
        pq.pop();
        if(dis[cur.second] != cur.first)
            continue;
        cout << "useing " << cur.second << '\n';
        for(auto it: Graph[cur.second]){
            if(cur.first + it.first < dis[it.second]){
                dis[it.second] = cur.first + it.first;
                pq.push(con(dis[it.second], it.second));
            }
        }
    }
    for (int i = 0; i < N; i++)
        cout << dis[i] << " ";
    cout << '\n';
    return 0;
}
/*
5
10
0 1 10
1 2 2
0 2 5
2 1 3
2 3 2
3 0 7
1 4 1
4 3 4
3 4 6
2 4 9
*/