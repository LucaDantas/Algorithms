typedef long long ll;

//If needed with modular operations check modular_arithmetic.cpp

//multiplies ans by base^(2^i) for every bit that is set on exponent
ll fastexpo(ll a, ll p){
	ll ans = 1;
	while(p > 0){
		if(p&1) ans *= a;
		a *= a;
		p >>= 1;
	}
	return ans;
}

//iterative is better but saved here just in case
ll power(ll a, ll p){
	if(p == 0) return 1;
	if(p == 1) return a;
	ll x = a*a;
	if(b&1) return power(x, b/2, p)*a;
	return power(x, b/2, p);
}
