// ST 表
struct Sparse_Table
{
	int a[MAXN],Log[MAXN], MAX[MAXN][23],MIN[MAXN][23];
	inline int max(int a, int b) {return a > b ? a : b;}
	inline void init(int n)
	{
		for (int i = 2; i <= n; i++)Log[i] = Log[i / 2] + 1;
		for (int i = 1; i <= n; i++)MAX[i][0] = a[i];
		for (int j = 1; (1 << j) <= n; j++)// log n
			for (int i = 1; i + (1 << j) - 1 <= n; i++)//n
				MAX[i][j] = max(MAX[i][j - 1], MAX[i + (1 << (j-1))][j-1]);
	}
	inline int query(int l,int r) {int k = Log[r - l + 1];return max(MAX[l][k], MAX[r - (1 << k) + 1][k]);}
}ST;