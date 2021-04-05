#include<bits/stdc++.h>
using namespace std;
struct edge
{
	int u,v,w;
	bool operator<(const edge &b)const
	{
		return w<b.w;// 
	}
}edges[10000];//存边
//并查集 
int fa[1000], rk[1000];
int n,m;//顶点个数和边数 
int find(int x)
{
	return (fa[x]==x)? x : fa[x] = find(fa[x]);
} 
void merge(int x,int y)
{
	x = find(x), y = find(y);
	if(x==y)return;
	if(rk[x]>rk[y])swap(x,y);
	fa[x] = y;
	rk[y] += rk[x];
}
void Kruskal()
{
	sort(edges,edges+m);
	int k=0;
	int sum=0;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=0;i<m;i++)
	{
		int u=edges[i].u,v=edges[i].v,w=edges[i].w;
		int fu=find(u),fv=find(v);
		if(fu!=fv)
		{
			sum+=w;
			merge(fu,fv);
			k++;
			if(k==n-1)break; 
		}
	}
	printf("%d",sum);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].w);
	}
	Kruskal();
}
