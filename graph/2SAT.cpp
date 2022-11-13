// 2-SAT (A or B) and (C or ^B) and (E) = true : O(n) = O(v+e)
/* common terms edge building
A : ^A -> A, which means A must be true 
not A : A -> ^A , which means A must be false
A or B : ^A -> B, ^B -> A 
not A or B : A -> B, ^B -> ^A
not A or not B : A -> ^B, B -> ^A
A xor B : A -> ^B, ^A -> B, B -> ^A, ^B -> A.
*/
struct twoSAT{
    Kosaraju mK;
    int n;
    vector<bool> value;
    void init(int nterm){
        this->n = nterm;
        mK.init(nterm * 2);
    }
    void addEdge(int u, int v){
        mK.addEdge(u, v);
    }
    int rv(int a) {
        if (a >= n) return a - n;
        return a + n;
    }
    void add_clause(int a, int b) { // a or b
        addEdge(rv(a), b), addEdge(rv(b), a);
    }
    void run(){
        mK.run();
    }
    bool satisfy(){ // assume A = i, then ^A = i+nterm
        value.clear();
        value.resize(n);
        for (int i = 0; i < n; i++){
            if(mK.scc[i] == mK.scc[i+n]){
                return false;
            }
            value[i] = mK.scc[i] > mK.scc[i + n];
        }
        return true;
    } 
};