#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

#define con pair<int, int> // first for distance, second for index
vector<vector<con>> Graph; //
vector<int> dis; // distance;
int main(){
    priority_queue<con, vector<con>, greater<con>> pq;
    dis[0] = 0;
    pq.emplace(con(0, 0));
    while(pq.size()){
        con cur = pq.top();
        pq.pop();
        if(cur.first != dis[cur.second])
            continue;
        for(auto it: Graph[cur.second]){
            if(cur.first + it.first < dis[it.second]){
                dis[it.second] = cur.first + it.first;
                pq.emplace(dis[it.second], it.second);
            }
        }         
    }
    return 0;
}