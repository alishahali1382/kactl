/**
 * Author: Parsa Alizadeh
 * Date: 2023-05-15
 * Source: Kolompeh
 * Description: Returns a vector of antipodal pairs of points.
 * Time: O(n \log n)
 * Status: tested with kattis:roberthood
*/

#pragma once

#include "Point.h"

typedef Point<ll> P;
vector<pair<P, P>> get_antipodals(vector<P> &p) {
    int n = SZ(p);
    sort(all(p));
    vector<P> U, L; // upper and lower hull
    for (int i = 0; i < n; i++) {
        while (SZ(U) > 1 && U[SZ(U)-2].cross(U[SZ(U)-1], p[i]) >= 0)
            U.pop_back();
        while (SZ(L) > 1 && L[SZ(L)-2].cross(L[SZ(L)-1], p[i]) <= 0)
            L.pop_back();
        U.push_back(p[i]);
        L.push_back(p[i]);
    }
    vector<pair<P, P>> res;
    int i = 0, j = SZ(L) - 1;
    while (i + 1 < SZ(U) || j > 0) {
        res.push_back({U[i], L[j]});
        if (i + 1 == SZ(U))
            j--;
        else if (j == 0)
            i++;
        else if ((L[j] - L[j-1]).cross(U[i+1] - U[i]) >= 0)
            i++;
        else
            j--;
    }
    return res;
}
