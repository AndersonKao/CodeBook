struct node {
    int key, val; // (key, val)
    int ans; // minans
    int pri, sz; //  priority, size
    node *l, *r;
    int rev, add; // lazy tag

    node () { }
    node (int key) : key(key), val(0), ans(0), pri(rand()), sz(1), l(nullptr), r(nullptr), rev(0), add(0){} 
    node (int key, int val) : key(key), val(val), ans(val), pri(rand()), l(nullptr), r(nullptr), sz(1), rev(0), add(0){} 
    void push(){
        if(rev){
            swap(l, r);
            if(l) l->rev ^= 1;
            if(r) r->rev ^= 1;
            rev ^= 1;
        }
        if(l){
            l->add += add;
            l->val += val;
            l->ans += add;
        }
        if(l){
            r->add += add;
            r->val += val;
            r->ans += add;
        }
        add = 0;
    }
    void pull(){
        ans = val;
		sz = 1;
		if(l){
			ans = min(ans, l->ans);
			sz += l->sz;
		}
		if(r){
			ans = min(ans, r->ans);
			sz += r->sz;
		}
    }
};
node * root;

int size(node * p){
    return p ? p->sz : 0;
}

void push(node * p){
    if(p){
        p->push();
    }
}

void pull(node * p){
    p->push();
}

node * merge (node * a, node * b) {
    if (!a || !b)  return a ? a : b;
    if (a->pri < b->pri){
        push(a);
        a->r = merge(a->r, b);
        pull(a);
        return a;
    }
    else{
        push(b);
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}

// all keys in tree l < key;
void split_by_key(node * rt, node * &a, node * &b, int key)
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
void split_by_size(node * rt, node * &a, node * &b, int k){
    push(rt);
    if (!rt) 
        a = b = nullptr;
    else if(k >= size(rt->l) + 1){
        a = rt;
        int nk = k - (size(rt->l) + 1);
        split_by_size(rt->r, a->r, b, nk);
    }
    else{
        b = rt;
        split_by_size(rt->l, a, b->l, k);
    }
    pull(rt);
}

// <-- Writing slower, Running Faster -->
// not necessary
void insert1(node * &rt, node * it)
{
    if (!rt)
        rt = it;
    else if (it->pri > rt->pri){
        split_by_key(rt, it->l, it->r, it->key);
        rt = it;
        pull(rt);
    }
    else{
        push(rt);
        insert1(rt->key < it->key ? rt->r : rt->l, it);
        pull(rt);
    }
}

// call this <--- insert item(key, val) --->
void Insert(node * &rt, int key, int val = 0){
    node *newp = new node(key, val);
    node *a, *b;
    split_by_key(rt, a, b, key);
    rt = merge(a, merge(newp, b));
/* <-- Writing slower, Running Faster -->
    insert1(rt, newp);
*/
}

// <-- Writing slower, Running Faster -->
// not necessary
void insert2(node* & rt, node* p, int pos){
	if(!rt){
		rt = p;
	}
	else if(p->pri < rt->pri){
		split_by_size(rt, p->l, p->r, pos);
		rt = p;
		pull(rt);
	}
	else{
		push(rt);
		if (pos <= size(rt->l))
			insert2(rt->l, p, pos);
		else
			insert2(rt->r, p, pos - (size(rt->l) + 1));
		pull(rt);
	}
}

// call this <--- insert item(val) after $pos$ items --->
void Insert_by_pos(node* &rt, int pos, int key, int val = 0){
    node *newp = new node(key);
    node *a, *b;
    split_by_size(rt, a, b, pos);
    rt = merge(a, merge(newp, b));
/* <-- Writing slower, Running Faster -->
    insert2(rt, newp, pos);
*/
}

bool erase (node * & rt, int key) {
    if(!rt)
        return false;
    if (rt->key == key)
    {
        node * del = rt;
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

bool erase_by_pos(node*& rt, int pos){
    node* a, *b, *c;
	split_by_size(rt, a, b, pos-1);
	split_by_size(b, b, c, 1);
	rt = merge(a, c);
	delete b;
}

// return 0-th, 1-th, 2-th, means: greater than x items in tree.
int order_of_key(node * root, int key){
    if(!root)
        return 0;
    if(root->key < key)
        return size(root->l) + 1 + order_of_key(root->r, key);
    else
        return order_of_key(root->l, key);
}

node * find_by_order(node * root, int k){
    if (k <= size(root->l))
        return find_by_order(root->l, k);
    if (k == size(root->l) + 1)
        return root;
    return find_by_order(root->l, k - size(root->l) + 1);
}

/* range query max, range reverse */
// reverse range [l, r] in [1, n]
void reverse(node * &root, int l, int r){
    node *a, *b, *c;
    split_by_size(root, a, b, l - 1);
    split_by_size(b, b, c, r - l + 1);
    b->rev ^= 1;
    root = merge(a, merge(b, c));
}

/* range query max, range reverse */
// revolve by T times in range [l, r] in [1, n]
void Revolve(node* & rt, int l, int r, int T){
	int len = (r-l+1);
	T %= len;
	node* a, *b, *c;
	split_by_size(rt, a, b, l-1);
	split_by_size(b, b, c, len);

	node* b1, *b2;
	split_by_size(b, b1, b2, len - T);
	rt = merge(a, merge( merge(b2, b1), c) );
}

// query range [l, r] in [1, n]
int query(node *& root, int l, int r){
    node *a, *b, *c;
    split_by_size(root, a, b, l - 1);
    split_by_size(b, b, c, r - l + 1);
    int ans = b->ans;
    root = merge(a, merge(b, c));
    return ans;
}

void Modify(node* & rt, int l, int r, int val){
	node* a, *b, *c;
	split_by_size(rt, a, b, l-1);
	split_by_size(b, b, c, (r - l + 1));

	b->add += val;
	b->val += val;
	b->ans += val;
	rt = merge(a, merge(b, c));
}

void heapify(node * t)
{
    if (!t) return;
    node * max = t;
    if (t->l != nullptr && t->l->pri > max->pri)
        max = t->l;
    if (t->r != nullptr && t->r->pri > max->pri)
        max = t->r;
    if (max != t) {
        swap (t->pri, max->pri);
        heapify (max);
    }
}

// Construct a treap on values {a[0], a[1], ..., a[n - 1]} in O(n)
node * build (int * a, int n) {
    if (n == 0) return nullptr;
    int mid = n / 2;
    node * t = new node (a[mid]);
    t->l = build (a, mid);
    t->r = build (a + mid + 1, n - mid - 1);
    heapify (t);
    pull(t);
    return t;
}