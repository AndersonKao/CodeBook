// BCC for bridge connected component
// by sylveon a.k.a LFsWang
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
#define MAX_N 200005
int timestamp = 1;
int bccid = 1;
int D[MAX_N];
int L[MAX_N];
int bcc[MAX_N];
stack<int> st;
vector<int> adj[MAX_N];
bool inSt[MAX_N];

void DFS(int v, int fa) { //call DFS(v,v) at first
    D[v] = L[v] = timestamp++; //timestamp > 0
    st.emplace(v);

    for (int w:adj[v]) {
        if( w==fa ) continue;
        if ( !D[w] ) { // D[w] = 0 if not visited
            DFS(w,v);
            L[v] = min(L[v], L[w]);
        }
        L[v] = min(L[v], D[w]);
    }
    if (L[v]==D[v]) {
        bccid++;
        int x;
        do {
            x = st.top(); st.pop();
            bcc[x] = bccid;
        } while (x!=v);
    }
    return ;
}