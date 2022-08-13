// 高斯消元 行列式计算
struct det
{
	ll a[500][500];
	ll gauss(int n)///高斯消元求行列式的值  用到了逆元把除法变乘法 避免精度问题
	{
		ll ret = 1;
		int flag = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = i + 1; j <= n; j++)
				while (a[j][i])
				{
					ll tmp = a[i][i] / a[j][i];
					for (int k = i; k <= n; k++)  ((a[i][k] -= a[j][k] * tmp % mod) += mod) %= mod;
					swap(a[i], a[j]);
					flag *= -1;
				}
			if (!a[i][i])   return 0;
			(ret *= a[i][i]) %= mod;
		}
		return flag == -1 ? mod - ret : ret;
	}

}D;