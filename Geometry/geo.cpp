/* BISMILLAHIR RAHMANIR RAHIM */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double pi = acos(-1);
const double eps = 1e-8;

//typedef double T;
typedef long long T;
inline int dcmp(T x) {
	//if( fabs(x) < eps ) return 0; // for double
	if( x == 0 ) return 0; // for int
	return x < 0 ? -1 : 1;
}

struct Point {
	T x, y;
	Point() { x = y = 0; }
	Point(T _x, T _y) { x = _x, y = _y; }
	bool operator == (Point o) const { return !dcmp(x - o.x) and !dcmp(y - o.y); }
	bool operator < (Point o) const { return !dcmp(x - o.x) ? (dcmp(y - o.y) < 0) : (dcmp(x - o.x) < 0); }
	Point operator + (Point o) const { return {x + o.x, y + o.y}; }	
	Point operator - (Point o) const { return {x - o.x, y - o.y}; }
	Point operator * (T a) const { return {x * a, y * a}; }
	Point operator / (T a) const { return {x / a, y / a}; }
};

typedef Point Vector;
namespace Vectorial {
	T dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
	T cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
	T lenSq(Vector a) { return a.x * a.x + a.y * a.y; }
	double len(Vector a) { return sqrt(lenSq(a)); }
	double getAngleInRad(Vector a, Vector b) { return acos(dot(a, b) / (len(a) * len(b))); }
};

struct Line {
	Point a, b;
	Line() { }
	Line(Point _a, Point _b) { a = _a, b = _b; }
};

namespace Linear {
	using namespace Vectorial;
	bool onSegment(Point a, Point b, Point p) {
		return dcmp(cross(a - p, b - p)) == 0 and dcmp(dot(a - p, b - p)) <= 0;
	}
	int linePointRelation(Line l, Point p) {
		int c = dcmp(cross(p - l.a, l.b - l.a));
		if( c < 0 ) return 1; // ccw
		if( c > 0 ) return 2; // cw
		return 0;             // colinear
	}
	double distancePoint2Line(Point p, Line l) {
		return abs(cross(p - l.a, l.b -l.a)) / len(l.b - l.a);
	}
	Point intersectPoint(Line l1, Line l2) {
		T a1 = cross(l2.b - l2.a, l1.a - l2.a);
		T a2 = cross(l2.b - l2.a, l1.b - l2.a);
		return {(l1.a.x * a2 - l1.b.x * a1) / (a2 - a1), (l1.a.y * a2 - l1.b.y * a1) / (a2 - a1)}; 
	}
};

typedef vector<Point> Polygon;
namespace Polygonal {
	using namespace Vectorial;

	Polygon getConvexPolygon(vector<Point>& p) {
		int n = p.size();
		if( n <= 1 ) return p;  
		sort(p.begin(), p.end());
		int cnt = 0;
		Polygon q(n + n);
		for(int i = 0; i < n; q[cnt++] = p[i++])
			for(; cnt >= 2 and dcmp(cross( q[cnt - 1] - q[cnt - 2], p[i] - q[cnt - 2] )) >= 0; --cnt);

		for(int i = n - 2, t = cnt; i >= 0; q[cnt++] = p[i--])
			for(; cnt > t and dcmp(cross( q[cnt - 1] - q[cnt - 2], p[i] - q[cnt - 2] )) >= 0; --cnt);

		q.resize(cnt - 1 - (q[0] == q[1]));
		return q;
	}
	bool pointInConvexPolygon(Polygon& p, Point a) {
		int n = p.size();
		assert(n >= 3);
		int lo = 1, hi = n - 1;
		if( dcmp(cross( p[lo] - p[0], p[hi] - p[0] )) > 0 ) swap(lo, hi);
		if( dcmp(cross( p[lo] - p[0], a - p[0] )) > 0 or 
			dcmp(cross( p[hi] - p[0], a - p[0] )) < 0 ) return false;
		while( abs(lo - hi) > 1 ) {
			int mid = (lo + hi) / 2;
			if( dcmp(cross( p[mid] - p[0], a - p[0] )) >= 0 ) hi = mid;
			else                                        lo = mid;
		} 
		return dcmp(cross( p[hi] - p[lo], a - p[lo] )) < 0;
	}
	double polygonArea(Polygon& p) {
		int n = p.size();
		if( n < 3 ) return 0;
		double area = 0;
		for(int i = 0; i < n - 1; i++) 
			area += cross( p[i] - p[0], p[i + 1] - p[0] );
	    
	    return fabs(area / 2.0);
	    //return abs(area); // for picks theorem
	}
	ll pointsOnBoundary(Polygon& p) {
		int n = p.size();
		ll ret = p.size();
		for(int i = 0; i < n; i++) {
			ll x = abs(p[i].x - p[(i + 1) % n].x);
			ll y = abs(p[i].y - p[(i + 1) % n].y);
			ret += __gcd(x, y) - 1;
		}
		return ret;
	}
	/** Picks theorem, S = I + B / 2 - 1; */
	ll numberOfInternalPoints(Polygon& p) {
		ll s = polygonArea(p); // s = s + s
		ll b = pointsOnBoundary(p);
		ll i = s + 2 - b;
		return i / 2; 
	}
	//(nlogn) solution using ternary search
	double minFarPointFromEdges(Polygon& p) {
		int n = p.size();
		if( n <= 2 ) return 0;
		double ret = 1e18;
		for(int i = 0; i < n; i++) {
			int j = (i + 1) % n;
			int r = (i - 1 + n) % n;
			int l = (j + 1) % n;
			while( (r - l + n) % n > 2 ) {
				int d = ((r - l + n) % n) / 3;
				int m1 = (l + d) % n;
				int m2 = (r - d + n) % n;
				//use fabs() when the points are double
				if( dcmp(abs(cross(p[j] - p[i], p[m1] - p[i])) - 
					abs(cross(p[j] - p[i], p[m2] - p[i]))) > 0 ) r = m2;
				else l = m1;
			}
			double h = max(abs(cross(p[j] - p[i], p[l] - p[i])), 
							abs(cross(p[j] - p[i], p[r] - p[i])));
			if( l != r ) h = max(h, (double)abs(cross(p[j] - p[i], p[(l + 1) % n] - p[i])));
			ret = min(ret, h / len(p[i] - p[j])); 
		}
		return ret;
	}
};

int main() {
	ios_base :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
}
