/**
 * Author: Ali Shahali
 * Date: 2020-06-16
 * License: CC0
 * Source: https://codeforces.com/contest/438/submission/83926262
 * Description: same as fft, be careful for mod. 998244353 is ok.
 * Time: O(N \log N)
 * Status: accepted-on-codeforces
 */
#pragma once

typedef vector<ll> Poly;
void NTT(Poly &A, bool inv){
	int n=A.size(), lg=0;
	while ((1<<lg)<n) lg++; A.resize(n=(1<<lg), 0);
	for (int i=1; i<n; i++){
		rev[i]=(rev[i>>1]>>1) | ((i&1)<<(lg-1));
		if (rev[i]<i) swap(A[rev[i]], A[i]);
	}
	for (int len=1; len<n; len<<=1){
		ll wn=powmod(3, mod/2/len);
		if (inv) wn=powmod(wn, mod-2);
		for (int i=0; i<n; i+=2*len){
			ll w=1;
			for (int j=i; j<i+len; j++){
				ll x=A[j], y=A[j+len]*w;
				A[j]=(x+y)%mod;
				A[j+len]=(x-y)%mod;
				w=w*wn%mod;
			}
		}
	}
	ll invn=powmod(n, mod-2);
	if (inv) for (int i=0; i<n; i++) A[i]=A[i]*invn%mod;
}
