//KMP
struct KMP
{
	int NEXT[MAXN];
	void GetNext(char* p)
	{
		int pLen = strlen(p);
		NEXT[0] = -1;
		int k = -1;
		int j = 0;
		while (j < pLen - 1)
		{
			//p[k]表示前缀，p[j]表示后缀
			if (k == -1 || p[j] == p[k])
			{
				++k;
				++j;
				NEXT[j] = k;
			}
			else
			{
				k = NEXT[k];
			}
		}
	}
	int find(char* s, char* p)
	{
		int i = 0;
		int j = 0;
		int sLen = strlen(s);
		int pLen = strlen(p);
		while (i < sLen && j < pLen)
		{
			//①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++    
			if (j == -1 || s[i] == p[j])
			{
				i++;
				j++;
			}
			else
			{
				//②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = NEXT[j]    
				//NEXT[j]即为j所对应的NEXT值      
				j = NEXT[j];
			}
		}
		if (j == pLen)
			return i - j;
		else
			return -1;
	}
}kmp;
