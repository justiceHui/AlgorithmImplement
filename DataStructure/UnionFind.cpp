// Union Find with Roll Back
// Time Complexity : O(log N), Space Complexity : O(N)
// call init(n) or constructor(n) before use

struct UnionFind{
	typedef pair<int, int> pii;
	vector<int> par, rnk;
	vector<pii> rollback;
	UnionFind(){ }
	UnionFind(int n){ init(n); }
	void init(int n){
		par.resize(n+1);
		rnk.resize(n+1);
		iota(par.begin(), par.end(), 0);
		fill(rnk.begin(), rnk.end(), 1);
		rollback.clear();
	}
	int find(int v){ return v == par[v] ? v : find(par[v]); }
	bool merge(int u, int v){
		u = find(u), v = find(v);
		if(u == v) return 0;
		if(rnk[u] > rnk[v]) swap(u, v);
		par[u] = v;
		if(rnk[u] == rnk[v]) rnk[v]++;
		rollback.push_back({u, v});
		return 1;
	}
	void undo(){
		assert(!rollback.empty());
		int u = rollback.back().x, v = rollback.back().y;
		rollback.pop_back();
		par[u] = u;
		if(rnk[u] == rnk[v]+1) rnk[v]--;
	}
};