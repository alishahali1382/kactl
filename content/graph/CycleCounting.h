/**
 * Author: Ali Shahali
 * Date: 2024-05-15
 * License: CC0
 * Source: my code
 * Description: Counts the number of cycles of length 3 and 4.
 * Time: O(E\sqrt{E})
 * Status: tested of codeforces
 */
#pragma once

pll CountCycles(ll n, vi G[]){
	ll C3=0, C4=0;
	vi deg(n), ord(n), mark(n, 0), cnt(n, 0);
	vector<vi> G2(n, vi());
	for (int i=0; i<n; i++) deg[i]=SZ(G[i]);
	vi P(n);
	iota(all(P), 0);
	sort(all(P), [&](int i, int j){ return deg[i]<deg[j];});
	int t=1;
	for (int i=n-1; ~i; i--){
		int u=P[i];
		ord[u]=i;
		for (int v:G[u]) if (mark[v]==t) G2[u].pb(v);
		mark[u]=t;
	}
	for (auto v:P){
		t++;
		for (int u:G[v]) for (int w:G2[u]) if (ord[v]<ord[w]){
			if (mark[w]!=t) mark[w]=t, cnt[w]=0;
			C4+=cnt[w];
			cnt[w]++;
		}
		for (int u:G2[v]) if (mark[u]==t) C3+=cnt[u];
	}
	return pll(C3/2, C4);
}
