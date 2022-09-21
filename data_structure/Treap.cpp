struct node {
    int key, pri, sz; // key, priority, size
    node *l, *r;
    node () { }
    node (int key) : key(key), pri(rand()), l(nullptr), r(nullptr), sz(1){ }
    node (int key, int prior) : key(key), pri(prior), l(nullptr), r(nullptr), sz(1) { }
};
using pnode = node *;
pnode root;

int get_size(pnode rt){
    return rt ? rt->sz : 0;
}

void push(pnode rt){
    if(rt){
        // do something.
    }
}

void pull(pnode rt){
    if(rt)
        rt->sz = 1 + get_size(rt->l) + get_size(rt->r);
}

pnode merge (pnode a, pnode b) {
    if (!a || !b)  return a ? a : b;
    if (a->pri < b->pri){
        a->r = merge(a->r, b);
        pull(a);
        return a;
    }
    else{
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}

// all keys in tree l < key;
void split_by_key(pnode rt, pnode &a, pnode &b, int key)
{
    push(rt);
    if (!rt)
        a = b = nullptr;
    else if (rt->key < key){
        a = rt;
        split_by_key(rt->r, rt->r, b, key);
    }
    else{
        b = rt;
        split_by_key (rt->l, a, rt->l, key);
    }
    pull(rt);
}

// split tree into size(l) = k, size(r) = size(rt) - k.
// all keys in l <= all keys in r.
void split_by_size(pnode rt, pnode &a, pnode &b, int k){
    if(!rt)
        a = b = nullptr;
    else if(k >= get_size(rt->l) + 1){
        a = rt;
        int nk = k - (get_size(rt->l) + 1);
        split_by_size(rt->r, a->r, b, nk);
    }
    else{
        b = rt;
        split_by_size(rt->l, a, b->l, k);
    }
    pull(rt);
}

void insert(pnode &rt, pnode it)
{
    if (!rt)
        rt = it;
    else if (it->pri > rt->pri){
        split_by_key(rt, it->l, it->r, it->key);
        rt = it;
    }
    else{
        insert (rt->key < it->key ? rt->r : rt->l, it);
    }
}

// call this
void Insert(pnode &rt, int val){
    node *newp = new node(val);
    insert(rt, newp);
}

bool erase (pnode & rt, int key) {
    if(!rt)
        return false;
    if (rt->key == key)
    {
        pnode del = rt;
        rt = merge(rt->l, rt->r);
        delete del;
        return true;
    }
    if(erase (key < rt->key ? rt->l : rt->r, key)){
        pull(rt);
        return true;
    }
    return false;
}

int Rank_of_key(pnode& root, int key){
    pnode a, b;
    split_by_key(root, a, b, key);
    int ans = get_size(a);
    root = merge(a, b);
    return ans;
}

// cp-algorithm to-do.
void heapify(pnode t)
{
    if (!t) return;
    pnode max = t;
    if (t->l != nullptr && t->l->pri > max->pri)
        max = t->l;
    if (t->r != nullptr && t->r->pri > max->pri)
        max = t->r;
    if (max != t) {
        swap (t->pri, max->pri);
        heapify (max);
    }
}

pnode build (int * a, int n) {
    // Construct a treap on values {a[0], a[1], ..., a[n - 1]}
    if (n == 0) return nullptr;
    int mid = n / 2;
    pnode t = new node (a[mid], rand ());
    t->l = build (a, mid);
    t->r = build (a + mid + 1, n - mid - 1);
    heapify (t);
    pull(t)
    return t;
}