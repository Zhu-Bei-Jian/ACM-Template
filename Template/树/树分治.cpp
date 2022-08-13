// 树 分治
int n,m;
struct E{
    int to,w,next;
}edge[MAXN<<1];
int cnt,head[MAXN];
inline void addedge(int u,int v,int w){
    edge[cnt].to=v,edge[cnt].next=head[u],edge[cnt].w=w,head[u]=cnt++;
}
int siz[MAXN],deep[MAXN],root,vis[MAXN],sn,tmp[MAXN],f[MAXN];
int tot;
ll ans;
void getroot(int x,int fa){ // 求重心
    f[x]=0,siz[x]=1;
    for (int i=head[x];~i;i=edge[i].next){
        int v=edge[i].to;
        if (v==fa||vis[v])continue;
        getroot(v,x); siz[x]+=siz[v]; f[x]=max(f[x],siz[v]);
    }
    f[x]=max(f[x],sn-siz[x]);
    if (f[root]>f[x])root=x;
}
void getdeep(int x,int fa){//得到所有点的距离
    tmp[++tot]=deep[x];
    for (int i=head[x];~i;i=edge[i].next){
        int v=edge[i].to;
        if (v==fa||vis[v])continue;
        deep[v]=deep[x]+edge[i].w;
        getdeep(v,x);
    }
}
ll calc(int x,int v){  //计算答案
    tot=0; getdeep(x,0); ll sum=0; sort(tmp+1,tmp+tot+1);
    int st=1,en=tot;
    while (st<en){
        if(tmp[st]+tmp[en]<=v)sum+=en-st,st++;
        else en--;
    }
    return sum;
}
void div(int x) {//分治
    deep[x] = 0, vis[x] = 1, ans += calc(x, m); // 假设全部的边都在一边
    for (int i = head[x]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (vis[v])continue;
        deep[v] = edge[i].w;
        ans -= calc(v, m); // 去掉子树的贡献
        sn = siz[v],root = 0;  getroot(v, 0);  div(root);
    }
}
void init(int n){
    cnt=0,ans=0;
    for (int i=1;i<=n;i++)head[i]=-1,vis[i]=0;
}