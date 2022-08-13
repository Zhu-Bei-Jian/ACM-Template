// 莫队算法
struct Qry {
    int l, r;
    int id;
}Q[MAXN];
int res = 0;
int ans[MAXN];
int bs = 0;
inline void add(int x)
{
    
}
inline void sub(int x)
{
     
}

int32_t main()
{
#ifdef DEBUG
    freopen("..\\DEBUG\\IO\\1.in", "r", stdin);
    // freopen("my.out", "w", stdout);
    clock_t c1 = clock();
#endif

     
    read(n, m);
    block_size = sqrt(n);
  
    for (int i = 1; i <= m; i++)
    {
        read(Q[i].l, Q[i].r);
        Q[i].id = i;
    }
    sort(Q + 1, Q + 1 + m, [](const Qry& fi, const Qry& se) {
        return fi.l / block_size ^ se.l / block_size ? fi.l < se.l : fi.r < se.r;
        });
    int l = 1; int r = 0;
    for (int i = 1; i <= m; i++)
    {
        while (l < Q[i].l)sub(l++);
        while (l > Q[i].l)add(--l);
        while (r < Q[i].r)add(++r);
        while (r > Q[i].r)sub(r--);

        ans[Q[i].id] = res;
    }
    for (int i = 1; i <= m; i++)println(ans[i]);

#ifdef DEBUG
    std::cerr << "Time:" << clock() - c1 << "ms" << std::endl;
#endif
    fastIO::flush();
    return Accepted;
}
///                 .-~~~~~~~~~-._       _.-~~~~~~~~~-.
///             __.'              ~.   .~              `.__
///           .'//                  \./                  \\`.
///        .'//                     |                     \\`.
///       .'// .-~"""""""~~~~-._     |     _,-~~~~"""""""~-. \\`.
///     .'//.-"                 `-.  |  .-'                 "-.\\`.
///   .'//______.============-..   \ | /   ..-============.______\\`.
/// .'______________________________\|/______________________________`.
