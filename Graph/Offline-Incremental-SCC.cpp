#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_V = 101010;
constexpr int MAX_E = 252525;

struct Edge{ int s, e; };

template<size_t _Sz> struct UnionFind {
    int P[_Sz];
    UnionFind(){ iota(P, P+_Sz, 0); }
    int find(int v){ return v == P[v] ? v : P[v] = find(P[v]); }
    bool merge(int u, int v){
        u = find(u); v = find(v);
        if(u == v) return false;
        P[u] = v; return true;
    }
};

template<size_t _Sz> struct SCC {
    vector<int> G[_Sz], R[_Sz], dfn, use;
    int id[_Sz], pv;
    int cnt[_Sz];
    void clear(){
        for(auto i : use) cnt[id[i]] = 0, G[i].clear(), R[i].clear(), id[i] = 0;
        dfn.clear(); use.clear(); pv = 0;
    }
    void addEdge(int s, int e){
        G[s].push_back(e);
        R[e].push_back(s);
        use.push_back(s);
        use.push_back(e);
    }
    void dfs(int v){
        id[v] = 1;
        for(auto i : G[v]) if(!id[i]) dfs(i);
        dfn.push_back(v);
    }
    void rfs(int v, int color){
        id[v] = color; cnt[color]++;
        for(auto i : R[v]) if(!id[i]) rfs(i, color);
    }
    void getSCC(){
        for(auto i : use) if(!id[i]) dfs(i);
        reverse(dfn.begin(), dfn.end());
        for(auto i : use) id[i] = 0;
        for(auto i : dfn) if(!id[i]) rfs(i, ++pv);
    }
};

int N, M;
Edge E[MAX_E];
UnionFind<MAX_V> uf;
SCC<MAX_V> scc;
int Time[MAX_E]; // connect time

void Solve(int s, int e, const vector<int> &li){
    if(s == e){
        for(const auto &i : li) uf.merge(E[i].s, E[i].e), Time[i] = s;
        // @TODO : operation (uf: maintain scc)
        return;
    }
    scc.clear();

    int m = s + e >> 1;
    for(const auto &i : li){
        int st = uf.find(E[i].s), ed = uf.find(E[i].e);
        if(i <= m) scc.addEdge(st, ed);
    }
    scc.getSCC();

    vector<int> l, r;
    for(const auto &i : li){
        if(i > m){ r.push_back(i); continue; }
        int st = uf.find(E[i].s), ed = uf.find(E[i].e);
        if(scc.id[st] == scc.id[ed]) l.push_back(i);
        else r.push_back(i);
    }
    Solve(s, m, l);
    Solve(m+1, e, r);
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> N >> M;
    for(int i=1; i<=M; i++) cin >> E[i].s >> E[i].e;

    vector<int> li(M);
    iota(li.begin(), li.end(), 1);
    Solve(1, M+1, li);
}
