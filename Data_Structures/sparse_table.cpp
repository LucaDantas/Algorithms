#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+100, maxl = 20;

int n;

int sparse[maxn][maxl];

int a[maxn];

int lg[maxn];

void build() {
	for(int i = 0; i < n; i++) {
		sparse[i][0] = a[i];
	}
	for(int k = 1; k < maxl; k++) {
		for(int i = 0; i <= n - (1 << k); i++) {
			sparse[i][k] = min(sparse[i][k-1], sparse[i+ (1 << (k-1)) ][k-1]);
		}
	}

	lg[1] = 0;
	for(int i = 2; i < maxn; i++) lg[i] = lg[i>>1]+1;
}

int query(int l, int r) {
	int tam = lg[r-l+1];
	return min(sparse[l][tam], sparse[r-(1<<tam)+1][tam]);
}