//支配树
#include<bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0; char c = getchar(); bool flag = 0;
    while (c < '0' || c>'9') { if (c == '-')flag = 1; c = getchar(); }
    while (c >= '0' && c <= '9') { x = (x + (x << 2) << 1) + c - '0'; c = getchar(); } return flag ? -x : x;
}
const int N = 2e5 + 5;
int n, m;
struct node {
    vector<int>edge[N];
    inline void add(int u, int v) {
        edge[u].push_back(v);
    }
} a, b, c, d;
int dfn[N], id[N], fa[N], cnt;
//dfn表示dfs序,id表示序号所对应的点,fa记录点u的父亲节点 
void dfs(int u)
{
    dfn[u] = ++cnt; id[cnt] = u;
    int len = a.edge[u].size();
    for (int i = 0; i < len; ++i)
    {
        int v = a.edge[u][i];
        if (dfn[v])continue;
        fa[v] = u;
        dfs(v);
    }
}
int sdom[N], idom[N], bel[N], val[N];
//sdom表示半支配点,idom表示支配点 
//val[x]表示从x到其已经被搜过的祖先的dfn的最小值val[x]
//bel[x]表示并查集中的fa 
inline int find(int x)
{
    if (x == bel[x])return x;
    int tmp = find(bel[x]);
    if (dfn[sdom[val[bel[x]]]] < dfn[sdom[val[x]]]) val[x] = val[bel[x]];
    //用sdom[val[x]]更新sdom[x] 
    return bel[x] = tmp;
}
inline void tarjan()
{
    for (int i = cnt; i > 1; --i)//在dfs树上遍历,从大到小 
    {
        int u = id[i], len = b.edge[u].size();
        for (int i = 0; i < len; ++i)
        {
            int v = b.edge[u][i];
            if (!dfn[v])continue;//不在dfs树上 
            find(v);
            if (dfn[sdom[val[v]]] < dfn[sdom[u]]) sdom[u] = sdom[val[v]];
        }
        c.add(sdom[u], u);
        bel[u] = fa[u], u = fa[u];
        len = c.edge[u].size();
        for (int i = 0; i < len; ++i)
        {
            int v = c.edge[u][i];
            find(v);
            if (sdom[val[v]] == u) idom[v] = u;
            else idom[v] = val[v];
        }
    }
    for (int i = 2; i <= cnt; ++i)
    {
        int u = id[i];
        if (idom[u] != sdom[u]) idom[u] = idom[idom[u]];
    }
}
int ans[N];
void dfs_ans(int u)
{
    //ans[u] = 1;
    int len = d.edge[u].size();
    for (int i = 0; i < len; ++i)
    {
        int v = d.edge[u][i];
        ans[v] = ans[u] + 1;
        dfs_ans(v);
        // ans[u] += ans[v];
    }
}
int main() {
   // freopen("1.in", "r", stdin);
    
    n = read(), m = read();
    for (int i = 1; i <= m; ++i)
    {
        int u = read(), v = read();
        a.add(u, v);//原图中的边 
        b.add(v, u);//原图中的反边 
    }
    for (int i = 1; i <= n; ++i) sdom[i] = bel[i] = val[i] = i;
    dfs(1);
    tarjan();
    for (int i = 2; i <= n; ++i) d.add(idom[i], i);
    dfs_ans(1);
    // for (int i = 1; i <= n; ++i)printf("%d ", ans[i]);
    int q;
    q = read();
    while (q--) {
        int x;
        x = read();
       // cout << ans[x] + 1 << endl;
        printf("%d\n", ans[x] + 1);
    }
}