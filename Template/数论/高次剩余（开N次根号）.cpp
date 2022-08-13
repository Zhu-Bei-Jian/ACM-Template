//高次剩余   （开 N次 根号）
namespace High_Surplus {
#define ll long long
	ll pow_mod(ll a, ll b, ll mod)
	{
		ll ans = 1;
		while (b)
		{
			if (b & 1)ans = ans * a % mod;
			b >>= 1;
			a = a * a % mod;
		}
		return ans;
	} 
	ll ex_gcd(ll a, ll b, ll& x, ll& y)
	{
		if (b == 0)
		{
			x = 1, y = 0;
			return a;
		}
		else
		{
			ll r = ex_gcd(b, a % b, y, x);
			y -= x * (a / b);
			return r;
		}
	}
	vector<ll>v;
	bool g_text(ll g, ll mod)
	{
		for (ll i = 0; i < v.size(); i++)if (pow_mod(g, (mod - 1) / v[i], mod) == 1)return 0;
		return 1;
	}
	ll primitive_root(ll mod)
	{
		v.clear();
		ll tmp = mod - 1;
		for (ll i = 2; i <= tmp / i; i++)
		{
			if (tmp % i == 0)
			{
				v.push_back(i);
				while (tmp % i == 0)tmp /= i;
			}
		}
		if (tmp != 1)v.push_back(tmp);
		ll g = 1;
		while (1)
		{
			if (g_text(g, mod))return g;
			++g;
		}
	}
	//求解原根
	struct sa
	{
		ll x;
		int id;
		bool operator<(const sa& b)const
		{
			if (x == b.x) return id < b.id;
			return x < b.x;
		}
	}rec[100500];
	//用rec存离散对数
	ll discerte_log(ll x, ll n, ll m)
	{
		int s = (int)(sqrt((double)m + 0.5));
		while ((ll)s * s <= m)s++;
		ll cur = 1;
		sa tmp;
		for (int i = 0; i < s; i++)
		{
			tmp.x = cur, tmp.id = i;
			rec[i] = tmp;
			cur = cur * x % m;
		}
		sort(rec, rec + s);
		ll mul = pow_mod(cur, m - 2, m) % m;
		cur = 1;
		for (ll i = 0; i < s; i++)
		{
			ll more = n * cur % m;
			tmp.x = more, tmp.id = -1;
			int j = lower_bound(rec, rec + s, tmp) - rec;
			if (rec[j].x == more)return i * s + rec[j].id;
			cur = cur * mul % m;
		}
		return -1;
	}
	//求解离散对数  //多个解 存于vector  ret
	vector<ll>residue(ll mod, ll n, ll a) // pow(a,1/n)=b  pow(b,n)=a;
	{
		vector<ll>ret;
		if (a == 0)
		{
			ret.push_back(0);
			return ret;
		}
		ll g = primitive_root(mod), m = discerte_log(g, a, mod);
		if (m == -1)return ret;
		ll A = n, B = mod - 1, C = m, x, y, G = ex_gcd(A, B, x, y);
		if (C % G != 0)return ret;
		x = x * (C / G) % B;
		ll delta = B / G;
		for (int i = 0; i < G; i++)
		{
			x = ((x + delta) % B + B) % B;
			ret.push_back(pow_mod(g, x, mod));
		}
		sort(ret.begin(), ret.end());
		ret.erase(unique(ret.begin(), ret.end()), ret.end());
		return ret;
	}

#undef ll
} 
using namespace High_Surplus;