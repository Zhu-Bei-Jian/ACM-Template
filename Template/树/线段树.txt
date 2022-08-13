//线段树
ll sum[MAXN << 2];
ll lazy[MAXN << 2];
ll a[MAXN];
#define lson rt<<1
#define rson rt<<1|1
void push_up(int rt)
{
	sum[rt] = sum[lson] + sum[rson];
}
void build(int l, int r, int rt)
{
	if (l == r)
	{
		sum[rt] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson);
	build(mid + 1, r, rson);
	push_up(rt);
}
void push_down(int l,int r,int rt)
{
	
	if (lazy[rt])
	{
		int mid = (l + r) >> 1;
		sum[lson] += (mid - l + 1) * lazy[rt];
		sum[rson] += (r - mid) * lazy[rt];
		lazy[lson] += lazy[rt];
		lazy[rson] += lazy[rt];
		lazy[rt] = 0;
	}
}
void update(int L, int R, ll c,int l, int r, int rt)
{
	if (L<=l && r <= R) {
		sum[rt] += c * (r - l + 1);
		lazy[rt] += c;
		return;
	}
	int mid = (l + r) >> 1;
	push_down(l, r, rt);
	if (L <= mid)update(L, R, c, l, mid, lson);
	if (R >= mid + 1)update(L, R, c, mid + 1, r, rson);
	push_up(rt);
}
ll query(int L, int R, int l, int r, int rt)
{
	ll res = 0;
	if (L <= l && r <= R)
	{
		 return sum[rt];
	}
	int mid = (l + r) >> 1;
	push_down(l, r, rt);
	if (L <=mid ) res+=query(L, R,  l, mid, lson);
	if (R>=mid+1)res+=query(L, R,  mid + 1, r, rson);
	return res;
}