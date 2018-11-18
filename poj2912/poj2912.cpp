#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct Node {
	int prt;
	int rk;
	int w;
};

struct Answer {
	int l;
	int r;
	int op;
};

Node vtx[600];
Answer ans[2100];
vector<int> judge;
int n, m;
int nMax = 0;

void init(int n)
{
	for (int i = 0; i < n; ++i)
	{
		vtx[i].prt = i;
		vtx[i].rk = 0;
		vtx[i].w = 0;
	}
}

int myfind(int i)
{
	if (vtx[i].prt == i)
		return i;
	else
	{
		int p = vtx[i].prt;
		int ld = myfind(p);
		vtx[i].w = (vtx[i].w + vtx[p].w) % 3;
		vtx[i].prt = ld;
		return ld;
	}
}

void myunion(int i, int j, int d)//w[i] - w[j] / i->j: d
{
	int li = myfind(i);
	int lj = myfind(j);
	if (vtx[li].rk > vtx[lj].rk)
	{
		vtx[lj].prt = li;
		vtx[lj].w = (6 - vtx[j].w + vtx[i].w - d) % 3;
	}
	else if (vtx[lj].rk > vtx[li].rk)
	{
		vtx[li].prt = lj;
		vtx[li].w = (3 - vtx[i].w + vtx[j].w + d) % 3;
	}
	else
	{
		vtx[lj].rk++;
		vtx[li].prt = lj;
		vtx[li].w = (3 - vtx[i].w + vtx[j].w + d) % 3;
	}
}

void testjg(int jg)//compute ignoring jg
{
	for (int i = 1; i <= m; ++i)
	{
		int t1 = ans[i].l, t2 = ans[i].r, op = ans[i].op;
		if (t1 == jg || t2 == jg)
			continue;

		if (myfind(t1) == myfind(t2))
		{
			if ((3 + vtx[t1].w - vtx[t2].w) % 3 != op)//conflict
			{
				nMax = max(i, nMax);//确定不是裁判
				return;
			}
		}
		else
		{
			myunion(t1, t2, op);
		}
	}
	judge.push_back(jg);
}


int main()
{
	char op;
	while (scanf("%d%d", &n, &m) == 2)
	{
		for (int i = 1; i <= m; ++i)
		{
			scanf("%d %c %d", &ans[i].l, &op, &ans[i].r);
			switch (op)
			{
			case('='):
				ans[i].op = 0;
				break;
			case('>'):
				ans[i].op = 1;
				break;
			case('<'):
				ans[i].op = 2;
				break;
			default:
				break;
			}
		}
		nMax = 0;
		judge.clear();
		for (int i = 0; i < n; ++i)//assume i is judge
		{
			init(n);
			testjg(i);
		}
		if (judge.size() == 0)
			printf("Impossible\n");
		else if (judge.size() > 1)
			printf("Can not determine\n");
		else
		{
			int k = judge.front();
			printf("Player %d can be determined to be the judge after %d lines\n", k, nMax);
		}
	}
	return 0;
}