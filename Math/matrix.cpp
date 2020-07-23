/*
	Matrix operations:
	This contains an optimized version for matrix exponentiation (fixed size square matrices)

	Also a version with more functionalities for general purpose
*/

// Matrix Exponentiation optimized

constexpr int mod = 1000000007;

int mul(int a, int b) {
	return (int)(1ll * a * b % mod);
}

void add_self(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

struct Matrix
{
	vector<vector<int>> mat;

	Matrix(int n) : mat(n, vector<int>(n)) {}

	Matrix() {}

	Matrix& operator*(const Matrix& a) {
		int n = sz(mat);

		static Matrix c;
		c.mat.assign(n, vector<int>(n));
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				for(int k = 0; k < n; k++)
					add_self(c.mat[i][j], mul(mat[i][k], a.mat[k][j]));

		return c;
	}

	friend ostream& operator<<(ostream &os, const Matrix& v) { 
		int n = sz(v.mat), m = sz(v.mat[0]);
		for(int i = 0; i < n; i++) {
			os << '['; string sep = "";
			for(int j = 0; j < m; j++) {
				os << sep << v.mat[i][j], sep = ", ";
			}
			os << "]\n";
		}
		return os;
	}
};

Matrix power(Matrix b, long long e) {
	int n = sz(b.mat);
	Matrix ans(n);
	rep(i,0,n) ans.mat[i][i] = 1;

	while(e) {
		if(e&1)
			ans = ans * b;
		b = b * b;
		e >>= 1;
	}

	return ans;
}

// General Version

constexpr int mod = 1000000007;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));
std::mt19937_64 rng64(std::chrono::steady_clock::now().time_since_epoch().count() ^ (long long) (make_unique<char>().get()));

template<typename T> T rnd(T v) {
  T k;
  if constexpr(sizeof(T) <= 32) k = (T) rng(); else k = (T) rng64();
  return (T) (((k % v) + v) % v);
}

template<typename T> T rnd(T l, T r) {
  if (r < l) swap(l, r);
  return (T) (l + rnd(r - l + 1));
}

// If no mod is needed just change those functions here

int mul(int a, int b) {
	return (int)(1ll * a * b % mod);
}

void add_self(int& a, int b) {
	a += b;
	if(a >= mod) a -= mod;
}

void sub_self(int& a, int b) {
	a -= b;
	if(a < 0) a += mod;
}

struct Matrix
{
	vector<vector<int>> mat;

	Matrix(int n) {
		mat.resize(n, vector<int>(n));
	}

	Matrix(int n, int m) {
		mat.resize(n, vector<int>(m));
	}

	Matrix() {}

	Matrix operator*(const Matrix& a) {
		int n = sz(mat), m = sz(mat[0]);
		int n2 = sz(a.mat), m2 = sz(a.mat[0]);

		assert(m == n2);

		Matrix c(n, m2);
		// static Matrix c;
		// c.mat.assign(n, vector<int>(m2));
		
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m2; j++)
				for(int k = 0; k < m; k++)
					add_self(c.mat[i][j], mul(mat[i][k], a.mat[k][j]));

		return c;
	}

	friend ostream& operator<<(ostream &os, const Matrix& v) { 
		int n = sz(v.mat), m = sz(v.mat[0]);
		rep(i,0,n) {
			os << '['; string sep = "";
			rep(j,0,m) {
				os << sep << v.mat[i][j], sep = ", ";
			}
			os << "]\n";
		}
		return os;
	}

	void rdm(int n) {
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				mat[i][j] = rnd(1, 1000000000);
	}

	void idt(int n) {
		for(int i = 0; i < n; i++) mat[i][i] = 1;
	}
};

Matrix power(Matrix b, long long e) {
	int n = sz(b.mat);
	Matrix ans(n);
	ans.idt(n);

	while(e) {
		if(e&1)
			ans = ans * b;
		b = b * b;
		e >>= 1;
	}

	return ans;
}

int main() {

}
