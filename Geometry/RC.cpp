//凸包直径
void RC()
{
	q[top+1]=q[1];
	int now=2;
	for(int i=1;i<=top;i++)
	{
		while((q[i+1]-q[i])*(q[now]-q[i])<(q[i+1]-q[i])*(q[now+1]-q[i]))
		{
			now++;
			if(now==top+1)now=1;
		}
		ans=max(ans,dis2(q[now]-q[i]));
	}
}
