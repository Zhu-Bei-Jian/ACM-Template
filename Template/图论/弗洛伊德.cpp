// 多源最短路  弗洛伊德
void Floyd(int n, int m)//n个顶点  m条边
{
	//先对邻接矩阵进行初始化 
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			edge[i][j] = INF;
		edge[i][i] = 0;
	}
	//建图 
	while (m--)
	{
		int u, v;
		in(u); in(v);
		ll tmp; in(tmp);
		edge[u][v] = min(edge[u][v], tmp);//处理重边
		edge[v][u] = edge[u][v];//无向图  双向建边
	}
	for (int k = 1; k <= n; k++)
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			 
				//若结点对跟中转点不连通，则跳过 
				if ( edge[i][j] > (edge[i][k] + edge[k][j]))
					//更新最短路径 
					edge[i][j] = edge[i][k] + edge[k][j];
	//cout << edge[1][n] << endl;
}