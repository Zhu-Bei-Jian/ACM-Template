import java.util.*;
import java.io.*;
import java.math.*;
 
public class Main
{
    static BigInteger a[] = new BigInteger[105],m[] = new BigInteger[105];;
    static int n;
    static BigInteger k;
    static BigInteger x,y;
    static BigInteger v0 = BigInteger.valueOf(0),v1 = BigInteger.valueOf(1);
    static BigInteger exgcd(BigInteger a,BigInteger b)
    {
        if(b.equals(v0))
        {
            y = v0;
            x = v1;
            return a;
        }
        BigInteger r = exgcd(b,a.remainder(b));
        BigInteger tmp = y;
        y = x.subtract(a.divide(b).multiply(y));
        x = tmp;
        return r;
    }
    static void exchina()
    {
        BigInteger M = m[1],A = a[1],t,d;
        for(int i = 2;i <= n;++i)
        {
            d = exgcd(M,m[i]);
            if(a[i].subtract(A).remainder(d).compareTo(v0) != 0)
            {
                System.out.println("he was definitely lying");
                return;
            }
            x = x.multiply((a[i].subtract(A)).divide(d));
            t = m[i].divide(d);
            x = (x.remainder(t).add(t)).remainder(t);
            A = M.multiply(x).add(A);
            M = M.divide(d).multiply(m[i]);
            A=A.remainder(M);
        }
        A = A.remainder(M).add(M).remainder(M);
        if(A.compareTo(k)>0)
            System.out.println("he was probably lying");
        else
            System.out.println(A);
    }
    public static void main(String args[])
    {
        Scanner in=new Scanner(System.in);
 
        n=in.nextInt();
        k = in.nextBigInteger();
 
 
        for(int i = 1;i <= n;++i)
        {
            m[i] = in.nextBigInteger();
            a[i] = in.nextBigInteger();
        }
        exchina();
    }
 
}