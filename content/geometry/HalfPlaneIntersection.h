/**
 * Author: Parsa Alizadeh
 * Date: 2023-05-15
 * Source: Kolompeh
 * Description: Half-planes are to the left of given lines.
 * Status: Tested on poj:3130 and codechef:CHN02
 */

#pragma once

#include "Point.h"

const int MAXLINES = 1e5 + 10;
const int INF = 2e7;
typedef ll T2;
typedef ll T4; // maybe int128_t
typedef Point<T2> P;
typedef pair<P, P> line;
bool cmp(line a, line b) {
  bool aa = a.X < a.Y;
  bool bb = b.X < b.Y;
  if (aa == bb) {
    P v1 = a.Y - a.X;
    P v2 = b.Y - b.X;
    if (v1.cross(v2) == 0)
      return b.X.cross(b.Y, a.X) > 0;
    else
      return v1.cross(v2) > 0;
  }
  else
    return aa;
}
bool parallel(line a, line b) {
  return (a.Y - a.X).cross(b.Y - b.X) == 0;
}
pair<T2, T2> alpha(line a, line b) {
  return pair<T2, T2>((b.X - a.X).cross(b.Y - b.X), (a.Y - a.X).cross(b.Y -b.X));
}
bool fcmp(T4 f1t, T4 f1b, T4 f2t, T4 f2b) {
  if (f1b < 0) {
    f1t *= -1;
    f1b *= -1;
  }
  if (f2b < 0) {
    f2t *= -1;
    f2b *= -1;
  }
  return f1t * f2b < f2t * f1b; // check with eps
}
bool check(line a, line b, line c) {
  bool crs = (c.Y - c.X).cross(a.Y - a.X) > 0;
  pair<T2, T2> a1 = alpha(a, b);
  pair<T2, T2> a2 = alpha(a, c);
  bool alp = fcmp(a1.X, a1.Y, a2.X, a2.Y);
  return (crs ^ alp);
}
bool notin(line a, line b, line c) { // is intersection of a and b in ccw direction of c?
  if (parallel(a, b))
    return false;
  if (parallel(a, c))
    return c.X.cross(c.Y, a.X) < 0;
  if (parallel(b, c))
    return c.X.cross(c.Y, b.X) < 0;
  return !(check(a, b, c) && check(b, a, c));
}
void print(vector<line> lines) {
  cerr << "@" << endl;
  for (int i = 0; i < lines.size(); i++)
    cerr << lines[i].X << " -> " << lines[i].Y << endl << endl;
}
line dq[MAXLINES];
vector<line> half_plane(vector<line> lines) {
  lines.push_back(line(P(INF, -INF), P(INF, INF)));
  lines.push_back(line(P(-INF, INF), P(-INF, -INF)));
  lines.push_back(line(P(-INF, -INF), P(INF, -INF)));
  lines.push_back(line(P(INF, INF), P(-INF, INF)));
  sort(all(lines), cmp);
  int ptr = 0;
  for (int i = 0; i < lines.size(); i++)
    if (i > 0 && (lines[i - 1].X < lines[i - 1].Y) == (lines[i].X < lines[i].Y) && parallel(lines[i - 1], lines[i]))
      continue;
    else
      lines[ptr++] = lines[i];
  lines.resize(ptr);
  if (lines.size() < 2)
    return lines;
  // print(lines);
  int f = 0, e = 0;
  dq[e++] = lines[0];
  dq[e++] = lines[1];
  for (int i = 2; i < lines.size(); i++) {
    while (f < e - 1 && notin(dq[e - 2], dq[e - 1], lines[i]))
      e--;
    // print(vector<line>(dq + f, dq + e));
    if (e == f + 1) {
      T2 crs = (dq[f].Y - dq[f].X).cross(lines[i].Y - lines[i].X) ;
      if (crs < 0)
        return vector<line>();
      else if (crs == 0 && lines[i].X.cross(lines[i].Y, dq[f].Y) < 0)
        return vector<line>();
    }
    while (f < e - 1 && notin(dq[f], dq[f + 1], lines[i]))
      f++;
    dq[e++] = lines[i];
  }
  while (f < e - 1 && notin(dq[e - 2], dq[e - 1], dq[f]))
    e--;
  while (f < e - 1 && notin(dq[f], dq[f + 1], dq[e - 1]))
    f++;
  vector<line> res;
  res.resize(e - f);
  for (int i = f; i < e; i++)
    res[i - f] = dq[i];
  return res;
}
