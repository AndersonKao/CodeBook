//need ext_gcd
//pass 2022-NCPC-Pre-D
//find smallest n s.t n%m_i = x_i
ll chineseReminder(vector<ll> &m, vector<ll> &x) {
	ll total = 1, ans = 0;
	ll s = 0, t = 0;
	vector<ll> e;
	for(auto &i : m) total*=i;
	for(int i=0;i<(int)m.size();i++) {
		ext_gcd(m[i], total/m[i], s, t);
		e.emplace_back(t * (total / m[i]));
	}
	for(int i=0;i<(int)m.size();i++) (ans+= (e[i] * x[i] % total)) %= total;
	return (ans+total)%total;
}