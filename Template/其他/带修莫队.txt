// 带修莫队
#include<bits/stdc++.h>
#define _unique(v) sort(v.begin(), v.end()), v.erase(unique(v.begin(), v.end()), v.end())
namespace fastIO {
#define BUF_SIZE 100000
#define OUT_SIZE 100000
    //fread->read
    bool IOerror = 0;
    //inline char nc(){char ch=getchar();if(ch==-1)IOerror=1;return ch;}
    inline char nc() {
        static char buf[BUF_SIZE], * p1 = buf + BUF_SIZE, * pend = buf + BUF_SIZE;
        if (p1 == pend) {
            p1 = buf; pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if (pend == p1) { IOerror = 1; return -1; }
        }
        return *p1++;
    }
    inline bool blank(char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }
    template<class T> inline bool read(T& x) {
        bool sign = 0; char ch = nc(); x = 0;
        for (; blank(ch); ch = nc());
        if (IOerror)return false;
        if (ch == '-')sign = 1, ch = nc();
        for (; ch >= '0' && ch <= '9'; ch = nc())x = x * 10 + ch - '0';
        if (sign)x = -x;
        return true;
    }
    inline bool read(double& x) {
        bool sign = 0; char ch = nc(); x = 0;
        for (; blank(ch); ch = nc());
        if (IOerror)return false;
        if (ch == '-')sign = 1, ch = nc();
        for (; ch >= '0' && ch <= '9'; ch = nc())x = x * 10 + ch - '0';
        if (ch == '.') {
            double tmp = 1; ch = nc();
            for (; ch >= '0' && ch <= '9'; ch = nc())tmp /= 10.0, x += tmp * (ch - '0');
        }
        if (sign)x = -x;
        return true;
    }
    inline bool read(char* s) {
        char ch = nc();
        for (; blank(ch); ch = nc());
        if (IOerror)return false;
        for (; !blank(ch) && !IOerror; ch = nc())*s++ = ch;
        *s = 0;
        return true;
    }
    inline bool read(char& c) {
        for (c = nc(); blank(c); c = nc());
        if (IOerror) { c = -1; return false; }
        return true;
    }
    template<class T, class... U>bool read(T& h, U&... t) { return read(h) && read(t...); }
    template<typename T>void Qans(T x) { char s[65]; int32_t cnt = 0; if (x > 0)while (x > 0)s[cnt++] = (x - (x / 10 * 10)) + '0', x /= 10; else if (x < 0) { while (x < 0)s[cnt++] = (x / 10 * 10) - x + '0', x /= 10; s[cnt++] = '-'; }if (cnt == 0)putchar('0'); else for (int32_t i = cnt - 1; ~i; i--)putchar(s[i]); }
    template<typename T>void print(T x) { Qans(x); putchar('\n'); }
    template<typename T, typename... types >void print(T x, types... oth) {
        Qans(x); putchar(' '); print(oth...);
    }
#undef OUT_SIZE
#undef BUF_SIZE
}
#define read fastIO::read
#define print fastIO::print
typedef long long ll;
using namespace std;
const int32_t MAXN = 1e6 + 5;
int n, m;
int a[MAXN];
struct Query
{
    int l, r, pre, id;
}Q[MAXN];
int Qnum = 0;
struct Modify
{
    int pos, val;
}C[MAXN];
int Cnum = 0;
int  bs = 0;
int Qans[MAXN];
int ans = 0;

bool cmp(const Query& a, const Query& b)
{
    if (a.l / bs != b.l / bs) return a.l < b.l;
    if (a.r / bs != b.r / bs) return a.r < b.r;
    return a.pre < b.pre;
}

inline void Add(int val)
{

}
inline void Del(int val)
{

}
inline void Time_Move(int Time_pointer, int i)
{
    if (C[Time_pointer].pos >= Q[i].l && C[Time_pointer].pos <= Q[i].r)
    {

        Del(a[C[Time_pointer].pos]);
        Add(C[Time_pointer].val);
    }
    //swap(C[Time_pointer].val, a[C[Time_pointer].pos]);
    int tmp = C[Time_pointer].val; C[Time_pointer].val = a[C[Time_pointer].pos]; a[C[Time_pointer].pos] = tmp;
}
inline void Mo_algorithm()
{
    int l = 1, r = 0, Time_pointer = 0;
    for (int i = 1; i <= Qnum; i++)
    {
        while (l < Q[i].l)Del(a[l++]);
        while (l > Q[i].l)Add(a[--l]);
        while (r < Q[i].r)Add(a[++r]);
        while (r > Q[i].r)Del(a[r--]);
        while (Time_pointer < Q[i].pre)Time_Move(++Time_pointer, i);
        while (Time_pointer > Q[i].pre)Time_Move(Time_pointer--, i);

        Qans[Q[i].id] = ans;

    }
    for (int i = 1; i <= Qnum; i++)
        printf("%d\n", Qans[i]);
}
int main()
{
#ifdef DEBUG
    freopen("..\\DEBUG\\IO\\1.in", "r", stdin);
    // freopen("my.Qans", "w", stdout);
#endif
    read(n, m);
    bs = pow(n, 2.0 / 3);
    for (int i = 1; i <= n; i++) read(a[i]);

    while (m--)
    {
        int op = -1;
        read(op);
        if (op == 1)//区间询问
        {
            ++Qnum; read(Q[Qnum].l, Q[Qnum].r);
            Q[Qnum].pre = Cnum;
            Q[Qnum].id = Qnum;
        }
        else//单点修改
        {
            ++Cnum;
            read(C[Cnum].pos, C[Cnum].val);
        }
    }

    sort(Q + 1, Q + Qnum + 1, cmp);
    Mo_algorithm();
    return 0;
}