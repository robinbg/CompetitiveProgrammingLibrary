void solve()
{
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(l<q[i].l)del(a[l]),l++;
		while(r>q[i].r)del(a[r]),r--;
		while(l>q[i].l)l--,add(a[l]);
		while(r<q[i].r)r++,add(a[r]);
		ans[q[i].id]=query(q[i].a,q[i].b);
	}
}
int main()
{
	n=read();m=read();blo=sqrt(n/2);
	cnt=n/blo+n%blo!=0;
	for(int i=1;i<=n;i++)bl[i]=(i-1)/blo+1;
	for(int i=1;i<=n;i++)
	{
		r[bl[i]]=i;
		if(!l[bl[i]])l[bl[i]]=i;
	}
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)
	{
		q[i].l=read();q[i].r=read();
		q[i].a=read();q[i].b=read();
		q[i].id=i;
	}
	sort(q+1,q+m+1);
	solve();
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
	return 0;
}
