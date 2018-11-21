#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;

#define maxN 20001
#define lowbit(x) (x & -x)
struct Cow {
	int vol;
	int x;
	bool operator<(const Cow &c)const { return vol < c.vol; }
};

Cow cow[maxN];
long long num[maxN];
long long numx[maxN];
int n;

long long sum(int pos, long long (&v)[maxN])
{
	long long ans = 0;
	while (pos > 0)
	{
		ans += v[pos];
		pos -= lowbit(pos);
	}
	return ans;
}

void add(int pos, int delta, long long(&v)[maxN])
{
	while (pos < maxN)
	{
		v[pos] += delta;
		pos += lowbit(pos);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d%d", &cow[i].vol, &cow[i].x);
	}
	long long ans = 0;
	sort(cow + 1, cow + 1 + n);
	//只需计算和前面牛的x坐标差的绝对值的和
	for (int i = 1; i <= n; ++i)
	{
		long long nm = sum(cow[i].x, num);//分布化降低复杂度（反离散化）
		long long nmx = sum(cow[i].x, numx);
		//ans += (sum(maxN - 1, numx) - nmx - (i - 1 - nm) * cow[i].x + cow[i].x * nm - nmx) * cow[i].vol;
		ans += (sum(maxN - 1, numx) - 2 * nmx + cow[i].x * (nm * 2 - i + 1)) * cow[i].vol;
		add(cow[i].x, 1, num);
		add(cow[i].x, cow[i].x, numx);
	}
	printf("%lld\n", ans);
	return 0;
}