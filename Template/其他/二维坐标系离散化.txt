// 二维坐标 离散化
vector<int>v;
int get_id(int x)
{
	return lower_bound(v.begin(), v.end(), x) - v.begin();
}
 
struct point
{
	int x; int y;
	point(){}
	point(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
};
point a[MAXN];//原来的二维坐标系
point b[MAXN];//离散化后的坐标系

void discretize(point a[], point b[],int n)
{
	for (int i = 0; i < n; i++)v.push_back(a[i].x - 1),v.push_back(a[i].x + 1),v.push_back(a[i].x);
	_unique(v); for (int i = 0; i < n; i++)b[i].x = get_id(a[i].x);v.clear();
	for (int i = 0; i < n; i++)v.push_back(a[i].y - 1), v.push_back(a[i].y + 1), v.push_back(a[i].y);
	_unique(v); for (int i = 0; i < n; i++)b[i].y = get_id(a[i].y);
}

int32_t main()
{
	
	//	freopen("Azir.in", "r", stdin); 
	int n;
	in(n);
	for (int i = 0; i < n; i++)
	{
		in(a[i].x);
		in(a[i].y);
	}
	discretize(a, b, n);
	 
	


	return 0;
}
