// Convex Hull Trick : max query
// Time Complexity : O(N), Space Complexity : O(N)
// call init() before use

struct CHT{
	struct Line{
		ll a, b, c; // y = ax + b, c = line index
		Line(ll a, ll b, ll c) : a(a), b(b), c(c) {}
		ll f(ll x){ return a * x + b; }
	};
	vector<Line> v; int pv;
	void init(){ v.clear(); pv = 0; }
	int chk(const Line &a, const Line &b, const Line &c){
		return (double)(a.b - b.b) / (b.a - a.a) >= (double)(c.b - b.b) / (b.a - c.a);
	}
	void insert(Line l){
		if(v.size() > pv && v.back().a == l.a){
			if(l.b < v.back().b) l = v.back();
			v.pop_back();
		}
		while(v.size() >= pv+2 && chk(v[v.size()-2], v.back(), l)) v.pop_back();
		v.push_back(l);
	}
	p query(ll x){
		// if min query, then v[pv].f(x) >= v[pv+1].f(x)
		while(pv+1 < v.size() && v[pv].f(x) <= v[pv+1].f(x)) pv++;
		return {v[pv].f(x), v[pv].c};
	}
} cht;