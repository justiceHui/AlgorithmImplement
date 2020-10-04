// NTT - Polynomial Multiply with Special Modulo
// Time Complexity : O(N log N)

/*
p = (a*2^b+1) |   a  b w
-----------------------
104,857,601   |  25 22 3
998,244,353   | 119 23 3
2,281,701,377 |  17 27 3
2,483,027,969 |  37 26 3
2,113,929,217 |  63 25 5
1,092,616,193 | 521 21 3
*/
typedef vector<ll> poly;
template<ll mod, ll w>
class NTT{
public:
    void ntt(poly &f, bool inv = 0){
        int n = f.size(), j = 0;
        vector<ll> root(n/2);
        for(int i=1; i<n; i++){
            int bit = n/2;
            while(j >= bit) j -= bit, bit >>= 1;
            j += bit;
            if(i < j) swap(f[i], f[j]);
        }
        ll ang = pw(w, (mod - 1) / n, mod); if(inv) ang = pw(ang, mod - 2, mod);
        root[0] = 1; for(int i=1; i<n/2; i++) root[i] = root[i-1] * ang % mod;
        for(int i=2; i<=n; i*=2){
            int step = n / i;
            for(int j=0; j<n; j+=i){
                for(int k=0; k<i/2; k++){
                    ll u = f[j | k], v = f[j | k | i/2] * root[step * k] % mod;
                    f[j | k] = (u + v) % mod;
                    f[j | k | i/2] = (u - v) % mod;
                    if(f[j | k | i/2] < 0) f[j | k | i >> 1] += mod;
                }
            }
        }
        ll t = pw(n, mod - 2, mod);
        if(inv) for(int i=0; i<n; i++) f[i] = f[i] * t % mod;
    }
    vector<ll> multiply(poly &_a, poly &_b){
        vector<ll> a(all(_a)), b(all(_b));
        int n = 2;
        while(n < a.size() + b.size()) n <<= 1;
        a.resize(n); b.resize(n);
        ntt(a); ntt(b);
        for(int i=0; i<n; i++) a[i] = a[i] * b[i] % mod;
        ntt(a, 1);
        return a;
    }
};