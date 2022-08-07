#define LL long long
#define IL(X) ((X << 1) + 1)
#define IR(X) ((X << 1) + 2)
#define MAXN 500005
// add tag
// tag += tag
// val += tag*size

struct segID{
    struct Node{
        LL val;
        LL lazy_tag;
        int size;
    };
    LL dataseq[MAXN];
    Node seq[MAXN * 4 + 5];
    void pull(int index){
        seq[index].val = seq[IL(index)].val + seq[IR(index)].val;
    }
    void push(int index){
        seq[IL(index)].lazy_tag += seq[index].lazy_tag;
        seq[IL(index)].val += seq[index].lazy_tag * seq[IL(index)].size;
        seq[IR(index)].lazy_tag += seq[index].lazy_tag;
        seq[IR(index)].val += seq[index].lazy_tag * seq[IR(index)].size;
        seq[index].lazy_tag = 0;
    }

    void build(int L, int R, int index){
        if(L == R){
            seq[index].val = dataseq[L];
            seq[index].size = 1;
            seq[index].lazy_tag = 0;
            return; 
        }
        int M = (L + R) / 2;
        build(L, M, IL(index));
        build(M + 1, R, IR(index));
        seq[index].size = seq[IL(index)].size + seq[IL(index)].size;
        pull(index);
    }

    void modify(int l, int r, int L, int R, int index, long long Add){
        if(l == L && r == R){
            seq[index].lazy_tag += Add;
            seq[index].val += Add * seq[index].size;
            return;
        }
        push(index);
        int M = (L + R) / 2;

        if(r <= M){
            modify(l, r, L, M, IL(index), Add);
        }else if(l > M){
            modify(l, r, M + 1, R, IR(index), Add);
        }else{
            modify(l, M, L, M, IL(index), Add);
            modify(M + 1, r, M + 1, R, IR(index), Add);
        }
        pull(index);
    }

    long long Query(int l, int r, int L, int R, int index){
        if(l == L && r == R){
            return seq[index].val;
        }
        int M = (L + R) / 2;
        push(index);
        if(r <= M){
            return Query(l, r, L, M, IL(index));
        }else if(l > M){
            return Query(l, r, M + 1, R, IR(index));
        }else{
            return Query(l, M, L, M, IL(index)) + 
            Query(M + 1, r, M + 1, R, IR(index));
        }

    }
};
