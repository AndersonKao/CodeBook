//O(nlgn) to build suffix array(sort cyclic shifts)
vector<int> sort_cyclic_shifts(string & s) {
	int n = (int)s.size();
	const int alphabet = 256;
	vector<int> c(n), p(n), cnt(max(n, alphabet), 0);
	
	for(int i=0;i<n;i++) cnt[s[i]]++;
	for(int i=1;i<alphabet;i++) cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--) p[--cnt[s[i]]] = i;
	
	c[p[0]] = 0;
	int classes = 1;
	for(int i=1;i<n;i++) {
		if(s[p[i]] != s[p[i-1]]) classes++;
		c[p[i]] = classes-1;
	}
 
	vector<int> pn(n), cn(n);
	for(int h = 0; (1 << h) < n; h++){
		for(int i = 0; i < n; i++) {
			pn[i] = p[i] - (1 << h);
			if(pn[i] < 0) pn[i]+=n;
		}
		fill(cnt.begin(), cnt.begin() + classes, 0);
		
		for(int i=0;i<n;i++) cnt[c[pn[i]]]++;
		for(int i=1;i<classes;i++) cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--) p[--cnt[c[pn[i]]]] = pn[i];
		
		cn[p[0]] = 0;
		classes = 1;
		for(int i=1;i<n;i++) {
			pii cur = pii(c[p[i]], c[(p[i] + (1 << h)) % n]);
			pii prev = pii(c[p[i-1]], c[(p[i-1] + (1 << h)) %n]);
			if(cur != prev) classes++;
			cn[p[i]] = classes - 1;
		}
		c.swap(cn);
	}
	return p;
}

vector<int> suffix_array_construction(string s){
	s += "$";
	vector<int> sorted_shifts = sort_cyclic_shifts(s);
	sorted_shifts.erase(sorted_shifts.begin());
	return sorted_shifts;

}

//O(n) to build lcp array
vector<int> LCP(vector<int> &sa, string &s) {
	int n = (int)sa.size();
 
	vector<int> order(n);
	for(int i=0;i<n;i++)
		order[sa[i]] = i;
	vector<int> lcp(n - 1);
	int k = 0;
	for(int i=0;i<n;i++) {
		if(order[i] == n-1){
			k = 0;
			continue;
		}
		
		int j = sa[order[i] + 1];
		while(i+k<n-1 && j+k<n-1 && s[i+k] == s[j+k])
			k++;
		lcp[order[i]] = k;
		if(k) k--;
	}
	return lcp;
}
