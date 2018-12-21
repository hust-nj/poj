//the least number of cashiers


#include<cstdio>
#include<cstring>
#include<queue>
// #include<unistd.h>
using namespace std;

int r[24];
int n;
int t[24];

const int Vnum = 25;
int s[Vnum];
//t[i-7] + t[i-6] + ... + t[i] >= r[i]
//let s[i] = t[0] + ... + t[i]
//即转化为
//s[i] - s[i-8] >= r[i] for i in [8, 22]
//s[23] - s[15] >= r[23]
//s[23] - s[i+16] + s[i] >= r[i] for i in [0, 6]
//s[7] >= r[7]
//0 <= s[i] - s[i-1] <= t[i] for i in [1, 22]
//0 <= s[23] - s[22] <= t[23]
//0 <= s[0] <= t[0]
//引入新的点P，设为source点 s[0] - P <= t[0], P - s[0] <= 0
const int P = 24;

struct Edge{
	int to, w, next;
}edge[30 * 4];

int head[Vnum];

int cnte = 0;
void add_edge(int u, int v, int w)//u->v:W
{
	edge[++cnte].to = v;
	edge[cnte].w = w;
	edge[cnte].next = head[u];
	head[u] = cnte;
}

void build_graph()
{
	memset(head, 0, sizeof(head));
	cnte = 0;//清空图
	int i;
	for(i = 8; i <= 22; ++i)
		add_edge(i, i-8, -r[i]);
	add_edge(P, 15, s[23] - r[23]);

	for(i = 0; i<= 6; ++i)
		add_edge(i, i+16, s[23] - r[i]);
	add_edge(7, P, -r[7]);

	for(i = 1; i <= 22; ++i)
	{
		add_edge(i-1, i, t[i]);
		add_edge(i, i-1, 0);
	}
	add_edge(P, 22, s[23]);
	add_edge(22, P, t[23] - s[23]);
	add_edge(P, 0, t[0]);
	add_edge(0, P, 0);

}


int spfa()
{

	bool inq[Vnum];
	int cnt[Vnum];
	memset(s, 0x3f, sizeof(s));
	memset(cnt, 0, sizeof(cnt));
	memset(inq, 0, sizeof(inq));

	queue<int> q;
	s[P] = 0;
	q.push(P);
	inq[P] = true;
	cnt[P] = 1;

	while(!q.empty())
	{
		int cur = q.front();
		if(cnt[cur] >= Vnum) return 1;//存在负环
		q.pop();
		inq[cur] = false;

		for(int i = head[cur]; i; i = edge[i].next)
		{
			int v = edge[i].to;
			int w = edge[i].w;
			if(s[v] > s[cur] + w)
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
	int num;
	scanf("%d", &num);
	int tmp;
	while(num--)
	{
		for(int i = 0; i < 24; ++i)
			scanf("%d", &r[i]);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", &tmp);
			t[tmp]++;
		}
		int l = 0, r = n;
		while(l <= r)//二分逼近
		{
			tmp = s[23] = (l + r) / 2;
			build_graph();
			// for(int i = 0; i < 25; ++i)
			// {
			// 	printf("vetex %d\n", i);
			// 	for(int adj = head[i]; adj; adj = edge[adj].next)
			// 	{
			// 		printf("%d -> %d\n", edge[adj].to, edge[adj].w);
			// 	}
			// 	printf("\n\n");
			// }
			if(spfa())//无解
				l = tmp + 1;
			else
			{
				r = tmp;
				if(l == r) break;
			}
			// printf("l = %d\n", l);
			// printf("r = %d\n", r);
			// printf("s[23] = %d\n", s[23]);
			// printf("exec once\n");
			// while(1)
			// 	sleep(1);
		}

		if(l > r)
			printf("No Solution\n");
		else
			printf("%d\n", l);
	}
	return 0;
}