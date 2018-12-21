#include<cstdio>
#include<cstring>
#include<queue>//get priority_queue
using namespace std;

const int maxn = 30000;
const int maxm = 150000;

//链式前向星-邻接链表
struct Edge{
	int to;
	int w;
	int next;
}edge[maxm+1];

int head[maxn+1];

int cnt = 1;
void addedge(int a, int b, int c)//a->b
{
	edge[cnt].to = b;
	edge[cnt].w = c;
	edge[cnt].next = head[a];
	head[a] = cnt++;
};

struct Node{
	int dist;
	int v;
	Node(){}
	Node(int dist, int v):dist(dist), v(v){}
	bool operator< (const Node &nd) const {return dist > nd.dist;}
};

int n, m;
int dist[maxn + 1];
void dijkstra()
{
	priority_queue<Node> pq;
	memset(dist, -1, sizeof(dist));
	pq.push(Node(0, 1));//init
	int v, w;
	Node cur;
	while(!pq.empty())
	{
		cur = pq.top();
		pq.pop();

		if(dist[cur.v] != -1)
			continue;
		else
			dist[cur.v] = cur.dist;
		if(cur.v == n)
			break;
        for(int i = head[cur.v]; i != 0; i = edge[i].next)
        {
            v = edge[i].to;
            w = edge[i].w;
            if(dist[v] == -1)
                pq.push(Node(dist[cur.v] + w, v));
        }
	}
}

int main()
{
	int a, b, c;
	scanf("%d%d", &n, &m);
	
	while(m--)
	{
		scanf("%d%d%d", &a, &b, &c);//b - a <= c
		addedge(a, b, c);
	}
	dijkstra();
	printf("%d\n", dist[n]);
	return 0;
}