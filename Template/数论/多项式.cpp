// 多项式 相关
namespace Polynomial{
    const ll P = 998244353, g = 3, gi = 332748118;
    static int rev[MAXN];
    int lim, bit;
    int add(int a, int b){
        return (a += b) >= P ? a - P : a;
    }
    int qpow(int a, int b){
        int prod = 1;
        while(b){
            if(b & 1) prod = (ll)prod * a % P;
            a = (ll)a * a % P;
            b >>= 1;
        }
        return (prod + P) % P;
    }
    void calrev() {
        for(int i = 1; i < lim; ++i)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    }
    void NTT(int *A, int inv){
        for(int i = 0; i < lim; ++i)
            if(i < rev[i]) swap(A[i], A[rev[i]]);
        for(int mid = 1; mid < lim; mid <<= 1){
            int tmp = qpow(inv == 1 ? g : gi, (P - 1) / (mid << 1));
            for(int j = 0; j < lim; j += (mid << 1)){
                int omega = 1;
                for(int k = 0; k < mid; ++k, omega = (ll)omega * tmp % P){
                    int x = A[j + k], y = (ll)omega * A[j + k + mid] % P;
                    A[j + k] = (x + y) % P;
                    A[j + k + mid] = (ll)(x - y + P) % P;
                }
            }
        }
        if(inv == 1) return;
        int invn = qpow(lim, P - 2);
        for(int i = 0; i < lim; ++i)
            A[i] = (ll)A[i] * invn % P;
    }
    static int x[MAXN], y[MAXN];
    void mul(int *a, int *b){ // 乘
        memset(x, 0, sizeof x);
        memset(y, 0, sizeof y);
        for(int i = 0; i < (lim >> 1); ++i)
            x[i] = a[i], y[i] = b[i];
        NTT(x, 1), NTT(y, 1);
        for( int i = 0; i < lim; ++i)
            x[i] = (ll)x[i] * y[i] % P;
        NTT(x, -1);
        for(int i = 0; i < lim; ++i)
            a[i] = x[i];
    }
    static int c[2][MAXN];
    void Inv(int *a, int n){ //求逆
        int p = 0;
        memset(c, 0, sizeof c);
        c[0][0] = qpow(a[0], P - 2);
        lim = 2, bit = 1;
        while(lim <= (n << 1))
        {
            lim <<= 1, bit++;
            calrev();
            p ^= 1;
            memset(c[p], 0, sizeof c[p]);
            for(int i = 0; i <= lim; ++i)
                c[p][i] = add(c[p^1][i], c[p^1][i]);
            mul(c[p^1], c[p^1]);
            mul(c[p^1], a);
            for(int i = 0; i <= lim; ++i)
                c[p][i] = add(c[p][i], P - c[p^1][i]);
        }
        for(int i = 0; i < lim; ++i)
            a[i] = c[p][i];
    }
    void derivative(int *a, int n){//求导
        for(int i = 1; i <= n; ++i)
            a[i - 1] = (ll)a[i] * i % P;
        a[n] = 0;
    }
    void inter(int *a, int n){//积分
        for(int i = n; i >= 1; --i)
            a[i] = (ll)a[i - 1] * qpow(i, P - 2) % P;
        a[0] = 0;
    }
    static int b[MAXN], T[MAXN], K[MAXN];
    void ln(int *a, int n){ //多项式取ln
        memcpy(b, a, sizeof b);
        Inv(b, n), derivative(a, n);
        while(lim <= (n << 2)) lim <<= 1, bit++;
        calrev();
        mul(a, b);
        inter(a, n);
        for(int i = n + 1; i <= lim; ++i)
            a[i] = 0;
    }
    void exp(int *a, int n){ //多项式exp
        int z, d;
        z = lim = 2, d = bit = 1;
        memset(K, 0, sizeof K);
        K[0] = 1;
        while(z <= (n<<1)){
            z <<= 1, d++;
            for(int i = 0; i < (z>>1); ++i)
                T[i] = K[i];
            ln(T, (z>>1) - 1);
            for(int i = 0; i < (z>>1); ++i)
                T[i] = add(a[i] + (i == 0), P - T[i]);
            lim = z, bit = d;
            calrev();
            mul(K, T);
            for(int i = z; i <= (z<<1); ++i)
                K[i] = T[i] = 0;
        }
        for(int i = 0; i <= n; ++i)
            a[i] = K[i];
    }
}
using namespace Polynomial;