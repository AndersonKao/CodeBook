string Minimal_Rotation(string &s) {
	int n = (int)s.size();
	int i=0, j=1, k=0;
	while(k<n && i<n && j<n) {
		if(s[(i+k)%n] == s[(j+k)%n]) k++;
		else {
			s[(i+k)%n] > s[(j+k)%n] ? i = i+k+1 : j = j+k+1;
			if(i == j) i++;
			k = 0;
		}
	}
	i = min(i,j);
	return s.substr(i) + s.substr(0,i);
}