// 树链剖分 点权
namespace TCP {

    int _N, TC_ROOT;
    int eCnt, head[MAXN], nex[MAXN << 1], to[MAXN << 1];
    ll w[MAXN], wt[MAXN];//链式前向星数组，w[]、wt[]初始点权数组
    int son[MAXN], id[MAXN], fa[MAXN], dfsCnt, dep[MAXN], siz[MAXN], top[MAXN];//son[]重儿子编号,id[]新编号,fa[]父亲节点,dfsCnt dfs_clock/dfs序,dep[]深度,siz[]子树大小,top[]当前链顶端节点
    inline void add(int x, int y) {//链式前向星加边
        to[++eCnt] = y;
        nex[eCnt] = head[x];
        head[x] = eCnt;
    }
    //-------------------------------------- 以下为线段树
    template<typename T>inline void swap(T& a, T& b) {
        T c = a; a = b; b = c;
    }

    ll sum[MAXN << 2];
    ll lazy[MAXN << 2];
#define lson rt<<1
#define rson rt<<1|1
    void push_up(int rt)
    {
        sum[rt] = sum[lson] + sum[rson];
    }
    void build(int l, int TC_ROOT, int rt)
    {
        lazy[rt] = 0;
        if (l == TC_ROOT)
        {
            sum[rt] = wt[l];
            return;
        }
        int mid = (l + TC_ROOT) >> 1;
        build(l, mid, lson);
        build(mid + 1, TC_ROOT, rson);
        push_up(rt);
    }
    void push_down(int l, int TC_ROOT, int rt)
    {

        if (lazy[rt])
        {
            int mid = (l + TC_ROOT) >> 1;
            sum[lson] += (mid - l + 1) * lazy[rt];
            sum[rson] += (TC_ROOT - mid) * lazy[rt];
            lazy[lson] += lazy[rt];
            lazy[rson] += lazy[rt];
            lazy[rt] = 0;
        }
    }
    void update(int L, int R, ll c, int l, int TC_ROOT, int rt)
    {
        if (L <= l && TC_ROOT <= R) {
            sum[rt] += c * (TC_ROOT - l + 1);
            lazy[rt] += c;
            return;
        }
        int mid = (l + TC_ROOT) >> 1;
        push_down(l, TC_ROOT, rt);
        if (L <= mid)update(L, R, c, l, mid, lson);
        if (R >= mid + 1)update(L, R, c, mid + 1, TC_ROOT, rson);
        push_up(rt);
    }
    ll query(int L, int R, int l, int TC_ROOT, int rt)
    {
        ll res = 0;
        if (L <= l && TC_ROOT <= R)
        {
            return sum[rt];
        }
        int mid = (l + TC_ROOT) >> 1;
        push_down(l, TC_ROOT, rt);
        if (L <= mid) res += query(L, R, l, mid, lson);
        if (R >= mid + 1)res += query(L, R, mid + 1, TC_ROOT, rson);


        return res;
    }


    //---------------------------------以上为线段树
    inline ll qRange(int x, int y) {
        ll ans = 0;
        while (top[x] != top[y]) {//当两个点不在同一条链上
            if (dep[top[x]] < dep[top[y]])swap(x, y);//把x点改为所在链顶端的深度更深的那个点
            ans += query(id[top[x]], id[x], 1, _N, 1);//ans加上x点到x所在链顶端 这一段区间的点权和
            x = fa[top[x]];//把x跳到x所在链顶端的那个点的上面一个点
        }
        //直到两个点处于一条链上
        if (dep[x] > dep[y])swap(x, y);//把x点深度更深的那个点
        ans += query(id[x], id[y], 1, _N, 1);//这时再加上此时两个点的区间和即可
        return ans;
    }

    inline void updRange(int x, int y, ll k) {//同上
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])swap(x, y);
            update(id[top[x]], id[x], k, 1, _N, 1);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])swap(x, y);
        update(id[x], id[y], k, 1, _N, 1);
    }

    inline void dfs1(int x, int f, int deep) {//x当前节点，f父亲，deep深度
        dep[x] = deep;//标记每个点的深度
        fa[x] = f;//标记每个点的父亲
        siz[x] = 1;//标记每个非叶子节点的子树大小
        int maxson = -1;//记录重儿子的儿子数
        for (int i = head[x]; i; i = nex[i]) {
            int y = to[i];
            if (y == f)continue;//若为父亲则continue
            dfs1(y, x, deep + 1);//dfs其儿子
            siz[x] += siz[y];//把它的儿子数加到它身上
            if (siz[y] > maxson)son[x] = y, maxson = siz[y];//标记每个非叶子节点的重儿子编号
        }
    }

    inline void dfs2(int x, int topf) {//x当前节点，topf当前链的最顶端的节点
        id[x] = ++dfsCnt;//标记每个点的新编号
        wt[dfsCnt] = w[x];//把每个点的初始值赋到新编号上来
        top[x] = topf;//这个点所在链的顶端
        if (!son[x])return;//如果没有儿子则返回
        dfs2(son[x], topf);//按先处理重儿子，再处理轻儿子的顺序递归处理
        for (int i = head[x]; i; i = nex[i]) {
            int y = to[i];
            if (y == fa[x] || y == son[x])continue;
            dfs2(y, y);//对于每一个轻儿子都有一条从它自己开始的链
        }
    }
    inline void init(int root)
    {
        TC_ROOT = 1;
        eCnt = 0;
        memset(head, 0, sizeof(head));
        dfsCnt = 0;
        memset(son, 0, sizeof(son));
    }
    /*
    init(root);  read(w[i])
     add(u,v) add(v,u)
     dfs1(TC_root,0,1) dfs2(TC_ROOT,TC_ROOT) build
    */

}
