const int MOD = 1000000009;
const int MAX = 1000000009;
int catalan[MAX];

void init(int n) {
    catalan[0] = catalan[1] = 1;
    for (int i=2; i<=n; i++) {
        catalan[i] = 0;
        for (int j=0; j < i; j++) {
            catalan[i] += (catalan[j] * catalan[i-j-1]) % MOD;
            if (catalan[i] >= MOD) {
                catalan[i] -= MOD;
            }
        }
    }
}

//pass CSES Bracket Sequences I
//O(nlogMOD)
void init(ll n) {
    //use long long
	catalan[0] = 1;
	for(ll i=1;i<=n;i++)
		catalan[i] = catalan[i-1] * 2 * (2*i+1) % MOD * binpow(i+2, MOD-2, MOD) % MOD;
} 

/*
C[0] = C[1] = 1.
C[n] = C[k]*C[n-1-k], k from 0 to n-1.  if n >= 2.

C[n] is solution for
Number of correct bracket sequence consisting of n opening and n closing brackets.
The number of rooted full binary trees with n+1 leaves (vertices are not numbered). A rooted binary tree is full if every vertex has either two children or no children.
The number of binary search trees that will be formed with N keys.
The number of ways to completely parenthesize n+1 factors.
The number of triangulations of a convex polygon with n+2 sides (i.e. the number of partitions of polygon into disjoint triangles by using the diagonals).
The number of ways to connect the 2n points on a circle to form n disjoint chords.
The number of non-isomorphic full binary trees with n internal nodes (i.e. nodes having at least one son). *full binary tree: nodes with either 2 or no children.
The number of monotonic lattice paths from point (0,0) to point (n,n) in a square lattice of size n*n, which do not pass above the main diagonal (i.e. connecting (0,0) to (n,n)).
Number of permutations of length n that can be stack sorted (i.e. it can be shown that the rearrangement is stack sorted if and only if there is no such index i<j<k, such that a_k < a_i < a_j ).
The number of non-crossing partitions of a set of n elements.
The number of ways to cover the ladder 1...n using n rectangles (The ladder consists of n columns, where i-th column has a height ).
*/
