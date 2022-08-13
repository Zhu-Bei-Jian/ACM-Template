namespace Splay_Tree {
#define lson(x) spl[x].ch[0]
#define rson(x) spl[x].ch[1]
#define T int
	struct node
	{
		//int fa;
		int ch[2];
		T val;
		int sum;//子树 中 所有权值出现的次数总和
		int cnt;// 当前结点 的val 出现次数
	};
	node spl[MAXN];
	int root, tot;//根节点 和 总结点个数
	inline void clear() {
		root = tot = 0;
		//memset(spl, 0, sizeof(spl));
	}
	inline void pushup(int x)
	{
		spl[x].sum = spl[lson(x)].sum + spl[rson(x)].sum + spl[x].cnt;
	}
	inline void zag(int& x)//左旋拎右 左挂右    //对 以x为根节点 的 子树 进行左旋
	{
		int rs = spl[x].ch[1];//右儿子编号 临时变量
		spl[x].ch[1] = spl[rs].ch[0];//原本自身右儿子的左儿子 成为 自身右儿子
		spl[rs].ch[0] = x;//自身 成为 原本右儿子 的 左儿子
		x = rs;//此时 原本右儿子成为 当前子树根  x赋值为根
		//spl[x].fa = spl[lson(x)].fa;
		//spl[lson(x)].fa = x;
		// 对子树发生变化的结点  pushup 保持正确性
		pushup(lson(x));// 儿子 先pushpu
		pushup(x);
	}
	inline void zig(int& x)
	{
		int ls = spl[x].ch[0];
		spl[x].ch[0] = spl[ls].ch[1];
		spl[ls].ch[1] = x;
		x = ls;
		//spl[x].fa = spl[rson(x)].fa;
		//spl[rson(x)].fa = x;
		pushup(rson(x));
		pushup(x);
	}
	void splay(int x, int& y)
	{
		if (x == y)return;
		int& l = spl[y].ch[0], & r = spl[y].ch[1];
		if (x == l)zig(y);
		else if (x == r)zag(y);
		else
		{
			if (spl[x].val < spl[y].val) {
				if (spl[x].val < spl[l].val)splay(x, spl[l].ch[0]), zig(l), zig(y);
				else splay(x, spl[l].ch[1]), zag(l), zig(y);
			}
			else {
				if (spl[x].val < spl[r].val)splay(x, spl[r].ch[0]), zig(r), zag(y);
				else splay(x, spl[r].ch[1]), zag(r), zag(y);
			}
		}
	}
	inline void newnode(int& x, T& val)
	{
		x = ++tot;
		spl[x].val = val;
		spl[x].sum = 1;
		spl[x].cnt = 1;
		lson(x) = rson(x) = 0;
	}

	void insert(int& x, T  val)
	{
		if (!x)newnode(x, val), splay(x, root);
		else if (val < spl[x].val)insert(spl[x].ch[0], val);
		else if (val > spl[x].val)insert(spl[x].ch[1], val);
		else {
			spl[x].sum++;
			spl[x].cnt++;
			splay(x, root);
		}
	}

	inline void delnode(int x)
	{
		splay(x, root);
		if (spl[x].cnt > 1) {
			spl[x].sum--;
			spl[x].cnt--;
		}
		else {
			if (spl[x].ch[1])
			{
				int p = rson(x);
				while (spl[p].ch[0]) {
					p = spl[p].ch[0];
				}
				splay(p, spl[x].ch[1]);
				spl[p].ch[0] = spl[x].ch[0];
				root = p;
				pushup(root);
			}
			else root = spl[x].ch[0];
		}
	}
	void del(int x, T val)
	{
		if (!x)return;
		if (val < spl[x].val) {
			del(spl[x].ch[0], val);
		}
		else if (val > spl[x].val) {
			del(spl[x].ch[1], val);
		}
		else
			delnode(x);
	}




	int getrank(int val)
	{
		int x = root, rk = 1;
		while (x)
		{
			if (spl[x].val == val)   //找到了要的结点，这个之前的没有
			{
				rk += spl[spl[x].ch[0]].sum;
				splay(x, root);
				break;
			}
			else if (val <= spl[x].val)
				x = spl[x].ch[0];
			else
			{
				rk += spl[spl[x].ch[0]].sum + spl[x].cnt;
				x = spl[x].ch[1];
			}
		}
		return rk;

	}
	int getnum(int rank)
	{
		int now = root;
		while (now)
		{
			int lsum = spl[spl[now].ch[0]].sum;
			if (lsum + 1 <= rank && rank <= lsum + spl[now].cnt) //如果在这个范围内，那就是当前结点
			{
				splay(now, root);
				break;
			}
			else if (lsum >= rank)
				now = spl[now].ch[0];
			else
			{
				rank -= lsum + spl[now].cnt;
				now = spl[now].ch[1];
			}
		}
		return spl[now].val;
	}
};
using namespace Splay_Tree;