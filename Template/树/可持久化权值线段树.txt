// 主席树
int a[MAXN];
vector<int>v;
int getid(int x)
{
	return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

struct node {
	int l, r;
	int sum;

}tree[MAXN*20];
int root[MAXN];
int cnt = 0;
#define ls(x) tree[x].l
#define rs(x) tree[x].r
void insert(int l,int r,int pre,int &now,int val)
{
	
	now = ++cnt;
	tree[now] = tree[pre];
	tree[now].sum++;
	if (l == r)return;
	int mid = (l + r) >> 1;
	if (val <= mid)insert(l, mid, ls(pre), ls(now), val);
	if (val > mid)insert(mid + 1, r, rs(pre), rs(now), val);
}
int kth(int l,int r,int L,int R,int k)
{
	if (l == r)return l;
	int tmp = tree[ls(R)].sum - tree[ls(L)].sum;
	int mid = (l + r) >> 1;
	if (k<=tmp)return kth(l, mid, ls(L), ls(R), k);
	else return kth(mid + 1, r, rs(L), rs(R), k - tmp);
}