//二分模板
//找到最大的合法解
while(l<=r)
{
    int mid=(l+r)>>1;
    if(check(mid))ans=mid,l=mid+1;
    else r=mid-1;
}
printf("%d\n",ans);


//找到最小的合法解
while(l<=r)
{
    int mid=(l+r)>>1;
    if(check(mid))ans=mid,r=mid-1;
    else l=mid+1;
}
printf("%d\n",ans);

在单调递增序列a中查找>=x的数中最小的一个（即x或x的后继）
while(l<r)
{
    int mid=(l+r)/2;
    if(a[mid]>=x)
        r=mid;
    else
        l=mid+1;
}
return a[l];
在单调递增序列a中查找<=x的数中最大的一个（即x或x的前驱）
while(l<r)
{
    int mid=(l+r+1)/2;
    if(a[mid]<=x)
        l=mid;
    else
        r=mid-1;
}
return a[l];

while (right-left>=eps)
{
 mid=(left+right)/2;
 if(f(mid))//大于等于eps成立
 right=mid;
 else
 left=mid;
}
for(int i=0;i<100;i++)//循环固定次数二分
{
    double mid=(l+r)/2;
    if(calc(mid))
        r=mid;
    else
        l=mid;
}//在实数域上的二分


//第k小check
    int l = 0, r = 1e7 + 7;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    printf("%d\n", l - 1);


//精确查找---用迭代的方式实现二分查找，精确查找目标元素的位置,假定数组递增排列，且不存在重复元素
int bsearch2(int low,int high,int target){
    while(low <= high){
        int mid = low + (high - low)/2;
        if(num[mid] > target){
            high = mid -1;
        }
        else if(num[mid] < target){
            low = mid + 1;
        }
        else{
            return mid;
        }
    }
    return -1;
}

#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN = 100005;
int mi[MAXN][50];//Çø¼ä×î´óÖµ£¬Çø¼ä×îÐ¡Öµ¡£
int lg[MAXN];
int num[MAXN];


//精确查找---用递归实现二分查找，精确查找目标元素的位置,假定数组递增排列，且不存在重复元素
int bsearch1(int low,int high,int target){
    if(low > high) return -1;

    int mid = low + (high - low)/2;
    if(num[mid] > target){
        return bsearch1(low,mid-1,target);
    }
    if(num[mid] < target){
        return bsearch1(mid+1,high,target);
    }
    return mid;
}



//精确查找---用迭代的方式实现二分查找，精确查找目标元素的位置,假定数组递增排列，且不存在重复元素
int bsearch2(int low,int high,int target){
    while(low <= high){
        int mid = low + (high - low)/2;
        if(num[mid] > target){
            high = mid -1;
        }
        else if(num[mid] < target){
            low = mid + 1;
        }
        else{
            return mid;
        }
    }
    return -1;
}



//界限查找----用二分查找寻找上届，正好大于目标数的那个数(严格界限，不包含自身)
int bsearchupperbound(int low,int high,int target){
    if(low > high || target >= num[high]){
        return -1;
    }

    while(low < high){
        int mid = low + (high - low)/2;
        if(num[mid] > target){
            high = mid;
        }
        else{
            low = mid + 1;
        }
    }
    return high;
}


//界限查找---用二分查找寻找上届，正好大于等于目标数的那个数(松散界限，可以包含自身)
int bsearch5(int low,int high,int target){
    if(low > high || target > num[high]){
        return -1;
    }
    while(low < high){
        int mid = low + (high -low)/2;
        if(num[mid] >= target){
            high = mid;
        }
        else{
            low = mid + 1;
        }
    }
    return high;
}



//界限查找---用二分查找寻找下届，正好小于目标数的那个数(严格界限，不包含自身)
int bsearchlowerbound(int low,int high,int target){
    if(low > high || target <= num[low]){
        return -1;
    }

    while(low < high){
        int mid = (low + high + 1) / 2;     //这里用向上取整，否则陷入死循环 因为low无法往上爬超过high

        if(num[mid] < target){
            low = mid;
        }
        else{
            high = mid -1;
        }
    }
    return low;
}


//界限查找---用二分法寻找下届，正好小于等于目标的那个数  (松散界限，可以包含自身)
int bsearch6(int low,int high,int target){
    if(low > high || target < num[low]){
        return -1;
    }
    while(low < high){
        int mid = (low + high + 1)/2;
        if(num[mid] <= target){
            low = mid;
        }
        else{
            high = mid - 1;
        }
    }
    return low;
}


//用二分查找找寻区域，找到目标元素出现的下标范围，允许重复元素(先找到严格上届和严格下届)
int results[] = {-1,-1};
void searchRange(int low, int high,int target,int len){
    if(low > high){
        return ;
    }
    int lower = bsearchlowerbound(0, len, target);
    lower = lower + 1;
    if(num[lower] == target){
        results[0] = lower;
    }
    else{
        return ;
    }

    int upper = bsearchupperbound(0, len - 1, target);
    upper = upper < 0 ? (len - 1) : (upper -1);

    results[1] = upper;

    return ;

}

//二分查找ST表
void ST_prework(int n){
	for(int i=1 ; i<=n ; ++i)mi[i][0] = num[i];//ÏÂ±ê´Ó1¿ªÊ¼
	//int t = log2(n) + 1;
	for(int i=2;i<=n;i++)lg[i] = lg[i/2] + 1;
	int t = lg[n] + 1;
	for(int i=1 ; i<t ; ++i){
		for(int j=1 ; j<=n-(1<<i)+1 ; ++j){
			mi[j][i] = min(mi[j][i-1],mi[j+(1<<(i-1))][i-1]);
		}
	}
}

int ST_query(int l,int r){//[l,r]±ÕÇø¼ä
	int k = lg[(r-l+1)];
	return min(mi[l][k],mi[r-(1<<k)+1][k]); //·µ»ØÇø¼ä×îÐ¡Öµ
}

int bsearch7(int l,int r){
    int re = num[l++];
    int ll,rr,tmp,mid,flag;
    while(l <= r && re){
        flag = 0;
        ll = l,rr = r;
        mid = l;
        while(ll<=rr){
            mid = (ll + rr)/2;
            if(ST_query(ll,mid) <= re){
                rr = mid-1;tmp = mid;flag = 1;
            }else if(ST_query(mid,rr) <= re){
                ll = mid+1;tmp = mid;flag = 1;
            }else{
                break;
            }
        }
        if(flag){
            re = re % num[tmp];
            l = tmp+1;
        }else break;
    }
    return re;
}
int main(){

	return 0;
}