/**
 * Author: Ali Shahali
 * License: CC0
 * Source: myself
 * Description: Eulerian Walk
 * Time: O(V + E)
 * Status: stress-tested
 */
#pragma once

inline void add_edge(int u, int v, int id){
	G[u].pb({v, id});
	GR[v].pb({u, id});
}
void euler(int node){
	while (SZ(GR[node])){
		int u=GR[node].back().first, id=GR[node].back().second;
		GR[node].pop_back();
		if (mark[id]) continue ;
		mark[id]=1;
		euler(u);
		tour.pb(id);
	}
}