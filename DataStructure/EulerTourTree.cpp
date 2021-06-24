using PII = pair<int, int>;

struct SplayNode{
    SplayNode *l, *r, *p;
    int sz;
    SplayNode() : sz(1) { l = r = p = nullptr; }
    ~SplayNode(){ if(l) delete l; if(r) delete r; }
    bool is_left() const { return p && this == p->l; }
    bool is_root() const { return !p || (this != p->l && this != p->r); }
    friend int get_sz(const SplayNode *x){ return x == nullptr ? 0 : x->sz; }
    void update(){ sz = 1 + get_sz(l) + get_sz(r); }
    void push(){ }
    void rotate(){
        p->push(); push();
        if(is_left()) r && (r->p = p), p->l = r, r = p;
        else l && (l->p = p), p->r = l, l = p;
        if(p->p) (p->is_left()? p->p->l : p->p->r) = this;
        auto *t = p; p = t->p; t->p = this;
        t->update(); update();
    }
};
SplayNode* splay(SplayNode *x){
    for(; !x->is_root(); x->rotate()){
        if(!x->p->is_root()) x->p->p->push(); x->p->push(); x->push();
        if(!x->p->is_root()) (x->is_left() ^ x->p->is_left() ? x : x->p)->rotate();
    }
    x->push();
    return x;
}
SplayNode* insertRight(SplayNode *root, SplayNode *x){
    if(!root) return x;
    while(root->r) root = root->r;
    splay(root);
    root->r = x; x->p = root;
    root->update();
    return splay(x);
}
SplayNode* concat(SplayNode *a, SplayNode *b){
    while(a->r) a = a->r; splay(a);
    a->r = b; b->p = a;
    a->update();
    return splay(b);
}
bool sameTree(SplayNode *a, SplayNode *b){
    splay(a);
    SplayNode *x = b;
    while(x->p) x = x->p; splay(b);
    return a == x;
}

struct EulerTourTree{
    int n;
    vector<SplayNode*> nodes;
    map<PII, SplayNode*> edges;
    EulerTourTree() = default;
    ~EulerTourTree() = default;
    EulerTourTree(int n) : n(n), nodes(n+1) {
        for(int i=1; i<=n; i++) nodes[i] = edges[{i,i}] = new SplayNode;
    }
    void reRoot(int v){
        SplayNode *x = nodes[v]; splay(x);
        auto lft = x->l, rgt = x->r;
        if(lft == nullptr || rgt == nullptr) return;
        x->l = x->r = lft->p = rgt->p = nullptr; x->update();
        insertRight(concat(rgt, lft), x);
    }
    void link(int u, int v){
        reRoot(u); reRoot(v);
        SplayNode *x = nodes[u], *y = nodes[v];
        if(sameTree(x, y)) return;
        auto e1 = edges[{u,v}] = new SplayNode;
        auto e2 = edges[{v,u}] = new SplayNode;
        insertRight(x, e1);
        concat(e1, y);
        insertRight(y, e2);
    }
    void cut(int u, int v){
        if(edges.find(PII(u, v)) == edges.end()) return;
        SplayNode *x = edges[{u,v}], *y = edges[{v,u}];
        splay(x);
        SplayNode *xl = x->l, *xr = x->r;
        if(xl) xl->p = nullptr;
        if(xr) xr->p = nullptr;
        splay(y);
        bool flag = xl != nullptr && (xl == y || xl->p != nullptr);
        SplayNode *yl = y->l, *yr = y->r;
        if(yl) yl->p = nullptr;
        if(yr) yr->p = nullptr;

        if(flag) y->l && xr && concat(y->l, xr);
        else y->r && xl && concat(xl, y->r);
        x->l = x->r = x->p = y->l = y->r = y->p = nullptr;
        delete x; delete y;
        edges.erase(PII(u, v));
        edges.erase(PII(v, u));
    }
    bool connected(int u, int v){
        return sameTree(nodes[u], nodes[v]);
    }
};
