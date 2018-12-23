//LCA模板题
//targan算法离线求LCA
//认为输入是棵树
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxV = 40000;
const int maxQ = 10000;
int n;
int m;
int k;

struct Edge{
	int to, next, w;
} edge[maxV * 2 - 1];

int uf[maxV + 1];

struct Query
{
	int to, next;
} qr[maxQ * 2 + 1];

int head[maxV + 1];
int ans[maxQ];
bool visit[maxV + 1];


int cnte;
inline void add_edge(int u, int v, int w)
{
	edge[++cnte] = (Edge){v, head[u], w};
	head[u] = cnte;
}

int cntq;
int headq[maxV + 1];
inline void add_query(int u, int v)
{
	qr[++cntq] = (Query){v, headq[u]};
	headq[u] = cntq;
}

void build_graph()
{
	for(int i = 0; i < m; ++i)
	{
		int a, b, w;
		scanf("%d%d%d %*c", &a, &b, &w);
		// printf("%d - %d - %d\n", a, b, w);
		add_edge(a, b, w);
		add_edge(b, a, w);
	}
}

void build_query()
{
	scanf("%d", &k);
	for(int i = 0; i < k; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add_query(u, v);
		add_query(v, u);
	}
}

int myfind(int v)
{
	if(v == uf[v])
		return v;
	uf[v] = myfind(uf[v]);
	return uf[v];
}

int dist[maxV + 1];
void dfs(int u)
{
	for(int i = headq[u]; i; i = qr[i].next)
	{//处理询问
		int q = qr[i].to;
		if(visit[q])
		{
			int lca = myfind(q);
			// printf("lca(%d, %d) = %d\n", u, q, lca);
			ans[(i-1)/2] = dist[u] + dist[q] - 2 * dist[lca];
		}
	}

	visit[u] = true;
	// printf("dfs %d\n", u);
	for(int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if(!visit[v])
		{
			dist[v] = dist[u] + edge[i].w;
			// printf("dist[%d] = %d\n", v, dist[v]);
			dfs(v);
			uf[v] = u;
		}
	}

	// printf("dfs exit %d\n", u);
	
}


void init()
{
	// cnte = 0;
	// dist[1] = 0;
	// memset(ans, 0, sizeof(ans));
	// memset(visit, 0, sizeof(visit));
	for(int i = 1; i <= n; ++i)
	{
		uf[i] = i;
	}
}

int main()
{
	scanf("%d%d", &n, &m);

	init();
	build_graph();
	build_query();

	dfs(1);

	for(int i = 0; i < k; i++)
		printf("%d\n", ans[i]);
	return 0;
}