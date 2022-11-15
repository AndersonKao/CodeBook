// scc[u] will be a topological sort order of each SCC
struct Kosaraju{
    int NodeNum;
    vector<vector<int>> G;
    vector<vector<int>> GT;
    stack<int> st;
    vector<bool> visited;
    vector<int> scc;
    int sccNum;

    void init(int N){
        NodeNum = N;
        G.assign(N, vec<int>());
        GT.assign(N, vec<int>());
        while(!st.empty())
            st.pop();
        visited.assign(N, false);
        scc.assign(N, 0);
        sccNum = 0;
    }
    void addEdge(int u, int v){
        G[u].eb(v);
        GT[v].eb(u);
    }
    void DFS(bool isG, int u, int sccID = -1){
        visited[u] = true;
        vector<vector<int>> &dG = (isG ? G : GT);
        for(int v: dG[u])
        {
            if(!visited[v]){
                DFS(isG, v, sccID);
            }
        }
        if(isG){
            st.push(u);
        }
        else{
            scc[u] = sccID;
        }
    }
    void run(){
        fill(al(visited), false);
        for (int i = 0; i < NodeNum; i++){
            if(!visited[i])
                DFS(true, i);
        }
        fill(al(visited), false);
        while(!st.empty()){
            if(!visited[st.top()])
                DFS(false, st.top(), sccNum++);
            st.pop();
        }
    }

    vector<vector<int>> reduceG(){ //call after run
        vector<vector<int>> reG;
        reG.resize(sccNum);
        for (int i = 0; i < NodeNum; i++){
            for(int w: G[i]){
               if(scc[i] == scc[w])
                   continue;
               reG[scc[i]].emplace_back(scc[w]);
            }
        }
        return reG;
    }
};
