// dependency :
// find x, y such that ax + by = gcd(a, b)
// Time Complexity : O(log min(a, b))

ll gcd(ll x, ll y) { return y ? gcd(y, x%y) : x; }
ll lcm(ll x, ll y) { return x / gcd(x, y) * y; }
ll mod(ll a, ll b) { return ((a%b) + b) % b; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) { //ax + by = gcd(a, b)
    ll g = a; x = 1, y = 0;
    if (b) g = ext_gcd(b, a % b, y, x), y -= a / b * x;
    return g;
}
ll inv(ll a, ll m){ //return x when (ax mod m = 1), fail -> -1
    ll x, y;
    ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}
// Return (z, M), fail -> M = -1
pll crt(ll a1, ll m1, ll a2, ll m2){
    ll s, t; ll g = ext_gcd(m1, m2, s, t);
    if(a1 % g != a2 % g) return pll(0, -1);
    s = mod(s*a2, m2); t = mod(t*a1, m1);
    ll res = mod(s*(m1/g) + t*(m2/g), m1/g*m2), M = m1/g*m2;
    return pll(res, M);
}
pll crt(const vector<ll> &a, const vector<ll> &m){
    if(a.size() == 1) return pll(a[0], m[0]);
    pll ret = crt(a[0], m[0], a[1], m[1]);
    for(int i=2; i<a.size(); i++) ret = crt(ret.x, ret.y, a[i], m[i]);
    return ret;
}