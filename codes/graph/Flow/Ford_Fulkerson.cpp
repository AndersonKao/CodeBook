#include <vector>
#include <tuple>
#include <cstring>
using namespace std;

// O((V+E)F)
#define maxn 101
// remember to change used into the maxNode size -- kattis elementary math
bool used[maxn];
int End;
vector<int> V[maxn];
vector<tuple<int, int>> E;

// x=>y 可以流 C 
// if undirected or 2-direc edge, bakcward Capacity become C;
// Graph build by edge array
// 反向邊的編號只要把自己的編號 xor 1 就能取得
void add_edge(int x, int y,int c)
{
    V[x].emplace_back( E.size() );
    E.emplace_back(y,c);
    V[y].emplace_back( E.size() );
    E.emplace_back(x,0);
}
int dfs(int v, int f)
{
    if( v==End ) return f;
    used[v] = true;
    int e,w;
    for( int eid : V[v] )
    {
        tie(e,w) = E[eid];
        if( used[e] || w==0 ) continue;
        
        w = dfs(e, min(w,f));
        if( w>0 )
        {
            // 更新流量
            get<1>(E[eid  ]) -= w;
            get<1>(E[eid^1]) += w;
            return w;
        }
    }
    return 0;// Fail!
}
int ffa(int s,int e)
{
    int ans = 0, f;
    End = e;
    while(true)
    {
        memset(used, 0, sizeof(used));
        f = dfs(s, INT_MAX);
        if( f<=0 ) break;
        ans += f;
    }
    return ans;
}
