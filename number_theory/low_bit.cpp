int lowbit(int x) { return x & (~x + 1); }
// O(3^n) // bitmask dp
for (int i = 0; i < n; i++) {
    for (int res = i; res; res = (res - 1) & i) { // all subset
    }
    // or this way
    int b = 0;
    do{

    }while((b = (b - i) & i));
}

int x = 5328; // 00000000000000000001010011010000
cout << __builtin_clz(x) << "\n"; // # of 0s at the beginning of the number = 19
cout << __builtin_ctz(x) << "\n"; // # of 0s at the end of the number = 4
cout << __builtin_popcount(x) << "\n"; // # of 1s in the number = 5
cout << __builtin_parity(x) << "\n"; // the parity(even or odd) of # of 1s = 1

