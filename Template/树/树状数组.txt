// 树状数组
ll tree[123213];

int lowbit(int k)
{
	return (k) & (-k);
}
void add(int x, ll k, int n)
{
	while (x <= n)
	{
		tree[x] += k;
		x += lowbit(x);
	}
}
ll get_sum(int x)
{
	ll ans = 0;
	while (x != 0)
	{
		ans += tree[x];
		x -= lowbit(x);
	}
	return ans;
}

inline ll query(int l, int r)
{
	return get_sum(r) - get_sum(l - 1);
}
