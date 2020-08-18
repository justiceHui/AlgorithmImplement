// LCA in O(1) time
// Time Complexity : pre-process O(N log N) Query O(1), Space Complexity : O(N log N)
// add all edges and call buildConstantLCA()

typedef pair<int, int> p;

namespace SparseTableRMQ{
    const int SZ = 505050*2, LG = 22; // Array Size, log2(SZ)
    int pw2[LG], lg2[SZ]; // 2^i, floor( log2(i) )
    p a[SZ], sparse[LG][SZ];
    // 1-based
    void build_sparse(int n){
        pw2[0] = 1; memset(lg2, -1, sizeof lg2);
        for(int i=1; i<LG; i++) pw2[i] = pw2[i-1] * 2;
        for(int i=0; i<LG; i++) if(pw2[i] < SZ) lg2[pw2[i]] = i;
        for(int i=0; i<SZ; i++) if(lg2[i] == -1) lg2[i] = lg2[i-1];
        
        for(int i=1; i<=n; i++) sparse[0][i] = a[i];
        for(int i=1; i<LG; i++) for(int j=1; j<=n; j++){
                sparse[i][j] = min(sparse[i-1][j], sparse[i-1][j+(1<<(i-1))]);
            }
    }
    p query(int l, int r){ int k = lg2[r-l+1]; return min(sparse[k][l], sparse[k][r-pw2[k]+1]); }
}

const int MV = 505050;
int n, q, dep[MV];
int tour[MV*2], pv, st[MV];
vector<int> g[MV];

void addEdge(int s, int e){ g[s].push_back(e); g[e].push_back(s); }
void dfs(int v, int b){
    tour[++pv] = v; st[v] = pv;
    for(auto i : g[v]) if(i != b){
            dep[i] = dep[v] + 1; dfs(i, v);
            tour[++pv] = v;
        }
}
void buildConstantLCA(){
    dfs(1, -1);
    for(int i=1; i<=pv; i++) SparseTableRMQ::a[i] = {dep[tour[i]], tour[i]};
    SparseTableRMQ::build_sparse(pv);
}
int lca(int u, int v){
    u = st[u]; v = st[v];
    if(u > v) swap(u, v);
    return SparseTableRMQ::query(u, v).y;
}