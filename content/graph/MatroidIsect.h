/**
 * Author: BQI343
 * Description: Computes a set of maximum size which is independent 
 	* in both graphic and colorful matroids, aka a spanning forest where
 	* no two edges are of the same color. In general, construct the exchange
 	* graph and find a shortest path. Can apply similar concept to partition
 	* matroid.
 * Time: $O(GI^{1.5})$ calls to oracles, where $G$ is size of ground set 
 	* and $I$ is size of independent set.
 * Source: https://codeforces.com/blog/entry/69287
 	* chilli (KACTL)
 * Usage: MatroidIsect<Gmat,Cmat> M(sz(ed),Gmat(ed),Cmat(col))
 */

// struct Matroid { // sample matroid
// 	void clear() {}
// 	void ins(int i) {} // insert i
// 	bool indep(int i) {} // can insert i?
// };
template<class M1, class M2> struct MatroidIsect {
	int n; vector<bool> iset; M1 m1; M2 m2;
	bool augment() {  /// start-hash
		vi pre(n+1,-1); queue<int> q({n});
		while (sz(q)) {
			int x = q.front(); q.pop();
			if (iset[x]) {
				m1.clear(); F0R(i,n) if (iset[i] && i != x) m1.ins(i);
				F0R(i,n) if (!iset[i] && pre[i] == -1 && m1.indep(i))
					pre[i] = x, q.push(i);
			} else {
				auto backE = [&]() { // back edge
					m2.clear(); 
					F0R(c,2) F0R(i,n) if((x==i || iset[i]) && (pre[i]==-1)==c){
						if (!m2.indep(i)) return c ? pre[i]=x,q.push(i),i : -1;
						m2.ins(i);
					}
					return n;
				};
				for (int y; (y = backE()) != -1;) if (y == n) { 
					for(; x != n; x = pre[x]) iset[x] = !iset[x];
					return 1;
				}
			}
		}
		return 0;
	}  /// end-hash
	MatroidIsect(int n, M1 m1, M2 m2):n(n), m1(m1), m2(m2) {  /// start-hash
		iset.assign(n+1,0); iset[n] = 1;
		m1.clear(); m2.clear(); // greedily add to basis
		R0F(i,n) if (m1.indep(i) && m2.indep(i)) 
			iset[i] = 1, m1.ins(i), m2.ins(i); 
		while (augment());
	}  /// end-hash
};
