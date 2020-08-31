// dependency :
// get Max Flow
// Dinic's Algorithm
// Time Complexity : O(V^2 E), Space Complexity : O(V + E)

const int SZ = 888;
struct Dinic{
    using FlowType = int;
    const FlowType flow_max = 1e9;
    int s, t; // source, sink;
    struct Edge{ int v, dual; FlowType c; };
    vector<Edge> g[SZ];
    void addEdge(int s, int e, FlowType x){
        g[s].push_back({e, (int)g[e].size(), x});
        g[e].push_back({s, (int)g[s].size()-1, 0});
    }
    int lv[SZ], work[SZ];
    bool bfs(){
        memset(lv, -1, sizeof lv);
        queue<int> q; q.push(s); lv[s] = 0;
        while(!q.empty()){
            int v = q.front(); q.pop();
            for(auto i : g[v]){
                if(lv[i.v] == -1 && i.c > 0){
                    q.push(i.v); lv[i.v] = lv[v] + 1;
                }
            }
        }
        return lv[t] != -1;
    }
    FlowType dfs(int v, int tot){
        if(v == t) return tot;
        for(int &_i=work[v]; _i<g[v].size(); _i++){
            Edge &i = g[v][_i];
            if(lv[i.v] == lv[v] + 1 && i.c > 0){
                int fl = dfs(i.v, min(tot, i.c));
                if(fl > 0){
                    i.c -= fl;
                    g[i.v][i.dual].c += fl;
                    return fl;
                }
            }
        }
        return 0;
    }
    FlowType run(int _s, int _t){
        s = _s; t = _t; FlowType ret = 0;
        while(bfs()){
            memset(work, 0, sizeof work);
            FlowType tmp;
            while((tmp = dfs(s, flow_max))) ret += tmp;
        }
        return ret;
    }
};