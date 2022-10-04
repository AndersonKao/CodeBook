vector<int> Z(string &s) {
	vector<int> z((int)s.size());
	fill(z.begin(), z.end(), 0);
	int L, R;
	L = R = 0;
	for(int i=1;i<(int)s.size();i++) {
		if(i <= R && i + z[i-L] - 1 < R) {
			z[i] = z[i-L];
		}  else {
			z[i] = max(0, R-i+1);
			while(s[z[i]] == s[i + z[i]])
				z[i]++;
			L = i;
			R = i + z[i] - 1;
		}
	}
	return z;
}