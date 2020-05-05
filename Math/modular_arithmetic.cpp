typedef long long ll;

// Add 2^i times a for every bit i of b that is set
ll mulmod(ll a, ll b, ll c){
	ll ans = 0;
	ll a %= c;
	while(b > 0){
		if(b&1) ans = (ans+a)%c;
		a = (a<<1)%c;
		b >>= 1;
	}
	return ans;
}

ll fastexpo(ll a, ll p){
	ll ans = 1;
	while(p > 0){
		if(p&1) ans = mulmod(ans, a, MOD);
		a = mulmod(a,a,MOD);
		p >>= 1;
	}
	return ans;
}
