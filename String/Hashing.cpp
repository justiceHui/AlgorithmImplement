/******************************
Author: jhnah917(Justice_Hui)
g++ -std=c++17 -DLOCAL
******************************/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<ll P, ll M> struct Hashing{
    vector<ll> H, B;
    void Build(const string &S){
        H.resize(S.size()+1);
        B.resize(S.size()+1);
        B[0] = 1;
        for(int i=1; i<=S.size(); i++) H[i] = (H[i-1] * P + S[i-1]) % M;
        for(int i=1; i<=S.size(); i++) B[i] = B[i-1] * P % M;
    }
    ll sub(int s, int e){
        ll res = (H[e] - H[s-1] * B[e-s+1]) % M;
        return res < 0 ? res + M : res;
    }
};

constexpr int P1 = 1299709, M1 = 1'000'000'007;
constexpr int P2 = 1301021, M2 = 1'000'000'009;

Hashing<P1, M1> H1;
Hashing<P2, M2> H2;

pair<int,int> sub(int s, int e){
    return {H1.sub(s, e), H2.sub(s, e)};
}

int main(){
    // BOJ 1786
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    string S, P;
    getline(cin, S);
    getline(cin, P);

    H1.Build(P); H2.Build(P);
    int P_H1 = H1.H.back();
    int P_H2 = H2.H.back();

    H1.Build(S); H2.Build(S);

    vector<int> res;
    for(int i=1; i+P.size()-1<=S.size(); i++){
        if(sub(i, i+P.size()-1) == make_pair(P_H1, P_H2)) res.push_back(i);
    }

    cout << res.size() << "\n";
    for(auto i : res) cout << i << " ";
}
