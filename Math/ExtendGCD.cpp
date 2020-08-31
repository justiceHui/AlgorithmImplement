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
ll inv(ll a, ll m){ //return x when ax mod m = 1, fail -> -1
    ll x, y;
    ll g = ext_gcd(a, m, x, y);
    if(g > 1) return -1;
    return mod(x, m);
}