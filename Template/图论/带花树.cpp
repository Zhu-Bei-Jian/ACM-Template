//带花树  一般图最大匹配

#define RG register
const int MAX_P = 300 * 2 + 600 + 123;
const int MAX_EDGE = 300 * 600 * 6 + 123;
inline int read()
{
	RG int x = 0, t = 1; RG char ch = getchar();
	while ((ch < '0' || ch>'9') && ch != '-')ch = getchar();
	if (ch == '-')t = -1, ch = getchar();
	while (ch <= '9' && ch >= '0')x = x * 10 + ch - 48, ch = getchar();
	return x * t;
}
struct EDGE {
	int v, NEXT;
	EDGE() {}
	EDGE(int v, int nex) {
		this->v = v;
		this->NEXT = nex;
	}
}E[MAX_EDGE];
int Head[MAX_P], cnt = 1;
inline void Add(int u, int v) { E[cnt] = EDGE(v, Head[u]); Head[u] = cnt++; }
int Match[MAX_P], pre[MAX_P], f[MAX_P], vis[MAX_P], tim, dfn[MAX_P];
int N, m, ans;
int getf(int x) { return x == f[x] ? x : f[x] = getf(f[x]); }
int lca(int u, int v)
{
	++tim; u = getf(u); v = getf(v);
	while (dfn[u] != tim)
	{
		dfn[u] = tim;
		u = getf(pre[Match[u]]);
		if (v)swap(u, v);
	}
	return u;
}
queue<int> Q;
void Blossom(int x, int y, int w)
{
	while (getf(x) != w)
	{
		pre[x] = y, y = Match[x];
		if (vis[y] == 2)vis[y] = 1, Q.push(y);
		if (getf(x) == x)f[x] = w;
		if (getf(y) == y)f[y] = w;
		x = pre[y];
	}
}
bool Aug(int S)
{
	for (int i = 1; i <= N; ++i)f[i] = i, vis[i] = pre[i] = 0;
	while (!Q.empty())Q.pop(); Q.push(S); vis[S] = 1;
	while (!Q.empty())
	{
		int u = Q.front(); Q.pop();
		for (int i = Head[u]; i; i = E[i].NEXT)
		{
			int v = E[i].v;
			if (getf(u) == getf(v) || vis[v] == 2)continue;
			if (!vis[v])
			{
				vis[v] = 2; pre[v] = u;
				if (!Match[v])
				{
					for (int x = v, lst; x; x = lst)
						lst = Match[pre[x]], Match[x] = pre[x], Match[pre[x]] = x;
					return true;
				}
				vis[Match[v]] = 1, Q.push(Match[v]);
			}
			else
			{
				int w = lca(u, v);
				Blossom(u, v, w);
				Blossom(v, u, w);
			}
		}
	}
	return false;
}
inline void init()
{
	//链式前向星 初始化
	cnt = 1;
	memset(Head, 0, sizeof(Head));
	//-------
	tim = 0;
	ans = 0;
	memset(Match, 0, sizeof(Match));
	memset(dfn, 0, sizeof(dfn));
}

//	for (int i = 1; i <= N; ++i)if (!Match[i])ans+=Aug(i);