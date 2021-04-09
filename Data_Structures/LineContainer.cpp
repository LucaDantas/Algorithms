#include <set>
#include <cassert>
using namespace std;

constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

struct Line
{
	long long a, b, x; // vou codar com inteiros msm
	Line(long long _a = 0, long long _b = 0, long long _x = inf) : a(_a), b(_b), x(_x) {}
	bool operator<(const Line& o) const { return a < o. a; } // change < for >, for min queries
	bool operator<(const long long& o) const { return x < o; }
};

struct LineContainer : multiset<Line, less<>>
{
	bool hasNext(iterator it) { return next(it) != end(); }
	bool hasPrev(iterator it) { return it != begin(); }
	long long div(long long a, long long b) { return a / b - ((a^b)<0 && a%b); }
	long long intersect(Line l1, Line l2) { return div(l1.b-l2.b, l2.a-l1.a); }
	bool bad(Line l1, Line l2, Line l3) { return intersect(l1, l3) <= intersect(l1, l2); }
	iterator get_x(iterator it) {
		if(!hasNext(it)) return it;
		Line l = *it;
		l.x = intersect(l, *next(it));
		erase(it);
		return insert(l);
	}
	void add(long long a, long long b) {
		Line l(a, b);
		auto it = lower_bound(l);
		if(it != end() && it->a == a) {
			if(it->b >= b) return;
			erase(it);
		}
		it = insert(l);
		if(hasPrev(it) && hasNext(it) && bad(*prev(it), *it, *next(it)))
			return (void)(erase(it));
		while(hasPrev(it) && hasPrev(prev(it)) && bad(*prev(prev(it)), *prev(it), *it))
			erase(prev(it));
		while(hasNext(it) && hasNext(next(it)) && bad(*it, *next(it), *next(next(it))))
			erase(next(it));
		it = get_x(it);
		if(hasPrev(it)) get_x(prev(it));
	}
	long long query(long long x) {
		assert(!empty());
		auto it = lower_bound(x);
		return it->a*x + it->b;
	}
};
