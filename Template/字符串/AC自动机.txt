// AC自动机
queue<int>q;
const int AlphaSize=26;
inline int getID(char ch){
    return ch-'a';
}
int c[MAXN][AlphaSize], val[MAXN], fail[MAXN], cnt;
void ins(char* s, int index) {
    int len = strlen(s); int now = 0;
    for (int i = 0; i < len; i++) {
        int v = getID(s[i]);
        if (!c[now][v])c[now][v] = ++cnt;
        now = c[now][v];
    }
    val[now]++;
}
void get_fail_pointer() {
    for (int i = 0; i < AlphaSize; i++)if (c[0][i])fail[c[0][i]] = 0, q.push(c[0][i]);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < AlphaSize; i++)
            if (c[u][i])fail[c[u][i]] = c[fail[u]][i], q.push(c[u][i]);
            else c[u][i] = c[fail[u]][i];
    }
}
 



