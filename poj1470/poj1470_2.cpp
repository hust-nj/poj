//LCA模板题
//倍增法在线求LCA

#include<cstdio>
#include<cstring>

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

int n;
int depth[maxV + 1];
int prt[maxV + 1];
int root;
int anc[maxV + 1][10];
void build_graph()
{
	for(int i = 0; i < n; ++i)
	{
		int v, num, adj;
		scanf("%d : ( %d )", &v, &num);
		while(num--)
		{
			scanf("%d", &adj);
			add_edge(v, adj);
			prt[adj] = v;
		}
	}
	root = 1;
	while(prt[root])
		root = prt[root];
}

void dfs(int u)
{
	for(int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		dfs(v);
		depth[v] = depth[u] + 1;
	}
}

const int N = maxV + 1;
const int M = 
int fa[maxV + 1][10];
void lca_init()
{
	for(int k = 1; k <= M-1; ++k)
		for(int i = 1; i <= n; ++i)
			fa[i][k] = fa[fa[i][k-1]][k-1];
}

int lca(int u, int v)
{
	if(depth[u] < depth[v])
		swap(u, v);

	for(int i = M-1; i >= 0; --i)
		if((dep[u] - dep[v] >> i) & 1)
			u = fa[u][i];

	for(int i = M-1; i >= 0; --i)
		if(fa[u][i] != fa[v][i])

	int dif = depth[u] - depth[v];

}

int main()
{
	int ans[maxV + 1];
	while(scanf("%d", &n) == 1)
	{
		build_graph();
		depth[root] = 0;
		dfs(root);

	}

	int num;
	scanf("%d", &num);
	while(num--)
	{
		int u, v;
		scanf("( %d %d )", &u, &v);
		ans[lca(u, v)]++;
	}
	for(int i = 1; i <= n; ++i)
	{
		if(ans[i] != 0)
			printf("%d:%d\n", i, ans[i]);
	}

	return 0;
}