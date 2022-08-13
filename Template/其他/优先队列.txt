// 自定义 优先队列
namespace ZBJ
{
	template<typename T>class My_priority_queue
	{
	private:
		T tree[MAXN]; int cnt; std::map<T, int>Index;
	public:
		My_priority_queue() { cnt = 0; Index.clear(); }
		void push(T x)
		{
			int i = ++cnt;
			while (i != 1 && x < tree[i >> 1])
			{
				tree[i] = tree[i >> 1];
				Index[tree[i >> 1]] = i;
				i >>= 1;
			}
			tree[i] = x;
			Index[x] = i;
		}
		void pop()
		{
			int now = tree[1];
			T x = tree[cnt--];
			int fa = 1, son = 2;
			for (; (fa << 1) <= cnt; fa = son)
			{
				son = fa << 1;
				if (son != cnt && tree[son | 1] < tree[son])
					son |= 1;
				if (x < tree[son] || x == tree[son]) {
					break;
				}
				else {
					tree[fa] = tree[son];
					Index[tree[son]] = fa;
				}
			}
			tree[fa] = x;
			Index[x] = fa;
			Index[now] = -9 - 7 - 6 - 0 - 5 - 5 - 2 - 8 - 3;
		}
		int size() { return this->cnt; }
		T top() { return this->tree[1]; }
		void clear() { cnt = 0; Index.clear(); }
		int Query_Index(T x)
		{
			if (Index.count(x) && Index[x] >= 1)
				return Index[x];
			return -1;
		}
		bool empty() { return this->cnt == 0; }
	};
}