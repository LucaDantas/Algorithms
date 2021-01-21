/*
	Bipartite Matching in O(nm)
*/

#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 1e3+10; // O(nm)

vector<int> g[maxn];

int color[maxn], edge_match[maxn];

bool mark[maxn], match[maxn];

int dfs(int u, int p) {
	mark[u] = 1;
	if(color[u] && !match[u]) {
		edge_match[u] = p;
		match[u] = 1;
		return 1;
	}
	
	if(color[u] && match[u]) {
		int ans = dfs(edge_match[u], u);
		if(ans == 0) return 0;
		edge_match[u] = p;
		match[u] = 1;
		return 1;
	}

	for(int v : g[u]) {
		if(mark[v]) continue;
		int ans = dfs(v, u);
		if(ans == -1) continue;
		edge_match[u] = v;
		match[u] = 1;
		return 1;
	}
	return 0;
}

int main() {
	int n, m; scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b; scanf("%d %d", &a, &b);
		g[a].pb(b), g[b].pb(a);
	}
	for(int i = 1; i <= n; i++)
		scanf("%d", &color[i]);

	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(color[i] || match[i]) continue;
		memset(mark, 0, sizeof mark);
		ans += dfs(i, 0);
	}

	printf("%d\n", ans);
}