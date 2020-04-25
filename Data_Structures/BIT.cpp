/*
 Binary Indexed Tree - Fenwick Tree
 Update: O(log n)
 Query: O(log n)  
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
int bit[maxn+1];

void update(int x, int v){
	for(; x <= maxn-1; x+=(x&-x))
		bit[x] += v;
}

int query(int x){
	int ans = 0;
	for(; x > 0; x-=(x&-x))
		ans += bit[x];
	return ans;
}
