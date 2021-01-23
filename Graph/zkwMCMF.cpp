// dependency :
// get Min Cost Max Flow
// zkw MCMF (hell-joseon MCMF)
// optimized for short-augmenting-path

template<typename FlowType, typename CostType, int _Sz, FlowType _Inf_f=1'000'000'007, CostType _Inf=1'000'000'007>
struct ZKW{
    struct Edge{ int v, dual; FlowType c; CostType d; };
    vector<Edge> G[_Sz];
    bool InQ[_Sz], Check[_Sz];
    CostType Pi[_Sz], Dist[_Sz];
    int Work[_Sz];
    void AddEdge(int s, int e, FlowType c, CostType d){
        G[s].push_back({e, (int)G[e].size(), c, d});
        G[e].push_back({s, (int)G[s].size()-1, 0, -d});
    }
    void Init(int S, int T){
        fill(Pi, Pi+_Sz, _Inf);
        fill(Dist, Dist+_Sz, _Inf);

        // Johnson's Algorithm with SPFA
        memset(InQ, false, sizeof InQ);
        queue<int> Q; Q.push(S); InQ[S] = true;
        while(Q.size()){
            int v = Q.front(); Q.pop(); InQ[v] = false;
            for(const auto &i : G[v]){
                if(i.c && Pi[i.v] > Pi[v] + i.d){
                    Pi[i.v] = Pi[v] + i.d;
                    if(!InQ[i.v]) InQ[i.v] = true, Q.push(i.v);
                }
            }
        }
        for(int i=0; i<_Sz; i++) for(auto &j : G[i]) if(j.c) j.d += Pi[i] - Pi[j.v];

        // Get Shortest Path DAG with Dijkstra
        priority_queue<pair<CostType, int>> pq; pq.emplace(0, S); Dist[S] = 0;
        while(pq.size()){
            auto [cst, now] = pq.top(); pq.pop(); cst = -cst;
            if(Dist[now] != cst) continue;
            for(auto i : G[now]){
                if(i.c && Dist[i.v] > Dist[now] + i.d){
                    Dist[i.v] = Dist[now] + i.d;
                    pq.emplace(-Dist[i.v], i.v);
                }
            }
        }
        for(int i=0; i<_Sz; i++) Dist[i] += Pi[T] - Pi[S];
    }
    bool Update(){ // Update DAG in O(V+E)
        CostType mn = _Inf;
        for(int i=0; i<_Sz; i++){
            if(!Check[i]) continue;
            for(const auto &j : G[i]){
                if(j.c && !Check[j.v]) mn = min(mn, Dist[i] + j.d - Dist[j.v]);
            }
        }
        if(mn == _Inf) return false;
        for(int i=0; i<_Sz; i++) if(!Check[i]) Dist[i] += mn;
        return true;
    }
    FlowType DFS(int v, int T, FlowType tot){
        Check[v] = true;
        if(v == T) return tot;
        for(int &_i=Work[v]; _i<G[v].size(); _i++){
            auto &i = G[v][_i];
            if(Check[i.v] || !i.c || Dist[i.v] != Dist[v] + i.d) continue;
            FlowType fl = DFS(i.v, T, min(tot, i.c));
            if(!fl) continue;
            i.c -= fl;
            G[i.v][i.dual].c += fl;
            return fl;
        }
        return 0;
    }
    pair<FlowType, CostType> MinCostFlow(int S, int T){
        Init(S, T);
        FlowType fl = 0, tmp; CostType cst = 0;
        do{
            memset(Check, false, sizeof Check);
            memset(Work, 0, sizeof Work);
            while((tmp = DFS(S, T, _Inf_f))){
                fl += tmp;
                cst += Dist[T] * tmp;
                memset(Check, false, sizeof Check);
            }
        }while(Update());
        return make_pair(fl, cst);
    }
};