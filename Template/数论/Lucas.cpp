// 卢卡斯
//C(n,m)=n!/((n-m)!*m!)
//性质1 C(n,m)= C(n,n-m);性质2 C(n,m)=C(n-1,m-1)+C(n-1,m)
//卢卡斯定理：C(n, m) % p  =  C(n / p, m / p) * C(n%p, m%p) % p
ll qpow(ll a,ll b,ll MOD)
{
    ll ans=1;
    while(b)
    {
        if(b&1)
            ans=(ans*a)%MOD;
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

//1.可以预处理阶乘表
ll fac[100005];
void Get_Fact(ll p)    //p代表你需要取模的素数
{
    fac[0]=1;
    for(int i=1;i<=p;i++)
        fac[i]=(fac[i-1]*i)%p;
}
ll Lucas(ll n,ll m,ll p)
{
    ll ans=1;
    while(n&&m)
    {
        ll a=n%p,b=m%p;
        if(a<b) return 0;
        ans=(ans*fac[a]*qpow(fac[b]*fac[a-b]%p,p-2,p))%p;
        n/=p;
        m/=p;
    }
    return ans;
}

//2.不预处理阶乘表
ll Comb(ll a,ll b, ll p)
{
    if(a < b) return 0;
    if(a == b) return 1;
    if(b > a-b) b = a-b;
    ll ans = 1, ca = 1, cb = 1;
    for(ll i=0; i<b; ++i)
    {
        ca = (ca*(a-i))%p;
        cb = (cb*(b-i))%p;
    }
    ans = (ca*qpow(cb, p-2, p))%p;
    return ans;
}
ll Lucas(int n, int m, int p)
{
    ll ans = 1;
    while(n && m && ans)
    {
        ans = (ans * Comb(n%p, m%p, p))%p;
        n /= p;
        m /= p;
    }
    return ans;
}

//3.递归求
ll Lucas(ll n, ll m, int p)
{
    return m ? Lucas(n/p, m/p, p) * Comb(n%p, m%p, p) % p : 1;
}