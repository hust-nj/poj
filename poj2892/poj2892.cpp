#include<stdio.h>
int n;//number of villages

int bitl[50001];
int bitr[50001];//反序数组
int stk[50001];//模拟栈

#define lowbit(x) (x & -x)

inline void add(int x, int delta)
{
	int y = n + 1 - x;
	while (x <= n)
	{
		bitl[x] += delta;
		x += lowbit(x);
	}
	while (y <= n)
	{
		bitr[y] += delta;
		y += lowbit(y);
	}
}

int query(int x)
{
	int left;
	int b = 0, e = x;
	int t;
	int sum = 0;
	while (e)
	{
		t = e - lowbit(e);
		if (bitl[e] == 0)//没有破坏
		{
			e = t;
		}
		else
		{
			b = t;
			break;
		}
	}//限定范围至(b, e] ----- b = e - lowbit[e]
	if (!e) 
	{
		left = 0;
	}
	else
	{
		t = lowbit(e);
		while (t != 1)
		{
			t >>= 1;
			//如果有破坏(b+t, e]
			if (bitl[e] != bitl[b + t] + sum)
			{
				b += t;
				sum += bitl[b];
			}
		}
		left = b + 1;
	}
	if (left == x)return 0;
	/* copy the code above to do the same thing(using bitr) */
	int right;
	b = 0, e = n + 1 - x;
	sum = 0;
	while (e)
	{
		t = e - lowbit(e);
		if (bitr[e] == 0)//没有破坏
		{
			e = t;
		}
		else
		{
			b = t;
			break;
		}
	}//限定范围至(b, e] ----- b = e - lowbit[e]
	if (!e)
	{
		right = 0;
	}
	else
	{
		t = lowbit(e);
		while (t != 1)
		{
			t >>= 1;
			//如果有破坏(b+t, e]
			if (bitr[e] != bitr[b + t] + sum)
			{
				b += t;
				sum += bitr[b];
			}
		}
		right = b + 1;
	}

	return n - left - right;
}


int main()
{
	int m;
	int x;
	char op;
	int i = 0;
	scanf("%d%d", &n, &m);
	while (m--)
	{
		getchar();
		op = getchar();
		if (op != 'R')scanf("%d", &x);
		switch (op)
		{
		case 'D':
			add(stk[i++] = x, 1);
			break;
		case 'R':
			add(stk[--i], -1);
			break;
		case 'Q':
			printf("%d\n", query(x));
		}
	}
	return 0;
}