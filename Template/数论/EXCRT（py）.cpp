x=0
y=0
def exgcd(a , b ):
    global x,y
    if b==0 :
        x=1
        y=0
        return a
    else :
        GCD=exgcd(b,a%b)
        tp=x
        x=y
        y=tp-a//b*y
        return GCD

ai=[0]
bi=[0]
def excrt(n):
    global  x,y
    M=int(bi[1])
    ans=int(ai[1])
    for i in range(2,n+1):
        a = M
        b = bi[i]
        c = (ai[i] - ans % b + b) % b
        GCD = exgcd( a , b )
        bg = b // GCD
        if (c%GCD) != 0 :
            return -1
        x=x*(c//GCD)%bg
        ans+=x*M
        M*=bg
        ans = (ans % M + M) % M
    return (ans % M + M) % M

n=int(input())

for i in range(1,n+1):
    t1,t2=map(int,input().split())
    bi.append(t1)
    ai.append(t2)
print(excrt(n))