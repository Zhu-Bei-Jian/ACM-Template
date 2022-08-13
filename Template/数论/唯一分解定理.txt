//唯一分解定理  因子个数 因子和
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int MAXN = 100005;
#define rep( i , a , b ) for ( int i = a ; i < b ; ++ i )
#define CLR(a) memset(a,0,sizeof a)
#define repf( i , a , b ) for ( int i = a ; i <= b ; ++ i )
template <class T>
void in(T& x) {
	static char ch; static bool neg;
	for (ch = neg = 0; ch < '0' || '9' < ch; neg |= ch == '-', ch = getchar());
	for (x = 0; '0' <= ch && ch <= '9'; (x *= 10) += ch - '0', ch = getchar());
	x = neg ? -x : x;
}


int k = 0;
struct Factor {//存分解后的素因子和该素因子个数 
	ll factor, Count;
	Factor() {
		Count = 0;
	}
}fa[100005];
void decompose(ll x) {//唯一分解定理 
	ll ans = 0;
	for (ll i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			fa[k].factor = i;
			while (x % i == 0) {
				x /= i;
				fa[k].Count++;
			}
			k++;
		}
	}
	if (x > 1) {
		fa[k].factor = x;
		fa[k].Count = 1;
		k++;
	}
}


ll dcpCount(ll x) {//所有因子的个数（包括1） 
	ll ans = 1;
	for (ll i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			ll temp = 0;
			while (x % i == 0) {
				x /= i;
				temp++;
			}
			ans *= (temp + 1);
		}
	}
	if (x > 1) ans *= 2;
	return ans;
}


ll dcpSum(ll x) {//所有因子的和（包括1）
	ll ans = 1;
	for (ll i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			ll temp = 1;
			while (x % i == 0) {
				x /= i;
				temp *= i;
			}
			ans *= (temp * i - 1) / (i - 1);
		}
	}
	if (x > 1) ans *= (1 + x);
	return ans;
}
 

int main()
{
	ll n;
	while (scanf("%lld", &n) != EOF) {
		ll temp = 1;
		memset(fa, 0, sizeof(fa));
		k = 0;
		decompose(n);
		for (int i = 0; i < k; i++) {
			if (i) printf(" * ");
			printf("%lld^%lld", fa[i].factor, fa[i].Count);
			//temp *= qpow(fa[i].factor, fa[i].Count);
		}
		printf(" = %lld\n", n);
		//printf("因子和： %lld\n", dcpSum(n));
		//printf("因子个数： %lld\n", dcpCount(n));
	}
	return 0;
}