/**
 * Author: Ali Shahali
 * Source: https://codeforces.com/contest/696/submission/69587196
 * Description: HLD
 * Time: O((\log N)^2)
 */
#pragma once

void dfs1(int node){/* find subtree-size, parents, and heights*/}
void dfs2(int node, int hd){
	head[node]=hd;
	stt[node]=timer++;
	ras[stt[node]]=node;
	int big=0;
	for (int v:G[node]) if (v!=par[node] && sz[v]>sz[big]) big=v;
	if (big) dfs2(big, hd);
	for (int v:G[node]) if (v!=par[node] && v!=big) dfs2(v, v);
	fnt[node]=timer;
}
pll GetPath(int u, int v){
	pll res={INF, -1};
	while (head[u]!=head[v]){
		if (h[head[u]]>h[head[v]]) swap(u, v);
		res=min(res, Get(1, 1, n+1, stt[head[v]], stt[v]+1));
		v=par[head[v]];
	}
	if (h[u]>h[v]) swap(u, v);
	res=min(res, Get(1, 1, n+1, stt[u], stt[v]+1));
	return res;
}