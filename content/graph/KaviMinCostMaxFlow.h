/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow. cap[i][j] != cap[j][i] is allowed; double edges are not.
 *  If costs can be negative, call setpi before maxflow, but note that negative cost cycles are not supported.
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against another implementation
 * Time: Approximately O(E^2)
 */
#pragma once

// #include <bits/extc++.h> /// include-line, keep-include

struct mcmf{
	struct edge{
		int to , flow , cap , cost;
	};
	int n , s , t , k;
	vector<int> dist , par;
	vector<edge> E;
	vector<vector<int>> adj;
	void init(int n){
		dist.clear(); par.clear(); E.clear(); adj.clear();
		dist.resize(n); par.resize(n); adj.resize(n);
	}
	void add(int v , int u , int cap , int cost){
		adj[v].push_back(SZ(E)); E.push_back({u , 0 , cap , cost});
		adj[u].push_back(SZ(E)); E.push_back({v , 0 , 0 , -cost});
	}
	int SPFA(){
		fill(all(dist) , MOD);
		fill(all(par) , -1);
		queue<int> q;
		dist[s] = 0; q.push(s);
		while(!q.empty()){
			int v = q.front(); q.pop();
			for(int i : adj[v]){
				int u = E[i].to , w = E[i].cost;
				if(E[i].flow == E[i].cap)	continue;
				if(dist[u] > dist[v] + w){
					dist[u] = dist[v] + w;
					par[u] = (i ^ 1);
					q.push(u);
				}
			}
		}
		return (dist[t] <= k);
	}
	int solve(){
		int x = t , mn = (dist[t] == 0 ? MOD : k / dist[t]) , ans = 0;
		while(par[x] != -1){
			mn = min(mn , E[par[x] ^ 1].cap - E[par[x] ^ 1].flow);
			x = E[par[x]].to;
		}
		ans += mn; k -= dist[t] * mn;
		x = t;
		while(par[x] != -1){
			E[par[x]].flow -= mn;
			E[par[x] ^ 1].flow += mn;
			x = E[par[x]].to;
		}
		return ans;
	}
	int maxFlow(int v , int u , int x){
		s = v , t = u , k = x;
		int ans = 0;
		while(SPFA())	ans += solve();
		return ans;
	}
};