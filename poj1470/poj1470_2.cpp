//LCA模板题
//倍增法在线求LCA

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxV = 900;
const int maxE = maxV - 1;

struct Edge{
	int to, next;
} edge[maxE + 1];

int head[maxV+1];

int cnte;
inline void add_edge(int u, int v)//u->v
{
	edge[++cnte].to = v;
	edge[cnte].next = head[u];
	head[u] = cnte;
}

const int N = maxV + 1;
const int M = 10;
int fa[N][M];
int n;
int depth[maxV + 1];
int root;
void build_graph()
{
	cnte = 0;
	memset(head, 0, sizeof(head));
	memset(fa, 0, sizeof(fa));
	
	for(int i = 0; i < n; ++i)
	{
		int v, num, adj;
		scanf("%d : ( %d )", &v, &num);
		for(int i = 0; i < num; ++i)
		{
			scanf("%d", &adj);
			add_edge(v, adj);
			fa[adj][0] = v;
		}
	}
	root = 1;
	while(fa[root][0])
		root = fa[root][0];//找到root
}

void dfs(int u)
{
	for(int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		depth[v] = depth[u] + 1;
		dfs(v);
	}
}

void lca_init()
{
	for(int k = 1; k <= M-1; ++k)
		for(int i = 1; i <= n; ++i)
			fa[i][k] = fa[fa[i][k-1]][k-1];
}

int lca(int u, int v)
{
	if(depth[u] < depth[v])
		swap(u, v);//depth[u] >= depth[v]

	for(int i = M-1; i >= 0; --i)
		if(((depth[u] - depth[v]) >> i) & 1)
			u = fa[u][i];//将u提高到和v相同的高度

	if(u == v)
		return u;


	for(int i = M-1; i >= 0; --i)
		if(fa[u][i] != fa[v][i])
		{
			u = fa[u][i];
			v = fa[v][i];//同时上升
		}

	return fa[u][0];
}

int ans[maxV + 1];
int main()
{
	// freopen("test.txt", "r", stdin);
	while(scanf("%d", &n) == 1)
	{
		memset(ans, 0, sizeof(ans));
		build_graph();
		depth[root] = 0;
		dfs(root);//得到深度
		lca_init();
		int num;
		scanf("%d", &num);
		for(int i = 0; i < num; ++i)
		{
			int u, v;
			scanf(" ( %d %d )", &u, &v);
			ans[lca(u, v)]++;
		}
		for(int i = 1; i <= n; ++i)
		{
			if(ans[i] != 0)
				printf("%d:%d\n", i, ans[i]);
		}
	}

	return 0;
}