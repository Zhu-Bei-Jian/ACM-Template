//无向图 生成树个数
ll  f[MAXN][MAXN];
void add(ll x, ll y)
{

    f[x][x] ++, f[y][y] ++;//度数
    f[x][y] --, f[y][x] --;//边
}

ll Gauss(int tot)
{
    ll ans = 1;
    for (ll i = 1; i < tot; i++)
    {
        for (ll j = i + 1; j < tot; j++)
            while (f[j][i])
            {
                ll t = f[i][i] / f[j][i];
                for (ll k = i; k < tot; k++)
                    f[i][k] = (f[i][k] - t * f[j][k] + mod) % mod;
                swap(f[i], f[j]);
                ans = -ans;
            }
        ans = (ans * f[i][i]) % mod;
    }
    return (ans + mod) % mod;
}
// 无向图的生成树个数 