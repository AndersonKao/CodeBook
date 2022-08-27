#define MAX 1000000
#define prime_mod 1073676287
ll h[MAX]; // 1-index, stores hashing of str[1...i]
ll h_base[MAX]; 
char str[MAX];
void hash_init(int len, ll prime = 0xdefaced)
{
    h_base[0] = 1, h[0] = 0;
    for (int i = 1; i <= len; i++){
        h[i] = (h[i - 1] * prime + str[i - 1]) % prime_mod;
        h_base[i] = (h_base[i - 1] * prime) % prime_mod;
    }
}

ll get_hash(int l, int r){
    return ((h[r+1] - h[l] * h_base[r - l + 1] % prime_mod) + prime_mod) % prime_mod;
}