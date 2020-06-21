/*
	Disjoint Set Union (Union-Find)
	Find -> O(α(n)) aka almost O(1)
	We use path compression and optimization by size to make it faster
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;

int pai[maxn], peso[maxn];

void init() {
	for(int i = 0; i < maxn; i++) {
		pai[i] = i;
		peso[i] = 1;
	}
}

int find(int x) {
	if(pai[x] == x) return x;
	return pai[x] = find(pai[x]);
}

void join(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y) return;

	if(peso[x] < peso[y]) swap(x,y);

	peso[x] += peso[y];
	pai[y] = x;
}
