/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: Simple convolution for FFT, use either this or FFT Mod for convolutions
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

#include "FastFourierTransform.h"

/// typedef complex<double> C;
/// typedef vector<double> vd;
/// void fft(vector<C>& a) {
/// 	int n = sz(a), L = 31 - __builtin_clz(n);
/// 	static vector<complex<long double>> R(2, 1);
/// 	static vector<C> rt(2, 1);  // (^ 10% faster if double)
/// 	for (static int k = 2; k < n; k *= 2) {
/// 		R.resize(n); rt.resize(n);
/// 		auto x = polar(1.0L, acos(-1.0L) / k);
/// 		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
/// 	}
/// 	vi rev(n);
/// 	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
/// 	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
/// 	for (int k = 1; k < n; k *= 2)
/// 		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
/// 			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
/// 			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
/// 			a[i + j + k] = a[i + j] - z;
/// 			a[i + j] += z;
/// 		}
/// }
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}
