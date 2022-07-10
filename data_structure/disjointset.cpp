#include <algorithm>
using namespace std;
#define MAX_N 200005
struct  disjointset
{
    int rank[MAX_N];
    int f[MAX_N];
    void init(int N){
        for (int i = 0; i < N;i++){
            f[i] = i;
            rank[i] = 1;
        }
            
    }
    int find(int v){
        if( f[v] == v)
            return v;
        return f[v] = find(f[v]);
    }
    bool same(int a, int b){
        return find(a) == find(b);
    }
    void Union(int a, int b){
        // f[find(a)] = find(b);
        if(!same(a,b)){
            if(rank[a] < rank[b])
                swap(a, b);
            f[f[b]] = f[a];
            rank[a]++;
        }
    }
};
