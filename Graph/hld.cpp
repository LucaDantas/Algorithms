#include <cstdio>
#include <vector>
#include <algorithm>

constexpr int maxn = 2e5+10;

std::vector<int> g[maxn];

struct HLD
{
	struct SegmentTree {
		int tree[4*maxn], n;
		void upd(int pos, int val) { upd(1, 1, n, pos, val); }
		void upd(int node, int i, int j, int pos, int val) {
			if(i == j) return (void)(tree[node] = val);
			int m = (i+j) >> 1;
			if(pos <= m) upd(2*node, i, m, pos, val);
			else upd(2*node+1, m+1, j, pos, val);
			tree[node] = std::max(tree[2*node], tree[2*node+1]);
		}

		int query(int l, int r) { return query(1, 1, n, l, r); }
		int query(int node, int i, int j, int l, int r) {
			if(i > r || j < l) return 0;
			if(i >= l && j <= r) return tree[node];
			int m = (i+j) >> 1;
			return std::max(query(2*node, i, m, l, r), query(2*node+1, m+1, j, l, r));
		}
	};
	int pai[maxn], chain[maxn], pos[maxn], sz[maxn], depth[maxn], n, t;
	SegmentTree seg;
	void dfsSZ(int u) {
		sz[u] = 1;
		for(int& v : g[u]) {
			g[v].erase(std::find(g[v].begin(), g[v].end(), u));
			pai[v] = u; depth[v] = depth[u]+1;
			dfsSZ(v); sz[u] += sz[v];
			if(sz[v] > sz[g[u][0]])
				std::swap(v, g[u][0]);
		}
	}
	int lca(int a, int b) {
		for(; chain[a] != chain[b]; a = pai[chain[a]])
			if(depth[chain[a]] < depth[chain[b]]) std::swap(a, b);
		return depth[a] < depth[b] ? a : b;
	}
	void dfs(int u) {
		pos[u] = ++t;
		for(int v : g[u]) {
			chain[v] = (v == g[u][0] ? chain[u] : v);
			dfs(v);
		}
	}
	void init(int _n) {
		n = _n; seg.n = n;
		depth[1] = 1;
		dfsSZ(1);
		chain[1] = 1;
		dfs(1);
	}
	void upd(int x, int v) { seg.upd(pos[x], v); }
	int query(int a, int b) {
		int ans = 0;
		for(; chain[a] != chain[b]; a = pai[chain[a]]) {
			if(depth[chain[a]] < depth[chain[b]]) std::swap(a, b);
			ans = std::max(ans, seg.query(pos[chain[a]], pos[a]));
		}
		if(depth[a] > depth[b]) std::swap(a, b);
		return std::max(ans, seg.query(pos[a], pos[b]));
	}
} hld;

int main() {
	int n, q; scanf("%d %d", &n, &q);
	std::vector<int> val(n+1);
	for(int i = 1; i <= n; i++)
		scanf("%d", &val[i]);
	for(int i = 1, a, b; i < n; i++)
		scanf("%d %d", &a, &b), g[a].push_back(b), g[b].push_back(a);
	hld.init(n);
	for(int i = 1; i <= n; i++)
		hld.upd(i, val[i]);
	while(q--) {
		int t, a, b; scanf("%d %d %d", &t, &a, &b);
		if(t == 1) hld.upd(a, b);
		else printf("%d\n", hld.query(a, b));
	}
}