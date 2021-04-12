struct P{double x,y;}p[2005],s[2005];
double dis(P a,P b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
P operator-(P a,P b)
{
	P t;t.x=a.x-b.x;t.y=a.y-b.y;return t;
}
double operator*(P a,P b)
{
	return a.x*b.y-a.y*b.x;
}
bool operator<(P a,P b)
{
	double t=(a-p[1])*(b-p[1]);
	if(t==0)return dis(a,p[1])<dis(b,p[1]);
	return t<0;
}
void graham()
{
	int k=1;
	for(int i=2;i<=n;i++)
		if(p[k].y>p[i].y||(p[k].y==p[i].y&&p[k].x>p[i].x))
			k=i;
	swap(p[1],p[k]);
	sort(p+2,p+n+1);
	s[++top]=p[1];s[++top]=p[2];
	for(int i=3;i<=n;i++)
	{
		while(top>1&&(p[i]-s[top-1])*(s[top]-s[top-1])<=0)
			top--;
		s[++top]=p[i];
	}
}
