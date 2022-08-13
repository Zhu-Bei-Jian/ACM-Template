// splay
typedef int tp;
struct Node
{
	tp val;
	int fa, ch[2],  cnt, size;  //ch[0]是左儿子，ch[1]是右儿子
}spl[MAXN];
int cnt, root;
inline void pushup(int x)
{
	spl[x].size = spl[spl[x].ch[0]].size + spl[spl[x].ch[1]].size + spl[x].cnt;
}
inline bool ident(int x, int f) { return spl[f].ch[1] == x; }  //查询父子关系
inline void connect(int x, int f, int s)          //建立父子关系
{
	spl[f].ch[s] = x;
	spl[x].fa = f;
}
void rotate(int x)      //合二为一的旋转
{
	int f = spl[x].fa, ff = spl[f].fa, k = ident(x, f);
	connect(spl[x].ch[k ^ 1], f, k);        //三次建立父子关系
	connect(x, ff, ident(f, ff));
	connect(f, x, k ^ 1);
	pushup(f), pushup(x);                //别忘了更新大小信息
}
void splay(int x, int top)//代表把x转到top的儿子，top为0则转到根结点
{
	if (!top) root = x;
	while (spl[x].fa != top)
	{
		int f = spl[x].fa, ff = spl[f].fa;
		if (ff != top) ident(f, ff) ^ ident(x, f) ? rotate(x) : rotate(f);
		rotate(x);      //最后一次都是旋转x
	}
}
void newnode(int& now, int fa, tp val)   //新建节点，要注意fa指针的初始化
{
	now = ++cnt;
	spl[now].val = val;
	spl[now].fa = fa;
	spl[now].size = spl[now].cnt = 1;
	spl[now].ch[0] = spl[now].ch[1] = 0;
}
void delnode(int x)                 //删除结点，要注意fa指针的维护
{
	splay(x, 0);
	if (spl[x].cnt > 1) spl[x].cnt--;
	else if (spl[x].ch[1])
	{
		int p = spl[x].ch[1];
		while (spl[p].ch[0]) p = spl[p].ch[0];
		splay(p, x);
		connect(spl[x].ch[0], p, 0);
		root = p;
		spl[p].fa = 0;
		pushup(root);
	}
	else root = spl[x].ch[0], spl[root].fa = 0;
}
void ins(tp val, int& now = root, int fa = 0)    //递归式，要传fa指针
{
	if (!now) newnode(now, fa, val), splay(now, 0);
	else if (val < spl[now].val) ins(val, spl[now].ch[0], now);
	else if (val > spl[now].val) ins(val, spl[now].ch[1], now);
	else spl[now].cnt++, splay(now, 0);
}
void del(tp val, int now = root)              //同上
{
	if (val == spl[now].val) delnode(now);
	else if (val < spl[now].val) del(val, spl[now].ch[0]);
	else del(val, spl[now].ch[1]);
}
int getrank(tp val)
{
	int now = root, rank = 1;
	while (now)
	{
		if (spl[now].val == val)   //找到了要的结点
		{
			rank += spl[spl[now].ch[0]].size;
			splay(now, 0);
			break;
		}
		if (val < spl[now].val)
			now = spl[now].ch[0];
		else //if (val > spl[now].val)
		{
			rank += spl[spl[now].ch[0]].size + spl[now].cnt;
			now = spl[now].ch[1];
		}
	}
	return rank;
}
tp getnum(int rank)
{
	int now = root;
	while (now)
	{
		int lsize = spl[spl[now].ch[0]].size;
		if (lsize + 1 <= rank && rank <= lsize + spl[now].cnt) //如果在这个范围内，那就是当前结点
		{
			splay(now, 0);
			break;
		}
		else if (lsize >= rank)
			now = spl[now].ch[0];
		else
		{
			rank -= lsize + spl[now].cnt;
			now = spl[now].ch[1];
		}
	}
	return spl[now].val;
}