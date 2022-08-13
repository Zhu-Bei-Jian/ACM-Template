// 线性筛  筛 莫比乌斯函数 / 欧拉函数 /因子个数/因子和
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
int tot;
int mu[N]; // 莫比乌斯函数 
int phi[N];// 欧拉函数 
int prime[N], vis[N];
int d[N]; // 约数个数 
int a[N]; // 每个数最小因子出现的次数 
int sd[N], sp[N]; // 求每个数的约数之和， sd维护和， sp维护最小因子 一项等比数列之和 
void get()
{
    mu[1] = 1;
    phi[1] = 1;
    d[1] = 1;
    sd[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        if (!vis[i])
        {
            prime[++tot] = i, mu[i] = -1, phi[i] = i - 1, d[i] = 2, a[i] = 1;
            sd[i] = sp[i] = i + 1;
        }
        for (int j = 1; j <= tot && i * prime[j] <= N; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                d[i * prime[j]] = d[i] / (a[i] + 1) * (a[i] + 2);
                a[i * prime[j]] = a[i] + 1;
                sd[i * prime[j]] = sd[i] / sp[i] * (sd[i] * prime[j] + 1);
                sp[i * prime[j]] = sp[i] * prime[j] + 1;
                break;
            }
            mu[i * prime[j]] = -mu[i];
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
            d[i * prime[j]] = d[i] * d[prime[j]], a[i * prime[j]] = 1;
            sd[i * prime[j]] = sd[i] * sd[prime[j]], sp[i * prime[j]] = sp[prime[j]] + 1;
        }
    }
}
int main()
{

    get();
    for (int i = 1; i <= 100; i++)
        cout << mu[i] << endl;
    return  0;
}
