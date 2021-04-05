
vector<int> u,v,c,_next;// Forward Star
int last[100];
inline int addedge(int _u,int _v,int _c)
{
    u.push_back(_u);
    v.push_back(_v);
    c.push_back(_c);
    _next.push_back(last[_u]);
    last[_u]=u.size()-1;
    u.push_back(_v);
    v.push_back(_u);
    c.push_back(0);
    _next.push_back(last[_v]);
    last[_v]=u.size()-1;
}
int dist[100];
int s,t;//source and sink
bool BFS()
{
    memset(dist,-1,sizeof(dist));
    queue<int> Q;
    Q.push(s);
    dist[s]=0;
    while(!Q.empty())
    {
        int f=Q.front();
        Q.pop();
        for(int i=last[f];i!=-1;i=_next[i])
        if(dist[v[i]]==-1 && c[i])
        {
            dist[v[i]]=dist[f]+1;
            Q.push(v[i]);
        }
    }
    return dist[t]!=-1;
}
int DFS(int f,int flow)
{
    if(f==t)return flow;
    int rest=flow;
    for(int i=last[f];i!=-1 && rest;i=_next[i])
    if(dist[v[i]]==dist[f]+1)
    {
        int delta=DFS(v[i],min(rest,c[i]));
        c[i]-=delta;
        c[i^1]+=delta;
        rest-=delta;
    }
    if(rest)dist[f]=-1;
    return  flow-rest;
}
int Dinic()
{
    int maxflow=0;
    while(BFS()) maxflow+=DFS(s,0x7fffffff);
    return maxflow;
}
