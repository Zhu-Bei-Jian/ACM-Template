// 杜教筛 欧拉函数  莫比乌斯函数 前缀和
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=3e6+10;
const int Pr=3e6;
unordered_map<LL,LL> mm,mp;

bool vis[N];
int tot=0,pri[N]; LL mu[N],phi[N];
void prework() {
    vis[1]=1; mu[1]=phi[1]=1;
    for (int i=2;i<=Pr;i++) {
        if (!vis[i]) pri[++tot]=i,mu[i]=-1,phi[i]=i-1;
        for (int j=1;j<=tot&&i*pri[j]<=Pr;j++) {
            int k=i*pri[j]; vis[k]=1;
            if (i%pri[j]==0) {
                mu[k]=0; phi[k]=phi[i]*pri[j];
                break;
            }
            mu[k]=-mu[i]; phi[k]=phi[i]*phi[pri[j]];
        }
    }
    for (int i=1;i<=Pr;i++) mu[i]+=mu[i-1];
    for (int i=1;i<=Pr;i++) phi[i]+=phi[i-1];
}

LL getmu(LL n) {
    if (n<=Pr) return mu[n];
    if (mm.count(n)) return mm[n];
    LL ret=0,i=2,j;
    while (i<=n) {
        j=n/(n/i);
        ret+=(j-i+1)*getmu(n/i);
        i=j+1;
    }
    return mm[n]=1-ret;
}

LL getphi(LL n) {
    if (n<=Pr) return phi[n];  //预处理的 
    if (mp.count(n)) return mp[n];  //算过的 
    LL ret=0,i=2,j;
    while (i<=n) {  //数论分块求出后面一坨 
        j=n/(n/i);
        ret+=(j-i+1)*getphi(n/i);
        i=j+1;
    } 
    return mp[n]=n*(n+1)/2-ret;
}

int main()
{
    prework();
    int T; cin>>T;
    while (T--) {
        LL n; scanf("%lld",&n);
        printf("%lld %lld\n",getphi(n),getmu(n));
    }
    return 0;
}