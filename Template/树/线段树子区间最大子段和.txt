//线段树 子区间 最大子段和
const int32_t MAXN = 5e5 + 5;
const LL INF = 1e18;
struct node
{
	LL sum;//区间和
	LL lsum;//从左端点往右 最大和
	LL rsum;//从右端点往左 最大和
	LL ans;//区间内最大子段和
	bool empty;
	node(bool f = false) {
		sum = 0;
		lsum = rsum = ans = -INF;
		empty = f;
	}

}d[MAXN << 2];
node operator +(const node& a, const node& b)
{
	node c;
	if (a.empty)return b;
	if (b.empty)return a;
	c.lsum = max(a.lsum, a.sum + b.lsum);
	c.rsum = max(b.rsum, a.rsum + b.sum);
	c.sum = a.sum + b.sum;
	c.ans = max(b.lsum + a.rsum, max(a.ans, b.ans));
	return c;
}
LL a[MAXN];
#define lson rt<<1
#define rson rt<<1|1
inline void push_up(int rt)
{
	d[rt] = d[lson] + d[rson];
}
void build(int l, int r, int rt)
{
	if (l == r)
	{
		d[rt].sum = d[rt].lsum = d[rt].rsum = d[rt].ans = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson);
	build(mid + 1, r, rson);
	push_up(rt);
}

void modify(int x, LL c, int l, int r, int rt)
{
	if (x <= l && r <= x) {
		d[rt].sum = d[rt].lsum = d[rt].rsum = d[rt].ans = c;
		return;
	}
	int mid = (l + r) >> 1;

	if (x <= mid)modify(x, c, l, mid, lson);
	if (x >= mid + 1)modify(x, c, mid + 1, r, rson);
	push_up(rt);
}
node query(int L, int R, int l, int r, int rt)
{
	node res(true);
	if (L <= l && r <= R)
	{
		return d[rt];
	}
	int mid = (l + r) >> 1;
	if (L <= mid) res = res + query(L, R, l, mid, lson);
	if (R >= mid + 1)res = res + query(L, R, mid + 1, r, rson);
	return res;
}