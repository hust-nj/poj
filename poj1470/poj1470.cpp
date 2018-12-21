//LCA模板题
//转RMQ O((nlogn)预处理 + O(1)在线询问)

#include<cstdio>
#include<cstring>

using namespace std;

const int maxV = ;
const int maxE = maxV + 1;

struct Edge{
	int to, next;
} edge[2 * maxE + 1];

int head[maxV];

int cnte;
void add_edge(int u, int v)
{
	edge[++cnte].to = v;
	edge[cnte].next = head[u];
	head[u] = cnte;

	edge[++cnte].to = u;
	edge[cnte].next = head[v];
	head[v] = cnte;
}

struct nodeDis{
	int no, dis;
} nds[maxE]	


int main()
{

}