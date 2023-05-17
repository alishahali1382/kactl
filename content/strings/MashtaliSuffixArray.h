/**
 * Author: Ali Shahali
 * Date: 2020-12-13
 * Source: https://oj.uz/submission/335699
 * Description: Builds suffix array for a string.
 * Time: O(n \log n)
 * Status: accepted on APIO14-palindrome
 */
#pragma once

int Rank[LOG][MAXN], P[MAXN], P2[MAXN], cnt[MAXN];
bool cmp(int x, int y, int pw){
	if (Rank[pw][x]!=Rank[pw][y]) return Rank[pw][x]<Rank[pw][y];
	if (max(x, y)+(1<<pw)>=m) return x>y;
	return Rank[pw][x+(1<<pw)]<Rank[pw][y+(1<<pw)]; 
}
void BuildSuffixArray(string S){  // m=SZ(S);
	for (int i=0; i<m; i++) P[i]=i;
	sort(P, P+m, [](int i, int j){ return S[i]<S[j];});
	for (int i=1; i<m; i++) Rank[0][P[i]]=Rank[0][P[i-1]]+(S[P[i-1]]<S[P[i]]);
	for (int j=0; j+1<LOG; j++){
		int x=0;
		for (int i=0; i<m; i++) if (P[i]+(1<<j)>=m) P2[x++]=P[i];
		for (int i=0; i<m; i++) if ((1<<j)<=P[i]) P2[x++]=P[i]-(1<<j);
		for (int i=0; i<m; i++) cnt[i]=0;
		for (int i=0; i<m; i++) cnt[Rank[j][i]]++;
		for (int i=1; i<m; i++) cnt[i]+=cnt[i-1];
		for (int i=m-1; ~i; i--) P[--cnt[Rank[j][P2[i]]]]=P2[i];
		for (int i=1; i<m; i++) Rank[j+1][P[i]]=Rank[j+1][P[i-1]] + cmp(P[i-1], P[i], j);
	}
}
int GetLcp(int x, int y){
	if (x<y) swap(x, y);
	int res=0;
	for (int i=LOG-1; ~i && x<m; i--) if (Rank[i][x]==Rank[i][y]){
		x+=(1<<i);
		y+=(1<<i);
		res|=(1<<i);
	}
	return res;
}