// 三分模板

double 版 注意模板中 的 while(...) 这里面可能还需要加其他条件  有时候会T或者WA 可以改一下精度或设置循环次数如++i<100 如 ZOJ 2340
double 版 还有另一种写法： lm=l+(r-l)/3; rm=r-(r-l)/3;
凸函数求极大值：

int版： （解释：若求极大值，若judge(lm)更大，即 lm 更靠近极值点(但是不确定是在左侧还是右侧)，但可以保证 rm 一定在极值点右侧），保留左端点，缩右端点 r 到 rm


while(l+1<r)
{
    int lm=(l+r)>>1,rm=(lm+r)>>1;
    if(judge(lm)>judge(rm))
        r=rm;
    else
        l=lm;
}

//答案取 l

double版：

while(l+eps<r)
{
    double lm=(l+r)/2,rm=(lm+r)/2;
    if(judge(lm)>judge(rm))
        r=rm;
    else
        l=lm;
}

//答案取 l 或 (l+r)/2  (尽管此时 l 和 r 已经相等，但因为精度问题，取 r 可能会错)


凹函数求极小值：

while(l+1<r)
{
    int lm=(l+r)>>1,rm=(lm+r)>>1;
    if(judge(lm)>judge(rm))
        l=lm;
    else
        r=rm;
}

//答案取 r


double版：

while(l+eps<r)
{
    double lm=(l+r)/2,rm=(lm+r)/2;
    if(judge(lm)>judge(rm))
        l=lm;
    else
        r=rm;
}

//答案取 r 或 (l+r)/2  (尽管此时 l 和 r 已经相等，但因为精度问题，取 l 可能会错)