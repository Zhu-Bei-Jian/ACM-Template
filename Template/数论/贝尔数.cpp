// 贝尔数
#include<bits/stdc++.h>
using namespace std;
#define maxn 300010
#define mod 998244353
#define MS(f,x) memset(f,0,4<<(x))
#define bin(x) (1<<(x))

int T, n;
int inv[maxn], log_2[maxn];
int ksm(int x, int y) { int re = 1; for (; (y & 1 ? re = 1ll * re * x % mod : 0), y; y >>= 1, x = 1ll * x * x % mod); return re; }
int* w[30]; void prep(int N) {
	inv[1] = 1; for (int i = 2; i <= N; i++)inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod, log_2[i] = ceil(log2(i));
	for (int i = 1, wn; i <= log_2[N]; i++) {
		w[i] = new int[bin(i - 1)]; w[i][0] = 1; wn = ksm(3, (mod - 1) / bin(i));
		for (int j = 1; j < bin(i - 1); j++)w[i][j] = 1ll * w[i][j - 1] * wn % mod;
	}
}
int limit, r[maxn]; void get(int lg) { for (int i = 1; i < bin(lg); i++)r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lg - 1)); }
void ntt(int* f, int lg, int type = 0)
{
	limit = bin(lg); if (type)reverse(f + 1, f + limit);
	for (int i = 1; i < limit; i++)if (i < r[i])swap(f[i], f[r[i]]);
	for (int mid = 1, Lg = 1; mid < limit; mid <<= 1, Lg++)for (int j = 0; j < limit; j += (mid << 1))for (int i = 0; i < mid; i++)
	{
		int t = 1ll * f[j + i + mid] * w[Lg][i] % mod; f[j + i + mid] = (f[j + i] - t + mod) % mod; f[j + i] = (f[j + i] + t) % mod;
	}
}
void NTT(int* f, int* g, int ln)
{
	int lg = log_2[ln * 2 - 1]; get(lg);
	ntt(f, lg); ntt(g, lg); for (int i = 0; i < bin(lg); i++)f[i] = 1ll * f[i] * g[i] % mod;
	ntt(f, lg, 1); for (int i = 0; i < bin(lg); i++)f[i] = i < ln ? 1ll * f[i] * inv[bin(lg)] % mod : 0;
}
int A[maxn], B[maxn], C[maxn], D[maxn], E[maxn];
void getinv(int* f, int* g, int ln)
{
	if (ln == 1) { g[0] = ksm(f[0], mod - 2); return; }getinv(f, g, (ln + 1) >> 1); int lg = log_2[ln * 2 - 1];
	get(lg); MS(A, lg); MS(B, lg); memcpy(A, f, ln << 2); memcpy(B, g, ln << 2);
	ntt(A, lg); ntt(B, lg); for (int i = 0; i < bin(lg); i++)A[i] = 1ll * (2 - 1ll * A[i] * B[i] % mod + mod) % mod * B[i] % mod;
	ntt(A, lg, 1); for (int i = 0; i < ln; i++)g[i] = 1ll * A[i] * inv[bin(lg)] % mod;
}
void Dao(int* f, int* g, int ln) { for (int i = 0; i < ln - 1; i++)g[i] = 1ll * f[i + 1] * (i + 1) % mod; g[ln - 1] = 0; }
void Jifen(int* f, int* g, int ln) { for (int i = ln - 1; i > 0; i--)g[i] = 1ll * f[i - 1] * inv[i] % mod; g[0] = 0; }
void getln(int* f, int* g, int ln)
{
	MS(C, log_2[ln * 2 - 1]); MS(D, log_2[ln * 2 - 1]);
	getinv(f, C, ln); Dao(f, D, ln); NTT(C, D, ln); Jifen(C, g, ln);
}
void getexp(int* f, int* g, int ln)
{
	if (ln == 1) { g[0] = 1; return; }getexp(f, g, (ln + 1) >> 1);
	MS(E, log_2[ln * 2 - 1]); getln(g, E, ln);
	for (int i = 0; i < ln; i++)E[i] = (f[i] - E[i] + mod) % mod; E[0]++; NTT(g, E, ln);
}
int fac[maxn], inv_fac[maxn];
void Wk(int N) {
	fac[0] = inv_fac[0] = 1; for (int i = 1; i <= N; i++)fac[i] = 1ll * fac[i - 1] * i % mod;
	inv_fac[N] = ksm(fac[N], mod - 2); for (int i = N - 1; i >= 1; i--)inv_fac[i] = 1ll * inv_fac[i + 1] * (i + 1) % mod;
}
int F[maxn], G[maxn];
void solve()
{
	Wk(262144); prep(262144);
	for (int i = 1; i <= 100000; i++)F[i] = inv_fac[i];
	getexp(F, G, 100001); for (int i = 1; i <= 100000; i++)G[i] = 1ll * G[i] * fac[i] % mod;
}

int main()
{
	solve();
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		printf("%d\n", G[n]);

	}
	return 0;
}
