//线性基
/*1.设线性基的异或集合中不存在0。
2.线性基的异或集合中每个元素的异或方案唯一，其实这个跟性质1是等价的。 
3.线性基二进制最高位互不相同。 
4.如果线性基是满的，它的异或集合为[1,2^n-1][1,2^n-1]。 
5.线性基中元素互相异或，异或集合不变。*/
int n;
struct LB{
    ll d[100];
    int tot;
    LB(){
        tot = 0;
        memset(d, 0, sizeof(d));
    }
    bool add(ll x){
        for (int i = 63; ~i; i--){
            if (x & (1ll << i)) //注意，如果i大于31，前面的1的后面一定要加ll
            {
                if (d[i])
                    x ^= d[i];
                else{
                    d[i] = x;
                    break; //记得如果插入成功一定要退出
                }
            }
        }
        return x > 0; //如果成功插入 返回true;
    }
    ll Max1(ll x) //与x异或最大值
    {
        ll ans = x;
        for (int i = 63; ~i; i--) //记得从线性基的最高位开始
            if ((ans ^ d[i]) > ans)
                ans ^= d[i];
        return ans;
    }
    ll Max2() //当前数集能异或出来的最大数字 线性基最大就令x = 0 - 贪心构造(二进制下高位的1对于答案的贡献要比下面所有的位数都为1的贡献还要大)
    {
        ll ans = 0;
        for (int i = 63; ~i; i--)
            if ((ans ^ d[i]) > ans)
                ans ^= d[i];
        return ans;
    }
    ll Min1(ll x) //与x异或最小值
    {
        ll ans = x;
        for (int i = 63; ~i; i--)
            if ((ans ^ d[i]) < ans)
                ans ^= d[i];
        return ans;
    }
    ll Min2() //线性基最小 -直接取出最后一位不是零的数字
    {
        for (int i = 0; i <= 63; i++)
            if (d[i])
                return d[i];
        return 0;
    }
    void rebuild() //处理线性基 变成阶梯型
    {
        for (int i = 1; i <= 63; i++)
            for (int j = 1; j <= i; j++)
                if (d[i] & (1ll << (j - 1)))
                    d[i] ^= d[j - 1];
    }
    ll k_th(ll k) //第k小
    {
        if (k == 1 && tot < n)
            return 0; //特判一下，假如k=1，并且原来的序列可以异或出0，就要返回0，tot表示线性基中的元素个数，n表示序列长度
        if (tot < n)
            k--;               //类似上面，去掉0的情况，因为线性基中只能异或出不为0的解
        if (k >= (1ll << tot)) //线性基包含的数为(1<<tot)-1(组合数之和减去不取的一种情况)  tot为线性基大小  返回-1为找不到k_th的数
            return -1;
        ll ans = 0;
        for (int i = 0; i <= 63; i++)
            if (d[i] != 0){
                if (k % 2 == 1)
                    ans ^= d[i];
                k /= 2;
            }
        if (k != 0)
            return -1;
        return ans;
    }
};
LB merge(LB &n1, LB &n2) //线性基合并
{
    LB ret = n1;
    for (int i = 0; i <= 63; i++)
        if (n2.d[i])
            ret.add(n2.d[i]);
    return ret;
}
LB Merge(LB A, LB B)//线性基求交
{
    LB All, C, D;
    for (int i = 63; ~i; i--){
        All.d[i] = A.d[i];
        D.d[i] = 1ll << i;
    }
    for (int i = 63; ~i; i--){
        if (B.d[i]){
            ll v = B.d[i], k = 0;
            bool can = true;
            for (int j = 63; ~j; j--){
                if (v & (1ll << j)){
                    if (All.d[j]){
                        v ^= All.d[j];
                        k ^= D.d[j];
                    }
                    else{
                        can = false;
                        All.d[j] = v;
                        D.d[j] = k;
                        break;
                    }
                }
            }
            if (can){
                ll v = 0;
                for (int j = 63; ~j; j--)
                    if (k & (1ll << j))
                        v ^= A.d[j];
                C.add(v);
            }
        }
    }
    C.rebuild();
    return C;
}