#include<cstdio>
#include<map>
#include<utility>

using namespace std;

struct vl {
	int prt;
	int rk;
	int w;
	vl() {}//use by map::operator[]
	vl(int prt, int rk, int w) :prt(prt), rk(rk), w(w) {}
};

map<int, vl> mp;//离散化

int myfind(int i)
{
	if (mp[i].prt == i)
		return i;
	else
	{
		int tmp = mp[i].prt;
		int ld = mp[i].prt = myfind(tmp);
		mp[i].w ^= mp[tmp].w;
		return ld;
	}
}

void myunion(int i, int j, int odd)
{
	int t1 = myfind(i);
	int t2 = myfind(j);
	if (mp[t1].rk > mp[t2].rk)
	{
		mp[t2].prt = t1;
		mp[t2].w = mp[i].w ^ mp[j].w ^ odd;
	}
	else if (mp[t2].rk > mp[t1].rk)
	{
		mp[t1].prt = t2;
		mp[t1].w = mp[i].w ^ mp[j].w ^ odd;
	}
	else
	{
		mp[t1].prt = t2;
		mp[t1].w = mp[i].w ^ mp[j].w ^ odd;
		mp[t2].rk++;
	}
}

int main()
{
	int len, num;
	scanf("%d%d", &len, &num);
	int b, e;
	char str[5];
	int cnt = 0;
	while (num--)
	{
		scanf("%d%d%s", &b, &e, str);
		--b;
		mp.insert(make_pair(b, vl(b, 0, 0)));
		mp.insert(make_pair(e, vl(e, 0, 0)));
		int odd = (*str == 'o') ? 1 : 0;
		if (myfind(b) == myfind(e))
		{
			if ((mp[b].w ^ mp[e].w) != odd)
				break;
		}
		else
			myunion(b, e, odd);
		cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}
