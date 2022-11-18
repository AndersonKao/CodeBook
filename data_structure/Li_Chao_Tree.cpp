// Miminimum Li Chao Tree
const ll inf = 1e18;
const int maxx = 1e6;
struct line
{
    ll m, b;
    line() { m = b = inf; }
    line(ll mm, ll bb){m = mm, b = bb;}
    ll y(ll x){
        if(m == inf || b == inf)
            return inf;
        return m * x + b;
    }
};
line segs[4 * maxx];
/*
a line is  y = k * x + b, using point to represent it.
*/
void add_line(line nw, int idx = 1, int l = 0, int r = maxx)
{
    int m = (l + r) >> 1;
    bool lef = nw.y(l) < segs[idx].y(l);
    bool mid = nw.y(m) < segs[idx].y(m);
    if(mid) {
        swap(line[idx], nw);
    }
    if(l == r) {
        return;
    } else if(lef != mid){
        add_line(nw, 2 * idx, l, m);
    } else {
        add_line(nw, 2 * idx + 1, m + 1, r);
    }
}

// get minimum in some line x;
ll query(int x, int idx = 1, int l = 0, int r = maxx)
{
    int m = (l + r) / 2;
    if(l == r) {
        return line[idx].y(x);
    } else if(x < m) {
        return min(line[idx].y(x), get(x, 2 * idx, l, m));
    } else {
        return min(line[idx].y(x), get(x, 2 * idx + 1, m + 1, r));
    }
}

// if the line slope is non-increasing. and query(x) is increasing.
// dp[i] = min{s[i] * f[j] + dp[j], for all j < i}. f[i] is non-increasing. s[i] increasing. 
ll inters(line l1,line l2){
	return (l2.b-l1.b)/(l1.m-l2.m);
}
bool check(line l1,line l2,line l3){
	ll l12=inters(l1,l2);
	ll l23=inters(l2,l3);
	return l23<l12;
}
ll s[maxn], f[maxn], dp[maxn];
int main(){
	int n,k; cin >> n >> k;
	for(int i=1;i<=n;i++) cin >> s[i];
	for(int i=1;i<=n;i++) cin >> f[i];
	
	deque<line> q;
	q.push_front({k,0});
	
	for(int i=1;i<=n;i++){
		int x=s[i];
		while(q.size()>=2 && q[0].y(x)>q[1].y(x)) q.pop_front();
		dp[i]=q.front().y(x);
		line now={f[i],dp[i]};
		
		if(q.back().a==now.a) continue;
		while(q.size()>=2 && check(q[q.size()-2],q[q.size()-1],now)) q.pop_back();
		q.push_back(now);
	}
	cout << dp[n] << '\n';
}