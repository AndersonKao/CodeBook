// by atsushi
// sccID[u] will be a REVERSED topological sort order of each SCC
struct tarjan_for_SCC{
    vector<vector<int>> G; // adjacency list
    vector<int> dfn;
    vector<int> low;
    vector<int> sccID;
    stack<int> st; // for SccID
    vector<bool> inSt;
    vector<vector<int>> conG; // contracted graph
    int Time, sccNum;
    void init(int n = 1){ // 0-base
        G.assign(n, vec<int>());
        dfn.assign(n, 0);
        low.assign(n, 0);
        sccID.assign(n, 0);
        inSt.assign(n, false);
        while(!st.empty())
            st.pop();
        conG.clear();
        sccNum = Time = 0;
    }
    void addEdge(int from, int to){
        G[from].eb(to);
    }
    void dfs(int u){ //call DFS(u) for all unvisited vertex 
        dfn[u] = low[u] = ++Time; //timestamp > 0
        st.push(u);
        inSt[u] = true;

        for(int v: G[u]){ 
            if(!dfn[v]){ // dfn[v] = 0 if not visited
                dfs(v);
                low[u] = min(low[u], low[v]);
            }else if(inSt[v])
            { /* v has been visited.
                if we don't add this, the low[u] will think that u can back to node whose index less to u.
                inSt[v] is true that u -> v is a cross edge
                opposite it's a forward edge
            */
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u]){
            int v;
            do{
                v = st.top(), st.pop();
                sccID[v] = sccNum, inSt[v] = false;
            } while (v != u);
            sccNum++;
        }
    }
    // generate induced graph.
    void generateReG(){
        conG.assign(sccNum, vec<int>());
        for (int u = 0; u < G.size(); u++){
            for(int v: G[u]){
                if(sccID[u] == sccID[v])
                    continue;
                conG[sccID[u]].emplace_back(sccID[v]);
            }
        }
    }
};