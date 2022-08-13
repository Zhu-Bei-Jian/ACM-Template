// 扩展欧几里得 求 最小整数解
LL exgcd(LL a, LL b, LL& x, LL& y)
{
	LL d = a;
	if (b != 0)
	{
		d = exgcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
	else
	{
		x = 1;
		y = 0;
	}
	return d;
}

LL cal(LL a,LL b,LL c)
{
    LL x = 0, y = 0;
	LL d = exgcd(a, b, x, y);
	if (c % d != 0)
	{
		return -1;
	}
	else
	{
		x *= c / d;
		LL t = b / d;
		if (t < 0)
			t = -t;
		x = (x % t + t) % t;
		return x;
 		// y=(c-a*x)/b
	}
}