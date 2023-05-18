/**
 * Author: Luca Dantas
 * Description: Linear Convex Hull Trick. Add and query lines by slope order
 * can be adapted to query beginning or end and adding increasing or decreasing
 * Time: $O(\log N)$.
*/


struct Line
{
	long long a, b; // ax + b
	Line(long long _a, long long _b) : a(_a), b(_b) {}
	Line() {}
	long long val(long long x) { return a*x + b; }
	long double intersect(Line L) { return (long double)(L.b-b)/(a-L.a); }
};

struct CHT
{
	deque<Line> hull;
	void insert(Line L) {
		while(hull.size() >= 2 && L.intersect(hull.back())
			>= L.intersect(hull[(int)hull.size()-2]))
			hull.pop_back();
		hull.push_back(L);
	}
	Line query(long long x) {
		while(hull.size() >= 2 && hull[0].val(x) <= hull[1].val(x))
			hull.pop_front();
		return hull.front();
	}
} cht;
