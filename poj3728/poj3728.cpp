#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50000;

struct Edge{
	int to, next;
} edge[2 * maxn - 1];

struct Query
{
	int to, next;
	int id, dr;
} query[2 * maxn + 1];

struct Res{
	int next;
	int u, v, id;
} res[maxn + 1];//from u to v

int n, q;
int fa[maxn + 1];
int head[maxn + 1];
int mn[maxn + 1];
int mx[maxn + 1];
int up[maxn + 1];//向上寻路的最大值
int down[maxn + 1];//向下寻路的最大值
int ans[maxn + 1];
int cnte;
inline void addedge(int u, int v)
{
	edge[++cnte].to = v;
	edge[cnte].next = head[u];
	head[u] = cnte;
}

int headq[maxn + 1];
int cntq;
inline void addq(int u, int v, int dr)
{
	query[++cntq].to = v;
	query[cntq].next = headq[u];
	query[cntq].id = cntq;
	query[cntq].dr = dr;
	headq[u] = cntq;
}

int headr[maxn + 1];
int cntr;
inline void addr(int lca, int u, int v, int id)
{
	res[++cntr].u = u;
	res[cntr].v = v;
	res[cntr].id = id;
	res[cntr].next = headr[lca];
	headr[lca] = cntr;
}

int find(int x)
{
	if(x == fa[x])
		return x;
	int y = fa[x];
	fa[x] = find(fa[x]);

	//额外增加的压缩合并操作
	up[x] = max(mx[y] - mn[x], max(up[x], up[y]));
	down[x] = max(mx[x] - mn[y], max(down[x], down[y]));
	mn[x] = min(mn[x], mn[y]);
	mx[x] = max(mx[x], mx[y]);

	return fa[x];
}

int visit[maxn + 1];
void dfs(int u)
{
	//处理询问
	visit[u] = 1;
	for(int i = headq[u]; i; i = query[i].next)
	{
		int v = query[i].to;
		if(visit[v])
		{
			int lca = find(v);
			// printf("%d: lca(%d, %d) = %d\n", i, lca, u, v);
			if(query[i].dr)
				addr(lca, u, v, (query[i].id + 1) / 2);
			else
				addr(lca, v, u, (query[i].id + 1) / 2);
		}
	}

	for(int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if(!visit[v])
		{
			dfs(v);
			fa[v] = u;
		}
	}

	for(int i = headr[u]; i; i = res[i].next)
	{
		int v1 = res[i].u, v2 = res[i].v; 
		find(v1), find(v2);
		// printf("v1 = %d, v2 = %d\n", v1, v2);
		// if(v1 == 1)
		// 	printf("id = %d, down[%d] = %d\n", res[i].id, v2, down[v2]);
		ans[res[i].id] = max(mx[v2] - mn[v1], max(up[v1], down[v2]));
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int w;
		scanf("%d", &w);
		mx[i] = mn[i] = w;
	}
	for(int i = 1; i <= n; ++i)
		fa[i] = i;//初始化并查集
	int u, v;
	for(int i = 0; i < n-1; ++i)
	{
		scanf("%d%d", &u, &v);
		addedge(u, v);
		addedge(v, u);
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i)
	{
		scanf("%d%d", &u, &v);
		addq(u, v, 1);
		addq(v, u, 0);
	}

	dfs(1);
	for(int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);

	return 0;
}