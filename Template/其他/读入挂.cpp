template<typename T>inline void read(T& x){ 
    static char ch; static bool neg; 
    for (ch = neg = 0; ch < '0' || '9' < ch; neg |= ch == '-', ch = getchar());
    for (x = 0; '0' <= ch && ch <= '9'; (x *= 10) += ch - '0', ch = getchar());
    x = neg ? -x : x; 
}
template<typename T, typename... Types>void read(T& x, Types& ... oth) {
    read(x);
    read(oth...);
}
