#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Hashing{
	//1e9-63, 1e9+7, 1e9+9, 1e9+103
	//1e5+3, 1e5+13, 131071, 524287
	vector<ll> hash1, base1;
	ll p, mod;
	
	Hashing(){
		p = 1e9-63, mod = 179;
	}
	
	Hashing(ll _p, ll _mod) : p(_p), mod(_mod) {}
	
	Hashing(string &s, ll _p, ll _mod) : Hashing(_p, _mod) {
		int n = s.size();
		hash1 = vector<ll>(n+1, 0);
		base1 = vector<ll>(n+1, 0);
		base1[0] = 1; base1[1] = p;
		for(int i=n-1; i>=0; i--){
			hash1[i] = (s[i] + hash1[i+1] * p) % mod;
		}
		for(int i=2; i<=n; i++){
			base1[i] = base1[i-1] * p % mod;
		}
	}
	
	int substr(int l, int r){ //[s, e]
		ll ret = hash1[l] - hash1[r+1] * base1[r-l+1];
		ret %= mod; ret += mod; ret %= mod;
		return ret;
	}
}h1, h2;

string s; int m;

bool chk(int q, int x){
	if(x == 0) return 1;
	
	int a = h1.substr(s.size()-x, s.size()-1);
	int b = h1.substr(q-x, q-1);
	
	int aa = h2.substr(s.size()-x, s.size()-1);
	int bb = h2.substr(q-x, q-1);
	
	return a == b && aa == bb;
}

int main(){
//BOJ13713
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> s >> m;
	h1 = Hashing(s, 1e9-63, 131071);
	h2 = Hashing(s, 1e9+9, 100005);
	while(m--){
		int t; cin >> t;
		int l = 0, r = t, mid;
		while(l <= r){
			mid = l + r >> 1;
			bool now = chk(t, mid);
			bool prv = chk(t, mid+1);
			if(now && !prv) break;
			if(!now) r = mid-1;
			else l = mid+1;
		}
		cout << mid << "\n";
	}
}
