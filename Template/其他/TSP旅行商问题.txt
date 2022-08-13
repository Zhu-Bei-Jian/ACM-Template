int TSP(int n)
{
    //定义dp[S][v]为已经经过了点集S之后，目前在点v(v已经包含在S中)，回到0节点的最小边权。 
    memset(dp,127,sizeof(dp));
    dp[(1<<n)-1][0] = 0;
    for(int S = (1<<n)-1 ; S >= 0 ; S --) {
        for(int i = 0 ; i < n ; i ++) {
            for(int j = 0 ; j < n ; j ++) {
                if(!(S>>j&1))
                    dp[S][i] = min(dp[S][i],dp[S|1<<j][j]+dis(i,j));
            }
        }
    }
   return dp[0][0];
}