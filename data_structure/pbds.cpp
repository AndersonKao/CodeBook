#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // tree
#include <ext/pb_ds/hash_policy.hpp> // hash
#include <ext/pb_ds/trie_policy.hpp> // trie
#include <ext/pb_ds/priority_queue.hpp> // priority_queue

#include <ext/pb_ds/detail/standard_policies.hpp> // general
using namespace __gnu_pbds;

/*
tree-based container has the following declaration: 

template<
typename Key, // Key type
typename Mapped, // Mapped-policy
typename Cmp_Fn = std::less<Key>, // Key comparison functor
typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
template<
typename Const_Node_Iterator,
typename Node_Iterator,
typename Cmp_Fn_,
typename Allocator_>
class Node_Update = null_node_update, // A policy for updating node invariants
typename Allocator = std::allocator<char> > // An allocator type
class tree;

*/

using ordered_set = tree<
int,   // Key type
null_type, // Mapped-policy
less<int>, // Key Compar
rb_tree_tag,
tree_order_statistics_node_update>
;
using order_map= tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
 

void test(){
    int x;
    ordered_set X;
    X.find(x); // find node with value x.
    X.insert(x); // insert node with value x.
    X.erase(it); // erase the node iterator point to.
    X.lower_bound(x); // return the first iterator with value >= x.
    X.upper_bound(x); // return the first iterator with value > x.
    ordered_set X2;
    X.join(X2); // combine two tree, X2 become empty.
    int r;
    X.split(r, X2);
//  X.split(const Key &r, ordered_set &other);
    // put elements > r into other, if we're using  `greater<Key>` then it's putting < r into other.
    ordered_set::point_iterator ptr = X.begin();
    ptr = X.end(); // iterator

    X.clear();
    X.insert(1);
    X.insert(2);
    X.insert(4);
    X.insert(8);
    X.insert(16);

    cout<<*X.find_by_order(1)<<endl; // 2
    cout<<*X.find_by_order(2)<<endl; // 4
    cout<<*X.find_by_order(4)<<endl; // 16
    cout<<(end(X)==X.find_by_order(6))<<endl; // true

    cout<<X.order_of_key(-5)<<endl;  // 0
    cout<<X.order_of_key(1)<<endl;   // 0
    cout<<X.order_of_key(3)<<endl;   // 2
    cout<<X.order_of_key(4)<<endl;   // 2
    cout<<X.order_of_key(400)<<endl; // 5
}