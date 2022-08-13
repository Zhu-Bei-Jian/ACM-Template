//最短路  Dijkstra
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

struct node
{
    int id;
    LL w;
    node(int id = 0, LL w = 0) {
        this->id = id;
        this->w = w;
    }
    bool operator<(const node& oth)const {
        return w > oth.w;
    }
};
priority_queue<node>q;
void dij(int st)
{
    for (int i = 1; i <= n; i++)dis[i] = INF;
    dis[st] = 0;
    q.push(node(st, 0));
    while (!q.empty())
    {
        node now = q.top();
        q.pop();
        int u = now.id;
        if (vis[u])continue;
        vis[u] = true;
        for (int i = head[u]; i; i = E[i].nex)
        {
            int v = E[i].to; LL w = E[i].w;

            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
            }
            q.push(node(v, dis[v]));
        }
    }
}