// l,r means [l, r]
const int maxn = 100000;

struct BIT {
    int data[maxn+1];
    void update(int idx, int val) {
        while (idx <= maxn) {
            data[idx] += val;
            idx += idx & (~idx + 1);
        }
    }
    void update(int l, int r, int val) {
        update(l, val);
        update(r + 1, -val);
    }
    int query(int idx) {
        int res = 0;
        while (idx > 0) {
            res += data[idx];
            idx -= idx & (~idx + 1);
        }
        return res;
    }
    int query(int l, int r) {
        return query(r) - query(l);
    }
};

// Range Modify, Range query prefix sum (all O(logn)).
struct LazyBIT {
    BIT bitAdd, bitSub;
    void update(int l, int r, int val) {
        bitAdd.update(l, r, val);
        bitSub.update(l, r, (l - 1) * val);
        bitSub.update(r + 1, (-r + l - 1) * val);
    }
    int query(int idx) {
        return idx * bitAdd.query(idx) - bitSub.query(idx);
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

// usage: problems that range modify can be turn into polynomial of idx.
/* like range update [l, r]: add 1 to l, 2 to l+1, ... (r-l+1) to r. this problem can be turn into 
for idx < l, nothing
for l <= idx <= r, add ((idx - l + 1) + 1)*(idx-l+1) / 2, just (a+b)*h/2.
for idx > r, add (r-l+1 + 1) * (r-l+1) / 2.
Decompose them into separate terms like (idx^2, idx, 2*dix, 2*C, origin val). */
struct Polynomial_Queries{
	vec<BIT<ll>> BITs;
	int n;
	// 0 "idx", 1 constant, 2 doubled "idx^2"
	// 3 doubled "idx", 4 doubled constant, 5 origin array
	Polynomial_Queries(){
		BITs.resize(6);
	}
	void Build(vec<ll> & data){
		n = data.size();
		REP(i, 5)
			BITs[i].Build(n); // implement by yourself.
		BITs[5].Build(data);
	}
	void update(int l, int r, ll val){
		BITs[0].r(l, r, val);
		BITs[1].update(l, r, (1- l) * val);
		BITs[2].update(l, r, 1);
		BITs[3].update(l, r, 1 - 2 * l);
		BITs[4].update(l, r, l * (l * 1LL)- l);
		ll len = r - l + 1;
		ll r_l = r - l;
		BITs[1].update(r + 1, n, len * val);
		BITs[4].update(r + 1, n, len * r_l);
	}
	ll query(int idx){
		ll ans = 0;
		ans += BITs[0].query(idx) * idx;
		ans += BITs[1].query(idx);
		ll doubled = 0;
		doubled += BITs[2].query(idx) * idx * idx;
		doubled += BITs[3].query(idx) * idx;
		doubled+= BITs[4].query(idx);
		ans += (doubled >> 1);
		ans += BITs[5].query(idx);
		return ans;
	}
	ll query(int l, int r){
		//cout << query(r) << ", " << query(l - 1) << endl;
		return query(r) - query(l - 1);
	}
};