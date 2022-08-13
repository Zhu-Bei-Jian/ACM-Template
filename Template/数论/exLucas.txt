//扩展卢卡斯
ll exgcd(ll a, ll b, ll& x, ll& y) {
	if (!b) { x = 1, y = 0; return a; }
	ll gcd = exgcd(b, a % b, x, y), tmp;
	tmp = x, x = y, y = tmp - a / b * y;
	return gcd;
}

inline ll Mod(ll x, ll mod) { return x > mod ? x - mod : x; }

inline ll inv(ll a, ll mod) {
	ll x, y; exgcd(a, mod, x, y);
	return (x % mod + mod) % mod;
}

inline ll qpow(ll x, ll n, ll mod) {
	ll res = 1;
	for (; n; x = x * x % mod, n >>= 1)
		if (n & 1) (res *= x) %= mod;
	return res;
}

ll fac(ll n, ll pi, ll pk) {
	if (!n) return 1;
	ll res = 1;
	for (ll i = 2; i < pk; i++)
		if (i % pi) (res *= i) %= pk;
	res = qpow(res, n / pk, pk);
	for (ll i = 2; i <= n % pk; i++)
		if (i % pi) (res *= i) %= pk;
	return fac(n / pi, pi, pk) * res % pk;
}

inline ll C(ll n, ll m, ll pi, ll pk) {
	if (n < m) return 0;
	ll r1 = fac(n, pi, pk), r2 = fac(m, pi, pk);
	ll r3 = fac(n - m, pi, pk), cnt = 0;
	for (ll i = n; i; i /= pi) cnt += i / pi;
	for (ll i = m; i; i /= pi) cnt -= i / pi;
	for (ll i = n - m; i; i /= pi) cnt -= i / pi;
	return r1 * inv(r2, pk) % pk * inv(r3, pk) % pk * qpow(pi, cnt, pk) % pk;
}

inline ll exlucas(ll n, ll m, ll p) {
	ll pi, pk, res = 0, x, y, gcd, c, M = 1;
	for (ll i = 2; i * i <= p; i++) {
		if (p % i == 0) {
			pi = i, pk = 1;
			while (p % i == 0) p /= i, pk *= i;
			gcd = exgcd(M, pk, x, y), c = Mod((C(n, m, pi, pk) - res) % pk + pk, pk);
			x = Mod(x * (c / gcd) % pk + pk, pk);
			res += M * x, M *= pk / gcd, res %= M;
		}
	}
	if (p > 1) {
		pi = pk = p; gcd = exgcd(M, pk, x, y);
		c = Mod((C(n, m, pi, pk) - res) % pk + pk, pk);
		x = Mod(x * (c / gcd) % pk + pk, pk);
		res += M * x, M *= pk / gcd, res %= M;
	}
	return res;
}