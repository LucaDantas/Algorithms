/*
	Persistent Segment Tree
	Always remember to set at the beginning: root[0] = new Node();
	Update creates a new version of the seg and returns the updated node

	Note that there are no bounds for the values as it works as a dynamic
	segtree. To perform this trick remeber to set a node referencing itself
	in the constructor

	Also implements queries of finding k-th active element in interval
	[l, r] by passing the (l-1)-th and r-th versions of the tree
*/
#include <cstdio>

constexpr int maxn = 1e5+10;

struct Node
{
	Node *l, *r; int val;
	Node() : l(this), r(this), val(0) {}
} *root[maxn];

struct PersistentSegmentTree
{
	Node* upd(Node *base, int i, int j, int pos, int v) {
		Node* node = new Node();
		*node = *base;

		node->val += v;

		if(i == j) return node;
		
		int m = (i+j) >> 1;
		
		if(pos <= m) node->l = upd(node->l, i, m, pos, v);
		else node->r = upd(node->r, m+1, j, pos, v);

		return node;
	}

	int query(Node* node, int i, int j, int l, int r) {
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return node->val;
		int m = (i+j) >> 1;
		return query(node->l, i, m, l, r) + query(node->r, m+1, j, l, r);
	}

	int find(Node* rmv, Node* add, int i, int j, int k) {
		if(add->val - rmv->val < k) return -1;
		if(i == j) return i;
		int m = (i+j) >> 1;
		int v = find(rmv->l, add->l, i, m, k);
		if(v != -1) return v;
		return find(rmv->r, add->r, m+1, j, k - (add->l->val - rmv->l->val));
	}
} seg;