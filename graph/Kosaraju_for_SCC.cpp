#include <vector>
#include <stack>
using namespace std;
#define MAX_N 200005
class Kosaraju_for_SCC{
    int NodeNum;
    vector<vector<int>> G;
    vector<vector<int>> GT;
    stack<int> st;
    vector<bool> visited;
    vector<int> scc;
    int sccID;

public:
    void init(int N){
        NodeNum = N;
        G.clear();
        G.resize(N + 5);
        GT.clear();
        GT.resize(N + 5);
        while(!st.empty())
            st.pop();
        visited.clear();
        visited.resize(N + 5, false);
        scc.clear();
        scc.resize(N + 5);
        sccID = 1;
    }
    void addEdge(int w, int v){
        G[w].emplace_back(v);
        GT[v].emplace_back(w);
    }
    void DFS(bool isG, int v, int k = -1){
        visited[v] = true;
        scc[v] = k;
        vector<vector<int>> &dG = (isG ? G : GT);
        for(int w: dG[v])
        {
            if(!visited[w]){
                DFS(isG, w, k);
            }
        }
        if(isG){
            st.push(v);
        }
    }
    void Kosaraju(int N){
        visited.clear();
        visited.resize(N + 5, false);
        for (int i = 1; i <= N; i++){
            if(!visited[i])
                DFS(true, i);
        }
        visited.clear();
        visited.resize(N + 5, false);
        while(!st.empty()){
            if(!visited[st.top()])
                DFS(false, st.top(), sccID++);
            st.pop();
        }
    }
    vector<vector<int>> generateReG(){
        vector<vector<int>> reG;
        reG.resize(sccID);
        for (int i = 1; i <= NodeNum; i++){
            for(int w: G[i]){
               if(scc[i] == scc[w])
                   continue;
               reG[scc[i]].emplace_back(scc[w]);
            }
        }
        return reG;
    }
};