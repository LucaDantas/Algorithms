const int maxn = 2e5 + 100;

int a[maxn];

ll tree[4*maxn];

void build(int node, int i, int j) {
	if(i == j) {
		tree[node] = a[i];
		return;
	}
	int mid = (i+j) >> 1;
	
	build(2*node, i, mid);
	build(2*node+1, mid+1, j);
	
	tree[node] = tree[2*node] + tree[2*node+1];
}

void update(int node, int i, int j, int pos, int val) {
	if(i == j) {
		tree[node] = val;
		a[pos] = val;
		return;
	}
	
	int mid = (i+j) >> 1;
	
	if(pos <= mid)
		update(2*node, i, mid, pos, val);
	else
		update(2*node+1, mid+1, j, pos, val);
		
	tree[node] = tree[2*node] + tree[2*node+1]; 
}

ll query(int node, int i, int j, int l, int r) {
	if(i > r || j < l)
		return 0;
	
	if(i >= l && j <= r)
		return tree[node];
		
	int mid = (i+j) >> 1;
	
	ll left = query(2*node, i, mid, l, r);
	ll right = query(2*node+1, mid+1, j, l, r);
	
	return left + right;
}
