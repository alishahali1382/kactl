/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

struct MaxFlow{
	struct Edge{
		ll to , flow , cap;
	};
	ll n , s , t , D;
	vector<Edge> E;
	vector<vector<int>> adj;
	vector<int> ptr,  dist;
 
	void init(int N){
		n = N;
		E.clear(); adj.clear(); ptr.clear(); dist.clear();
		adj.resize(n); ptr.resize(n); dist.resize(n);
	}
	int addEdge(int v , int u , ll cap){
		adj[v].push_back(SZ(E)); E.push_back({u , 0 , cap});
		adj[u].push_back(SZ(E)); E.push_back({v , 0 , 0});
		return SZ(E) - 2;
	}
 
	int BFS(){
		fill(all(ptr) , 0);
		fill(all(dist) , MOD);
		queue<int> Q;
		Q.push(s); dist[s] = 0;
		while(!Q.empty()){
			int v = Q.front(); Q.pop();
			for(int i : adj[v]){
				ll u = E[i].to, rem = E[i].cap - E[i].flow;
				if(dist[u] == MOD && rem >= D){
					dist[u] = dist[v] + 1;
					Q.push(u);
				}
			}
		}
		return (dist[t] < MOD);
	}
 
	ll DFS(int v, ll f){
		if(v == t || f == 0){
			return f;
		}
		ll res = 0;
		for( ; ptr[v] < SZ(adj[v]) ; ptr[v]++){
			ll ind = adj[v][ptr[v]] , u = E[ind].to, rem = E[ind].cap - E[ind].flow;
			if(dist[v] + 1 != dist[u])	continue;
			ll cur = DFS(u , min(f , rem));
			f -= cur; res += cur;
			E[ind].flow += cur;
			E[ind ^ 1].flow -= cur;
			if(f == 0)	break;
		}
		return res;
	}
 
	ll maxFlow(int v , int u){
		ll ans = 0;
		s = v; t = u; D = INF;
		while(D > 0){
			while(BFS()){
				ans += DFS(v , INF);
			}
			D /= 2;
		}
		return ans;
	}
}