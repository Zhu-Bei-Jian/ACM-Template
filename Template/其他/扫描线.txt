//扫描线
#include<bits/stdc++.h>
#define _unique(v) sort(v.begin(), v.end()), v.erase(unique(v.begin(), v.end()), v.end())
namespace fastIO {
#define BUF_SIZE 100000
#define OUT_SIZE 100000
#define ll long long
	//fread->read
	bool IOerror = 0;
	//	inline char nc(){char ch=getchar();if(ch==-1)IOerror=1;return ch;}
	inline char nc() {
		static char buf[BUF_SIZE], * p1 = buf + BUF_SIZE, * pend = buf + BUF_SIZE;
		if (p1 == pend) {
			p1 = buf; pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if (pend == p1) { IOerror = 1; return -1; }
		}
		return *p1++;
	}
	inline bool blank(char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }
	template<class T> inline bool read(T& x) {
		bool sign = 0; char ch = nc(); x = 0;
		for (; blank(ch); ch = nc());
		if (IOerror)return false;
		if (ch == '-')sign = 1, ch = nc();
		for (; ch >= '0' && ch <= '9'; ch = nc())x = x * 10 + ch - '0';
		if (sign)x = -x;
		return true;
	}
	inline bool read(double& x) {
		bool sign = 0; char ch = nc(); x = 0;
		for (; blank(ch); ch = nc());
		if (IOerror)return false;
		if (ch == '-')sign = 1, ch = nc();
		for (; ch >= '0' && ch <= '9'; ch = nc())x = x * 10 + ch - '0';
		if (ch == '.') {
			double tmp = 1; ch = nc();
			for (; ch >= '0' && ch <= '9'; ch = nc())tmp /= 10.0, x += tmp * (ch - '0');
		}
		if (sign)x = -x;
		return true;
	}
	inline bool read(char* s) {
		char ch = nc();
		for (; blank(ch); ch = nc());
		if (IOerror)return false;
		for (; !blank(ch) && !IOerror; ch = nc())*s++ = ch;
		*s = 0;
		return true;
	}
	inline bool read(char& c) {
		for (c = nc(); blank(c); c = nc());
		if (IOerror) { c = -1; return false; }
		return true;
	}
	template<class T, class... U>bool read(T& h, U&... t) { return read(h) && read(t...); }
	//fwrite->print
	struct Ostream_fwrite {
		char* buf, * p1, * pend;
		Ostream_fwrite() { buf = new char[BUF_SIZE]; p1 = buf; pend = buf + BUF_SIZE; }
		//		void out(char ch){putchar(ch);}
		inline void out(char ch) { if (p1 == pend) { fwrite(buf, 1, BUF_SIZE, stdout); p1 = buf; }*p1++ = ch; }
		template<class T>inline void print(T x) {
			static char s[41], * s1; s1 = s;
			if (!x)*s1++ = '0'; if (x < 0)out('-'), x = -x;
			while (x)*s1++ = x % 10 + '0', x /= 10;
			while (s1-- != s)out(*s1);
		}
		inline void print(double x, int y = 6) {
			static ll mul[] =
			{ 1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,
			10000000000LL,100000000000LL,1000000000000LL,10000000000000LL,
			100000000000000LL,1000000000000000LL,10000000000000000LL,100000000000000000LL };
			if (x < -1e-12)out('-'), x = -x;
			ll x2 = (ll)floor(x); if (!y && x - x2 >= 0.5)++x2; x -= x2; x *= mul[y];
			ll x3 = (ll)floor(x); if (y && x - x3 >= 0.5)++x3; print(x2);
			if (y > 0) { out('.'); for (size_t i = 1; i < y && x3 * mul[i] < mul[y]; out('0'), ++i); print(x3); }
		}
		inline void print(char* s) { while (*s)out(*s++); }
		inline void print(const char* s) { while (*s)out(*s++); }
		inline void flush() { if (p1 != buf) { fwrite(buf, 1, p1 - buf, stdout); p1 = buf; } }
		~Ostream_fwrite() { flush(); }
	}Ostream;
	template<class T>inline void print(T x) { Ostream.print(x); }
	template<class T>inline void println(T x) { Ostream.print(x); Ostream.out('\n'); }
	inline void print(char x) { Ostream.out(x); }
	inline void println(char x) { Ostream.out(x); Ostream.out('\n');; }
	inline void print(char* s) { Ostream.print(s); }
	inline void println(char* s) { Ostream.print(s); Ostream.out('\n');; }
	inline void print(std::string s) { Ostream.print(s.c_str()); }
	inline void println(std::string s) { Ostream.print(s.c_str()); Ostream.out('\n');; }
	inline void print(const char* s) { Ostream.print(s); }
	inline void println(const char* s) { Ostream.print(s); Ostream.out('\n');; }
	inline void print(double x, int y = 6) { Ostream.print(x, y); }
	inline void println(double x, int y = 6) { Ostream.print(x, y); Ostream.out('\n');; }
	template<class T, class... U>void print(const T& h, const U&... t) { print(h); Ostream.out(' ');; print(t...); }
	template<class T, class... U>void println(const T& h, const U&... t) { print(h); Ostream.out(' ');; println(t...); }
	template<class T>inline void println(T x[], int n) {
		for (int i = 0; i < n - 1; i++)print(x[i]), Ostream.out(' ');; print(x[n - 1]), Ostream.out('\n');;
	}
	template<class T>inline void println(std::vector<T> x) {
		int n = x.size();
		for (int i = 0; i < n - 1; i++)print(x[i]), Ostream.out(' ');; print(x[n - 1]), Ostream.out('\n');;
	}

	inline void flush() { Ostream.flush(); }
#undef ll
#undef OUT_SIZE
#undef BUF_SIZE
};
using namespace fastIO;
typedef long long ll;
using namespace std;
const int32_t MAXN = 3e5 + 5;
struct EDGE {//矩阵的 竖边
	int x;
	int y1, y2;
	int mark; // 1 左边  -1 右边

}E[MAXN<<1];
// node 不再维护单点  ,只维护真正意义上的线段
// n 个 点（离散化以后的）  有n-1 条线段   线段树维护的是 n-1 条线段
// [1,2]  [2,3] [3,4]  …… [n-1,n]
// 线段树上 [L,R] 对应 的真实线段 [ val[L],val[R+1] ]

struct node
{
	int l, r;// 离散化以后 的下标  l,r  。对应原线段 val[l]~val[r+1]
	int cover;//线段 被完全覆盖的次数
	int len;//如果线段被完全覆盖 一次及以上  ,len = val[r+1]-val[l]+1 //即该区间长度
	//如果线段只是部分被覆盖 ,len = len(lson) + len(rson) // 左右儿子 贡献相加

}tree[MAXN<<3];
#define lson rt<<1
#define rson rt<<1|1
ll val[MAXN<<1];
inline void pushup(int rt)
{
	if (tree[rt].cover)
		tree[rt].len = val[tree[rt].r + 1] - val[tree[rt].l];
	else
		tree[rt].len = tree[lson].len + tree[rson].len;
}
void build(int l,int r,int rt)
{
	tree[rt].l = l; tree[rt].r = r;
	tree[rt].cover = 0;
	tree[rt].len = 0;
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;

	build(l, mid, lson);
	build(mid + 1, r, rson);
}

void update(ll L,ll R,int c,int l,int r,int rt)// [L,R]（未离散化的真实线段）
{
	if (val[l]>=R || val[r + 1]<=L)return;
	if (L <= val[l] && val[r + 1] <= R)
	{
		tree[rt].cover += c;
		pushup(rt);
		return;
	}
	int mid = (l + r) >> 1;
	update(L, R, c, l, mid, lson);
	update(L, R, c, mid + 1, r, rson);
	pushup(rt);
}

int32_t main()
{
#ifdef DEBUG
	freopen("..\\DEBUG\\IO\\1.in", "r", stdin);
	// freopen("my.out", "w", stdout);
	clock_t c1 = clock();
#endif

	int n;
	read(n);
	int ecnt = 0;
	int vcnt = 0;
	for (int i = 1; i <= n; i++)
	{
		int X1, Y1, X2, Y2;
		read(X1, Y1, X2, Y2);
		E[++ecnt].mark = 1;//左 竖边
		E[ecnt].x = X1;
		E[ecnt].y1 = Y1;
		E[ecnt].y2 = Y2;

		E[++ecnt].mark = -1;//右 竖边
		E[ecnt].x = X2;
		E[ecnt].y1 = Y1;
		E[ecnt].y2 = Y2;
		val[++vcnt]=Y1;
		val[++vcnt]=Y2;
	}

	sort(E + 1, E + 1 + ecnt, [](EDGE& fi,EDGE & se) {
		return fi.x < se.x;
		});
	sort(val + 1, val + 1 + vcnt);
	vcnt = unique(val + 1, val + 1 + vcnt) - val-1;

	build(1, vcnt-1, 1);
	unsigned long long One = 1;
	unsigned long long ans = 0;
	for (int i = 1; i < ecnt; i++)
	{

		update(E[i].y1, E[i].y2, E[i].mark, 1, vcnt-1, 1);
		ans += One * tree[1].len * (E[i+1].x - E[i].x);
	}
	printf("%llu\n", ans);

#ifdef DEBUG
	std::cerr << "Time:" << clock() - c1 << "ms" << std::endl;
#endif
	fastIO::flush();
	return 0;
}