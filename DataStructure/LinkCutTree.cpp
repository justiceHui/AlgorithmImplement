struct Node{
    Node *l, *r, *p;
    bool flip; int sz;
    Node(){ l = r = p = nullptr; sz = 1; flip = false; }
    bool IsLeft() const { return p && this == p->l; }
    bool IsRoot() const { return !p || (this != p->l && this != p->r); }
    friend int GetSize(const Node *x){ return x ? x->sz : 0; }
    void Rotate(){
        if(IsLeft()) r && (r->p = p), p->l = r, r = p;
        else l && (l->p = p), p->r = l, l = p;
        if(!p->IsRoot()) (p->IsLeft() ? p->p->l : p->p->r) = this;
        auto t = p; p = t->p; t->p = this;
        t->Update(); Update();
    }
    void Update(){
        sz = 1 + GetSize(l) + GetSize(r);
    }
    void Push(){
        if(flip){
            swap(l, r);
            if(l) l->flip ^= 1;
            if(r) r->flip ^= 1;
            flip = false;
        }
    }
};
void Splay(Node *x){
    for(; !x->IsRoot(); x->Rotate()){
        if(!x->p->IsRoot()) x->p->p->Push(); x->p->Push(); x->Push();
        if(!x->p->IsRoot()) (x->IsLeft() ^ x->p->IsLeft() ? x : x->p)->Rotate();
    }
    x->Push();
}
void Access(Node *x){
    Splay(x); x->r = nullptr;
    for(; x->p; Splay(x)) Splay(x->p), x->p->r = x;
}
int GetDepth(Node *x){
    Access(x); return GetSize(x->l);
}
Node* GetRoot(Node *x){
    Access(x); x->Push();
    while(x->l) x = x->l, x->Push();
    Splay(x); return x;
}
Node* GetPar(Node *x){
    Access(x); if(!x->l) return nullptr;
    x = x->l; x->Push();
    while(x->r) x = x->r, x->Push();
    Splay(x); return x;
}
void Link(Node *p, Node *c){
    Access(c); Access(p); c->l = p; p->p = c;
}
void Cut(Node *x){
    Access(x); x->l->p = nullptr; x->l = nullptr;
}
void Cut(Node *x, Node *y){
    Cut(GetPar(x) == y ? x : y);
}
Node* GetLCA(Node *x, Node *y){
    Access(x); Access(y); Splay(x);
    return x->p ? x->p : x;
}
Node* Ancestor(Node *x, int k){
    k = GetDepth(x) - k; assert(k >= 0);
    for(;;x->Push()){
        int s = GetSize(x->l);
        if(s == k) return Access(x), x;
        if(s < k) k -= s + 1, x = x->r;
        else x = x->l;
    }
    assert(false);
}
void MakeRoot(Node *x){
    Access(x); Splay(x); x->flip ^= 1;
}
bool IsConnect(Node *x, Node *y){
    return GetRoot(x) == GetRoot(y);
}
