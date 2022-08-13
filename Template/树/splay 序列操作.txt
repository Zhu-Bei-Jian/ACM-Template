
// SPLAY  序列操作
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 7;
const int INF = 1e9;
int n, m;
int ch[maxn][2]; //0做孩子， 1右孩子
int f[maxn]; //每个节点的父亲
int sz[maxn]; //每个节点为根子树的大小
int val[maxn]; //这个节点所表示的值
int cnt[maxn]; //这个节点所表示值的数量
int mi[maxn]; //这个节点子树的最小值
int rev[maxn]; //反转标记
int lazy[maxn]; //延迟标记
int root;  // splay的根
int tot; //树所有的节点数量
inline void Swap(int& x, int& y)
{
    x ^= y; y ^= x; x ^= y;
}
int Min(int x, int y)
{
    return x < y ? x : y;
}
inline void pd_rev(int x) //更新反转
{
    if (!x) return;
    Swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;  //如果这一层曾经被转过下面就不用转了， 把rev取消了
}
inline void pd_add(int x, int v)
{
    if (x) lazy[x] += v, val[x] += v, mi[x] += v;
}
inline void newnode(int rt, int v, int fa)
{
    f[rt] = fa; sz[rt] = 1;
    val[rt] = mi[rt] = v;
    ch[rt][0] = ch[rt][1] = rev[rt] = lazy[rt] = 0; //加点的时候把所有的信息都更新了
}
inline void clearNode(int rt)
{
    f[rt] = val[rt] = sz[rt] = mi[rt] = 0;
    ch[rt][0] = ch[rt][1] = rev[rt] = lazy[rt] = 0;
}
inline void pushup(int x)  //跟线段树一样，从下往上不断更新
{
    if (!x)return;
    sz[x] = 1, mi[x] = val[x];
    if (ch[x][0]) sz[x] += sz[ch[x][0]], mi[x] = Min(mi[x], mi[ch[x][0]]); //更新个数跟当前子树最小值
    if (ch[x][1]) sz[x] += sz[ch[x][1]], mi[x] = Min(mi[x], mi[ch[x][1]]);
}
inline void pushdown(int x)
{
    if (!x) return;
    if (rev[x])
    {
        pd_rev(ch[x][0]);
        pd_rev(ch[x][1]);
        rev[x] = 0;
    }
    if (lazy[x])
    {
        pd_add(ch[x][0], lazy[x]);
        pd_add(ch[x][1], lazy[x]);
        lazy[x] = 0;
    }

}
inline void build(int& rt, int l, int r, int fa) //rt是节点编号，节点的大小代表了两个数位置的相对顺序
{                       //一共tot个节点
    if (l > r) return;
    int mid = (r + l) >> 1;
    rt = mid; newnode(rt, val[rt], fa);
    build(ch[rt][0], l, mid - 1, rt);
    build(ch[rt][1], mid + 1, r, rt);
    pushup(rt);
}
inline void Rotate(int x, int k) // k = 0左旋， k = 1右旋
{
    int y = f[x]; int z = f[y];
    //pushdown(y); pushdown(x);
    ch[y][!k] = ch[x][k];
    if (ch[x][k]) f[ch[x][k]] = y;
    f[x] = z;
    if (z) ch[z][ch[z][1] == y] = x;
    f[y] = x; ch[x][k] = y;
    pushup(y), pushup(x);
}
inline void splay(int x, int goal)
{
    pushdown(x);
    while (f[x] != goal)
    {
        int y = f[x], z = f[y];
        //在这里下传翻转标记，在rotate里下传标记可能会使树形改变导致旋转出错
        pushdown(z); pushdown(y); pushdown(x);
        if (f[y] == goal) Rotate(x, ch[y][0] == x);
        else
        {
            int p = ch[f[y]][0] == y;
            if (ch[y][p] == x) Rotate(x, !p), Rotate(x, p);
            else Rotate(y, p), Rotate(x, p);
        }
    }
    pushup(x);
    if (goal == 0) root = x;
}

//以x为根的子树 的极值点  0 极小 1 极大
inline int extreme(int x, int k)
{
    while (ch[x][k]) x = ch[x][k];
    splay(x, 0);  //所有操作之后都伸展下
    return x;
}
//以节点编号x为根的子树 第k个数的节点编号
inline int kth(int x, int k)
{
    pushdown(x);
    if (sz[ch[x][0]] + 1 == k) return x;
    else if (sz[ch[x][0]] >= k) return kth(ch[x][0], k);
    else return kth(ch[x][1], k - sz[ch[x][0]] - 1);
}
//交换区间 [L,mid-1] 与 [mid,R]
//   1 2 3 4 5   [1,5]  mid=3   [1,2]与[3,5]交换
//-> 3 4 5 1 2
inline void exchange(int L, int mid, int R)
{
    int x = kth(root, mid - 1), y = kth(root, R + 1);
    splay(x, 0), splay(y, x);
    int tmp_right = ch[y][0]; ch[y][0] = 0; //“剪贴下来”
    x = kth(root, L - 1), y = kth(root, L);
    splay(x, 0), splay(y, x);
    ch[y][0] = tmp_right;
    f[tmp_right] = y;
}
//区间翻转
inline void reversal(int l, int r)
{
    int x = kth(root, l - 1), y = kth(root, r + 1);
    splay(x, 0); splay(y, x);
    pd_rev(ch[y][0]);  //ch[y][0]就是l-r区间
}
//区间加
inline void add(int l, int r, int v)
{
    int x = kth(root, l - 1), y = kth(root, r + 1);
    //    cout << 1 <<endl;
    splay(x, 0); splay(y, x);
    pd_add(ch[y][0], v); //ch[y][0]就是l-r区间
}
//在第k个数后插入值为x的节点
inline void Insert(int k, int x) {
    int r = kth(root, k), rr = kth(root, k + 1);
    splay(r, 0), splay(rr, r);
    newnode(++tot, x, rr); ch[rr][0] = tot; //节点个数增加
    for (r = rr; r; r = f[r]) pushdown(r), pushup(r);
    splay(rr, 0);
}
//删除第k位置的数
inline void Delete(int k)
{
    splay(kth(root, k - 1), 0);
    splay(kth(root, k + 1), root);
    clearNode(ch[ch[root][1]][0]);//清空该节点所有信息
    ch[ch[root][1]][0] = 0;
    pushup(ch[root][1]);
    pushup(root);
}
//获取区间最小值
inline int get_min(int l, int r)
{
    int x = kth(root, l - 1), y = kth(root, r + 1);
    splay(x, 0); splay(y, x);
    return mi[ch[y][0]];
}
inline void init(int n)
{
    root = 0;
    tot = n;
    f[0] = sz[0] = ch[0][0] = ch[0][1] = rev[0] = lazy[0] = 0;
    build(root, 1, n, 0);
    pushup(root);
}
inline int findpos(int x, int val)//平衡树内部二分
{
    int px = kth(root, x);
    splay(px, 0);
    x = ch[px][0];
    //  dfs(px);
    while (x)
    {
        if (ch[x][1] && mx[ch[x][1]] > val)x = ch[x][1];
        else if (priority_[x] > val)break;
        else if (ch[x][0])x = ch[x][0];
        else break;
    }
    splay(x, 0);
    int l = sz[ch[x][0]] + 1;

    return l;
}
void dfs(int  u)//中序遍历
{
    if (u == 0)return;
    dfs(ch[u][0]);
    if (abs(val[u]) != INF)cout << u << " ";
    dfs(ch[u][1]);
}

int main()
{
    scanf("%d", &n);
    val[n + 2] = INF;
    val[1] = -INF; //增加两个哨兵  把区间1-n包起来  区间编号整体+1 , [2,n+1] 对应原区间[1,n]
    for (int i = 2; i <= n + 1; i++) scanf("%d", &val[i]);
    init(n + 2);

    //int d, l, r;
    //scanf(" %s", s);
    //if (s[0] == 'A')
    //{ //ADD
    //    scanf("%d%d%d", &l, &r, &d);
    //    add(l + 1, r + 1, d);
    //}
    //else if (s[0] == 'I')
    //{ //INSERT
    //    scanf("%d%d", &l, &d);
    //    Insert(l + 1, d);
    //}
    //else if (s[0] == 'M')
    //{ //MIN
    //    scanf("%d%d", &l, &r);
    //    printf("%d\n", get_min(l + 1, r + 1));
    //}
    //else if (s[0] == 'D')
    //{ //DELETE
    //    scanf("%d", &l);
    //    Delete(l + 1);
    //}
    //else if (s[3] == 'E')
    //{ //REVERSE
    //    scanf("%d%d", &l, &r);
    //    reversal(l + 1, r + 1); //增加了1一个节点全体后移一个
    //}
    //else
    //{ //REVOLVE
    //    scanf("%d%d%d", &l, &r, &d);
    //    d = d % (r - l + 1);
    //    if (d) exchange(l + 1, r - d + 1, r - d + 1 + 1, r + 1);
    //}
}
return 0;
}
