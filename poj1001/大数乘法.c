#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* multiply(char *a, char*b)
{
	const int length = strlen(a) + strlen(b);
	int *result;
	int i, j;
	int temp = 0;//进位值
	result = (int *)malloc((length)*sizeof(int));//位数最多为a与b位数和
	char *sresult = (char *)malloc((length + 1) * sizeof(char));//转换成字符串存储
	memset(result, 0, sizeof(int)*length);
	for (i = 0; i < strlen(a); i++)
		for (j = 0; j < strlen(b); j++)
			result[i + j + 1] += (a[i]-'0') * (b[j]-'0');
	/*完成乘法，然后进位*/
	for (i = length - 1; i >= 1; i--)
	{
		result[i] += temp;
		temp = result[i] / 10;
		result[i] %= 10;
	}
	result[0] = temp;
	if (temp == 0)
	{
		sresult++;
		result++;
		sresult[length-1] = '\0';
	}
	else
	{
		sresult[length] = '\0';
	}
	for (i = 0; sresult[i] != '\0'; i++)
		sresult[i] = result[i] + '0';
	return sresult;
}

int main(void)
{
	char a[100], b[100];
	char *p;
	scanf("%s%s", a, b);
	p = multiply(a, b);
	printf("%s\n", p);
	return 0;
}
