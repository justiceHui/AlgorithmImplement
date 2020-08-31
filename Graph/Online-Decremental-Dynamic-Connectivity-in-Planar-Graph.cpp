// dependency :
// Online Decremental Dynamic Connectivity in Planar Graphs
// Time Complexity : O((N+Q) log N), amortized O(log N) per query, Space Complexity : O(V + E)

#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

typedef long long ll;

namespace Solver{
#define x first
#define y second
	typedef pair<ll, ll> p;
	const int MV = 101010, ME = 101010; // MAX_V, MAX_E
	
	namespace DualGraph{
		p pt[MV];
		vector<p> g[MV]; // g[s].emplace_back(e, edge_id);
		set<p> gph[MV]; // g[s].emplace_back(e, edge_id);
		vector<int> dual_pt;
		
		ll ccw(const p &a, const p &b, const p &c){
			ll dx1 = b.x - a.x, dy1 = b.y - a.y;
			ll dx2 = c.x - b.x, dy2 = c.y - b.y;
			ll res = dx1*dy2 - dx2*dy1;
			if(res > 0) return 1;
			if(res) return -1;
			return 0;
		}
		
		// Union Find
		int par[ME * 2];
		void uf_init(){ iota(par, par+ME*2, 0); }
		int find(int v){ return v == par[v] ? v : par[v] = find(par[v]); }
		int merge(int u, int v){
			u = find(u); v = find(v);
			if(u == v) return 0;
			par[u] = v; return 1;
		}
		
		p base;
		bool cmp_angle(const p &_a, const p &_b){
			p a = pt[_a.x], b = pt[_b.x];
			if((a > base) != (b > base)) return a > b;
			return ccw(a, base, b) > 0;
		}
		
		void addEdge(int s, int e, int id){
			g[s].emplace_back(e, id);
			g[e].emplace_back(s, id);
			gph[s].emplace(e, id); // if use removeEdge
			gph[e].emplace(s, id); // if use removeEdge
		}
		
		void removeEdge(int s, int e, int id){
			gph[s].erase(gph[s].find(p(e, id)));
			gph[e].erase(gph[e].find(p(s, id)));
		}
		
		int out; //outer face
		void getDual(int n, int m){
			uf_init();
			for(int i=1; i<=n; i++){
				base = pt[i];
				sort(all(g[i]), cmp_angle);
				// up, left : *2+1
				// down, right : *2
				for(int j=0; j<g[i].size(); j++){
					int k = j ? j - 1 : g[i].size()-1;
					int u = g[i][k].y << 1 | 1, v = g[i][j].y << 1;
					p p1 = pt[g[i][k].x], p2 = pt[g[i][j].x];
					if(p1 > base) u ^= 1;
					if(p2 > base) v ^= 1;
					merge(u, v);
				}
			}
			int mn_idx = min_element(pt+1, pt+n+1) - pt;
			out = find(g[mn_idx][0].y << 1 | 1);
			
			for(int i=1; i<=m; i++){
				dual_pt.push_back(find(i << 1));
				dual_pt.push_back(find(i << 1 | 1));
			}
			compress(dual_pt);
		}
	}
	
	map<p, int> edgeList;
	int visitCheck[101010];
	int vertexColor[101010], colorCount = 0;
	
	void _coloring(int a, int b){
		colorCount++;
		vector<p> stk[2];
		vector<int> arr[2];
		stk[0].emplace_back(a, 0);
		stk[1].emplace_back(b, 0);
		while(stk[0].size() && stk[1].size()){
			for(int i=0; i<2; i++){
				int v = stk[i].back().x, c = stk[i].back().y; stk[i].pop_back();
				arr[i].push_back(v); visitCheck[v] = colorCount;
				auto it = DualGraph::gph[v].lower_bound(p(c, -1));
				if(it == DualGraph::gph[v].end()) continue;
				stk[i].emplace_back(v, it->x + 1);
				if(visitCheck[it->x] != colorCount) stk[i].emplace_back(it->x, 0);
			}
		}
		if(stk[0].empty()) for(auto i : arr[0]) vertexColor[i] = colorCount;
		else for(auto i : arr[1]) vertexColor[i] = colorCount;
	}
	
	void _addPoint(int x, int y, int idx){ DualGraph::pt[idx] = p(x, y); }
	void _addEdge(int a, int b, int idx){
		if(a > b) swap(a, b);
		DualGraph::addEdge(a, b, idx);
		edgeList[p(a, b)] = idx;
	}
	
	void _getGraphInfo(int n, int m){
		for(int i=1; i<=n; i++){
			int x, y; cin >> x >> y;
			_addPoint(x, y, i);
		}
		for(int i=1; i<=m; i++){
			int u, v; cin >> u >> v;
			_addEdge(u, v, i);
		}
	}
	
	void _dfs(int v, int color){
		vertexColor[v] = color;
		for(auto i : DualGraph::g[v]) if(!vertexColor[i.x]) _dfs(i.x, color);
	}
	
	// Call after add edge
	void buildSolver(int n, int m){
		_getGraphInfo(n, m);
		DualGraph::getDual(n, m);
		for(int i=1; i<=n; i++) if(!vertexColor[i]) _dfs(i, ++colorCount);
	}
	
	void removeEdge(int a, int b){
		if(a > b) swap(a, b);
		if(edgeList.find(p(a, b)) == edgeList.end()) return;
		int edge_id = edgeList[p(a, b)];
		edgeList.erase(p(a, b));
		DualGraph::removeEdge(a, b, edge_id);
		if(DualGraph::merge(edge_id << 1, edge_id << 1 | 1)) return;
		_coloring(a, b);
	}
	
	bool isConnected(int a, int b){ return vertexColor[a] == vertexColor[b]; }

#undef x
#undef y
}

// use example
int main(){
	const int REMOVE_EDGE = 1;
	const int IS_CONNECTED = 2;
	
	int n, m, q;
	cin >> n >> m >> q;
	Solver::buildSolver(n, m);
	for(int i=0; i<q; i++){
		int op, a, b;
		cin >> op >> a >> b;
		if(op == REMOVE_EDGE) Solver::removeEdge(a, b);
		else if(op == IS_CONNECTED) cout << Solver::isConnected(a, b) << "\n";
	}
}