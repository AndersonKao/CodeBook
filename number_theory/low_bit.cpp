int lowbit(int x) { return x & (~x + 1); }
// O(3^n) // bitmask dp
for (int i = 0; i < n; i++) {
    for (int res = i; res; res = (res - 1) & i) { // all subset
        
    }
} 