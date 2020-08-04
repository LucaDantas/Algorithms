#include<bits/stdc++.h>
using namespace std;

using ll = long long;

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

using polygon = vector<Pt>;

bool cw(Pt a, Pt b, Pt c) { return (b-a)/(c-a) < 0; }
bool ccw(Pt a, Pt b, Pt c) { return (b-a)/(c-a) > 0; }
bool col(Pt a, Pt b, Pt c) { return (b-a)/(c-a) == 0; }

polygon hull(polygon& pts) {
	int n = (int)pts.size();
	sort(pts.begin(), pts.end(), [](const Pt& a, const Pt& b) {
		if(a.x == b.x) return a.y < b.y;
		return a.x < b.x;
	});
	polygon upper, lower;
	upper.push_back(pts[0]); lower.push_back(pts[0]);
	for(int i = 1; i < n; i++) {
		if(i == n-1 || ccw(pts[0], pts.back(), pts[i])) {
			while(upper.size() >= 2 && !cw(upper[(int)upper.size()-2], upper.back(), pts[i]))
				upper.pop_back();
			upper.push_back(pts[i]);
		}
		if(i == n-1 || cw(pts[0], pts.back(), pts[i])) {
			while(lower.size() >= 2 && !ccw(lower[(int)lower.size()-1], lower.back(), pts[i]))
				lower.pop_back();
			lower.push_back(pts[i]);
		}
	}
	polygon complete = upper;
	for(int i = (int)lower.size() - 2; i >= 1; i--)
		complete.push_back(lower[i]);
	return complete;
}

int main() {
	
}