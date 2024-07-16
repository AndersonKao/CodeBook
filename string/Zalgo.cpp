// Z(k): the length of longest substring of s that begins at k and is a prefix of s.
vector<int> Zalgorithm(string &s) {
	int n = s.size();
	vector<int> z(n, 0);
	int L = 0, R = 0;
	for(int i=1;i<n;i++) {
		z[i] = max(0, min(z[i-L], R-i+1));
		while(i + z[i] < n && s[z[i]] == s[i + z[i]]){
			L = i;
			R = i + z[i];
			z[i]++;
		}
	}
	return z;
}
