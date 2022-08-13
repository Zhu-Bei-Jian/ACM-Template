//回文树
const int MAXN = 3e5 + 10;// n(空间复杂度o(n*ALP)),实际开n即可
const int ALP = 26;
struct PAM { // 每个节点代表一个回文串
	int next[MAXN][ALP]; // next指针,参照Trie树
	int fail[MAXN]; // fail失配后缀链接  //指向 最长回文后缀
	int cnt[MAXN]; // 此回文串出现个数
	int num[MAXN];//fail 链的长度  //即以 该位置为结尾的 的回文串 个数
	int len[MAXN]; // 回文串长度
	int s[MAXN]; // 存放添加的字符
	int last; //指向上一个字符所在的节点，方便下一次add
	int n; // 已添加字符个数
	int p; // 节点个数
	int newnode(int w) { // 初始化节点，w=长度
		for (int i = 0; i < ALP; i++)
			next[p][i] = 0;
		cnt[p] = 0;
		num[p] = 0;
		len[p] = w;
		return p++;
	}
	void init() {
		p = 0;
		newnode(0);
		newnode(-1);
		last = 0;
		n = 0;
		s[n] = -1; // 开头放一个字符集中没有的字符，减少特判
		fail[0] = 1;
	}
	int get_fail(int x) { // 和KMP一样，失配后找一个尽量最长的
		while (s[n - len[x] - 1] != s[n]) x = fail[x];
		return x;
	}
	void add(int c) {
		c -= 'a';
		s[++n] = c;
		int cur = get_fail(last);
		if (!next[cur][c]) {
			int now = newnode(len[cur] + 2);
			fail[now] = next[get_fail(fail[cur])][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last]++;
	}
	void count() {
		// 最后统计一遍每个节点出现个数
		// 父亲累加儿子的cnt,类似SAM中parent树
		// 满足parent拓扑关系
		for (int i = p - 1; i >= 0; i--)
			cnt[fail[i]] += cnt[i];
	}
}pam;
char s[MAXN];
 /*
	pam.init();
	scanf("%s", s);
	int len = strlen(s);
	for (int i = 0; i < len; i++)pam.add(s[i]);
 */