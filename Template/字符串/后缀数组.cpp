//后缀数组
int  Log[MAXN], MIN[MAXN][30]
inline int query(int l, int r) { int k = Log[r - l + 1]; return min(MIN[l][k], MIN[r - (1 << k) + 1][k]); }
int n;
int a[MAXN];//原数组
int rrank[MAXN];//第一关键字
int Rank[MAXN];//第i个前缀排第几
int tp[MAXN];//第二关键字，序号为第二关键字的排名，值为对应的第一关键字的位置
int c[MAXN];//用于基数排序用的数组
int Sa[MAXN];//后缀数组，排名为i的后缀是哪一个后缀
int Height[MAXN];//排名为i的后缀与排名为i - 1的后缀的lcp
bool judge(int* x, int loc, int ww)
{
	if (x[Sa[loc]] == x[Sa[loc - 1]] && x[Sa[loc] + ww] == x[Sa[loc - 1] + ww]) return true;
	else return false;
}
int m;
void suffix()
{
	memset(tp, -1, sizeof(tp));//注意，一定要清0
	for (int i = 1; i <= n; i++) rrank[i] = a[i];
	for (int i = 1; i <= n; i++) tp[i] = i;
	for (int i = 0; i <= 128; i++) c[i] = 0;
	for (int i = 1; i <= n; i++) c[rrank[tp[i]]]++;
	for (int i = 1; i <= 128; i++) c[i] += c[i - 1];
	for (int i = n; i >= 1; i--) Sa[c[rrank[tp[i]]]--] = tp[i];
	m = 128;
	for (int w = 1, p = 0; w <= n; w += w, m = p)
	{
		p = 0;
		for (int i = n - w + 1; i <= n; i++) tp[++p] = i;

		for (int i = 1; i <= n; i++)
		{
			if (Sa[i] > w) tp[++p] = Sa[i] - w;
		}
		for (int i = 0; i <= m; i++) c[i] = 0;
		for (int i = 1; i <= n; i++) c[rrank[tp[i]]]++;
		for (int i = 1; i <= m; i++) c[i] += c[i - 1];
		for (int i = n; i >= 1; i--) Sa[c[rrank[tp[i]]]--] = tp[i];
		for (int i = 0; i <= n; i++) tp[i] = rrank[i];//重新计算rank的值
		rrank[Sa[1]] = 1;
		p = 1;
		for (int i = 2; i <= n; i++)
		{
			if (judge(tp, i, w)) rrank[Sa[i]] = p;
			else rrank[Sa[i]] = ++p;
		}
		if (p >= n) break;
	}
	for (int i = 1; i <= n; i++)
	{
		Rank[Sa[i]] = i;
	}
	int k = 0;
	Height[1] = 0;
	for (int i = 1; i <= n; i++)
	{
		if (k) k--;
		while (a[i + k] == a[Sa[Rank[i] - 1] + k])
		{
			k++;
		}
		Height[Rank[i]] = k;
	}
}

inline void init(int n)
{
	for (int i = 2; i <= n; i++)Log[i] = Log[i / 2] + 1;
	for (int i = 1; i <= n; i++)MIN[i][0] = Height[i];
	for (int j = 1; (1 << j) <= n; j++)// log n
		for (int i = 1; i + (1 << j) - 1 <= n; i++)//n
			MIN[i][j] = min(MIN[i][j - 1], MIN[i + (1 << (j - 1))][j - 1]);
}
char s[MAXN];
 /*	int k;
		read(k);
		read(s);
		n = strlen(s);
		memset(Height, 0, sizeof(Height));
		memset(a, -1, sizeof(a));//注意，一定要重置。在这里wa了无数次
		for (int i = 0; i < n; i++)
		{
			a[i + 1] = s[i];
		}
		suffix();
		init(n);
		*/
	 