#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

#define con pair<int, int> // first for distance, second for index


vector<vector<con>> Graph; //
vector<int> dis; // distance;
int main(){
    priority_queue<con> pq;
    pq.emplace(con(dis[0] = 0, 0));

    while(pq.size()){
        con cur = pq.top();
        pq.pop();
        for(auto it: Graph[cur.second]){

            if(dis[it.second] != it.first) continue;
            dis[it.second] = min(dis[it.second], cur.first + it.first);
            pq.push(con(dis[it.second], it.second));
        }
    }
    return 0;
}