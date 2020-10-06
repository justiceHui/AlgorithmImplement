// Persistent Segment Tree
// Time Complexity : O(log N)
// call init(root[0], s, e) before use
// verify : BOJ7469, BOJ16978 (by Ryute)

#define PST_MAX 101010
typedef ll size_v;
struct PSTNode {
	PSTNode* l, * r; size_v v;
	PSTNode() { l = r = nullptr; v = 0; }
};
struct PST {
	PSTNode* root[PST_MAX];
	int n, cnt;
	PST(int _n) : n(_n), cnt(0) { memset(root, 0, sizeof root); }
	void init(PSTNode* node, int s, int e, vector<size_v>& in) {
		if (s == e) { if (!in.empty()) node->v = in[s]; return; }
		int m = s + e >> 1;
		node->l = new PSTNode; node->r = new PSTNode;
		init(node->l, s, m, in); init(node->r, m + 1, e, in);
		node->v = node->l->v + node->r->v;
	}
	void init(vector<size_v>& in) { root[0] = new PSTNode; cnt++; init(root[0], 0, n - 1, in); }
	void init() { vector<size_v> tmp; init(tmp); }
	void update(PSTNode* prv, PSTNode* now, int s, int e, int x, size_v v) {
		if (s == e) { now->v = v; return; }
		// IF addition query: DO if (s == e) { now->v = prv ? prv->v + v : v; return; }
		int m = s + e >> 1;
		if (x <= m) {
			now->l = new PSTNode; now->r = prv->r;
			update(prv->l, now->l, s, m, x, v);
		}
		else {
			now->r = new PSTNode; now->l = prv->l;
			update(prv->r, now->r, m + 1, e, x, v);
		}
		size_v t1 = now->l ? now->l->v : 0;
		size_v t2 = now->r ? now->r->v : 0;
		now->v = t1 + t2;
	}
	void update(int prv_idx, int x, size_v v) {
		root[cnt] = new PSTNode;
		update(root[prv_idx], root[cnt], 0, n - 1, x, v); cnt++;
	} void update(int x, size_v v) { update(cnt - 1, x, v); }
	size_v query(PSTNode* node, int s, int e, int l, int r) {
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) return node->v;
		int m = s + e >> 1;
		return query(node->l, s, m, l, r) + query(node->r, m + 1, e, l, r);
	} size_v query(int root_idx, int l, int r) { return query(root[root_idx], 0, n - 1, l, r); }
	int kth(PSTNode* prv, PSTNode* now, int s, int e, int k) { //MUST be an addition query
		if (s == e) return s;
		int m = s + e >> 1;
		size_v diff = now->l->v - prv->l->v;
		if (k <= diff) return kth(prv->l, now->l, s, m, k);
		else return kth(prv->r, now->r, m + 1, e, k - diff);
	} int kth(int st, int en, int k) { return kth(root[st - 1], root[en], 0, n - 1, k); }
};