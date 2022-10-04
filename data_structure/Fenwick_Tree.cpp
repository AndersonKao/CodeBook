int maxn = 200000;
int BIT[maxn + 1]; // BIT using [1, n].
int query(int idx){
    int ans = 0;
    while(idx > 0){
        ans += BIT[idx];
        idx -= (idx & (~idx + 1));
    }
    return ans;
}
void modify(int idx, int val){
    while(idx <= maxn){
        BIT[idx] += val;
        idx += (idx & (~idx + 1));
    }
}