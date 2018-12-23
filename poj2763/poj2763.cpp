//lca + BIT求和优化

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define lowbit(x) ((x) & (-x))
const int maxn = 100010;
const int root = 1;
const int l2 = 17;//log2 maxn
int n, q, s;


struct Edge{
	int to, next, w;
} edge[maxn * 2];


int head[maxn + 1];
int cnte;
inline void add_edge(int u, int v, int w)
{
	edge[++cnte].to = v;
	edge[cnte].w = w;
	edge[cnte].next = head[u];
	head[u] = cnte;
}

void build_graph()
{
	int u, v, w;
	for(int i = 0; i < n-1; ++i)
	{
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
}

struct Pos{
	int pb;
	int pe;
} pos[maxn + 1];//记录访问位置
int dn[maxn * 2];//dfs序列，记录求和长度

struct Rmq{
	int v;
	int dist;
} rmq[maxn * 2][l2];//转rmq

int cnt;
void dfs(int u, int p)
{
	if(u == root)
	{
		pos[u].pb = cnt;
		rmq[cnt][0].v = u;
		rmq[cnt++][0].dist = pos[u].pb;
	}
	for(int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		int w = edge[i].w;
		if(v == p)
			continue;
		dn[cnt] = w;//向下访问为正
		pos[v].pb = cnt;//开始访问点
		rmq[cnt][0].v = v;
		rmq[cnt++][0].dist = pos[v].pb;
		dfs(v, u);
		dn[cnt] = -w;//向上访问为负
		pos[v].pe = cnt;
		rmq[cnt][0].v = u;
		rmq[cnt++][0].dist = pos[u].pb;
	}
}

inline int log2floor(int m)
{
	int k = 0;
	for(; 1 << k <= m; ++k);
	return k-1;
}

void rmq_pre()//ST算法
{
	for(int i = 1; (1 << i) <= cnt; ++i)
		for(int j = 0; j + (1 << i) - 1 < cnt; ++j)
		{
			const Rmq &r1 = rmq[j][i-1];
			const Rmq &r2 = rmq[j + (1 << (i-1))][i-1];
			rmq[j][i] = r1.dist < r2.dist ? r1 : r2;
		}
}

int rmq_pro(int u, int v)
{
	if(u > v)
		swap(u, v);
	int k = log2floor(v - u + 1);
	const Rmq &r1 = rmq[u][k];
	const Rmq &r2 = rmq[v - (1 << k) + 1][k];
	return r1.dist < r2.dist ? r1.v : r2.v;
}

int bit[maxn * 2];

inline void initbit()
{
	for(int i = 1; i <= cnt-1; ++i)
		bit[i] = bit[i-1] + dn[i];
	for(int i = cnt-1; i >= 1; --i)
		bit[i] -= bit[i - lowbit(i)];
}

inline void update(int p, int v)
{
	while(p <= cnt-1)
	{
		bit[p] += v;
		p += lowbit(p);
	}
}

inline int getsum(int p)
{
	int res = 0;
	while(p)
	{
		res += bit[p];
		p -= lowbit(p);
	}
	return res;
}

inline int getlen(int u, int v)
{
	int lca = rmq_pro(pos[u].pb, pos[v].pb);
	// printf("lca(%d, %d) = %d\n", u, v, lca);
	return getsum(pos[u].pb) - (getsum(pos[lca].pb) << 1) + getsum(pos[v].pb);
}

inline void change(int u, int v, int w)//w是差值
{
	if(pos[u].pb > pos[v].pb)
		swap(u, v);
	//u->v
	update(pos[v].pb, w);
	update(pos[v].pe, -w);
}

int main()
{
	scanf("%d%d%d", &n, &q, &s);
	build_graph();
	dfs(root, root);
	// printf("cnt = %d\n", cnt);
	initbit();
	rmq_pre();
	int flag;
	while(q--)
	{
		scanf("%d", &flag);

		if(flag == 0)
		{
			int t;
			scanf("%d", &t);
			printf("%d\n", getlen(s, t));
			s = t;
		}
		else
		{
			int i, w;
			scanf("%d%d", &i, &w);
			change(edge[2 * i - 1].to, edge[2 * i].to, w - edge[2 * i].w);
			edge[2 * i].w = w;//记得更新权值！
		}
	}

	return 0;
}