// k-d tree : find closest point from arbitrary point
// Time Complexity : average O(log N), worst O(N)
// verify : BOJ7890

struct KDNode{
    pll v; bool dir;
    ll sx, ex, sy, ey;
    KDNode(){ sx = sy = inf; ex = ey = -inf; }
};
const auto xcmp = [](pll a, pll b){ return tie(a.x, a.y) < tie(b.x, b.y); };
const auto ycmp = [](pll a, pll b){ return tie(a.y, a.x) < tie(b.y, b.x); };
struct KDTree{
    // Segment Tree Size
    static const int S = 1 << 18;
    KDNode nd[S]; int chk[S];
    vector<pll> v;
    KDTree(){ init(); }
    void init(){ memset(chk, 0, sizeof chk); }
    void _build(int node, int s, int e){
        chk[node] = 1;
        nd[node].sx = min_element(v.begin()+s, v.begin()+e+1, xcmp)->x;
        nd[node].ex = max_element(v.begin()+s, v.begin()+e+1, xcmp)->x;
        nd[node].sy = min_element(v.begin()+s, v.begin()+e+1, ycmp)->y;
        nd[node].ey = max_element(v.begin()+s, v.begin()+e+1, ycmp)->y;
        nd[node].dir = !nd[node/2].dir;
        
        if(nd[node].dir) sort(v.begin()+s, v.begin()+e+1, ycmp);
        else sort(v.begin()+s, v.begin()+e+1, xcmp);
        
        int m = s + e >> 1; nd[node].v = v[m];
        if(s <= m-1) _build(node << 1, s, m-1);
        if(m+1 <= e) _build(node << 1 | 1, m+1, e);
    }
    void build(const vector<pll> &_v){
        v = _v; sort(all(v));
        _build(1, 0, v.size()-1);
    }
    ll query(pll t, int node = 1){
        ll tmp, ret = inf;
        if(t != nd[node].v) ret = min(ret, dst(t, nd[node].v));
        bool x_chk = (!nd[node].dir && xcmp(t, nd[node].v));
        bool y_chk = (nd[node].dir && ycmp(t, nd[node].v));
        if(x_chk || y_chk){
            if(chk[node << 1]) ret = min(ret, query(t, node << 1));
            if(chk[node << 1 | 1]){
                if(nd[node].dir) tmp = nd[node << 1 | 1].sy - t.y;
                else tmp = nd[node << 1 | 1].sx - t.x;
                if(tmp*tmp < ret) ret = min(ret, query(t, node << 1 | 1));
            }
        }
        else{
            if(chk[node << 1 | 1]) ret = min(ret, query(t, node << 1 | 1));
            if(chk[node << 1]){
                if(nd[node].dir) tmp = nd[node << 1].ey - t.y;
                else tmp = nd[node << 1].ex - t.x;
                if(tmp*tmp < ret) ret = min(ret, query(t, node << 1));
            }
        }
        return ret;
    }
};