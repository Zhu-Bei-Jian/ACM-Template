// 最短路  SPFA
struct EDGE {
    int to;
    int nex;
    LL w;
    bool operator<(const EDGE& oth)const {
        return w > oth.w;
    }
}E[MAXN << 1];
int head[MAXN];
int tot = 0;
inline void add(int u, int v, LL w)
{
    E[++tot].to = v;
    E[tot].nex = head[u];
    head[u] = tot;
    E[tot].w = w;
}
const LL INF = 1e18;
bool vis[MAXN];
LL dis[MAXN];
int n;

queue<int>q;
void SPFA(int st)
{
    for (int i = 1; i <= n; i++)dis[i] = INF;
    dis[st] = 0;
    q.push(st);
    vis[st] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i; i = E[i].nex)
        {
            int v = E[i].to; LL w = E[i].w;

            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }

        }
    }
}