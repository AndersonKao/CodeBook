//fat data structure
struct node {
	int hit = 0;
	node* next[26] = {};
};

using pnode = node* ;
 
void insert(const char *s, pnode* root) {
	if(!*root)
		*root = new node;
	if(s[0] == '\0') {
		(*root)->hit++;
	} else {
		insert(s+1, &(*root)->next[*s-'a']);
	}
}