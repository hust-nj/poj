//s[i] - s[i-1] >= 0 for i in [2, n]
//s[x] - s[y] <= l for input x > y
//s[x] - s[y] >= d for input x > y

#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int maxE = 20001;
const int maxV = 1001;
int n, ml, md;

struct Edge{
	int to, w, next;
}edge[maxE];

int head[maxE];

int cnte;
void add_edge(int u, int v, int w)//u->v:w
{
	edge[++cnte].to = v;
	edge[cnte].w = w;
	edge[cnte].next = head[u];
	head[u] = cnte;
}

void build_graph()
{
	int a, b, d;
	for(int i = 2; i <= n; ++i)
		add_edge(i, i-1, 0);
	for(int i = 0; i < ml; ++i)
	{
		scanf("%d%d%d", &a, &b, &d);
		add_edge(a, b, d);
	}
	for(int i = 0; i < md; ++i)
	{
		scanf("%d%d%d", &a, &b, &d);
		add_edge(b, a, -d);
	}
}

bool inq[maxV];
int dist[maxV];
int cnt[maxV];
bool visit[maxV];
int spfa(int p)
{
	memset(dist, 0x3f, sizeof(dist));
	memset(cnt, 0, sizeof(cnt));
	memset(inq, 0, sizeof(inq));
	queue<int> q;
	q.push(p);
	visit[p] = true;
	inq[p] = true;
	dist[p] = 0;
	cnt[p] = n-2;
	while(!q.empty())
	{
		int u = q.front();
		if(++cnt[u] >= n)
			return 1;
		q.pop();
		inq[u] = false;

		for(int i = head[u]; i; i = edge[i].next)
		{
			int v = edge[i].to;
			int w = edge[i].w;
			if(dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				if(!inq[v])
				{
					q.push(v);
					inq[v] = true;
					visit[v] = true;
				}
			}
		}
	}
	return 0;
}

int main()
{
	scanf("%d%d%d", &n, &ml, &md);
	build_graph();
	if(spfa(1))
		printf("-1\n");
	else
	{
		if(visit[n])
			printf("%d\n", dist[n]);
		else
		{
			for(int i = 2; i <= n; ++i)
			{
				if(!visit[i])
				{
					if(spfa(i))
					{
						printf("-1\n");
						return 0;
					}
				}
			}
			printf("-2\n");
			return 0;
		}
	}
	return 0;
}