/*
	Implementation of max-segtree and extra find function
	
	Complexities:
		build: O(n)
		update: O(logn)
		find: O(logn)
		query: O(logn)
	
	Notice that the query might not be necessary, but I implemented anyway

	REMEMBER TO DO THE CHECK INSIDE THE MAIN FUNCTION - IF YOU FORGET THERE'LL BE AN ERROR
*/

// What we want to do is to find the first value that is greater or equal to v
// To do this we'll do a max-seg and the function find we'll choose where to go
// depending on the max of the left segment, if the max-value of the left segment
// if it is greater or equal to v we go to the left and if the value is smaller than v
// we'll go to the right side, and if there is no value in the whole interval that fits
// that value we need we return 0 - then 0-check we must do inside the main function
// and before calling the function by looking at tree[1] and comparing with v

const int maxn = 2e5 + 100, inf = 0x3f3f3f3f;

int a[maxn], tree[4*maxn];

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = a[i];
	}
	else {
		int mid = (i+j) >> 1;
		build(2*node, i, mid);
		build(2*node+1, mid+1, j);

		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
}

void update(int node, int i, int j, int pos, int val) {
	if(i == j) {
		tree[node] -= val;
	}
	else {
		int mid = (i+j) >> 1;
		if(pos <= mid) update(2*node, i, mid, pos, val);
		else update(2*node+1, mid+1, j, pos, val);
		tree[node] = max(tree[2*node], tree[2*node+1]);
	}
}

int query(int node, int i, int j, int l, int r) {
	if(i > r || j < l) return -inf;
	if(i >= l && j <= r) return tree[node];
	int mid = (i+j) >> 1;
	return max(query(2*node, i, mid, l, r), query(2*node+1, mid+1, j, l, r));
}

int find(int node, int i, int j, int v) {
	if(i == j) return i;

	int mid = (i+j) >> 1;

	if(tree[2*node] >= v) return find(2*node, i, mid, v);
	else return find(2*node+1, mid+1, j, v);
}