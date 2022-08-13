// 权值线段树
int a[MAXN];
vector<int>v;
int f[MAXN*20];
int get_id(int x)
{
	return lower_bound(v.begin(), v.end(), x)-v.begin()+1;
}

void add(int l, int r, int v, int x)
{
	if (l == r) f[v]++;
	else
	{
		int mid = (l + r) / 2;
		if (x <= mid) add(l, mid, v * 2, x); else add(mid + 1, r, v * 2 + 1, x);
		f[v] = f[v * 2] + f[v * 2 + 1];
	}
}

int find(int l, int r, int v, int x, int y)
{
	if (l == x && r == y) return f[v];
	else
	{
		int mid = (l + r) / 2;
		if (y <= mid) return find(l, mid, v * 2, x, y);
		else if (x > mid) return find(mid + 1, r, v * 2 + 1, x, y);
		else return find(l, mid, v * 2, x, mid) + find(mid + 1, r, v * 2 + 1, mid + 1, y);
	}
}
int kth(int l, int r, int v, int k)
{
	if (l == r) return l;
	else
	{
		int mid = (l + r) / 2, s1 = f[v * 2], s2 = f[v * 2 + 1];
		if (k <= s2) return kth(mid + 1, r, v * 2 + 1, k); else return kth(l, mid, v * 2, k - s2);
	}
}

int32_t main()
{
	//	freopen("Azir.in", "r", stdin); 
	int n;
	in(n);
	for (int i = 1; i <= n; i++)
	{
		in(a[i]);
		//add(1, n, 1, a[i]);
		v.push_back(a[i]);
	}
	_unique(v);
	for (int i = 1; i <= n; i++)
	{
		add(1, n, 1, get_id(a[i]));
	}

	string s;
	while (cin >> s)
	{
		if (s == "find")
		{
			int x; int y;
			cin >> x >> y;
			int x_id = get_id(x);
			int y_id = get_id(y);
			cout << find(1, n, 1, x_id, y_id) << endl;
		}
		if (s == "kth")
		{
			int k; cin >> k;
			cout << a[kth(1, n, 1, k)] << endl;
		}
	}

	return 0;
}