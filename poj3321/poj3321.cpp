#include<cstdio>
#include<vector>
using namespace std;

const int maxN = 100000 + 1;

struct Edge {
	int to, next;
}edge[2 * maxN];
int head[maxN];

pair<int, int> mapinterval[maxN];//闭区间
int n;
int nv[maxN];
int bit[maxN];//树状数组

void initgraph()
{
	int x, y;
	int cnt = 1;
	for (int i = 1; i <= n - 1; ++i)
	{
		scanf("%d%d", &x, &y);
		edge[cnt].to = y;
		edge[cnt].next = head[x];
		head[x] = cnt++;
		edge[cnt].to = x;
		edge[cnt].next = head[y];
		head[y] = cnt++;
	}
}

int r = 1;
void dfs(int v, int fa)
{
	nv[r] = 1;
	mapinterval[v].first = r;
	for (int i = head[v]; i; i = edge[i].next)
	{
		if (edge[i].to == fa)
			continue;
		++r;
		dfs(edge[i].to, v);
	}
	mapinterval[v].second = r;
}

inline int lowbit(int x)
{
	return x & -x;
}

inline void add(int i, int delta)
{
	for (int j = i; j <= n; j += lowbit(j))
		bit[j] += delta;
}

inline int sum(int k)
{
	int ans = 0;
	for (int i = k; i > 0; i -= lowbit(i))
		ans += bit[i];
	return ans;
}

inline void build()
{
	for (int i = 1; i <= n; ++i)
		add(i, 1);
}

int main()
{
	scanf("%d", &n);
	initgraph();
	dfs(1, 1);
	build();//建立树状数组
	int m;
	scanf("%d", &m);
	char op;
	int t;
	while (m--)
	{
		scanf(" %c%d", &op, &t);
		if (op == 'Q')
			printf("%d\n", sum(mapinterval[t].second) - sum(mapinterval[t].first - 1));
		else
		{
			add(mapinterval[t].first, nv[mapinterval[t].first] ? -1 : 1);
			nv[mapinterval[t].first] = !nv[mapinterval[t].first];
		}
	}
	return 0;
}