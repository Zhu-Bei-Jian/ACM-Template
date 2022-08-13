template<class T>
struct LinkCutTree
{
    int fa[N], ch[N][2];
    bool isroot[N];
    int rev[N], sz[N], si[N];

    T othTag[N];//其他懒惰标记
    LinkCutTree()
    {
        memset(isroot, true, sizeof(isroot));
    }
    inline void pd_oth_tag(int x, T c)//下推 其他 懒惰标记
    {

    }
    //标记 代表 当前结点 已经信息正确 ，左右子树仍需更新
    inline void pushdown(int x)//下推一次  当前结点的 所有懒惰标记
    {
        int& l = ch[x][0], & r = ch[x][1];
        if (rev[x])//翻转
        {
            swap(l, r);
            rev[l] ^= 1;
            rev[r] ^= 1;
            rev[x] = 0;
        }
        //if (othTag[x]) {//其他标记
        //    if (l)pd_oth_tag(l, dpTag[x]);
        //    if (r)pd_oth_tag(r, dpTag[x]);
        //    othTag[x] = 0;
        //}
    }
    inline  void PD_ALL_TAG(int x)//头递归  从上到下 将整个splay的标记 全部下推
    {
        if (!isroot[x])
            PD_ALL_TAG(fa[x]);
        pushdown(x);
    }
    inline  void pushup(int x)
    {
        if (x)sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + si[x] + 1;
    }
    inline void rotate(int x)
    {
        int f = fa[x], ff = fa[f];
        int dir = (ch[f][1] == x);
        swap(isroot[x], isroot[f]);
        if (!isroot[x])ch[ff][ch[ff][1] == f] = x;
        fa[x] = ff;
        ch[f][dir] = ch[x][dir ^ 1];
        fa[ch[x][dir ^ 1]] = f;
        ch[x][dir ^ 1] = f;
        fa[f] = x;
        pushup(f), pushup(x);
    }
    inline void splay(int x)
    {
        PD_ALL_TAG(x);
        while (!isroot[x])
        {
            int f = fa[x], ff = fa[f];
            if (!isroot[f])
                rotate((ch[f][1] == x) == (ch[ff][1] == f) ? f : x);
            rotate(x);
        }
    }
    //访问x 返回新根
    inline int access(int x)
    {
        int y = 0;
        while (x)
        {
            splay(x);
            //si[x] x结点 所有虚儿子的贡献
            //y 虚->实  减去y的贡献   x的右儿子 实->虚  加上  右儿子的贡献
            si[x] = si[x] - sz[y] + sz[ch[x][1]];//维护原树图 中子树大小  split(1,x) return si[x]+1

            isroot[ch[x][1]] = true;
            isroot[ch[x][1] = y] = false;

            pushup(y), pushup(x);
            y = x, x = fa[x];
        }
        return y;
    }

    //将x置为根
    inline void makeroot(int x)
    {
        access(x);
        splay(x);
        rev[x] ^= 1;
    }
    inline int findroot(int x)          //寻找结点在原树的根
    {
        access(x);                      //先拉实链
        splay(x);                    //再伸展
        while (ch[x][0])                    //因为根结点必定深度最小，所以不停往左找就OK了
        {
            pushdown(x);                  //下传
            x = ch[x][0];
        }
        splay(x);                    //用来保证时间复杂度，防止卡链
        return x;
    }
    inline bool isConnected(int x, int y) {
        makeroot(x);
        return findroot(y) == x;
    }
    //连接x,y
    inline void link(int x, int y)
    {
        makeroot(x);
        makeroot(y);
        fa[x] = y;// x 与 y 之间 连接一条虚边   x是 y 的 虚儿子
        si[y] += sz[x];
        pushup(y);
    }
    inline void cut(int x, int y)
    {
        makeroot(x);
        //? 如果y跟x不在一棵树上 or x和y之间不是紧紧挨着的，return
    //! 注意这里findroot后由于保证复杂度的一句伸展，导致刚才被换成根的x成为了Splay的根结点
    //* 又因为x在原树中是根结点，深度最小，所以在Splay中一定是x为根结点y为其右儿子
        if (findroot(y) != x || fa[y] != x || ch[y][0])return;
        fa[y] = ch[x][1] = 0;
        pushup(x);
    }
    inline void split(int x, int y)      //把x--y的路径拆出来
    {
        makeroot(x);                      //换根
        access(y);                      //拉实链
        splay(y);                    //伸展
        //? 此时y必定没有右儿子且左儿子是一条到x的实链，所以访问y就可以作任何关于这条链的操作了
    }

    /*
    LCT.sz[0] = LCT.si[0] = 0;
    for (int i = 1; i <= n; i++)LCT.sz[i] = 1, LCT.si[i] = 0;
    */
};

LinkCutTree<int>LCT;
