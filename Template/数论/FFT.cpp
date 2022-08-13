//FFT 
const double Pi = acos(-1.0);
struct complex_
{

    double x, y;
    complex_(double xx = 0, double yy = 0) { x = xx, y = yy; }
    complex_ operator + (complex_ oth) { return complex_(x + oth.x, y + oth.y); }
    complex_ operator - (complex_ oth) { return complex_(x - oth.x, y - oth.y); }
    complex_ operator * (complex_ oth) { return complex_(x * oth.x - y * oth.y, x * oth.y + y * oth.x); }
}a[MAXN], b[MAXN];
int N, M;
int l, r[MAXN];
int limit;
double ans[MAXN];
void FFT(complex_* A, int type)
{
    for (int i = 0; i < limit; i++)
        if (i < r[i]) std::swap(A[i], A[r[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        complex_ Wn(cos(Pi / mid), type * sin(Pi / mid));
        for (int R = mid << 1, j = 0; j < limit; j += R)
        {
            complex_ w(1, 0);//幂 
            for (int k = 0; k < mid; k++, w = w * Wn)
            {
                complex_ x = A[j + k], y = w * A[j + mid + k];
                A[j + k] = x + y;
                A[j + mid + k] = x - y;
            }
        }
    }
}
void  Get_convolution(double ans[])//卷积
{
    limit = 1;
    l = 0;
    r[0] = 0;
    while (limit <= N + M) limit <<= 1, l++;
    for (int i = 0; i < limit; i++)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    FFT(a, 1);
    FFT(b, 1);
    for (int i = 0; i <= limit; i++) a[i] = a[i] * b[i];
    FFT(a, -1);
    for (int i = 0; i <= N + M; i++)
        ans[i] = a[i].x / limit;
    for (int i = 0; i <= limit; i++) {//初始化 两个多项式
        a[i].x = a[i].y = b[i].x = b[i].y = 0;
    }
}

