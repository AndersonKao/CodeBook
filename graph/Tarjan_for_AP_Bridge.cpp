#include <vector>
#include <utility>
using namespace std;
#define MAX_N 200005;
#define enp pair<int, int> // edge-weight, node-index
#define con pair<int, int> // connection

class tarjan{
    vector<vector<int>> G; // adjacency List
    vector<int> D;  // visit or visited and D-value
    vector<int> L;  // for L-value
    vector<con> edgeBridge;
    vector<int> APnode;
    int timestamp;
    tarjan(int size = 1){
        init(size);
    }
    void init(int size = 1){
        timestamp = 1;
				G.clear(), D.clear(), L.clear();
        G.resize(size);
        D.resize(size, 0);
        L.resize(size, 0);
        edgeBridge.clear();
        APnode.clear();
    }
    void addedge(int u, int v)
    {   // undirected graph
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void DFS(int v, int pa){ // init: call DFS(v,v)
        D[v] = L[v] = timestamp++;
        int Childcount = 0;
        bool isAP = false;
        for(int w: G[v]){
            if(w == pa)
                continue;
            if(!D[w]){ // 用 D[w] == 0 if not visited
                DFS(w, v);
                Childcount++;
                if(D[v] <= L[w])
                    isAP = true; // 結 論 2 對於除了 root 點以外的所有點 v，v 點在 G 上為 AP 的充要條件為其在 T 中至少有一個子節點 w 滿足 D(v) ≤ L(w)
                if(D[v] < L[w])
                    edgeBridge.emplace_back(v,w);// 結 論 3 對於包含 r 在內的所有點 v 和 v 在 T 中的子節點 w，邊 e(v, w) 在圖 G 中為bridge 的充要條件為 D(v) < L(w)。
                L[v] = min(L[v], L[w]);
            }
            L[v] = min(L[v], D[w]);
        }
        if(v == pa && Childcount < 2)
            isAP = false;
        if(isAP)
            APnode.emplace_back(v);
    }
};


