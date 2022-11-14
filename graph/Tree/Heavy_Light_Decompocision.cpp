//subT[v] : 以v為根的子樹節點數，要先預處理
//linkR[v] : v所在的長鏈中最靠近root的節點
//linkP[v] : v與linkR[v]的距離
void HLD(int root) {
	linkR[root] = root;
	linkP[root] = 0;
	queue<int> Q;
	Q.emplace(root);
	
	while(!Q.empty()) {
		int v = Q.front(); Q.pop();
		pii res(-1, -1);
		for(auto &e : Tree[v]) {
			if(linkP[e] != -1) continue;
			if(subT[e] > res.first) res = pii(subT[e], e);
			Q.emplace(e);
		}
		
		
		if(res.second == -1) continue;
		linkR[res.second] = linkR[v];
		linkP[res.second] = linkP[v] + 1;
		
		for(auto &e : Tree[v]) {
			if(linkP[e] != -1) continue;
			linkR[e] = e;
			linkP[e] = 0;
		}
	}
}