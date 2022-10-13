const int maxn = 250;
// time complexity: O(EV), V times DFS
// G[i]記錄了左半邊可以配到右邊的那些點
/* bipartite graph be like..
0\ /-0
1-X--1
2/ \/2
3  /\3
4 /  4
5/   5
.    .
.    .
*/
// match[i] 記錄了右半邊配對到左半邊的哪個點
vec<int> G[maxn];
int match[maxn]; // A <=B
bool used[maxn];
bool dfs(int v)
{
    for(int e:G[v])
    {
        if( used[e] ) continue;
        used[e] = true;
        if( match[e] == -1 || dfs( match[e] ) )
        {
            match[e] = v;
            return true;               
        }
    }
    return false;
}
int konig(int n) // num of vertices of left side
{
    memset(match,-1,sizeof(match));

    int ans=0;
    
    for(int i=0;i<n;++i)
    {
        memset(used, 0, sizeof(used));
        if( dfs(i) )
            ans++;
    }

    return ans;
}
void addedge(int u, int v){ // left side, right side
    G[u].eb(v);
}