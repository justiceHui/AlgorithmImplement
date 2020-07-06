// Heavy Light Decomposition
// dfs : undirected graph(inp) -> directed graph(g)
// dfs1 : get subtree size, node depth, parent node
// dfs2 : make heavy chain, euler tour trick

namespace HLD{
	const int SZ = 101010;
	vector<int> inp[SZ], g[SZ];
	int sz[SZ], par[SZ], dep[SZ], top[SZ], in[SZ], out[SZ];
	void addEdge(int s, int e){
		inp[s].push_back(e); inp[e].push_back(s);
	}
	void dfs(int v, int b = -1){
		for(auto i : inp[v]) if(i != b) g[v].push_back(i), dfs(i);
	}
	void dfs1(int v){
		sz[v] = 1;
		for(auto &i : g[v]){
			dep[i] = dep[v] + 1; par[i] = v;
			dfs1(i); sz[v] += sz[i];
			if(sz[i] > sz[g[v][0]]) swap(i, g[v][0]);
		}
	}
	void dfs2(int v){
		in[v] = ++pv;
		for(auto i : g[v]) top[i] = (i == g[v][0]) ? top[v] : i, dfs2(i);
		out[v] = pv;
	}
	void hld(int root){ dfs(root); dfs1(root); dfs2(root); }
	void updatePath(int u, int v, ll x){
		for(; top[u]!=top[v]; u=par[top[u]]){
			if(dep[top[u]] < dep[top[v]]) swap(u, v);
			update(in[top[u]], in[u], x);
		}
		if(dep[u] > dep[v]) swap(u, v);
		update(in[u], in[v], x);
		// if edge query, then update(in[u]+1, in[v], x)
	}
	ll queryPath(int u, int v){
		ll ret = 0;
		for(; top[u]!=top[v]; u=par[top[u]]){
			if(dep[top[u]] < dep[top[v]]) swap(u, v);
			ret += query(in[top[u]], in[u]);
		}
		if(dep[u] > dep[v]) swap(u, v);
		ret += query(in[u], in[v]);
		// if edge query, then query(in[u]+1, in[v])
		return ret;
	}
}