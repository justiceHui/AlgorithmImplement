using PII = pair<int, int>;

inline ll f(int s, int e){ return s * MAX_N + e; }
namespace splayTree{
    struct SplayNode{
        SplayNode *p, *l, *r;
        int a, b, sz, flag;
        SplayNode() : SplayNode(-1, -1){}
        SplayNode(int a, int b) : a(a), b(b) { l = r = p = nullptr; sz = 1; flag = 0; };
        friend int get_sz(const SplayNode *x) { return x ? x->sz : 0; }
        bool is_left() const { return p && this == p->l; }
        void update(){
            sz = 1 + get_sz(l) + get_sz(r);
        }
        void rotate(){
            if(is_left()) r && (r->p = p), p->l = r, r = p;
            else l && (l->p = p), p->r = l, l = p;
            if(p->p) (p->is_left()? p->p->l : p->p->r) = this;
            auto *t = p; p = t->p; t->p = this;
            t->update(); update();
        }
    };
    void splay(SplayNode *x){
        for(; x->p; x->rotate()){
            if(x->p->p) (x->is_left() ^ x->p->is_left() ? x : x->p)->rotate();
        }
    }
    SplayNode* concat(SplayNode *a, SplayNode *b){
        while(a->r) a = a->r; splay(a);
        a->r = b; b->p = a; a->update();
        return a;
    }
    bool is_same_tree(SplayNode *a, SplayNode *b){
        splay(a); splay(b);
        while(a->p) a = a->p;
        return a == b;
    }
}

struct EulerTourTree{
    unordered_map<ll, splayTree::SplayNode*> edges;
    EulerTourTree(int n){ for(int i=1; i<=n; i++) edges[f(i,i)] = new splayTree::SplayNode(i, i); }
    void reRoot(int v){
        auto x = edges[f(v,v)]; splay(x);
        auto xl = x->l, xr = x->r;
        if(!xl || !xr) return;
        x->l = x->r = xl->p = xr->p = nullptr; x->update();
        concat(xr, xl); concat(xl->p, x);
    }
    void link(int u, int v){
        if(is_connected(u,v)) return;
        auto x = edges[f(u,u)], y = edges[f(v,v)];
        reRoot(u); reRoot(v);
        splay(x); splay(y);
        auto e1 = edges[f(u,v)] = new splayTree::SplayNode(u, v);
        auto e2 = edges[f(v,u)] = new splayTree::SplayNode(v, u);
        concat(x, e1); concat(e1, y); concat(e1, e2);
    }
    void cut(int a, int b){
        if(!edges.count(f(a,b))) return;
        auto x = edges[f(a,b)], y = edges[f(b,a)];
        splay(x);
        auto xl = x->l, xr = x->r;
        if(xl) xl->p = nullptr;
        if(xr) xr->p = nullptr;
        splay(y);
        auto yl = y->l, yr = y->r;
        bool flag = xl && (xl == y || xl->p);
        if(yl) yl->p = nullptr;
        if(yr) yr->p = nullptr;
        if(flag) yl && xr && concat(yl, xr);
        else xl && yr && concat(xl, yr);
        edges.erase(f(a,b)); edges.erase(f(b,a));
        delete x; delete y;
    }
    bool is_connected(int u, int v){
        return is_same_tree(edges[f(u,u)], edges[f(v,v)]);
    }
    int size(int v){
        auto x = edges[f(v,v)];
        splay(x); return x->sz;
    }
};
