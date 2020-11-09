#include <tuple>
#include <vector>
#include <algorithm>
#include <numeric> // for iota(first, last, val) setting iterator value
using namespace std;

struct DSU // disjoint set no rank-comp-merge
{
    vector<int> fa;
    DSU(int n) : fa(n) { iota(fa.begin(), fa.end(), 0); } // auto fill fa from 0 to n-1
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    void merge(int x, int y) { fa[find(x)] = find(y); }
};
int kruskal(int V, vector<tuple<int, int, int>> E) // save all edges into E, instead of saving graph via adjacency list
{
    sort(E.begin(), E.end()); 
    DSU dsu(V);
    int mcnt = 0;
    int ans = 0;
    for (auto e : E)
    {
        int w, u, v; // w for start, u for des, v for val
        tie(w, u, v) = E;
        if (dsu.find(u) == dsu.find(v))
            continue;
        dsu.merge(u, v);
        ans += w;
        if (++mcnt == V - 1)
            break;
    }
    return ans;
}
