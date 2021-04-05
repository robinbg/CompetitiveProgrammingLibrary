#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f

typedef long long LL;

const int M=2010;
const int N=510;

struct edge
{
    int to;
    int next;
    int cap;
    int cost;
} e[11000];

int head[N],tot;
int d[N], pre[N], path[N];
bool vis[N];

void init()
{
    memset(head,-1,sizeof(head));
    tot = 0;
}

void addedge(int s, int t, int cap, int cost)
{
    e[tot].to=t;
    e[tot].cap=cap;
    e[tot].cost=cost;
    e[tot].next=head[s];
    head[s] = tot++;
    e[tot].to=s;
    e[tot].cap=0;
    e[tot].cost=-cost;
    e[tot].next=head[t];
    head[t] = tot++;
}

int spfa(int s, int t)
{
    memset(d,INF,sizeof(d));
    memset(pre,-1,sizeof(pre));
    memset(path,-1,sizeof(path));
    memset(vis,false,sizeof(vis));
    d[s] = 0;
    vis[s] = true;
    queue<int>q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; ~i; i = e[i].next)
        {
            int v = e[i].to;
            if (d[v] > d[u] + e[i].cost && e[i].cap > 0)
            {
                d[v] = d[u] + e[i].cost;
                pre[v] = u;
                path[v] = i;
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return pre[v] != -1;
}

int MinCostMaxFlow(int s, int t,int &cost)
{
    int flow;
    flow=cost=0;
    while (spfa(s, t))
    {
        int minn = INF;
        for (int i = t; i != s && ~i; i = pre[i])
            minn = min(minn, e[path[i]].cap);
        for (int i = t; i != s && ~i; i = pre[i])
        {
            e[path[i]].cap -= minn;
            e[path[i] ^ 1].cap += minn;
        }
        if (d[t] < 0)
            break;
        flow += minn;
        cost += minn * d[t];
    }
    return flow;
}

int main(void)
{
    int n,m;
    while (cin>>n>>m)
    {
        init();
        int s=0,t=n+1,cost;
        for (int i=1; i<=n; i++)
        {
            int a,b,c,d;
            cin>>a>>b>>c>>d;
            addedge(s,i,b,-a);
            addedge(i,t,d,c);
        }
        while (m--)
        {
            int u,v,k;
            cin>>u>>v>>k;
            addedge(u,v,INF,-k);
            addedge(v,u,INF,-k);
        }
        MinCostMaxFlow(s,t,cost);
        cout<<cost<<endl;
    }
    return 0;
}
