#include<stdio.h>
int inverse(int s, int m,int *a,int *b)//求s关于m的逆元//as+bm=1
{
	if (m == 0)
	{
		*a = 1;
		*b = 0;
		return s;
	}
	else
	{
		int gcd = inverse(m, s%m, a, b);
		int temp = *a;
		*a = *b;
		*b = temp - s / m **b;
		return gcd;
	}
}
int main(void)
{
	int p, e, i, d;
	int count = 0;
	while (scanf("%d%d%d%d", &p, &e, &i, &d) && !(p == -1 && e == -1 && i == -1 && d == -1))
	{
		count++;
		int a23, a28, a33, b23, b28, b33;
		inverse(23 * 28, 33, &a33, &b33);
		inverse(23 * 33, 28, &a28, &b28);
		inverse(28 * 33, 23, &a23, &b23);
		int k = (a23 * 28 * 33 * p + a28 * 23 * 33 * e + a33 * 23 * 28 * i) % (23 * 28 * 33);
		while (k <= d)
			k += 23 * 28 * 33;
		printf("Case %d: the next triple peak occurs in %d days.\n", count, k - d);
	}
	return 0;
}
