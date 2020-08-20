/*
	Iterative Seg
	Everything is O(logn) but FAST (almost like a BIT)
	I implemented a min-seg but it's easy to change
*/

#include<bits/stdc++.h>
using namespace std;

constexpr int maxn = 2e5+10, inf = 0x3f3f3f3f;

int n;

struct SegmentTree {
	int tree[2*maxn];
	void build() {
		for(int i = n-1; i > 0; i--)
			tree[i] = min(tree[i<<1], tree[i<<1|1]);
	}
	void upd(int p, int v) {
		for(tree[p += n] = v; p > 0; p >>= 1)
			tree[p>>1] = min(tree[p], tree[p^1]);
	}
	// query the segment [l..r)
	int query(int l, int r) {
		int ans = inf;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if(l&1) ans = min(ans, tree[l++]);
			if(r&1) ans = min(ans, tree[--r]);
		}
		return ans;
	}
} seg;

int main() {
	int q; scanf("%d %d", &n, &q);
	for(int i = 0; i < n; i++)
		scanf("%d", &seg.tree[i+n]);
	seg.build();
	while(q--) {
		int t, a, b; scanf("%d %d %d", &t, &a, &b);
		if(t == 1) {
			seg.upd(a-1, b);
		} else {
			printf("%d\n", seg.query(a-1, b));
		}
	}
}
