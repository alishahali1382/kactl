/**
 * Author: Ali Shahali
 * Date: 2020-06-17
 * License: CC0
 * Source: myself
 * Description: Finds all biconnected components in an undirected graph,
 *  And returns the Block-Decomposition of graph,
 *  that is a bipartite graph which represents connections between BCCs and vertices.
 * Time: O(E + V)
 * Status: accepted on APIO2018-duathlon
 */
#pragma once

vector<int> bcc;
int dfs(int node){
	int res=h[node]=h[par[node]]+1;
	bcc.pb(node);
	for (int v:G[node]){
		if (!h[v]) par[v]=node, res=min(res, dfs1(v));
		else res=min(res, h[v]);
	}
	if (res==h[par[node]]){
		while (1){
			int v=bcc.back();
			bcc.pop_back();
			E.pb({node+n, v});
			if (v==node) break ;
		}
		E.pb({node+n, par[node]});
	}
	if (!par[node]) bcc.pop_back();
	return res;
}