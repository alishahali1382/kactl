/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: Simple bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Time: O(VE)
 * Usage: vi btoa(m, -1); dfsMatching(g, btoa);
 * Status: works
 */
#pragma once

bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {  /// start-hash
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	for (int e : g[di])
		if (!vis[e] && find(e, g, btoa, vis)) {
			btoa[e] = di;
			return 1;
		}
	return 0;
}  /// end-hash
int dfsMatching(vector<vi>& g, vi& btoa) {  /// start-hash
	vi vis;
	rep(i,0,SZ(g)) {
		vis.assign(SZ(btoa), 0);
		for (int j : g[i])
			if (find(j, g, btoa, vis)) {
				btoa[j] = i;
				break;
			}
	}
	return SZ(btoa) - (int)count(all(btoa), -1);
}   /// end-hash
