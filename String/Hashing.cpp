using ll = long long;

template<ll P, ll M> struct Hashing{
    vector<ll> H, B;
    void Build(const vector<int> &S){
        H.resize(S.size()+1);
        B.resize(S.size()+1);
        B[0] = 1;
        for(int i=1; i<=S.size(); i++) H[i] = (H[i-1] * P + S[i-1]) % M;
        for(int i=1; i<=S.size(); i++) B[i] = B[i-1] * P % M;
    }
    ll sub(int s, int e){
        s++; e++;
        ll res = (H[e] - H[s-1] * B[e-s+1]) % M;
        return res < 0 ? res + M : res;
    }
};
