// DSU  ON TREE
#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
const int MAXN = 1e5 + 10;
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

int N;//树的结点个数
int col[MAXN];//结点的权值
int hSon[MAXN];// hSon[x]  代表 x的重儿子
int siz[MAXN];//子树大小
//int Mx;//子树相关信息 （统计新子树时 初始化  
int nowHson;//nowHnow 当前子树的重儿子(统计新子树 时 初始化
//int cnt[MAXN];//用于统计当前子树信息的数据结构 （ 根据题目决定  

//LL sum = 0, ans[MAXN]; //存储答案
vector<int> G[MAXN];//存图
void dfs(int x, int fa) {//第一遍 DFS 处理出 所有结点的重儿子
    siz[x] = 1;
    for (int v : G[x]) {
        if (v == fa) continue;
        dfs(v, x);
        siz[x] += siz[v];
        if (siz[v] > siz[hSon[x]]) hSon[x] = v;//轻重链剖分
    }
}
void Count(int x, int fa, int val) {//这个函数 因题目而异 （如何统计当前这棵子树
    //cnt[col[x]] += val; 
    //if (cnt[col[x]] > Mx) Mx = cnt[col[x]], sum = col[x];
    //else if (cnt[col[x]] == Mx) sum += (LL)col[x];
    for (int v : G[x]) {
        if (v == fa || v == nowHson) continue;
        Count(v, x, val);
    }
}
void dfs2(int x, int fa, int opt) {
    for (int i = 0; i < G[x].size(); i++) {
        int to = G[x][i];
        if (to == fa) continue;
        if (to != hSon[x]) dfs2(to, x, 0);//暴力统计轻边的贡献，opt = 0表示递归完成后消除对该点的影响
    }
    if (hSon[x]) dfs2(hSon[x], x, 1), nowHson = hSon[x];//统计重儿子的贡献，不消除影响

     
    Count(x, fa, 1); nowHson = 0;//暴力统计所有轻儿子的贡献
   // ans[x] = sum;//更新答案

    if (!opt) {//如果需要删除贡献的话就删掉
        Count(x, fa, -1);
        //sum = 0; Mx = 0; //初始化子树相关信息 
    }
}
int main() {
    N = read();
    for (int i = 1; i <= N; i++) col[i] = read();
    for (int i = 1; i <= N - 1; i++) {
        int x = read(), y = read();
        G[x].push_back(y); G[y].push_back(x);
    }
    dfs(1, 0);
    dfs2(1, 0, 0);
    // for (int i = 1; i <= N; i++) printf("%I64d ", ans[i]);
    return 0;
}