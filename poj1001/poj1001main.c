#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 6

int deal(char *);
char* dealresult(char *, int);

int main(void)
{
	char a[N+1];
	int n;

	while (scanf("%s%d", a, &n) == 2)
	{
		int np;//小数位数
		int *iresult;
		int i, j;
		int k;
		int *before;
		int size = N;
		char *sresult;
		char *output;

		np = deal(a);

		iresult = (int *)malloc(sizeof(int)*N*n);//结果最大位数为n*N
		sresult = (char*)malloc(sizeof(char)*N*n + 1);
		before = (int *)malloc(sizeof(int)*N);//第一次长度为N
		memset(iresult, 0, sizeof(int)*N*n);
		for (i = 0; i < N; i++)
			before[i] = a[i] - '0';
		if (n == 1)
			for (i = 0; i < N; i++)
				iresult[i] = a[i] - '0';

		for (k = 0; k < n - 1; k++)
		{
			for (i = 0; i < size; i++)
				for (j = 0; j < N; j++)
					iresult[i + j + 1] += before[i] * (a[j] - '0');
			/*下面开始进行进位*/
			for (i = size + N - 1; i > 0; i--)
			{
				iresult[i - 1] += iresult[i] / 10;
				iresult[i] = iresult[i] % 10;
			}
			/*传值给before*/
			size += N;
			free(before);
			if (k != n - 2)
			{
				before = (int *)malloc(sizeof(int)*size);
				for (int i = 0; i < size; i++)
					before[i] = iresult[i];
				memset(iresult, 0, sizeof(int)*N*n);
			}
		}
		for (k = 0; k < size; k++)
		{
			sresult[k] = iresult[k] + '0';
		}
		sresult[size] = '\0';
		/*整数乘法已完成*/
		np *= n;
		output = dealresult(sresult, np);
		printf("%s\n", output);
		free(sresult);
		free(iresult);
	}
	return 0;
}

/*处理输入字符串函数*/
int deal(char* s)
{
	int dif = 0;//小数位数
	char *p = strchr(s, '.');
	if (p != NULL)
	{
		dif = N - (p - s + 1);
		p--;
		while (p >= s)
		{
			*(p + 1) = *p;
			p--;
		}
		*s = '0';
	}
	return dif;
}

/*处理最终结果格式*/
char* dealresult(char *result,int dig)
{
	int length = strlen(result);
	int count = 0;
	char *p;
	if (*result == '0')
	{
		char *mark = result;
		while (*result == '0' && count < length - dig)
		{
			result++;
			count++;
		}
		for (int i = 0; i < strlen(result) - dig ; i++)
		{
			result[i-1] = result[i];
		}
		result--;
		mark[length - dig - 1] = '.';

		p = strchr(result,'\0');
		p--;
		while (*p == '0')
		{
			p--;
		}
		if (*p == '.')
			*p = '\0';
		else
			*(p + 1) = '\0';
	}
	return result;
}
