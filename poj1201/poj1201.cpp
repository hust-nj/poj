#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

//差分约束关系
//s[0] = 0, s[i] - s[i-1] = I[i-1]
//0 <= s[i] - s[i-1] <= 1
//s[bi + 1] - s[ai] >= ci
//最小化s[Vnum-1] - s[0]
//以s[0]为源点，b-a >= c，求解最大路

int n;

const int Vnum = 50002;

int s[Vnum];
int head[Vnum];

struct Edge{
	int to, w, next;
}edge[50001 * 3];

int cnte = 0;
inline void add_edge(int u, int v, int w)//u->v:W
{
	edge[++cnte].to = v;
	edge[cnte].w = w;
	edge[cnte].next = head[u];
	head[u] = cnte;
}

void build_graph()
{
	for(int i = 1; i < Vnum; ++i)
	{
		add_edge(i-1, i, 0);
		add_edge(i, i-1, -1);
	}

	for(int i = 0; i < n; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add_edge(a, b+1, c);
	}
}

bool inq[Vnum];
int cnt[Vnum];
const int P = 0;
bool spfa()
{
	memset(s, -1, sizeof(s));

	queue<int> q;
	s[P] = 0;
	q.push(P);
	inq[P] = true;
	cnt[P] = 1;

	while(!q.empty())
	{
		int cur = q.front();
		if(cnt[cur] >= Vnum) return 1;//存在正权环
		q.pop();
		inq[cur] = false;

		for(int i = head[cur]; i; i = edge[i].next)
		{
			int v = edge[i].to;
			int w = edge[i].w;
			if(s[v] < s[cur] + w)
			{
				s[v] = s[cur] + w;
				if(!inq[v])
				{
					inq[v] = true;
					cnt[v]++;
					q.push(v);
				}
			}
		}
	}

	return 0;
}

int main()
{
	scanf("%d", &n);
	build_graph();
	spfa();
	printf("%d\n", s[Vnum-1]);
	return 0;
}