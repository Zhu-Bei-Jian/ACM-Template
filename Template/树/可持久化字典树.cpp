//可持久化字典树
struct node
{
    int sum[2];
    int ch[2];
}tr[MAXN * 32];
int cnt = 0;
int rt[MAXN];
int ans = 0;
void build(int pre, int now, int val, int pos)
{
    if (pos < 0) return;
    int tmp = bool(val & (1 << pos));
    tr[now] = tr[pre];
    tr[now].sum[tmp]++;
    tr[now].ch[tmp] = ++cnt;
    build(tr[pre].ch[tmp], tr[now].ch[tmp], val, pos - 1);
}
void query(int pre, int now, int val, int pos)
{
    if (pos < 0) return;
    int tmp = bool(val & (1 << pos));
    if (tr[now].sum[!tmp] > tr[pre].sum[!tmp])
    {
        ans += (1 << pos);
        query(tr[pre].ch[!tmp], tr[now].ch[!tmp], val, pos - 1);
    }
    else query(tr[pre].ch[tmp], tr[now].ch[tmp], val, pos - 1);
}

// memset(tr, 0, sizeof(tr));
//cnt = 0;
//for (int i = 1; i <= n; i++) {
 //           build(rt[i - 1], rt[i], tv[i], 30);
   //     }

//   query(rt[l - 1 ], rt[r], x, 30);