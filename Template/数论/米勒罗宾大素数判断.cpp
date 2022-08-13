// 米勒罗宾大素数判定
ll q_mul(ll a, ll b, ll mod) {    //快乘法 基于快速幂的二分思想 
	ll ans = 0;                    //由于考虑到取模数很大 快速幂会溢出 
	while (b) {                    //必须使用该方法 
		if (b & 1)                    //我这里写的是非递归版 
			ans = (ans + a) % mod;
		a = a * 2 % mod;
		b >>= 1;
	}
	return ans;
}

ll q_pow(ll a, ll n, ll mod)
//a^b % mod
{
	ll ret = 1;
	ll tmp = a % mod;
	while (n)
	{
		if (n & 1)//ret = ret * tmp % mod;
			ret = q_mul(ret, tmp, mod);
		//tmp = tmp * tmp % mod;
		tmp = q_mul(tmp, tmp, mod);
		n >>= 1;
	}return ret;
}

bool Miller_Rabbin(ll n, ll a) {//米勒拉宾素数判断函数主体
	ll d = n - 1, s = 0, i;
	while (!(d & 1)) {            // 先把(2^s)*d 算出来 
		d >>= 1;
		s++;
	}
	ll t = q_pow(a, d, n);    //a^d取一次余判断 
	if (t == 1 || t == -1)        //一或负一则可以声明这可能是质数 
		return 1;
	for (i = 0; i < s; i++) {                //不是的话继续乘上s个2 
		if (t == n - 1)            //(n-1)*(n-1)%n=1 这一步是优化 
			return 1;
		t = q_mul(t, t, n);    // 快乘 
	}
	return 0;
}

bool is_prime(ll n) {

	if (n < 2) return 0;
	else if (n == 2) return 1;
	else {
		if (!n % 2)return 0;
	}


	ll i, tab[4] = { 3,4,7,11 };//本来应该取[1,n]内任意整数 
	for (i = 0; i < 4; i++) {                //但一般这几个数足以,不需要太多组测试 
		if (n == tab[i])
			return 1;        //小判断小优化~ 
		if (!n % tab[i])
			return 0;
		if (n > tab[i] && !Miller_Rabbin(n, tab[i]))
			return 0;
	}
	return 1;
}ll n;



 //------------------------上面为米勒拉宾大数素数判别-----------------------------------------------------------------------------------------
//   -------------------------
bool isPrime(int n)
{    //返回1表示判断为质数，0为非质数，在此没有进行输入异常检测
	double n_sqrt;
	if (n == 2 || n == 3) return true;
	if (n % 6 != 1 && n % 6 != 5) return false;
	n_sqrt = floor(sqrt((double)n));
	for (int i = 5; i <= n_sqrt; i += 6)
	{
		if (n % (i) == 0 | n % (i + 2) == 0) return false;
	}
	return true;
}