// 动态开点 线段树
struct Dsegtree{
    typedef int type;
    #define mid (l+r)/2
    struct node{
        int ls, rs;
        type val;
    } tree[MAXN * 41];
    int cnt = 0;
    int newnode(){
        int p = ++cnt;
        tree[p].ls = tree[p].rs = tree[p].val = 0;
        return p;
    }
    void update(int p){
        tree[p].val = tree[tree[p].ls].val + tree[tree[p].rs].val;
    }
    void c_tree(int l, int r, int p, int x, int y){
        if (l == r){
            tree[p].val = y;
            return;
        }
        if (x <= mid){
            if (!tree[p].ls){
                tree[p].ls = newnode();
            }
            c_tree(l, mid, tree[p].ls, x, y);
        }
        else{
            if (!tree[p].rs){
                tree[p].rs = newnode();
            }
            c_tree(mid + 1, r, tree[p].rs, x, y);
        }
        update(p);
    }
    int m_tree(int l,int r,int t1,int t2){
        if (t1&&t2){
            int t = newnode();
            if (l==r){
                tree[t].val=tree[t1].val+tree[t2].val;
                return t;
            }
            tree[t].ls=m_tree(l,mid,tree[t1].ls,tree[t2].ls);
            tree[t].rs=m_tree(mid+1,r,tree[t1].rs,tree[t2].rs);
            update(t);
            return t;
        }
        else return t1|t2;
    }
    int q_point(int l,int r,int p,int x){
        if (l==r){
            return tree[p].val;
        }
        if (x<=mid)return q_point(l,mid,tree[p].ls,x);
        else return q_point(mid+1,r,tree[p].rs,x);
    }
};