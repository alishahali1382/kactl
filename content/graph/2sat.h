/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: myself
 * Description: 2-sat solver. 
 * Negated variables are represented by (\texttt{{}x xor 1}).
 * Time: O(N+E)
 * Status: accepted-on-cf
 */
#pragma once

const int MAXN=1e5+10;

bool mark[MAXN*2];
int comp[MAXN*2], id=1;
vector<int> G[MAXN*2], GR[MAXN*2];
vector<int> topol;

void add_edge(int u, int v){
	G[u].pb(v);
	GR[v].pb(u);
}
void add_clause(int u, int v){
	add_edge(u^1, v);
	add_edge(v^1, u);
}
void dfs1(int node){
	mark[node]=1;
	for (int v:G[node]) if (!mark[v]) dfs1(v);
	topol.pb(node);
}
void dfs2(int node, int cid){
	comp[node]=cid;
	for (int v:GR[node]) if (!comp[v]) dfs2(v, cid);
}
void SCC(){
	for (int i=0; i<MAXN*2; i++) if (!mark[i]) dfs1(i);
	reverse(all(topol));
	for (int v:topol) if (!comp[v]) dfs2(v, id++);
}
bool SAT(){
	SCC();
	for (int i=0; i<MAXN; i+=2) if (comp[i]==comp[i^1]) return 0;
	return 1;
}