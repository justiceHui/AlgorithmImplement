const int SPLAY_TREE = 1;
const int LINK_CUT_TREE = 2;
struct LinkCutNode{
  LinkCutNode *l, *r, *p;
  ll sz, v, mn; bool flip, dummy;
  LinkCutNode() : LinkCutNode(0) {}
  LinkCutNode(ll _v) : LinkCutNode(_v, nullptr) {}
  LinkCutNode(ll _v, LinkCutNode *_p){
    p = _p; l = r = nullptr;
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
    x->sz = 1; x->mn = x->v;
    if(x->l) x->sz += x->l->sz, x->mn = min(x->mn, x->l->mn);
    if(x->r) x->sz += x->r->sz, x->mn = min(x->mn, x->r->mn);
  }
  void push(LinkCutNode *x){
    if(!x->flip) return;
    swap(x->l, x->r); x->flip = 0;
    if(x->l) x->l->flip ^= 1;
    if(x->r) x->r->flip ^= 1;
  }
  void rotate(LinkCutNode *x){
    if(!x->p) return;
    auto p = x->p; push(p); push(x);
    if(_is_left(x)) x->r && (x->r->p = p), p->l = x->r, x->r = p;
    else x->l && (x->l->p = p), p->r = x->l, x->l = p;
    if(!_is_root(p)) (_is_left(p)? p->p->l : p->p->r) = x;
    else if(type == SPLAY_TREE) root = x;
    x->p = p->p; p->p = x; update(p); update(x);
  }
  LinkCutNode* splay(LinkCutNode *x, LinkCutNode *g = nullptr){
    for(; !_is_root(x) && x->p != g; rotate(x)){
      if(_is_root(x->p) || x->p->p == g) continue;
      if(x->p->p != g) rotate(_is_left(x) ^ _is_left(x->p) ? x : x->p);
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
  LinkCutNode* splay_flip(int s, int e){ // flip range [s, e]
    LinkCutNode *x = splay_gather(s, e);
    x->flip = !x->flip; return x;
  }
  LinkCutNode* splay_shift(int s, int e, int k){ //rightShift(k) range [s, e]
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
    splay(x); push(x); x->r = nullptr; update(x);
    for(; x->p; splay(x)){
      splay(x->p); push(x->p); x->p->r = x; update(x->p);
    }
  }
  void lct_link(int _u, int _p){
    auto u = nd[_u], p = nd[_p];
    access(u); access(p); push(u);
    u->l = p; p->p = u; update(u);
  }
  void lct_cut(int _u){
    auto u = nd[_u]; access(u); push(u);
    u->l->p = 0; u->l =	nullptr; update(u);
  }
  LinkCutNode* lct_lca(int _u, int _v){
    auto u = nd[_u], v = nd[_v];
    access(u); access(v); splay(u);
    return u->p? u->p : u;
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
  void inorder(LinkCutNode *x){
    push(x);
    if(x->l) inorder(x->l);
    if(!x->dummy) print(x);
    if(x->r) inorder(x->r);
  }
  bool _is_left(LinkCutNode *x){ return x == x->p->l; }
  bool _is_root(LinkCutNode *x){ return !x->p || (!_is_left(x) && x != x->p->r); }
} tree;