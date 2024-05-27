/**
 * Author: Ali Shahali
 * Date: 2020-06-16
 * Source: https://codeforces.com/blog/entry/12513
 * Description: computes Inverse and Sqrt of generating function
 * Time: O(N \log N) 
 * Status: Accepted on codeforces
 */

#pragma once

typedef vector<ll> Poly;
Poly Inverse(Poly A){ // A[0]!=0  /// start-hash
	Poly B={powmod(A[0], mod-2)};
	for (int n=1; n<A.size(); n<<=1){
		Poly C(4*n, 0), D(4*n, 0);
		for (int i=0; i<2*n; i++) C[i]=A[i];
		for (int i=0; i<n; i++) D[i]=B[i];
		NTT(C, 0);
		NTT(D, 0);
		for (int i=0; i<4*n; i++) C[i]=C[i]*D[i]%mod*D[i]%mod;
		NTT(C, 1);
		B.resize(2*n, 0);
		for (int i=0; i<2*n; i++) B[i]=(2*B[i]-C[i])%mod;
	}
	return B;
} /// end-hash

Poly Sqrt(Poly A){ // A[0]=1  /// start-hash
	Poly B={1};
	for (int n=1; n<A.size(); n<<=1){
		B.resize(2*n, 0);
		Poly C=A, D=Inverse(B);
		C.resize(2*n, 0);
		C.resize(4*n, 0);
		D.resize(4*n, 0);
		NTT(C, 0);
		NTT(D, 0);
		for (int i=0; i<4*n; i++) C[i]=C[i]*D[i]%mod;
		NTT(C, 1);
		for (int i=0; i<2*n; i++) B[i]=(B[i]+C[i])*(mod+1)/2%mod;
	}
	return B;
} /// end-hash