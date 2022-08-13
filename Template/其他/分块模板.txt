//分块模板 
const int32_t MAXN = 1e5 + 5;
const int MAXBS = 350;//sqrt(MAXN)


int a[MAXN];
int block[MAXN];// block[i] // i号元素属于第几块
int block_size;//每个块的大小
int fl[MAXN];
int fr[MAXN];



inline void update(int l, int r)//区间修改
{
    int ans = 0;
    if (block[l] == block[r]) {
        for (int i = l; i <= r; i++)
        {

        }
    }
    else
    {
        int first_block_end = fr[block[l]];//暴力修改第一块
        for (int i = l; i <= first_block_end; i++) {

        }

        //--------------------------------------------------
        int last_block_begin = fl[block[r]];//暴力修改最后一块
        for (int i = last_block_begin; i <= r; i++) {

        }


        //--------------------------------------------------
        for (int i = block[l] + 1; i <= block[r] - 1; i++) {//遍历中间完整块   //i 块号

        }

    }


}

inline int query(int l, int r)//区间查询
{
    int ans = 0;
    if (block[l] == block[r]) {
        for (int i = l; i <= r; i++)
        {

        }
    }
    else
    {
        int first_block_end = fr[block[l]];//暴力查询第一块
        for (int i = l; i <= first_block_end; i++) {

        }

        //--------------------------------------------------
        int last_block_begin = fl[block[r]];//暴力查询最后一块
        for (int i = last_block_begin; i <= r; i++) {

        }


        //--------------------------------------------------
        for (int i = block[l] + 1; i <= block[r] - 1; i++) {//遍历中间完整块   //i 块号

        }

    }

    return ans;
}

inline void pre_work(int n)//预处理工作
{
    for (int i = 1; i <= block[n]; i++)// 块信息的预处理
    {
        int l = fl[i]; int r = fr[i];
        for (int j = l; j <= r; j++) {


        }
    }
}
int32_t main()
{
#ifdef DEBUG
	freopen("..\\DEBUG\\IO\\1.in", "r", stdin);
	// freopen("my.out", "w", stdout);
	clock_t c1 = clock();
#endif

    int n, m;
    read(n, m);
    block_size = sqrt(n);//每个块的大小
    for (int i = 1; i <= n; i++)//元素下标从1开始
    {
        read(a[i]);
        fl[i] = ((i - 1) * (block_size)) + 1; fr[i] = i * block_size < n ? i * block_size : n; // 每个块的左右端点
        block[i] = (i - 1) / block_size + 1;//块的下标也从1开始
    }
    pre_work(n);



#ifdef DEBUG
	std::cerr << "Time:" << clock() - c1 << "ms" << std::endl;
#endif
	fastIO::flush();
	return Accepted;
}
///                 .-~~~~~~~~~-._       _.-~~~~~~~~~-.
///             __.'              ~.   .~              `.__
///           .'//                  \./                  \\`.
///        .'//                     |                     \\`.
///       .'// .-~"""""""~~~~-._     |     _,-~~~~"""""""~-. \\`.
///     .'//.-"                 `-.  |  .-'                 "-.\\`.
///   .'//______.============-..   \ | /   ..-============.______\\`.
/// .'______________________________\|/______________________________`.
