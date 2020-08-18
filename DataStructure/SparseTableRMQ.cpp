// RMQ with Sparse Table
// Time Complexity : pre-process O(N log N) Query O(1), Space Complexity : O(N log N)
// fill SparseTableRMQ::a[1..N] and call build_sparse(N)
// query(s, e) : Min( A[s], A[s+1], ... , A[e] )

namespace SparseTableRMQ{
    const int SZ = 505050, LG = 22; // Array Size, log2(SZ)
    int pw2[LG], lg2[SZ]; // 2^i, floor( log2(i) )
    int a[SZ], sparse[LG][SZ];
    // 1-based
    void input(int n){
        for(int i=1; i<=n; i++) cin >> a[i];
    }
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
    int query(int l, int r){ int k = lg2[r-l+1]; return min(sparse[k][l], sparse[k][r-pw2[k]+1]); }
}