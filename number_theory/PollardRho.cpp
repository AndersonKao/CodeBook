//find a factor in O(n^1/4)
//n need to be Composite number
//sometimes it may fail, just keep running.
//Floyd version, wait for Brent version
ll mul(ull a, ull b, ull m) {//need unsigned long long to avoid overflow
	ll ans = 0;
	while(b) {
		if(b&1) {
			ans+=a;
			if(ans>=m) ans-=m;
		}
		a<<=1, b>>=1;
		if(a>=m) a-=m;
	}
	return ans;
}

mt19937 mt(time(nullptr));
ll f(ll x, ll& c, ll& pmod) {
	return (mul(x,x,pmod)+c%pmod)%pmod;
}

ll pollard(ll x) {
	ll c = mt()%x;
	ll a=2, b=2;
	
	while(1) {
		a = f(a, c, x);
		b = f(f(b, c, x), c, x);
		ll d = __gcd(x, abs(a-b));
		if(a==b) return -1;//in cycle
		if(d!=1) return d;//find
	} 
}