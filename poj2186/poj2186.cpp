#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

int dfs(int u, int &r, int &region, vector<vector<int> > &vtx, vector<int> &dfn, vector<int> &belong, stack<int> &stk, vector<bool> &stk_flag);

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int> > vtx(n+1);
    for(int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        vtx[a].push_back(b);
    }
    vector<int> dfn(n+1, 0);
    vector<int> belong(n+1, 0);
    stack<int> stk;
    int r = 0;
    int region = 1;
    vector<bool> stk_flag(n+1, false);
    for(int i = 1; i <= n; ++i)
    {
        vtx[0].push_back(i);
    }
    dfs(0, r, region, vtx, dfn, belong, stk, stk_flag);
    vector<int> outedge(belong[0], 0);
    vector<int> rgn(belong[0], 0);
    for(int i = 1; i <= n; ++i)
    {
        for(vector<int>::iterator p = vtx[i].begin(); p != vtx[i].end(); ++p)
        {
            if(belong[*p] != belong[i])
                outedge[belong[i]]++;
        }
        rgn[belong[i]]++;
    }
    int cnt = 0;
    int record;
    for(int i = 1; i < belong[0]; ++i)
    {
        if(outedge[i] == 0)
        {
            record = i;
            cnt ++;
        }
        if(cnt >= 2)
        {
            cout << 0 << endl;
            return 0;
        }
    }
    if(cnt == 0)
        cout << 0 << endl;
    else
        cout << rgn[record] << endl;
    return 0;
}

int dfs(int u, int &r, int &region, vector<vector<int> > &vtx, vector<int> &dfn, vector<int> &belong, stack<int> &stk, vector<bool> &stk_flag)
{
    dfn[u] = r;
    stk.push(u);
    stk_flag[u] = true;
    int minu = dfn[u];
    for(vector<int>::iterator p = vtx[u].begin(); p != vtx[u].end(); ++p)
    {
        int v = *p;
        if(dfn[v] == 0)//not visit
            minu = min(minu, dfs(v, ++r, region, vtx, dfn, belong, stk, stk_flag));
        else if(stk_flag[v] == true)
            minu = min(minu, dfn[v]);
    }

    if(minu == dfn[u])
    {
        int v;
        do
        {
            v = stk.top();
            stk.pop();
            stk_flag[v] = false;
            belong[v] = region;
        }while(v != u);
        ++region;
    }
    return minu;
}
