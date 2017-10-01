#include<stdio.h>
void cal(long long *t, long long *s, long long *gcd, long long z, long long L);
int main(void)
{
	long long x, y, m, n, L;
	scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L);
	long long z = (n - m) % L;
	z = z >= 0 ? z : (z + L);
	long long t, gcd, s;
	cal(&t, &s, &gcd, z, L);
	if ((x - y) % gcd)
		printf("Impossible");
	else
	{
		long long num = L / gcd;
		t = (t * (x - y)/gcd)%num;
		t = t >= 0 ? t : t + num;
		printf("%d\n", t);
	}
	return 0;
}
/*用扩展欧几里得算法求解同余方程 zt+sL=gcd(z,L) 与 gcd(z,L) */
void cal(long long *t, long long *s,long long *gcd, long long z, long long L)
{//L>z;
	if (z != 0)
	{
		long long div = L / z;
		cal(t, s, gcd, L%z, z);
		long long temp = *s;
		*s = *t;
		*t = temp - div * *t;
	}
	else
	{
		*gcd = L;
		*t = 0;
		*s = 1;
	}
}
