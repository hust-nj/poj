#include<cstdio>
using namespace std;

struct node{
    int rank;
    int parent;
    int weight;
};

node vtx[50001];

int myfind(int i)
{
    if(vtx[i].parent == i)
        return i;
    else
    {
        int p = vtx[i].parent;
        int leader = myfind(p);
        vtx[i].weight = (vtx[p].weight + vtx[i].weight) % 3;//update the weight to parent
        vtx[i].parent = leader;
        return leader;
    }
}

void myunion(int i, int j, int w)//w: i -> j
{
    int l1 = myfind(i);
    int l2 = myfind(j);
    if(vtx[l1].rank > vtx[l2].rank)
    {
        vtx[l2].parent = l1;
        vtx[l2].weight = (vtx[i].weight - w - vtx[j].weight + 6) % 3;
    }
    else if(vtx[l1].rank < vtx[l2].rank)
    {
        vtx[l1].parent = l2;
        vtx[l1].weight = (w + vtx[j].weight - vtx[i].weight + 3) % 3;
    }
    else
    {
        vtx[l1].parent = l2;
        vtx[l2].rank++;
        vtx[l1].weight = (w + vtx[j].weight - vtx[i].weight + 3) % 3;
    }
}

int main()
{
    int N, K;
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= N; ++i)
    {
        vtx[i].parent = i;
        vtx[i].rank = vtx[i].weight = 0;
    }

    int cnt = 0;
    for(int i = 0; i < K; ++i)
    {
        int d, x, y;
        scanf("%d%d%d", &d, &x, &y);
        if(x > N || y > N || d == 2 && x == y)
        	cnt++;
        else if(myfind(x) == myfind(y))// x和y有关系
        {
            if((vtx[x].weight - vtx[y].weight + 3) % 3 != d - 1)
                cnt++;
        }
        else
        {
            myunion(x, y, d-1);
        }
    }
    printf("%d\n", cnt);
    return 0;
}
