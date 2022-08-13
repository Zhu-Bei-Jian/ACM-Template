// 康托展开
int n, tr[MAXN];
long long ans, fac[MAXN];
inline void add(int x, int k) {
	for (; x <= n; x += x & -x) tr[x] += k;
}
inline int query(int x) {
	int t = 0;
	for (; x; x -= x & -x) t += tr[x];
	return t;
}
int main() {
	scanf("%d", &n);
	fac[0] = 1;
	for (int i = 1; i <= n; i++) {
		fac[i] = fac[i - 1] * i % 998244353;
		add(i, 1);
	}
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		ans = (ans + (query(x) - 1) * fac[n - i]) % 998244353;
		add(x, -1);
	}
	printf("%lld", ans + 1);
	return 0;
}




//逆康托展开
#include<bits/stdc++.h>
using namespace std;
int k,n,ans[1000001];//记录排列
int t[1000001];//树状数组
int lowbit(int x)
{
    return x&-x;
}
void update(int x,int v)//区间修改
{
    while(x<=n)
    {
        t[x]+=v;
        x+=lowbit(x);
    }
}
int sum(int x)//单点查询
{
    int p=0;
    while(x>0)
    {
        p+=t[x];
        x-=lowbit(x);
    }
    return p;
}
int main()
{
    cin>>k;
    while(k--)//样例个数
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            update(i,1);//初始化
        }
        int val;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&val);//一位一位的遍历
            int l=1,r=n;
            while(l<r)//二分查找这个数
            {
                int mid=(l+r)/2;
                int q=sum(mid)-1;
                if(q<val)l=mid+1;
                else r=mid;
            }
            update(r,-1);//并实锤这个数
            ans[i]=r;//记录
        }
        for(int i=1;i<n;i++)
        {
            printf("%d ",ans[i]);//输出控制一下格式
        }
        printf("%d\n",ans[n]);
    }
}