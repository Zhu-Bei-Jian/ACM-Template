//求凸包
typedef long long LL;
using namespace std;
const int32_t MAXN = 1e6 + 5;
int n;
struct Point
{
	double x, y;
}p[10005], s[10005];
double check(Point a1, Point a2, Point b1, Point b2)//检查叉积是否大于0，如果是a就逆时针转到b 
{
	return (a2.x - a1.x) * (b2.y - b1.y) - (b2.x - b1.x) * (a2.y - a1.y);
}
double d(Point p1, Point p2)//两点间距离。。。 
{
	return sqrt((p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x));
}
bool cmp(Point p1, Point p2)
{
	double tmp = check(p[1], p1, p[1], p2);
	if (tmp > 0)
		return 1;
	if (tmp == 0 && d(p[0], p1) < d(p[0], p2))
		return 1;
	return 0;
}
Azir main()
{
	read(n);
	double mid;
	for (int i = 1; i <= n; i++)
	{
		read( p[i].x, p[i].y);
		if (i != 1 && p[i].y < p[1].y)//这是是去重 
		{
			mid = p[1].y; p[1].y = p[i].y; p[i].y = mid;
			mid = p[1].x; p[1].x = p[i].x; p[i].x = mid;
		}
	}
	sort(p + 2, p + 1 + n, cmp);//系统快排 
	s[1] = p[1];//最低点一定在凸包里 
	int cnt = 1;
	for (int i = 2; i <= n; i++)
	{
		while (cnt > 1 && check(s[cnt - 1], s[cnt], s[cnt], p[i]) <= 0) //判断前面的会不会被踢走，如果被踢走那么出栈
			cnt--;
		cnt++;
		s[cnt] = p[i];
	}
	s[cnt + 1] = p[1];//最后一个点回到凸包起点
	double ans = 0;
	for (int i = 1; i <= cnt; i++)
		ans += d(s[i], s[i + 1]);//然后s里存好了凸包序列，只需要把两两距离累加就行
	println(ans,2);
