// by atsushi
// sccID[u] will be a REVERSED topological sort order of each SCC
class tarjan_for_SCC{
private:
    vector<vector<int>> G; // adjacency list
    vector<int> D;
    vector<int> L;
    vector<int> sccID;
    stack<int> st; // for SccID
    vector<bool> inSt;
    vector<vector<int>> reG;
    int timeStamp, sccIDstamp;
public:
    void init(int size = 1){
        G.clear();
        G.resize(size + 3);
        D.clear();
        D.resize(size + 3, 0);
        L.clear();
        L.resize(size + 3, 0);
        sccID.clear();
        sccID.resize(size + 3, 0);
        while(!st.empty())
            st.pop();
        inSt.clear();
        inSt.resize(size + 3, false);
        reG.clear();
        sccIDstamp = timeStamp = 1;
    }
    void addEdge(int from, int to){
        G[from].emplace_back(to);
    }
    void DFS(int v, int pa){ //call DFS(v,v) at first
        D[v] = L[v] = timeStamp++; //timestamp > 0
        st.push(v);
        inSt[v] = true;

        for(int w: G[v]){ // directed graph don't need w == pa
            if(!D[w]){ // D[w] = 0 if not visited
                DFS(w, v);
                L[v] = min(L[v], L[w]);
            }else if(inSt[w])
            { /* w has been visited.
                if we don't add this, the L[v] will think that v can back to node whose index less to v.
                inSt[w] is true that v -> w is a cross edge
                opposite it's a forward edge
            */
                L[v] = min(L[v], D[w]); // why D[w] instead of L[w]??
            }
        }
        if(D[v] == L[v]){
            int w;
            do{
                w = st.top();
                st.pop();
                sccID[w] = sccIDstamp; // scc ID for this pooint at which SCC
                inSt[w] = false;
            } while (w != v);
            sccIDstamp++;
        }
    }
    // generate induced graph.
    void generateReG(int N = 1){
        reG.clear();
        reG.resize(sccIDstamp);
        for (int i = 1; i <= N; i++){
            for(int w: G[i]){
                if(sccID[i] == sccID[w])
                    continue;
                reG[sccID[i]].emplace_back(sccID[w]);
            }
        }
    }
    bool visited(int v){
        return D[v];
    }
};