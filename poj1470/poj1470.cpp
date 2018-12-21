//LCA模板题
//转RMQ O((nlogn)预处理 + O(1)在线询问)

#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxV = 900;
int root;
int n;

struct Edge{
	int to, next;
} edge[maxV];

int head[maxV+1];

int cnte;
inline void add_edge(int u, int v)//u->v
{
	edge[++cnte].to = v;
	edge[cnte].next = head[u];
	head[u] = cnte;
}

struct NodeDis{
	int no, dis;
} nds[2 * maxV][20];

int ndcnt;
int pos[maxV+1];
int dep[maxV+1];
int fa[maxV+1];

void dfs(int u)
{
	nds[++ndcnt][0].no = u;
	nds[ndcnt][0].dis = dep[u];//start visit
	pos[u] = ndcnt;
	for(int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		dep[v] = dep[u] + 1;
		dfs(v);
		nds[++ndcnt][0].no = u;
		nds[ndcnt][0].dis = dep[u];//return visit
	}
}

inline int log2_floor(int m)
{
	int k = 0;
	for(; 1 << k <= m; ++k);
	return k-1;
}

//rmq预处理
void rmq_pre()
{
	for(int i = 1; (1 << i) <= ndcnt; ++i)
		for(int j = 1; j + (1 << i) - 1 <= ndcnt; j++)
		{
			const NodeDis &nd1 = nds[j][i-1];
			const NodeDis &nd2 = nds[j + (1 << (i-1))][i-1];
			nds[j][i] = nd1.dis < nd2.dis ? nd1 : nd2;
		}
}

NodeDis rmq(int u, int v)
{
	if(u > v)
		swap(u, v);
	int len = v - u + 1;
	int t = log2_floor(len);
	const NodeDis &nd1 = nds[u][t];
	const NodeDis &nd2 = nds[v - (1 << t) + 1][t];
	return nd1.dis < nd2.dis ? nd1 : nd2;
}

int ans[maxV+1];
void init()
{
	cnte = 0;
	memset(head, 0, sizeof(head));
	ndcnt = 0;
	memset(ans, 0, sizeof(ans));
	memset(pos, 0, sizeof(pos));
	memset(dep, 0, sizeof(dep));
	memset(fa, 0, sizeof(fa));
}

void build_graph()
{
	for(int i = 0; i < n; ++i)
	{
		int v, num, son;
		scanf("%d : ( %d )", &v, &num);
		// printf("v = %d, num = %d\n", v, num);
		for(int i = 0; i < num; ++i)
		{
			scanf("%d", &son);
			add_edge(v, son);
			fa[son] = v;
		}
	}
	root = 1;
	while(fa[root])
		root = fa[root];//找到root
}

int main()
{
	while(scanf("%d", &n) == 1)
	{
		init();
		build_graph();
		// printf("root = %d\n", root);
		dfs(root);//转rmq
		rmq_pre();
		int num; scanf("%d", &num);
		for(int i = 0; i < num; ++i)
		{
			int u, v;
			scanf(" ( %d %d )", &u, &v);
			NodeDis res = rmq(pos[u], pos[v]);
			ans[res.no]++;
		}
		for(int i = 1; i <= n; ++i)
			if(ans[i])
				printf("%d:%d\n", i, ans[i]);
	}

	return 0;
}