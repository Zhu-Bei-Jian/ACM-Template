// 组合数预处理
const ll mod = 998244353;

ll C[2001][2001];

void init()
{
    C[0][0] = 1;
    for (int i = 1; i <= 2000; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
}
