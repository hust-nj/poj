//#pragma warning(disable: 4996)
//
#include<cstdio>
#include<algorithm>

using namespace std;

const int maxN = 600;

struct Node {
	int prt;
	int rk;
	int w;
	int zero_num; //%2 == 0的数量
	int one_num; //%2 == 1的数量
};

Node vtx[maxN + 1];

void init(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		vtx[i].prt = i;
		vtx[i].rk = vtx[i].w = 0;
		vtx[i].zero_num = 1;
		vtx[i].one_num = 0;
	}
}

int myfind(int i)
{
	if (vtx[i].prt == i)
		return i;
	int p = vtx[i].prt;
	int ld = myfind(p);
	vtx[i].w ^= vtx[p].w;
	vtx[i].prt = ld;
	return ld;
}

void myunion(int i, int j, int no)
{
	int t1 = myfind(i);
	int t2 = myfind(j);
	if (vtx[t1].rk < vtx[t2].rk)
	{
		vtx[t1].prt = t2;
		vtx[t1].w = vtx[i].w ^ vtx[j].w ^ no;
		if (vtx[t1].w)
		{
			vtx[t2].one_num += vtx[t1].zero_num;
			vtx[t2].zero_num += vtx[t1].one_num;
		}
		else
		{
			vtx[t2].one_num += vtx[t1].one_num;
			vtx[t2].zero_num += vtx[t1].zero_num;
		}
	}
	else if (vtx[j].rk < vtx[i].rk)
	{
		vtx[t2].prt = t1;
		vtx[t2].w = vtx[i].w ^ vtx[j].w ^ no;
		if (vtx[t2].w)
		{
			vtx[t1].one_num += vtx[t2].zero_num;
			vtx[t1].zero_num += vtx[t2].one_num;
		}
		else
		{
			vtx[t1].one_num += vtx[t2].one_num;
			vtx[t1].zero_num += vtx[t2].zero_num;
		}
	}
	else
	{
		vtx[t2].prt = t1;
		vtx[t2].w = vtx[i].w ^ vtx[j].w ^ no;
		vtx[t1].rk++;
		if (vtx[t2].w)
		{
			vtx[t1].one_num += vtx[t2].zero_num;
			vtx[t1].zero_num += vtx[t2].one_num;
		}
		else
		{
			vtx[t1].one_num += vtx[t2].one_num;
			vtx[t1].zero_num += vtx[t2].zero_num;
		}
	}
}


int main()
{
    //freopen("in.txt", "r", stdin);
	int n, p1, p2;
	while (scanf("%d%d%d", &n, &p1, &p2) && (n || p1 || p2))
	{
		init(p1 + p2);
		int x, y;
		char str[4];
		while (n--)
		{
			scanf("%d%d%s", &x, &y, str);
			if (myfind(x) != myfind(y))
				myunion(x, y, *str == 'n');
		}
		if (p1 == p2)
		{
			printf("no\n");
			continue;
		}

		int idx[maxN + 1];
		int idx_sz = 0;//idx数组实际用的大小
		for (int i = 1; i <= p1 + p2; ++i)
		{
			if (vtx[i].prt == i)
				idx[idx_sz++] = i;
		}
		/* 类似01背包问题求解，idx_sz为商品数， 和为p1 */
		int dp[maxN + 1] = { 1 };//存方法数
		int backpoint[maxN+1][maxN + 1];//记录dp返回点
		for (int i = 0; i < idx_sz; ++i)
		{
			int t1 = vtx[idx[i]].one_num;
			int t2 = vtx[idx[i]].zero_num;
			for (int j = p1; j >= 0; --j)
			{
				int x = 0, y = 0;
				if (j >= t1)x = dp[j - t1];
				if (j >= t2)y = dp[j - t2];
				dp[j] = x + y;
				backpoint[i][j] = x;//非零表示选择1这条路
			}
		}
		int choose[maxN + 1];
		if (dp[p1] == 1)
		{
			int w = p1;
			for (int i = idx_sz - 1; i >= 0; w -= backpoint[i][w] ? vtx[idx[i]].one_num : vtx[idx[i]].zero_num, --i)
				choose[idx[i]] = backpoint[i][w];
			for (int i = 1; i <= p1 + p2; ++i)
			{
			    myfind(i);
				if (choose[vtx[i].prt] == vtx[i].w)
					printf("%d\n", i);
			}
			printf("end\n");
		}
		else
		{
			printf("no\n");
		}
	}
	return 0;
}
