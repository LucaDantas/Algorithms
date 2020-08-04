#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
constexpr ld eps = 1e-9;

// int -> long long points

ll sq(int x) {
	return 1ll * x * x;
}
struct Pt {
	int x, y;
	Pt(int _x, int _y) : x(_x), y(_y) {}
	Pt() {}
	Pt operator+(Pt a) { return Pt(x+a.x, y+a.y); }
	Pt operator-(Pt a) { return Pt(x-a.x, y-a.y); }
	void operator-=(Pt a) { x -= a.x; y -= a.y; }
	void operator+=(Pt a) { x += a.x; y += a.y; }
	ll operator*(Pt a) { // dot -> cos(theta)
		return 1ll * x * a.x + 1ll * y * a.y;
	}
	ll operator/(Pt a) { // cross -> sin(theta)
		return 1ll * x * a.y - 1ll * y * a.x;
	}
	ll operator%(Pt a) { // square of the distance
		return sq(a.x - x) + sq(a.y - y);
	}
	bool operator==(Pt a) { return x == a.x && y == a.y; }
	bool operator!=(Pt a) { return x != a.x || y != a.y; }
	friend ostream& operator<<(ostream& os, const Pt& a) {
		return os << '(' << a.x << ", " << a.y << ')';
	}
};

// long double points
ld sq(ld a) {
	return a*a;
}
struct Pt {
	ld x, y;
	Pt(ld _x, ld _y) : x(_x), y(_y) {}
	Pt(double _x, double _y) : x(_x), y(_y) {}
	Pt(int _x, int _y) : x(_x), y(_y) {}
	Pt() : x(0), y(0) {}
	Pt operator+(Pt a) { return Pt(x+a.x, y+a.y); }
	Pt operator-(Pt a) { return Pt(x-a.x, y-a.y); }
	void operator-=(Pt a) { x -= a.x; y -= a.y; }
	void operator+=(Pt a) { x += a.x; y += a.y; }
	ld operator*(Pt a) { // dot -> cos(theta)
		return x * a.x + y * a.y;
	}
	ld operator/(Pt a) { // cross -> sin(theta)
		return x * a.y - y * a.x;
	}
	ld operator%(Pt a) { // distance (sqrt taken)
		return sqrtl(sq(a.x - x) + sq(a.y - y));
	}
	bool operator==(Pt a) { return x - a.x < eps && y - a.y < eps; }
	bool operator!=(Pt a) { return fabs(x - a.x) >= eps || fabs(y - a.y) >= eps; }
	friend ostream& operator<<(ostream& os, const Pt& a) {
		return os << '(' << a.x << ", " << a.y << ')';
	}
};

int main() {

}