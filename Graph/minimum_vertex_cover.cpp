/*
	Bipartite Matching in O(nm)
	+
	Minimum Vertex Cover on O(n+m)

	Using Kőnig's theorem we can build the minimum vertex cover
	from the maximum matching on bipartite graphs, and they have
	the same size
	
	https://en.wikipedia.org/wiki/K%C5%91nig%27s_theorem_(graph_theory)#Proofs
*/

#include<bits/stdc++.h>
using namespace std;

#define pb push_back

constexpr int maxn = 1e3+10; // O(nm)

vector<int> g[maxn];

int color[maxn], edge_match[maxn];

bool mark[maxn], match[maxn];

bool dfs(int u) {
	mark[u] = 1;

	if(color[u]) {
		if(match[u])
			return dfs(edge_match[u]);
		return 1;
	}

	for(int v : g[u]) {
		if(mark[v] || !dfs(v)) continue;
		match[u] = match[v] = 1;
		edge_match[u] = v, edge_match[v] = u;
		return 1;
	}

	return 0;
}

bool in[maxn];

vector<int> t;

void dfs2(int u) {
	mark[u] = 1;

	if(color[u]) return (void)(t.pb(u), dfs2(edge_match[u]));

	in[u] = 1;
	for(int v : g[u]) {
		if(mark[v]) continue;
		dfs2(v);
	}
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
		ans += dfs(i);
	}

	memset(mark, 0, sizeof mark);
	for(int i = 1; i <= n; i++) {
		if(color[i] || match[i] || mark[i]) continue;
		dfs2(i);
	}

	printf("%d\n", ans);
	for(int i = 1; i <= n; i++)
		if(!in[i] && !color[i]) printf("%d ", i);
	for(int x : t)
		printf("%d ", x);
	printf("\n");
}