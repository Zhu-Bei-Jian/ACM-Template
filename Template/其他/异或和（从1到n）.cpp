// 1到n 的 异或和
// (1,n)
ll xor_sum(ll n){
    ll t=n&3;
    if (t&1) return t/2ull^1;
    return t/2ull^n;
}