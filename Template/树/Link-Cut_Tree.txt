// LCT
typedef long long tp;
struct Node
{
	int fa, ch[2];
	//int siz;
	//tp val;
	bool tag;               //翻转懒标记

}LCT[MAXN];
#define ls(x) (LCT[x].ch[0])
#define rs(x) (LCT[x].ch[1])
#define fa(x) (LCT[x].fa)
#define ident(x,f) (rs(f)==x)       //和下面的connect都是Splay的辅助函数
#define connect(x,f,s) LCT[fa(x)=f].ch[s]=x
//#define push_up(x) LCT[x].sum=LCT[ls(x)].sum^LCT[rs(x)].sum^LCT[x].val
#define ntroot(x) (ls(fa(x))==x||rs(fa(x))==x)  //判断结点是否为Splay的根
#define reverse(x) std::swap(ls(x),rs(x)),LCT[x].tag^=1
inline void push_up(int x)
{
	if (x)
	{

	}
}

inline void push_down_rev(int x)
{
	std::swap(ls(x), rs(x)), LCT[x].tag ^= 1;
}
inline void push_down(int x)           //懒标记下传
{
	if (LCT[x].tag)
	{
		if (ls(x))push_down_rev(ls(x));
		if (rs(x)) push_down_rev(rs(x));
		LCT[x].tag = 0;
	}

}
void push_down_all_tag(int x)                 //头递归，从上到下下传所有懒标记
{
	if (ntroot(x))push_down_all_tag(fa(x));
	push_down(x);
}
inline void rotate(int x)           //Splay基操
{
	int f = fa(x), ff = fa(f), k = ident(x, f);
	connect(LCT[x].ch[k ^ 1], f, k);
	fa(x) = ff;
	if (ntroot(f)) LCT[ff].ch[ident(f, ff)] = x;//※重要，不能忘记判断，关系到虚实边
	connect(f, x, k ^ 1);
	push_up(f), push_up(x);
}
inline void Splay(int x)         //Splay基操，都是伸展到根结点
{
	push_down_all_tag(x);                     //要先把上面的懒标记全都下传
	while (ntroot(x))
	{
		int f = fa(x), ff = fa(f);
		if (ntroot(f)) ident(f, ff) ^ ident(x, f) ? rotate(x) : rotate(f);
		rotate(x);
	}
	//push_up(x);
}
inline void access(int x)           //从x到原树根结点拉一条实链
{
	for (int y = 0; x; x = fa(y = x))        //y为上一个Splay的根
	{
		Splay(x);                //伸展到当前Splay的根
		rs(x) = y;                    //右儿子连上上一个Splay的根
		push_up(x);                  //更新
	}
}
inline void mkroot(int x)           //给原树换根
{
	access(x);                      //先拉实链，拉好后x一定在Splay的最右（深度最大）
	Splay(x);                    //再伸展，伸展后x必定没有右儿子
	reverse(x);                     //翻转拉出来这条实链，使深度顺序翻转
}
inline int findroot(int x)          //寻找结点在原树的根
{
	access(x);                      //先拉实链
	Splay(x);                    //再伸展
	while (ls(x))                    //因为根结点必定深度最小，所以不停往左找就OK了
	{
		push_down(x);                  //下传
		x = ls(x);
	}
	Splay(x);                    //用来保证时间复杂度，防止卡链
	return x;
}
inline bool isConnected(int x, int y) {
	mkroot(x);
	return findroot(y) == x;
}
inline void link(int x, int y)       //连边，不保证数据合法
{
	mkroot(x);                      //换根
	//if (findroot(y) == x) return false;      //如果y所在的树的根结点是x，那说明两者在一棵树上
	fa(x) = y;
	//return true;
}
inline void cut(int x, int y)        //断边，不保证数据合法
{
	mkroot(x);                      //换根
	//? 如果y跟x不在一棵树上 or x和y之间不是紧紧挨着的，return
	//! 注意这里findroot后由于保证复杂度的一句伸展，导致刚才被换成根的x成为了Splay的根结点
	//* 又因为x在原树中是根结点，深度最小，所以在Splay中一定是x为根结点y为其右儿子
	if (findroot(y) != x || fa(y) != x || ls(y)) return;
	fa(y) = rs(x) = 0;                  //断边
	push_up(x);                      //更新
}
inline void split(int x, int y)      //把x--y的路径拆出来
{
	mkroot(x);                      //换根
	access(y);                      //拉实链
	Splay(y);                    //伸展
	//? 此时y必定没有右儿子且左儿子是一条到x的实链，所以访问y就可以作任何关于这条链的操作了
}
