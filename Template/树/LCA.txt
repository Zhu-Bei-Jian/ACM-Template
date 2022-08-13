//LCA
struct EDGE {
    int to, nex;
}E[500010 << 1]; int head[500010], tot;
void add(int x, int y) {
    E[++tot].to = y;
    E[tot].nex = head[x];
    head[x] = tot;
}
int depth[500001], fa[500001][22], lg[500001];
void dfs(int now, int fath) {
    fa[now][0] = fath; depth[now] = depth[fath] + 1;
    for (int i = 1; i <= lg[depth[now]]; ++i)
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (int i = head[now]; i; i = E[i].nex)
        if (E[i].to != fath) dfs(E[i].to, now);
}
int LCA(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    while (depth[x] > depth[y])
        x = fa[x][lg[depth[x] - depth[y]] - 1];
    if (x == y) return x;
    for (int k = lg[depth[x]] - 1; k >= 0; --k)
        if (fa[x][k] != fa[y][k])
            x = fa[x][k], y = fa[y][k];
    return fa[x][0];
}


///for (int i = 1; i <= n; ++i)
   //		lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
   	//dfs(1, 0);