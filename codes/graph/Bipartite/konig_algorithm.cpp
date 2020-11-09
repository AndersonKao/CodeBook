#include <vector>
#include <cstring>
using namespace std;

vector<int> V[205];
// V[i]記錄了左半邊可以配到右邊的那些點
int match[205]; // A<=B
// match[i] 記錄了右半邊配對到左半邊的哪個點
bool used[205];
int n;
bool dfs(int v)
{
    for(int e:V[v])
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
int konig()
{
    memset(match,-1,sizeof(match));

    int ans=0;
    
    for(int i=1;i<=n;++i)
    {
        memset(used, 0, sizeof(used));
        if( dfs(i) )
            ans++;
    }

    return ans;
}