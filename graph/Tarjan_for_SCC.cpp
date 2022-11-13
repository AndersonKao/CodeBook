// by atsushi
// sccID[u] will be a REVERSED topological sort order of each SCC
struct tarjan_for_SCC{
    vector<vector<int>> G; // adjacency list
    vector<int> D;
    vector<int> L;
    vector<int> sccID;
    stack<int> st; // for SccID
    vector<bool> inSt;
    vector<vector<int>> conG; // contracted graph
    int timeStamp, sccNum;
    void init(int n = 1){
        G.assign(n, vec<int>());
        D.assign(n, 0);
        L.assign(n, 0);
        sccID.assign(n, 0);
        inSt.assign(n, false);
        while(!st.empty())
            st.pop();
        conG.clear();
        sccNum = timeStamp = 0;
    }
    void addEdge(int from, int to){
        G[from].eb(to);
    }
    void DFS(int u){ //call DFS(u) for all unvisited vertex 
        D[u] = L[u] = ++timeStamp; //timestamp > 0
        st.push(u);
        inSt[u] = true;

        for(int v: G[u]){ 
            if(!D[v]){ // D[v] = 0 if not visited
                DFS(v);
                L[u] = min(L[u], L[v]);
            }else if(inSt[v])
            { /* v has been visited.
                if we don't add this, the L[u] will think that u can back to node whose index less to u.
                inSt[v] is true that u -> v is a cross edge
                opposite it's a forward edge
            */
                L[u] = min(L[u], D[v]);
            }
        }
        if(D[u] == L[u]){
            int v;
            do{
                v = st.top(), st.pop();
                sccID[v] = sccNum, inSt[v] = false;
            } while (v != u);
            sccNum++;
        }
    }
    // generate induced graph.
    void generateReG(int N = 1){
        conG.assign(sccNum, vec<int>());
        for (int i = 1; i <= N; i++){
            for(int v: G[i]){
                if(sccID[i] == sccID[v])
                    continue;
                conG[sccID[i]].emplace_back(sccID[v]);
            }
        }
    }
};