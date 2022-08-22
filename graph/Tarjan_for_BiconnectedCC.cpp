void DFS(int v, int fa) { //call DFS(v,v) at first
    D[v] = L[v] = timestamp++; //timestamp > 0
    st.emplace(v);

    for (int w:adj[v]) {
        if( w==fa ) continue;
        if ( !D[w] ) { // D[w] = 0 if not visited
            DFS(w,v);
            L[v] = min(L[v], L[w]);
            if (L[u] >= D[v]) { // 找到割點!
            	int x;
                bcc.push_back({});
                do {
                    x = st.top(); st.pop();
                    bcc.back().emplace_back(x);
                } while (x!=v);
                st.push(v); // 把割點擺回去
            }
        }
        L[v] = min(L[v], D[w]);
    }

    return ;
} // 用完我 stack 要記得清乾淨!!