namespace MF {

    const int maxn = 1e5 + 1000;
#define inf 2000000000
    typedef long long typeF;
    int N, S, T, cnt;
    int head[maxn], cur[maxn], d[maxn];
    struct Edge
    {
        int to;
        typeF val;
        int nxt;
    }edge[int(1e6 + 5)];

    inline void ADD_ONE(int u, int v, typeF w)
    {
        edge[++cnt].to = v;
        edge[cnt].val = w;
        edge[cnt].nxt = head[u];
        head[u] = cnt;
    }
    inline void addedge(int u, int v, typeF w) {
        ADD_ONE(u, v, w);
        ADD_ONE(v, u, 0);
    }
    bool bfs()
    {
        queue<int> q;
        while (!q.empty()) q.pop();
        for (int i = 0; i <= N; i++) d[i] = -1;
        d[S] = 0;
        q.push(S);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = head[u]; i != -1; i = edge[i].nxt) {
                int v = edge[i].to;
                if (d[v] == -1 && edge[i].val > 0) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[T] != -1;
    }
    typeF dfs(int u, typeF flow)
    {
        typeF nowflow = 0;
        if (u == T) return flow;
        for (int i = cur[u]; i != -1; i = edge[i].nxt) {
            cur[u] = i;
            int v = edge[i].to;
            if (d[v] == d[u] + 1 && edge[i].val > 0) {
                if (typeF k = dfs(v, min(flow - nowflow, edge[i].val))) {
                    edge[i].val -= k;
                    edge[i ^ 1].val += k;
                    nowflow += k;
                    if (nowflow == flow) break;
                }
            }
        }
        if (!nowflow) d[u] = -1;
        return nowflow;
    }
    typeF Dinic()
    {
        typeF ans = 0;
        while (bfs())
        {
            for (int i = 0; i <= N; i++) cur[i] = head[i];
            ans += dfs(S, inf);
        }
        return ans;
    }
    inline void init()
    {
        cnt = -1;
        for (int i = 0; i <= N; i++)head[i] = -1;
        //memset(head, -1, sizeof(head));
    }
}