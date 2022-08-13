// 矩阵旋转
void xz()
{

      for(int i=1; i<=n/2; i++ )
     {
        for( int j=i; j<n-i+1; j++ )
         {
            int t = M[i][j];
            M[i][j] = M[n-j+1][i];
            M[n-j+1][i] = M[n-i+1][n-j+1];
            M[n-i+1][n-j+1] = M[j][n-i+1];
            M[j][n-i+1] = t;
        }
    }
}