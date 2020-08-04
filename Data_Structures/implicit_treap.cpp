#include<bits/stdc++.h>
using namespace std;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));

template<typename T> T rnd(T v) {
  T k;
  k = (T) rng();
  return (T) (((k % v) + v) % v);
}

struct Treap
{
	struct Node
	{
		int pri, val, tam;
		Node *l, *r;
		Node() {}
		Node(int _val) : pri(rnd(0x3f3f3f3f)), val(_val), tam(1), l(NULL), r(NULL) {}
	} *root;

	Treap() : root(NULL) {}

	int size(Node *node){return node==NULL?0:node->tam;}
	void upd(Node *node){
		if(node == NULL) return;
		node->tam = size(node->l) + size(node->r) + 1;
	}

	void split(Node *node, int pos, Node *&a, Node *&b) {
		if(node == NULL) {a = b = NULL; return;}
		if(size(node->l) < pos) {
			split(node->r, pos - size(node->l) - 1, node->r, b);
			a = node; upd(a);
		} else {
			split(node->l, pos, a, node->l);
			b = node; upd(b);
		}
	}

	Node* merge(Node* l, Node* r) {
		if(!l || !r) return l?l:r;
		if(l->pri > r->pri) {
			l->r = merge(l->r, r);
			upd(l); return l;
		}
		r->l = merge(l, r->l);
		upd(r); return r;
	}

	void insert(int val, int pos) {
		Node *a, *b;
		Node *c = new Node(val);
		split(root, pos, a, b);
		
		root = merge(a, c);
		root = merge(root, b);
	}

	void print() {
		print(root); printf("\n");
	}

	void print(Node* node) {
		if(!node) return;
		print(node->l);
		printf("%d ", node->val);
		print(node->r);
	}
};

int main() {
	
}
