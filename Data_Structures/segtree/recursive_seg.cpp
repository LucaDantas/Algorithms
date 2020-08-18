/*
	Regular Recursive Segment Tree + Fractional Cascading
	Everything is O(logn)
	I implemented a max-seg but it's easy to change
*/

#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10;

int n;

struct SegmentTree {
	int tree[4*maxn], a[maxn];

	void build() { build(1, 1, n); }
	void build(int node, int i, int j) {
		if(i == j) return (void)(tree[node] = a[i]);
		int m = (i+j) >> 1;
		build(2*node, i, m); build(2*node+1, m+1, j);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}

	void update(int pos, int val) { update(1, 1, n, pos, val); }
	void update(int node, int i, int j, int pos, int val) {
		if(i == j) return (void)(tree[node] = val, a[i] = val);
		int m = (i+j) >> 1;
		if(pos <= m) update(2*node, i, m, pos, val);
		else update(2*node+1, m+1, j, pos, val);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}

	int query(int l, int r) { return query(1, 1, n, l, r); }
	int query(int node, int i, int j, int l, int r) {
		if(i > r || j < l) return 0;
		if(i >= l && j <= r) return tree[node];
		int m = (i+j) >> 1;
		return max(query(2*node, i, m, l, r), query(2*node+1, m+1, j, l, r));
	}

	// finds the first item greater or equal to k in the interval [l..r]
	int find(int l, int r, int k) { return find(1, 1, 1, l, r, k); }
	int find(int node, int i, int j, int l, int r, int k) {
		if(tree[node] < k || i > r || j < l) return -1;
		if(i == j) return i;
		int m = (i+j) >> 1;
		int p1 = find(2*node, i, m, l, r, k);
		if(p1 != -1) return p1;
		return find(2*node+1, m+1, j, l, r, k);
	}
} seg;
