// 后缀自动机
struct SAM {
    struct node {
        int ch[26];
        int len, fa, siz[2];
        node() {
            memset(ch, 0, sizeof(ch)), len = 0;
        }
    } pi[MAXN << 1];
    int last, tot;
    void init(){
        last=tot=1;
        pi[1].fa=pi[1].len=0;
        memset(pi[1].ch,0,sizeof(pi[1].ch));
    }
    int inline newnode(){
        ++tot;
        memset(pi[tot].ch,0,sizeof(pi[tot].ch));
        pi[tot].fa=pi[tot].len=0;
        return tot;
    }
    int add(int c,int last,int id){
        if (pi[last].ch[c]){ //广义后缀自动机
            int p=last,x=pi[p].ch[c];
            if (pi[p].len+1==pi[x].len){pi[x].siz[id]=1;return x;}
            else {
                int q=newnode();
                pi[q]=pi[x];
                pi[q].siz[0]=pi[q].siz[1]=0;
                pi[q].len=pi[p].len+1,pi[q].fa=0;
                while (p&&pi[p].ch[c]==x)pi[p].ch[c]=q,p=pi[p].fa;
                pi[q].fa=pi[x].fa,pi[x].fa=q;
                pi[q].siz[id]=1;
                return q;
            }
        }
        int p = last, np = newnode();
        pi[np].len = pi[p].len + 1;
        for (; p && !pi[p].ch[c]; p = pi[p].fa) {
            pi[p].ch[c] = np;
        }
        if (!p)pi[np].fa = 1;
        else {
            int q = pi[p].ch[c];
            if (pi[q].len == pi[p].len + 1)pi[np].fa = q;
            else {
                int nq = newnode();
                pi[nq] = pi[q];
                pi[nq].len = pi[p].len + 1;
                pi[nq].siz[0]=pi[nq].siz[1]=0;
                for (; p && pi[p].ch[c] == q; p = pi[p].fa)pi[p].ch[c] = nq;
                pi[nq].fa=pi[q].fa,pi[q].fa = pi[np].fa = nq;
            }
        }
        pi[np].siz[id]=1;
        return np;
    }
    int cnt[MAXN<<1],id[MAXN<<1];
    void sort(){
        for (int i=1;i<=tot;i++)cnt[i]=0;
        for (int i=1;i<=tot;i++)cnt[pi[i].len]++;
        for (int i=1;i<=tot;i++)cnt[i]+=cnt[i-1];
        for (int i=1;i<=tot;i++)id[cnt[pi[i].len]--]=i;
    }
}sam;
/*
 * sam.init()
 * sam.last=sam.add(s[i]-'a',sam.last)
 * sam.sort()
 * 几个串,siz开几维
 * */