//强连通分量
void tarjan(int x)
{
	low[x]=dfn[x]=++ind;
	q[++top]=x;inq[x]=1;
	for(int i=last[x];i;i=e[i].next)
		if(!dfn[e[i].to])
		{
			tarjan(e[i].to);
			low[x]=min(low[x],low[e[i].to]);
		}
		else if(inq[e[i].to])
			low[x]=min(low[x],dfn[e[i].to]);
	if(low[x]==dfn[x])
	{
		scc++;
		int now=0;
		while(x!=now)
		{
			now=q[top--];inq[now]=0;
			bl[now]=scc;
		}
	}
}

//边双连通分量
void tarjan(int x,int fa)
{
	low[x]=dfn[x]=++ind;
	q[++top]=x;inq[x]=1;
	for(int i=last[x];i;i=e[i].next)
		if(i!=(fa^1))
		{
			if(!dfn[e[i].to])
			{
				tarjan(e[i].to,i);
				low[x]=min(low[x],low[e[i].to]);
			}
			else if(inq[e[i].to])
				low[x]=min(low[x],dfn[e[i].to]);
      /*
        dfn[e[i].to]>low[x], 则i为割边
        dfn[e[i].to]==low[x], x为割点
        */
		}
	if(low[x]==dfn[x])
	{
		scc++;
		int now=0;
		while(x!=now)
		{
			now=q[top--];inq[now]=0;
			bl[now]=scc;
		}
	}
}

//点双连通分量
int pre[maxn],iscut[maxn],bccno[maxn], dfs_clock, bcc_cnt;
vector<int> G[maxn], bcc[maxn];
stack<Edge> S;

int dfs(int u,int fa) {
  int lowu = pre[u] = ++dfs_clock;
  int child = 0;
  for(int i=0;i<G[u].size();i++)
  {
    int v = G[u][i];
    Edge e = (Edge){u,v};
    if(!pre[v]){
      S.push(e);
      child++;
      int lowv = dfs(v, u);
      lowu = min(lowu, lowv);
      if(lowv >= pre[u]){
        iscut[u] = true;
        bcc_cnt ++;
        bcc[bcc_cnt].clear();
        for(;;){
          Edge x = S.top();S.pop();
          if(bccno[x.u]!=bcc_cnt){bcc[bcc_cnt].push_back(x.u);bccno[x.u] = bcc_cnt;}
          if(x.v == v && x.u == u)break;
        }
      }
    }
    else if(pre[v]<pre[u] && v!=fa){
      S.push(e);
      lowu = min(lowu, pre[v]);
    }
  }
  if(fa<0 && child==1)iscut[u]=0;
  return lowu;
}
