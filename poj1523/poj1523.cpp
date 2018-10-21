#include<iostream>
#include<vector>
#include<algorithm>
#define MAX_NUM 1000
using namespace std;

int dfs(vector<vector<int> > &graph, vector<int> &res, vector<int> &dfn, int &r, int v = 1)//visit v
{
    dfn[v] = r;
    int minr = r;
    for(vector<int>::iterator p = graph[v].begin(); p != graph[v].end(); ++p)
    {
        if(!dfn[*p])//not visit then visit
        {
            int pmin = dfs(graph, res, dfn, ++r, *p);
            if(pmin == dfn[v]) res[v]++;
            minr = min(minr, pmin);
        }
        else
            minr = min(minr, dfn[*p]);
    }
    if(v == 1) res[v] -= 1;
    return minr;
}

int main()
{
    int x, y;
    int times = 1;
    while(1)
    {
        vector<vector<int> > graph(MAX_NUM+1);
        int num = 0;
        while(cin >> x && x && cin >> y && y)
        {
            graph[x].push_back(y);
            graph[y].push_back(x);
            ++num;
        }//construct graph
        if(num == 0)break;
        vector<int> dfn(MAX_NUM+1, 0);
        int r = 1;
        vector<int> res(MAX_NUM+1, 1);
        dfs(graph, res, dfn, r);
        cout << "Network #" << times << endl;
        int cnt = 0;
        for(int i = 1; i < r+1; ++i)
        {
            if(res[i] > 1)
            {
                cout << "  SPF node " << i << " leaves "
                << res[i] << " subnets" << endl;
                cnt++;
            }
        }
        if(cnt == 0)
            cout << "  No SPF nodes" << endl;
        cout << "\n";
        ++times;
    }
    return 0;
}
