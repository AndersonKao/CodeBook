#include <utility>
#include <vector>
#include <algorithm>
using namespace std;


int subTsize[200005];
vector<int> adj[200005];
int n; // n for node num ??
pair<int, int> Tree_Centroid(int v, int pa)
{
    // return (最 大 子 樹 節 點 數 , 節 點ID)
    subTsize[v] = 1;
    pair<int, int> res(INT_MAX, -1); // ans: tree cnetroid
    int max_subT = 0; // 最大子樹節點數
    for (size_t i = 0; i < adj[v].size(); ++i)
    {
        int x = adj[v][i];
        if (x == pa)
            continue;
        res = min(res, Tree_Centroid(x, v));
        subTsize[v] += subTsize[x];
        max_subT = max(max_subT, subTsize[x]);
    }
    res = min(res, make_pair(max(max_subT, n - subTsize[v]), v)); // (n - subTsize[v]) for maybe parent tree is the biggest
    // min because all res will be greater than n/2;
    // the min one is the tree centroid
    return res;
}
