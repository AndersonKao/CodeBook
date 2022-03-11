#include <bits/stdc++.h>
using namespace std;
// O(V^2E) O(VE) finding argument path
// if unit capacity network then O(min(V^3/2, E^1/2) E)
// solving bipartite matching O(E V^1/2) better than konig and flow(EV)
#define MAXN 101
#define INT_MAX 10000000
int End, dist[MAXN];
vector<tuple<int, int, int>> V[MAXN];
// node-index, cap, the index of the reverse edge
void addEdge(int u, int v, int c){
    V[u].emplace_back(v, c, V[v].size());
    V[v].emplace_back(u, 0, V[u].size() - 1);
}
bool bfs(int s) {
    memset(dist, -1, sizeof(dist));
    queue<int> qu;
    qu.emplace(s);
    dist[s]=0;

    while( !qu.empty() ) {
        int S = qu.front(); qu.pop();
        for(auto &p : V[S]) {
            int E, C;
            tie(E, C, ignore) = p;
            if( dist[E]==-1 && C!=0 ) {
                dist[E]=dist[S]+1;
                qu.emplace(E);
            }
        }
    }
    return dist[End] != -1;
}
int dfs(int v, int f) { 
    int e,w,rev;
    if( v==End || f==0 ) return f;
    for( auto &t : V[v] )
    {
        tie(e,w,rev) = t;
        if( dist[e]!=dist[v]+1 || w==0 )
            continue;

        w = dfs(e, min(w,f));
        if( w>0 )
        {
            get<1>(t) -= w;
            get<1>(V[e][rev]) += w;
            return w;
        }
    }
    dist[v] = -1; //優化，這個點沒用了 
    return 0;// Fail!
}
int dinic(int s,int e)
{
    int ans = 0, f;
    End = e;
    while(bfs(s))
    {
        while( f = dfs(s, INT_MAX) )
            ans += f;
    }
    return ans;
}
