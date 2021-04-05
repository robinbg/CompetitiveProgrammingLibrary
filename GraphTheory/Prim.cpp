#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>//pb_ds may be unavailable in some contests
using namespace std;
vector<int> v[1000],w[1000];
struct node
{
	int v;
	int dist;
	bool operator<(const node & b)const
	{
		return dist>b.dist;
	}
};
int dist[1000];
bool flag[1000];
using Heap = priority_queue<node>;

void PrimWithHeap()
{
	memset(flag,0,sizeof(flag));
	memset(dist,0x3f3f3f3f,sizeof(dist)); 
	dist[0]=0;
    Heap q;
	int sum=0;
	q.push((node){0,dist[0]});
	while(!q.empty())
	{
		int u=q.top().v;
		q.pop();
		if(flag[u])continue;
		flag[u]=1;
		sum+=dist[u];
		for(int i=0;i<v[u].size();i++)
		{
			int v_=v[u][i];
			if(w[u][i]>=dist[v_])continue;
			dist[v_]=w[u][i];
			q.push((node){v_,dist[v_]});
			
		}
	}
	printf("%d",sum);
}

using ParingHeap = __gnu_pbds::priority_queue<node, less<node>, __gnu_pbds::pairing_heap_tag>;
using Iterator = PairingHeap::iterator;

void PrimWithPairingHeap()
{
	memset(flag,0,sizeof(flag));
	memset(dist,0x3f3f3f3f,sizeof(dist)); 
	dist[0]=0;
    PairingHeap q;
    Iterator pos[1000];
	int sum=0;
	for(int i=0;i<n;i++)
	pos[i] = q.push((node){i, dist[i]});
	while(!q.empty())
	{
		int u=q.top().v;
		q.pop();
		flag[i] = 1;
		sum+=dist[u];
		for(int i=0;i<v[u].size();i++)
		{
			int v_=v[u][i];
			if(w[u][i]>=dist[v_])continue;
			dist[v_]=w[u][i];
			q.modify(pos[v_], (node){v_, dist[v_]});
		}
	}
	printf("%d",sum);
}
