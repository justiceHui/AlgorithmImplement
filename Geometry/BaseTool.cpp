#define x first
#define y second

using ll = long long;
using ld = long double;
using Point = pair<ll, ll>;
const ld eps = 1e-7;

istream& operator >> (istream &in, Point &t){ in >> t.x >> t.y; return in; }
Point operator + (Point p1, Point p2){ return {p1.x+p2.x, p1.y-p2.y}; }
Point operator - (Point p1, Point p2){ return {p1.x-p2.x, p1.y-p2.y}; }
ll    operator * (Point p1, Point p2){ return p1.x*p2.x + p1.y*p2.y; } /// dot product
ll    operator / (Point p1, Point p2){ return p1.x*p2.y - p2.x*p1.y; } /// cross product

ll _CCW(const Point &p1, const Point &p2, const Point &p3){ return (p2-p1)/(p3-p2); }
int CCW(Point p1, Point p2, Point p3){
    ll res = _CCW(p1, p2, p3);
    return (res > 0) - (res < 0);
}
ll D(const Point &p1, const Point &p2){
    ll dx = p1.x - p2.x, dy = p1.y - p2.y;
    return dx*dx + dy*dy;
}