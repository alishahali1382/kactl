/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: faster inverse by euclid
 */
#pragma once

#include "euclid.h"

ll invert(ll a, ll mod) {
	ll x, y, g = euclid(a, mod, x, y);
	assert(g == 1); return (x + mod) % mod;
}

