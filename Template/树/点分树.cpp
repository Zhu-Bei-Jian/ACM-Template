// 点分树
int n,m;
vector<int>mp[MAXN];
typedef ll type;
int fa[MAXN],siz[MAXN],f[MAXN],dep[MAXN],rt,vis[MAXN],ac[MAXN][22];//fa存点分树上的节点的父亲 f求重心用的 dep深度数组 vis标记在点分树上的第几层 ac求第k个祖先
int dis[MAXN][22],uh[MAXN][22];//dis记录某个节点到点分树上某层的根节点的距离 uh记录节点在第几层的哪个子树上
vector<type>tr[MAXN][22];// 树状数组
int lowbit(int x){return x&-x;}
type query(int st,int x,int y){// 求x点在st层距离小于y的和
    type sum=0;
    while (y){
        sum+=tr[x][st][y],y-=lowbit(y);
    }
    return sum;
}
void add(int st,int x,int y,type w){// 向第st层的x点的树状数组中在距离为y的位置插入w
    while (y<=tr[x][st].size()-1){
        tr[x][st][y]+=w,y+=lowbit(y);
    }
}
void getroot(int &rt,int u,int fa,int sn){// 求重心 顺便求节点在原树上的深度 sn为当前树大小
    f[u]=0,siz[u]=1;
    if (sn==n){
        ac[u][0]=fa,dep[u]=dep[fa]+1;
    }
    for (int v:mp[u]){
        if (v==fa||vis[v])continue;
        getroot(rt,v,u,sn);
        siz[u]+=siz[v];
        f[u]=max(f[u],siz[v]);
    }
    f[u]=max(f[u],sn-siz[u]);
    if (f[u]<f[rt])rt=u;
}
void dfs(int u,int fa,int st){
    siz[u]=1;
    if (vis[u]!=st)dis[u][st]=dis[fa][st]+1;// 求出u到st层的距离 顺便求在哪颗子树上
    for (int v:mp[u]){
        if (vis[v]||v==fa)continue;
        if (!dis[u][st])uh[v][st]=v;
        else uh[v][st]=uh[u][st];
        dfs(v,u,st);
        siz[u]+=siz[v];
    }
}
void div(int u,int sn,int pre,int st){// 树分治
    rt=0;
    getroot(rt,u,0,sn);
    fa[rt]=pre;
    vis[rt]=st;
    dis[rt][st]=0;
    uh[rt][st]=rt;
    dfs(rt,0,st);
    int flag=rt;
    tr[rt][st].resize(siz[rt]+2);
    for (int v:mp[rt]){
        if (vis[v])continue;
        tr[v][st].resize(siz[v]+2);
        div(v,siz[v],flag,st+1);
    }
}
type ask(int x,int r){// 查询，注意要在点分树上往上跳
    int st=vis[x],y;
    type sum=0;
    y=fa[x];
    sum=query(st,x,min(r+1,(int)tr[x][st].size()-1));
    st--;
    while (st){
        if (dis[x][st]<=r){
            sum+=query(st,y,min(r+1-dis[x][st],(int)tr[y][st].size()-1));
            sum-=query(st,uh[x][st],min(r+1-dis[x][st],(int)tr[uh[x][st]][st].size()-1));
        }
        st--,y=fa[y];
    }
    return sum;
}
void modify(int x,type w){// 修改节点的值，注意要在点分树上往上跳
    int st=vis[x],y;
    add(st,x,1,w);
    st--;y=fa[x];
    while (st){
        add(st,y,dis[x][st]+1,w);
        add(st,uh[x][st],dis[x][st]+1,w);
        st--;y=fa[y];
    }
}
void init(){
    for (int i=1;i<=n;i++){
        vis[i]=0,mp[i].clear();
        for (int j=0;j<22;j++)tr[i][j].clear();
    }
}
int main(){
    f[0]=INT_MAX;
    int t;
    read(t);
    while (t--){
        read(n,m);
        init();
        for (int i=1;i<n;i++){
            int u,v;
            read(u,v);
            mp[u].push_back(v);
            mp[v].push_back(u);
        }
        div(1,n,0,1);
        for (int i=1;i<22;i++){
            for (int j=1;j<=n;j++){
                ac[j][i]=ac[ac[j][i-1]][i-1];
            }
        }
    }
    return 0;
}