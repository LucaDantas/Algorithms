/*
	Disjoint Set Union (Union-Find) with roolback (persistency)
	Find -> O(log n) due to no path compression, which can't be implemented 
	alongside rollback
	We use optimization by size to make the queries aroung O(log n) and we also
	save it in the roolback
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;

struct Op
{
	int x, y, pesoX, pesoY;
};

stack<Op> s; // saves the last state of the changed nodes

int pai[maxn], peso[maxn];

void init() {
	for(int i = 0; i < maxn; i++) {
		pai[i] = i;
		peso[i] = 1;
	}
}

int find(int x) {
	if(pai[x] == x) return x;
	return find(pai[x]);
}

void join(int x, int y) {
	x = find(x);
	y = find(y);

	if(peso[x] < peso[y]) swap(x,y);

	Op now = {x,y,peso[x],peso[y]};
	s.push(now);

	if(x == y) return;

	peso[x] += peso[y];
	pai[y] = x;
}

void rollback(){
	Op now = s.top();
	s.pop();
	peso[now.x] = now.pesoX;
	peso[now.y] = now.pesoY;
	pai[now.x] = now.x;
	pai[now.y] = now.y;
}
