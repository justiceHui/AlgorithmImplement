#define x first
#define y second
typedef long long ll;
typedef pair<ll, ll> p;
istream& operator >> (istream &in, p &t){ in >> t.x >> t.y; return in; }
ostream& operator << (ostream &out, p t){ out << t.x << t.y; return out; }
p operator + (p a, p b){ return p(a.x + b.x, a.y + b.y); }
p operator - (p a, p b){ return p(a.x - b.x, a.y - b.y); }

inline ll _ccw(const p &a, const p &b){ return a.x*b.y - b.x*a.y; }
inline ll _ccw(const p &a, const p &b, const p &c){ return _ccw(b-a, c-b); }
inline ll area(const p &a, const p &b, const p &c){ return abs(_ccw(a, b, c)); }
inline int ccw(const p &a, const p &b, const p &c){
    ll cw = _ccw(a, b, c);
    if(cw > 0) return 1;
    if(cw) return -1;
    return 0;
}
inline ll dst(const p &a, const p &b){
    ll dx = b.x - a.x, dy = b.y - a.y;
    return dx*dx + dy*dy;
}