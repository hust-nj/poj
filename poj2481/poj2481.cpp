#include<cstdio>
#include<algorithm>
#include<string.h>
using namespace std;

const int maxN = 100000;
int bit[maxN + 2];

struct Interval {
	int s, e;
	int sum;
	bool operator< (const Interval &x) const
	{
		if (s < x.s)
			return true;
		else if (s == x.s && e > x.e)
			return true;
		else 
			return false;
	}
};

Interval interval[maxN + 1];

inline int lowbit(int x) { return x & -x; }

inline void add(int x, int d)
{
	while (x <= maxN + 1)
	{
		bit[x] += d;
		x += lowbit(x);
	}
}

inline int sum(int x)
{
	int ans = 0;
	while (x)
	{
		ans += bit[x];
		x -= lowbit(x);
	}
	return ans;
}

int table[maxN + 1];

bool cmp(int i, int j)
{
	return interval[i] < interval[j];
}

int main()
{
	int n;
	while (scanf("%d", &n) && n)
	{
		memset(bit, 0, sizeof(bit));
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d%d", &interval[i].s, &interval[i].e);
			table[i] = i;
		}
		sort(table + 1, table + 1 + n, cmp);
		int cnt = 0;
		for (int j = 1; j <= n; ++j)
		{
			int t = table[j];
			int t_last = table[j - 1];
			if (j > 1 && interval[t].s == interval[t_last].s && interval[t].e == interval[t_last].e)
				cnt++;
			else
				cnt = 0;
			interval[t].sum = sum(maxN + 1 - interval[t].e) - cnt;
			add(maxN + 1 - interval[t].e, 1);
		}
		for(int i = 1; i <= n; ++i)
			printf("%d ", interval[i].sum);
		putchar('\n');
	}
	return 0;
}