#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<vector<ll> > matrix;

const int MOD = 1e9 + 100;

//With mod
matrix operator *(matrix a, matrix b){
	int n = (int)a.size(); //rows of a
	int m = (int)(b[0].size()); //columns of b
	matrix c(n, vector<ll>(m));
	vector<ll> col(m);
	for(int i = 0; i < n; i++){ //for every row of a
		for(int j = 0; j < m; j++){ //multiply by every column in b
			for(int k = 0; k < n; k++) 
				col[k] = b[k][j];
			ll s = 0;
			for(int k = 0; k < n; k++) //for every item in row i of a, multiply by every item in column j of b
				s = ((s + (a[i][k]*col[k])%MOD)%MOD + MOD)%MOD; //maybe too careful
				//s = (s + (a[i][k]*col[k])%MOD)%MOD;
			c[i][j] = s;
		}
	}
	return c;
}

matrix operator +(matrix a, matrix b){
	int n = (int)(a.size()), m = (int)(a[0].size());
	assert(a.size()==b.size() && a[0].size() == b[0].size());
	matrix c(n, vector<ll>(m));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	return c;
}

matrix operator *(ll v, matrix a){
	for(auto &i : a)
		for(auto &j : i)
			j *= v;
	return a;
}

matrix operator -(matrix a, matrix b){
	return a+(-1*b);
}

//Without mod
//matrix operator*(matrix a, matrix b){
	//int n = (int)a.size(); //rows of a
	//int m = (int)(b[0].size()); //columns of b
	//matrix c(n, vector<ll>(m));
	//vector<ll> col(m);
	//for(int i = 0; i < n; i++){ //for every row of a
		//for(int j = 0; j < m; j++) //multiply by every column in b
			//col[k] = b[k][j];
		//for(int j = 0; j < m; j++){
			//ll s = 0;
			//for(int k = 0; k < n; k++) //for every item in row i of a, multiply by every item in column j of b
				//s += a[i][k]*col[k];
			//c[i][j] = s;
		//}
	//}
	//return c;
//}

matrix identity(int siz){
	matrix ret(siz, vector<ll>(siz));
	for(int i = 0; i < siz; i++)
		ret[i][i] = 1;
	return ret;
}

//remember to also import identity for pow
matrix pow(matrix A, ll p){
	matrix ret = identity((int)A.size());
	while(p > 0){
		if(p&1)
			ret = ret*A;
		A = A*A;
		p >>= 1;
	}
	return ret;
}

//int main(){
	//matrix a = {{1, 5},{5,2}}, b = {{13, 45},{99,7}};
	//for(auto i : a+b){
		//for(auto j : i)
			//cout << j << ' ';
		//cout << endl;
	//}
	//cout << endl;
	//for(auto i : a-b){
		//for(auto j : i)
			//cout << j << ' ';
		//cout << endl;
	//}
	//cout << endl;
	//for(auto i : a*b){
		//for(auto j : i)
			//cout << j << ' ';
		//cout << endl;
	//}
	//cout << endl;
	//for(auto i : 5*b){
		//for(auto j : i)
			//cout << j << ' ';
		//cout << endl;
	//}
	//cout << endl;
	//for(auto i : pow(a,0x3f3f3f3f3f3f3f3f)){
		//for(auto j : i)
			//cout << j << ' ';
		//cout << endl;
	//}
	//cout << endl;
//}