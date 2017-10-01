#include<stdio.h>
int judge(double);
int main(void)
{
	double a;
	scanf("%lf", &a);
	while (a != 0)
	{
		printf("%d card(s)\n", judge(a));
		scanf("%lf", &a);
	}
}
int judge(double x)
{
	int n = 1;
	double sum = 0;
	do {
		sum += 1.0 / (n+1);
		n++;
	} while (sum < x);
	return n - 1;
}
