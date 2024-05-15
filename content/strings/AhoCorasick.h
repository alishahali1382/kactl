/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: stress-tested
 */
#pragma once

const int MAXN=1e5, SGM=26;
struct Aho{
	int C[MAXN][SGM], F[MAXN], ts;
	int Q[MAXN], QL, QR;
	int AddTrie(string &s){
		int v=0;
		for (char ch:s){
			if (!C[v][ch-'a']) C[v][ch-'a']=++ts;
			v=C[v][ch-'a'];
		}
		return v;
	}
	void BuildAho(){
		for (int i=0; i<SGM; i++) if (C[0][i]) Q[QR++]=C[0][i];
		while (QL<QR){
			int v=Q[QL++];
			// if (ID[v]) UP[v]=v;
			// else UP[v]=UP[F[v]];
			// G[F[v]].pb(v);
			for (int i=0; i<SGM; i++){
				if (!C[v][i]) C[v][i]=C[F[v]][i];
				else{
					Q[QR++]=C[v][i];
					F[C[v][i]]=C[F[v]][i];
				}
			}
		}
	}
};