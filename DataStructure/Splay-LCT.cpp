// Splay Tree + Link Cut Tree
// Time Complexity : amortimzed O(log N)
// splay_init(element_count), lct_init(vertex_count)
// verify : BOJ13159(Splay Tree), BOJ13539(Link Cut Tree)

const int SPLAY_TREE = 1;
const int LINK_CUT_TREE = 2;
struct LinkCutNode{
    LinkCutNode *l, *r, *p, *pp;
    ll sz, v, mn, flip, dummy;
    LinkCutNode() : LinkCutNode(0) {}
    LinkCutNode(ll _v) : LinkCutNode(_v, nullptr) {}
    LinkCutNode(ll _v, LinkCutNode *_p){
        p = _p; pp = l = r = nullptr;
        sz = 1; v = mn = _v; flip = dummy = 0;
    }
    ~LinkCutNode(){ if(l) delete l; if(r) delete r; }
};
struct LinkCutTree{
    LinkCutNode *root, *nd[1010101]; int type;
    LinkCutTree() : root() { memset(nd, 0, sizeof nd); }
    ~LinkCutTree(){ if(root) delete root; }
    void splay_init(int n){
        type = SPLAY_TREE;
        if(root) delete root;
        auto *now = root = new LinkCutNode(-inf); //left dummy node
        for(int i=1; i<=n; i++){
            nd[i] =  now->r = new LinkCutNode(i, now); now = now->r;
        }
        now->r = new LinkCutNode(inf, now); //right dummy node
        root->dummy = now->r->dummy = 1;
        for(int i=n; i>=1; i--) update(nd[i]);
    }
    void lct_init(int n){
        type = LINK_CUT_TREE;
        for(int i=1; i<=n; i++) nd[i] = new LinkCutNode(i);
    }
    void update(LinkCutNode *x){
        x->mn = x->v; x->sz = 1;
        if(x->l) x->mn = min(x->mn, x->l->mn), x->sz += x->l->sz;
        if(x->r) x->mn = min(x->mn, x->r->mn), x->sz += x->r->sz;
    }
    void push(LinkCutNode *x){
        if(!x->flip) return;
        swap(x->l, x->r); x->flip = 0;
        if(x->l) x->l->flip ^= 1;
        if(x->r) x->r->flip ^= 1;
    }
    void rotate(LinkCutNode *x){
        if(!x->p) return;
        LinkCutNode *p = x->p, *y; push(p); push(x);
        if(x == p->l) p->l = y = x->r, x->r = p;
        else p->r = y = x->l, x->l = p;
        x->p = p->p; p->p = x;
        if(y) y->p = p;
        if(x->p && p == x->p->l) x->p->l = x;
        else if(x->p && p == x->p->r) x->p->r = x;
        else if(type == SPLAY_TREE) root = x;
        update(p); update(x);
        if(type == LINK_CUT_TREE && p->pp){
            x->pp = p->pp; p->pp = nullptr;
        }
    }
    LinkCutNode* splay(LinkCutNode *x, LinkCutNode *g = nullptr){
        while(x->p != g){
            LinkCutNode *p = x->p;
            if(p->p == g){ rotate(x); break; }
            auto pp = p->p;
            if((p->l == x) == (pp->l == p)) rotate(p), rotate(x);
            else rotate(x), rotate(x);
        }
        if(type == LINK_CUT_TREE || !g) return root = x;
        return root;
    }
    LinkCutNode* splay_kth(int k){ // 1-based, return kth element
        auto now = root; push(now);
        while(1){
            while(now->l && now->l->sz > k) now = now->l, push(now);
            if(now->l) k -= now->l->sz;
            if(!k) break; k--;
            now = now->r; push(now);
        }
        return splay(now);
    }
    LinkCutNode* splay_gather(int s, int e){ // gather range [s, e]
        auto a = splay_kth(e+1), b = splay_kth(s-1);
        return splay(a, b)->r->l;
    }
    void splay_flip(int s, int e){ // flip range [s, e]
        LinkCutNode *x = splay_gather(s, e);
        x->flip = !x->flip;
    }
    LinkCutNode* splay_shift(int s, int e, int k){ // right_shift(k) range [s, e]
        LinkCutNode *range = splay_gather(s, e);
        if(k >= 0){
            k %= (e-s+1); if(!k) return range;
            splay_flip(s, e); splay_flip(s, s+k-1); splay_flip(s+k, e);
        }else{
            k *= -1; k %= (e-s+1); if(!k) return range;
            splay_flip(s, e); splay_flip(s, e-k); splay_flip(e-k+1, e);
        }
        return splay_gather(s, e);
    }
    // get node index(position)
    int splay_getidx(int k){ return splay(nd[k])->l->sz; }
    
    void access(LinkCutNode *x){
        splay(x); push(x);
        if(x->r) x->r->pp = x, x->r = x->r->p = nullptr;
        update(x);
        while(x->pp){
            auto *nxt = x->pp;
            splay(nxt); push(nxt);
            if(nxt->r) nxt->r->pp = nxt, nxt->r = nxt->r->p = nullptr;
            nxt->r = x; x->p = nxt; x->pp = nullptr;
            update(nxt); splay(x);
        }
    }
    LinkCutNode* lct_root(int _x){
        auto x = nd[_x]; access(x); push(x);
        while(x->l) x = x->l, push(x);
        access(x); return x;
    }
    LinkCutNode* lct_par(int _x){
        auto x = nd[_x]; access(x); push(x);
        if (!x->l) return nullptr;
        x = x->l; push(x);
        while(x->r) x = x->r, push(x);
        access(x); return x;
    }
    LinkCutNode* lct_lca(int _s, int _t){
        auto s = nd[_s], t = nd[_t]; access(s); access(t); splay(s);
        if(!s->pp) return s; return s->pp;
    }
    void lct_link(int _son, int _par){
        auto son = nd[_son], par = nd[_par];
        access(par); access(son);
        son->flip ^= 1; // remove if needed
        push(son);
        son->l = par; par->p = son;
        update(son);
    }
    void lct_cut(int _son){
        auto son = nd[_son]; access(son); push(son);
        if(son->l) son->l = son->l->p = nullptr;
        update(son);
    }
    void inorder(LinkCutNode *x){
        push(x);
        if(x->l) inorder(x->l);
        if(!x->dummy) print(x);
        if(x->r) inorder(x->r);
    }
};