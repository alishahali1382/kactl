/**
 * Author: Ali Shahali
 * Date: 2021-02-07
 * License: CC0
 * Source: https://codeforces.com/contest/286/submission/106748659
 * Description: do fft on both polynomials, then element-wise multiplications, and finally fft-inverse
 * Time: O(N \log N) 
 * Status: accepted-on-codeforces
 */
#pragma once

typedef complex<double> cd;
const double PI=acos(-1);
void fft(cd *A, int inv){
	int n=(1<<N);
	for (int i=1; i<n; i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(N-1));
	for (int i=1; i<n; i++) if (rev[i]<i) swap(A[rev[i]], A[i]);
	for (int ln=1; ln<n; ln<<=1){
		double theta=PI/ln*inv;
		cd wn(cos(theta), sin(theta));
		for (int i=0; i<n; i+=2*ln){
			cd wnk=1;
			for (int j=i; j<i+ln; j++){
				cd x=A[j], y=A[j+ln]*wnk;
				A[j]=x+y;
				A[j+ln]=x-y;
				wnk*=wn;
			}
		}
	}
	if (inv==-1) for (int i=0; i<n; i++) A[i]/=n;
}
