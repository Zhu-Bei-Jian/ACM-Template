//乘法逆元 相关
ll ex_gcd(ll a, ll b, ll& x, ll& y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	ll r = ex_gcd(b, a % b, x, y);
	ll t = x;
	x = y;
	y = t - a / b * y;
	return r;
}
ll mod_reverse(ll a, ll n)//ax=1(mod n)  
{
	ll d, x, y;
	d = ex_gcd(a, n, x, y);
	if (d == 1)
		return (x % n + n) % n;
	else
		return -1;
}


// 线性预处理 1~n 的逆元
void init_inv()
{
    inv[1] = 1;
    for(int i = 2;i < n;i++)  inv[i] = (mod -  mod / i) * inv[mod % i] % mod;  //加mod不改变结果
}