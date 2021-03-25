// Kruskal Reconstruction Tree

/*
	The function addEdge does not check if the nodes are already connected
	
	The new nodes created in the function addEdge must be in increasing order
	(of key, not necessarily of value)

	First you add the edges then you build the sparse table and the intervals
	of each vertex

	Use the function get to binary lift up to the lowest node that satisfies
	the condition you've passed
	
	Nodes must be in monotonic order (by value, not key) when inserted

	DSU does not use union by size or rank because we must know the real parent
	of the subtree

	DSU structure is global because it is needed inside the main function to
	find which edges to add to the tree
*/

#include <cstdio>
#include <vector>

constexpr int maxn = 2e5+10, logn = 20;

struct DSU
{
	int pai[maxn];
	DSU() { for(int i = 0; i < maxn; i++) pai[i] = i; }
	void init() { for(int i = 0; i < maxn; i++) pai[i] = i; }
	int find(int x) { return pai[x]==x?x:pai[x]=find(pai[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return 0;
		pai[b] = a;
		return 1;
	}
} dsu;

struct KRT
{
	std::vector<int> g[maxn];
	int tab[maxn][logn], val[maxn], head = 0, t = 1, n;

	int in[maxn], out[maxn];

	DSU aux;

	void addEdge(int from, int to, int weight) {
		head = from;
		val[from] = weight;

		to = aux.find(to);
		aux.join(from, to);

		tab[to][0] = from;
		g[from].push_back(to);
	}

	void dfs(int u) {
		if(u <= n) return (void)(in[u] = out[u] = t++);

		in[u] = t;
		for(int v : g[u])
			dfs(v);
		out[u] = t-1;
	}

	void build(int _n) {
		n = _n;
		dfs(head);

		for(int l = 1; l < logn; l++)
			for(int i = 1; i <= head; i++)
				tab[i][l] = tab[tab[i][l-1]][l-1];
	}

	int get(int u, int v, int k) {
		auto comp = [&](int a, int b) { return k?a>=b:a<=b; };
		for(int l = logn-1; l >= 0; l--) {
			if(tab[u][l] && comp(val[tab[u][l]], v))
				u = tab[u][l];
		}
		return u;
	}
} krt;