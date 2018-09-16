#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;

stack<int> stk;

void dfs(int u, int prt, const vector<vector<int> > &graph, vector<int> &dfn, vector<int> &low, int &globr, vector<int> &belong, int &globn)
{
	dfn[u] = low[u] = ++globr;
	stk.push(u);
	bool flag = true;//notice: for multi-edge!!!
	for (vector<int>::const_iterator p = graph[u].begin(); p != graph[u].end(); ++p)
	{
		if (flag && *p == prt) // visit parent -- return
		{
			flag = false;
			continue;
		}
		if (!dfn[*p])//not visit
		{
			dfs(*p, u, graph, dfn, low, globr, belong, globn);
			low[u] = min(low[u], low[*p]);
		}
		else
			low[u] = min(low[u], dfn[*p]);
	}

	if (low[u] == dfn[u]) // u, prt is the cut-edge
	{
		globn++;
		int v;
		do
		{
			v = stk.top();
			stk.pop();
			belong[v] = globn;
		} while (u != v); // pop include u
	}
}

int main()
{
	int F, R;
	cin >> F >> R;
	int globr = 0, globn = 0;
	vector<int> dfn(F + 1);
	vector<int> low(F + 1);
	vector<int> belong(F + 1);
	vector<vector<int> > graph(F + 1);
	for (int i = 0; i < R; ++i)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs(1, 1, graph, dfn, low, globr, belong, globn);
	//contract the graph
	vector<int> degree(belong[1] + 1);
	for (int u = 1; u <= F; ++u)
		for (int v = 0; v < graph[u].size(); ++v)
			if (belong[u] != belong[graph[u][v]])
				degree[belong[u]] += 1;
	int cnt = 0;
	for (vector<int>::iterator p = degree.begin() + 1; p != degree.end(); ++p)
	{
		if (*p == 1)
			cnt++;
	}
	cout << (cnt + 1) / 2 << endl;
	return 0;
}