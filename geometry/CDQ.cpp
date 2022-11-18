// for each j store number of pair (i, j) such that Xi <= Xj and Yi <= Yj and Zi <= Zj
struct point{
        int x, y, z;
        int idx;
        point(){x = y = z = 0;}
        point(int a, int b, int c, int id):x(a), y(b), z(c), idx(id){}
        bool operator==(const point &a){
                return x == a.x && y == a.y && z == a.z;
        }
};
const int maxn = 100001;
vec<point> pts;
point staticArr[maxn];
int ans[maxn], mt[maxn]; // mt is an binary index tree

void cdq(int l, int r){
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);

    vec<int> arr;
    for(int i = l ;i <= r; i++)
        arr.eb(pts[i].z);
    sort(al(arr)); arr.resize(unique(al(arr)) - arr.begin());
    fill(mt, mt + arr.size()+1, 0);

    int cpidx = 0, lid = l, rid = mid + 1;
    for(rid = mid+1; rid <= r; rid++){
        while(lid <= mid && pts[lid].y <= pts[rid].y){
                add(upper_bound(al(arr), pts[lid].z) - arr.begin(), 1);
                staticArr[cpidx++] = pts[lid];
                lid++;
        }
        ans[pts[rid].idx] += query(upper_bound(al(arr), pts[rid].z) - arr.begin());
        staticArr[cpidx++] = pts[rid];
    }
    while(lid <= mid) staticArr[cpidx++] = pts[lid++];
    for(int i = l; i <= r; i++) pts[i] = staticArr[ i - l ];
}
int main(){
    int n, idx = 0; cin >> n; fill(ans, ans+n, 0); pts.resize(n);
    for(point& e: pts)
            cin >> e.x >> e.y >> e.z; e.idx = idx++;
    auto cmp_1 = [](point&a , point &b){ return a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y < b.y ): a.x < b.x; };
    sort(al(pts), cmp_1);
    for(int i = n-2; i >= 0 ; i--){
            if(pts[i] == pts[i+1]){
                    ans[pts[i].idx] = ans[pts[i+1].idx] + 1; // calculate ans that (pts[i] == pts[j] && i > j) as for ans (pts[i] == pts[j] && i < j) will be calculate in normal process
            }
    }
    cdq(0, n-1);
}