//马拉车
char M_S[MAXN];//插入特殊字符后的 串
char st[MAXN];//原来的字符串
int R[MAXN];//回文半径
int init_str()//插入特殊字符 
{
    int len = strlen(st);int j = 2;
    M_S[0] = '^';M_S[1] = '$';
    for (int i = 0; i < len; i++)M_S[j++] = st[i], M_S[j++] = '$';
    M_S[j] = '&';
    return j;
}
void Manacher()
{
    int len = init_str(), mid = 1, mx = 1, ans = -1;
    for (int i = 1; i < len; i++)
    {
        if (i < mx)R[i] = min(mx - i, R[mid * 2 - i]);
        else R[i] = 1;
        while (M_S[i - R[i]] == M_S[i + R[i]])R[i]++;
        if (mx < i + R[i])
        {
            mid = i;
            mx = i + R[i];
        }
    }
}
//回文半径 R[i] 
//对应的实际回文长度  R[i]-1
//实际回文串的起始下标 (i-R[i])/2    //  原字符串 下标 0开始
